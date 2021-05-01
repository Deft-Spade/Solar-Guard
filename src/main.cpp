#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "fixed_8x8_sprite_font.h"
#include "fixed_8x16_sprite_font.h"
#include "variable_8x8_sprite_font.h"
#include "variable_8x16_sprite_font.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

namespace
{
    constexpr const bn::music_item solar_conflict(0);
    constexpr const bn::music_item solar_patrol(1);
    constexpr const bn::music_item solar_somber(2);
    constexpr const bn::music_item theme_menu(3);
    constexpr const bn::music_item theme_title(4);
    constexpr const bn::music_item theme_upbeat(5);

    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);

    void scene_1()
    {
        theme_title.play();

        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Title Music", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Menu Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_2()
    {
        theme_menu.play();

        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Menu Music", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Upbeat Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_3()
    {
        theme_upbeat.play();

        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Upbeat Music", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Patrol Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_4()
    {
        solar_patrol.play();

        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Patrol Music", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Conflict Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_5()
    {
        solar_conflict.play();

        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Conflict Music", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Somber Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_6()
    {
        solar_somber.play();

        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Somber Music", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Title Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }
}

int main()
{
    bn::core::init();

    while(true)
    {
        scene_1();
        bn::core::update();

        scene_2();
        bn::core::update();

        scene_3();
        bn::core::update();

        scene_4();
        bn::core::update();

        scene_5();
        bn::core::update();

        scene_6();
        bn::core::update();
    }
}
