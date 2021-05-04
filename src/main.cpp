#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_earth_and_sun.h"

#include "fixed_8x8_sprite_font.h"
#include "fixed_8x16_sprite_font.h"
#include "variable_8x8_sprite_font.h"
#include "variable_8x16_sprite_font.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

namespace
{
    constexpr const bn::music_item bgm_solar_conflict(0);
    constexpr const bn::music_item bgm_solar_patrol(1);
    constexpr const bn::music_item bgm_solar_somber(2);
    constexpr const bn::music_item bgm_tactical(3);
    constexpr const bn::music_item bgm_theme_menu(4);
    constexpr const bn::music_item bgm_theme_title(5);
    constexpr const bn::music_item bgm_theme_upbeat(6);

    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);

    void scene_1()
    {
        bgm_theme_title.play();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -6, "Currently Playing", text_sprites);
        text_generator.generate(0, 6, "Title Music", text_sprites);
        text_generator.generate(0, text_y_limit -10, "Press START to Switch to", text_sprites);
        text_generator.generate(0, text_y_limit, "Menu Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_2()
    {
        bgm_theme_menu.play();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -6, "Currently Playing", text_sprites);
        text_generator.generate(0, 6, "Menu Music", text_sprites);
        text_generator.generate(0, text_y_limit -10, "Press START to Switch to", text_sprites);
        text_generator.generate(0, text_y_limit, "Upbeat Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_3()
    {
        bgm_theme_upbeat.play();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -6, "Currently Playing", text_sprites);
        text_generator.generate(0, 6, "Upbeat Music", text_sprites);
        text_generator.generate(0, text_y_limit -10, "Press START to Switch to", text_sprites);
        text_generator.generate(0, text_y_limit, "Tactical Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_4()
    {
        bgm_tactical.play();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -6, "Currently Playing", text_sprites);
        text_generator.generate(0, 6, "Tactical Music", text_sprites);
        text_generator.generate(0, text_y_limit -10, "Press START to Switch to", text_sprites);
        text_generator.generate(0, text_y_limit, "Patrol Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_5()
    {
        bgm_solar_patrol.play();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -6, "Currently Playing", text_sprites);
        text_generator.generate(0, 6, "Patrol Music", text_sprites);
        text_generator.generate(0, text_y_limit -10, "Press START to Switch to", text_sprites);
        text_generator.generate(0, text_y_limit, "Conflict Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_6()
    {
        bgm_solar_conflict.play();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -6, "Currently Playing", text_sprites);
        text_generator.generate(0, 6, "Conflict Music", text_sprites);
        text_generator.generate(0, text_y_limit -10, "Press START to Switch to", text_sprites);
        text_generator.generate(0, text_y_limit, "Somber Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void scene_7()
    {
        bgm_solar_somber.play();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -6, "Currently Playing", text_sprites);
        text_generator.generate(0, 6, "Somber Music", text_sprites);
        text_generator.generate(0, text_y_limit -10, "Press START to Switch to", text_sprites);
        text_generator.generate(0, text_y_limit, "Title Music", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }
}

int main()
{
    bn::core::init();

    text_generator.set_center_alignment();

    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_earth_and_sun.create_bg(0, 15);

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

        scene_7();
        bn::core::update();
    }
}
