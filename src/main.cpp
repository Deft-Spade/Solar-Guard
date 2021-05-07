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
#include "bn_regular_bg_items_bg_earth_horizon.h"
#include "bn_regular_bg_items_bg_seamless_stars.h"

#include "fixed_8x16_sprite_font.h"
#include "variable_8x16_sprite_font.h"
#include "bn_sprite_items_menu_arrow.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

#include "music.h"

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

    int current_selection = 1;
    int max_items = 2;
}

void primary_menu()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_earth_and_sun.create_bg(0, 15);
    bn::sprite_ptr menu_selector = bn::sprite_items::menu_arrow.create_sprite(-(bn::display::width() / 2) + 10, -10);

    bgm_theme_title.play();

    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
    text_generator.set_center_alignment();
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(0, -text_y_limit, "Solar Guard (Development Version)", text_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-(bn::display::width() / 2) + 20, - 10, "Gameplay Testing", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 10, "Music Playback", text_sprites);

    while(! bn::keypad::start_pressed())
    {
        if(bn::keypad::down_held() && current_selection < max_items)
        {
            current_selection++;
        }
        else if(bn::keypad::up_held() && current_selection > 1)
        {
            current_selection--;
        }

        menu_selector.set_y(-10 + (current_selection - 1) * 20);

        bn::core::update();
    }
}


int main()
{
    bn::core::init();

    while(true)
    {
        primary_menu();
        bn::core::update();

        switch (current_selection) {
            case 1:
                // Do nothing.
            break;

            case 2:
                music_scene_1();
                bn::core::update();

                music_scene_2();
                bn::core::update();

                music_scene_3();
                bn::core::update();

                music_scene_4();
                bn::core::update();

                music_scene_5();
                bn::core::update();

                music_scene_6();
                bn::core::update();

                music_scene_7();
                bn::core::update();
            break;

            default:
                // Do nothing.
            break;
        }
    }
}
