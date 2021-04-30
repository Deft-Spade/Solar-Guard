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
    constexpr const bn::music_item menu_theme(0);
    constexpr const bn::music_item title_theme(1);

    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    void text_scene_1()
    {
        menu_theme.play();

        bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Menu Theme", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Title Theme", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void text_scene_2()
    {
        title_theme.play();

        bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Playing Title Theme", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START to Switch to Menu Theme", text_sprites);

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
        text_scene_1();
        bn::core::update();

        text_scene_2();
        bn::core::update();
    }
}
