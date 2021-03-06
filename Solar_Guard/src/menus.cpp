/* Solar Guard by Deft Spade
 * Using Butano by GValiente
 * Made for GBA JAM 2021
 * Source Code and Assets Licensed Under GPL-3.0
 * 
 * This source code has known issues. No promises are made as to the
 * quality/reliability of anything in this source code. Such issues
 * include and are not necessarily limited to code repetition, magic
 * numbers, undocumented conventions for what certain variable values
 * mean, etc. Lots of refactoring and commenting/documenting is needed
 * to bring the overall code quality up-to-scratch, after all, this was
 * developed as fast as possible within 3 months for a game jam. Also,
 * there are no guarantees about how much I'll further develop this
 * game after GBA JAM 2021. This means I may never get around to fully
 * fixing/completing everything.
 */

/*
    Solar Guard
    Copyright (C) 2021  Deft Spade

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_assert.h"

#include "menus.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_items_spr_logo.h"

#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_title_screen.h"
#include "bn_regular_bg_items_bg_main_menu.h"

#include "font_menu.h"
#include "font_menu.h"
#include "bn_sprite_items_menu_arrow.h"

#include "music.h"
#include "bn_sound_items.h"

namespace
{
    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    // Menu selection variables.
    int current_selection = 1;
    const int max_items = 3;
    const int cs_orign_y = -20 * (max_items / 2);
    int current_scene = 0;
}

void draw_mainmenu_text(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites)
{
    text_generator.set_left_alignment();
    text_generator.generate(-(bn::display::width() / 2) + 20, - 20, "Mission Select", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, 0, "Music Playback", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 20, "Information", text_sprites);
}

// The submenus contain duplicate code, the submenu functions should be refactored into one function with more arguments at some point.

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

    // Play select sound since submenu was selected from main menu.
    bn::sound_items::sfx_menu_select.play();

    // Menu operation loop (exits upon pressing A, relies on
    // current_selection being set correctly by indicator position).
    while(true)
    {
        // Adjust selection in response to user input.
        if(bn::keypad::down_pressed() && mission_selection < max_missions)
        {
            mission_selection++;
            bn::sound_items::sfx_menu_move.play();
        }

        if(bn::keypad::up_pressed() && mission_selection > 1)
        {
            mission_selection--;
            bn::sound_items::sfx_menu_move.play();
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

int submenu_information(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites, bn::sprite_ptr &menu_selector)
{
    int option_selection = 1;
    int max_options = 4;
    int ms_orign_y = -30;

    // Draw the sub-menu text.
    text_sprites.clear();
    text_generator.set_center_alignment();
    text_generator.generate(0, -text_y_limit, "Information", text_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-(bn::display::width() / 2) + 20, - 30, "Controls", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, - 10, "Known Issues", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 10, "Credits", text_sprites);
    text_generator.generate(-(bn::display::width() / 2) + 20, + 30, "Art Acknowledgments", text_sprites);

    // Extra update to process another frame to set A to not pressed
    // to avoid mission selection activation in the same frame as the
    // sub-menu selection activation from the main menu.
    bn::core::update();

    // Play select sound since submenu was selected from main menu.
    bn::sound_items::sfx_menu_select.play();

    // Menu operation loop (exits upon pressing A, relies on
    // current_selection being set correctly by indicator position).
    while(true)
    {
        // Adjust selection in response to user input.
        if(bn::keypad::down_pressed() && option_selection < max_options)
        {
            option_selection++;
            bn::sound_items::sfx_menu_move.play();
        }

        if(bn::keypad::up_pressed() && option_selection > 1)
        {
            option_selection--;
            bn::sound_items::sfx_menu_move.play();
        }

        // Set the menu selection arrow sprite to the selection's position.
        menu_selector.set_y(ms_orign_y + (option_selection - 1) * 20);

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
            return option_selection;
        }

        bn::core::update();
    }
}

int main_menu()
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
    bn::sprite_text_generator text_generator(font_menu);
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
            return current_scene;
        }

        // Adjust selection in response to user input.
        if(bn::keypad::down_pressed() && current_selection < max_items)
        {
            current_selection++;
            bn::sound_items::sfx_menu_move.play();
        }

        if(bn::keypad::up_pressed() && current_selection > 1)
        {
            current_selection--;
            bn::sound_items::sfx_menu_move.play();
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
                        return current_scene;
                    }
                    else
                    {
                        // Play menu back sound since user has backed out of submenu.
                        bn::sound_items::sfx_menu_back.play();
                    }
                    break;

                case 2:
                    // Instruct game to go to music playback scene.
                    current_scene = 2;

                    // Return out of the main menu's own loop.
                    return current_scene;

                case 3:
                    sprite_logo.set_visible(false);
                    submenu_selection = submenu_information(text_generator, text_sprites, menu_selector);
                    sprite_logo.set_visible(true);

                    if (submenu_selection != -1)
                    {
                        // Set scene variable to relevant option.
                        current_scene = 30 + submenu_selection;

                        // Return out of the main menu's own loop.
                        return current_scene;
                    }
                    else
                    {
                        // Play menu back sound since user has backed out of submenu.
                        bn::sound_items::sfx_menu_back.play();
                    }
                    break;

                default:
                    BN_ERROR("Invalid menu selection number: ", current_selection);
                    break;
            }
        }

        bn::core::update();
    }
}
