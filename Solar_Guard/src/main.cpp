#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_assert.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_items_spr_logo.h"

#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_title_screen.h"
#include "bn_regular_bg_items_bg_main_menu.h"

#include "fixed_8x16_sprite_font.h"
#include "variable_8x16_sprite_font.h"

#include "splash_screens.h"
#include "menus.h"
#include "music.h"
#include "information.h"

#include "briefings.h"
#include "mission_1.h"
#include "mission_2.h"
#include "mission_3.h"
#include "mission_4.h"
#include "mission_5.h"

namespace
{
    // An important int that determines which scene the game is in at any given time.
    int current_scene = 0;
}

void title_screen()
{
    // Title screen background.
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_title_screen.create_bg(0, 0);

    // Play the title screen music.
    bgm_theme_title.play();

    // Draw the text.
    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
    text_generator.set_center_alignment();
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(0, 55, "Press START", text_sprites);

    // Wait for player to press start.
    while(! bn::keypad::start_pressed())
    {
        bn::core::update();
    }
}


int main()
{
    bn::core::init();

    // Splash screens.
    splash_screen_developer();
    bn::core::update();
    splash_screen_engine();
    bn::core::update();
    splash_screen_event();
    bn::core::update();

    // Initial title screen.
    title_screen();
    bn::core::update();

    while(true)
    {
        current_scene = main_menu();
        bn::core::update();

        switch (current_scene) {
            case 0:
                title_screen();
                bn::core::update();
                break;

            case 11:
                briefing_1();
                bn::core::update();

                mission_1();
                bn::core::update();
                break;

            case 12:
                briefing_2();
                bn::core::update();

                mission_2();
                bn::core::update();
                break;

            case 13:
                briefing_3();
                bn::core::update();

                mission_3();
                bn::core::update();
                break;

            case 14:
                briefing_4();
                bn::core::update();

                mission_4();
                bn::core::update();
                break;

            case 15:
                briefing_5();
                bn::core::update();

                mission_5();
                bn::core::update();
                break;

            case 2:
                scene_music_playback();
                bn::core::update();
                break;

            case 31:
                scene_controls();
                bn::core::update();
                break;

            case 32:
                scene_credits();
                bn::core::update();
                break;

            case 33:
                scene_oga_credits();
                bn::core::update();
                break;

            default:
                BN_ERROR("Invalid scene number: ", current_scene);
                break;
        }
    }
}
