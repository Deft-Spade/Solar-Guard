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
#include "bn_sprite_items_menu_arrow.h"

#include "splash_screens.h"
#include "music.h"

#include "mission_1.h"
#include "mission_2.h"
#include "mission_3.h"
#include "mission_4.h"
#include "mission_5.h"

#include "briefings.h"

namespace
{
    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    // An important int that determines which scene the game is in at any given time.
    int current_scene = 0;

    // Menu selection variables.
    int current_selection = 1;
    const int max_items = 3;
    const int cs_orign_y = -10 * (max_items / 2);
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

void draw_mainmenu_text(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites)
{
    text_generator.set_left_alignment();
    text_generator.generate(-(bn::display::width() / 2) + 20, - 10, "Mission Select", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 10, "Music Playback", text_sprites);
}

int submenu_missions(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites, bn::sprite_ptr &menu_selector)
{
    int mission_selection = 1;
    int max_missions = 5;
    int ms_orign_y = -20 * (max_missions / 2);

    // Draw the sub-menu text.
    text_sprites.clear();
    text_generator.set_center_alignment();
    text_generator.generate(0, -text_y_limit, "Mission Select", text_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-(bn::display::width() / 2) + 20, - 40, "ORBIT TIDYING: Destroy Space Junk", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, - 20, "CLEAR THE WAY: Escort Transport", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 0, "SWIFT DEFENSE: Repel Pirates", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 20, "COUNTER PROBE: Recon Pirate Base", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 40, "DISTANT REACH: Rescue Operation", text_sprites);

    // Extra update to process another frame to set A to not pressed
    // to avoid mission selection activation in the same frame as the
    // sub-menu selection activation from the main menu.
    bn::core::update();

    // Menu operation loop (exits upon pressing A, relies on
    // current_selection being set correctly by indicator position).
    while(true)
    {
        // Adjust selection in response to user input.
        if(bn::keypad::down_pressed() && mission_selection < max_missions)
        {
            mission_selection++;
        }

        if(bn::keypad::up_pressed() && mission_selection > 1)
        {
            mission_selection--;
        }

        // Set the menu selection arrow sprite to the selection's position.
        menu_selector.set_y(ms_orign_y + (mission_selection - 1) * 20);

        // Return to the title screen if B is pressed.
        if (bn::keypad::b_pressed())
        {
            // Re-draw the main menu text.
            text_sprites.clear();
            draw_mainmenu_text(text_generator, text_sprites);

            // Indicate sub-menu exit with no selection made.
            return -1;
        }

        // Go to selected mission.
        if (bn::keypad::a_pressed())
        {
            // Return which mission was selected.
            return mission_selection;
        }

        bn::core::update();
    }
}

void main_menu()
{
    // Make sure that the current selection variable is equal to 1 if it's out of bounds.
    if (current_selection < 1 || current_selection > max_items) current_selection = 1;

    // Set a background for the main menu.
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_main_menu.create_bg(0, 15);

    // Create the menu selector arrow sprite.
    bn::sprite_ptr menu_selector = bn::sprite_items::menu_arrow.create_sprite(-(bn::display::width() / 2) + 10, cs_orign_y);

    // Create the logo sprite.
    bn::sprite_ptr sprite_logo = bn::sprite_items::spr_logo.create_sprite(0,-65);

    // Play the main menu music.
    bgm_theme_menu.play();

    // Draw the main menu text.
    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 64> text_sprites;
    draw_mainmenu_text(text_generator, text_sprites);

    // Menu operation loop (exits upon pressing A, relies on current_selection being set correctly by indicator position).
    while(true)
    {
        // Return to the title screen if B is pressed.
        if (bn::keypad::b_pressed())
        {
            // Set current scene variable to zero to indicate backing out to the title screen.
            current_scene = 0;

            // Return out of the main menu's own loop.
            return;
        }

        // Adjust selection in response to user input.
        if(bn::keypad::down_pressed() && current_selection < max_items)
        {
            current_selection++;
        }

        if(bn::keypad::up_pressed() && current_selection > 1)
        {
            current_selection--;
        }

        // Set the menu selection arrow sprite to the selection's position.
        menu_selector.set_y(cs_orign_y + (current_selection - 1) * 20);

        // Make selection if A is pressed.
        if (bn::keypad::a_pressed())
        {            
            int submenu_selection;

            switch (current_selection)
            {
                case 1:    
                    sprite_logo.set_visible(false);
                    submenu_selection = submenu_missions(text_generator, text_sprites, menu_selector);
                    sprite_logo.set_visible(true);

                    if (submenu_selection != -1)
                    {
                        // Set scene variable to relevant mission.
                        current_scene = 10 + submenu_selection;

                        // Return out of the main menu's own loop.
                        return;
                    }
                    break;

                case 2:
                    // Instruct game to go to music playback scene.
                    current_scene = 2;

                    // Return out of the main menu's own loop.
                    return;
                    break;

                default:
                    BN_ERROR("Invalid menu selection number: ", current_selection);
                    break;
            }
        }

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
        main_menu();
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

            default:
                BN_ERROR("Invalid scene number: ", current_scene);
                break;
        }
    }
}
