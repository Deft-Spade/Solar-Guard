#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_title_screen.h"
#include "bn_regular_bg_items_bg_earth_and_sun.h"
#include "bn_regular_bg_items_bg_earth_horizon.h"

#include "fixed_8x16_sprite_font.h"
#include "variable_8x16_sprite_font.h"
#include "bn_sprite_items_menu_arrow.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

#include "gameplay_testing.h"
#include "music.h"

namespace
{
    constexpr const bn::music_item bgm_rescue(0);
    constexpr const bn::music_item bgm_solar_conflict(1);
    constexpr const bn::music_item bgm_solar_patrol(2);
    constexpr const bn::music_item bgm_solar_somber(3);
    constexpr const bn::music_item bgm_tactical(4);
    constexpr const bn::music_item bgm_theme_menu(5);
    constexpr const bn::music_item bgm_theme_title(6);
    constexpr const bn::music_item bgm_theme_upbeat(7);

    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    int current_selection = 1;
    int max_items = 2;
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

void primary_menu()
{
    // Make sure that the current selection variable is equal to 1 if it's out of bounds.
    if (current_selection < 1 || current_selection > max_items) current_selection = 1;

    // Set a background for the main menu.
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_earth_and_sun.create_bg(0, 15);

    // Create the menu selector arrow sprite.
    bn::sprite_ptr menu_selector = bn::sprite_items::menu_arrow.create_sprite(-(bn::display::width() / 2) + 10, -10);

    // Play the main menu music.
    bgm_theme_menu.play();

    // Draw the main menu text.
    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
    text_generator.set_center_alignment();
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(0, -text_y_limit, "Solar Guard (Development Version)", text_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-(bn::display::width() / 2) + 20, - 10, "Gameplay Testing", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 10, "Music Playback", text_sprites);

    // Menu operation loop (exits upon pressing A, relies on current_selection being set correctly by indicator position).
    while(! bn::keypad::a_pressed())
    {
        // Adjust selection in response to user input.
        if(bn::keypad::down_held() && current_selection < max_items)
        {
            current_selection++;
        }
        else if(bn::keypad::up_held() && current_selection > 1)
        {
            current_selection--;
        }

        // Set the menu selection arrow sprite to the selection's position.
        menu_selector.set_y(-10 + (current_selection - 1) * 20);

        // Return to the title screen if B is pressed.
        if (bn::keypad::b_pressed())
        {
            // Set current selection variable to zero to indicate backing out to the title screen.
            current_selection = 0;

            // Break out of the main menu's own loop.
            break;
        }

        bn::core::update();
    }
}


int main()
{
    bn::core::init();

    // Initial title screen.
    title_screen();
    bn::core::update();

    while(true)
    {
        primary_menu();
        bn::core::update();

        switch (current_selection) {
            case 0: // 0 is used to indicate backing out into the title screen.
                title_screen();
                bn::core::update();
            break;

            case 1:
                scene_gameplay_testing();
                bn::core::update();
            break;

            case 2:
                scene_music_playback();
                bn::core::update();
            break;

            default:
                // Do nothing.
            break;
        }
    }
}
