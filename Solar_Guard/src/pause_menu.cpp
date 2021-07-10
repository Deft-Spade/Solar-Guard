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

#include "pause_menu.h"

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

int pause_menu()
{
    int pause_selection = 1;
    int max_selections = 2;
    int ms_orign_y = -10 * (max_selections / 2);

    bn::sprite_ptr menu_selector = bn::sprite_items::menu_arrow.create_sprite(-30,0);

    bn::sprite_text_generator text_generator(font_menu);
    bn::vector<bn::sprite_ptr, 64> text_sprites;

    // Draw the sub-menu text.
    text_sprites.clear();
    text_generator.set_center_alignment();
    text_generator.generate(0, -50, "Paused", text_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-20, - 10, "Resume", text_sprites);
    text_generator.generate(-20, + 10, "Exit", text_sprites);

    // Extra update to process another frame to set A to not pressed.
    bn::core::update();

    // Menu operation loop (exits upon pressing A, relies on
    // current_selection being set correctly by indicator position).
    while(true)
    {
        // Adjust selection in response to user input.
        if(bn::keypad::down_pressed() && pause_selection < max_selections)
        {
            pause_selection++;
            bn::sound_items::sfx_menu_move.play();
        }

        if(bn::keypad::up_pressed() && pause_selection > 1)
        {
            pause_selection--;
            bn::sound_items::sfx_menu_move.play();
        }

        // Set the menu selection arrow sprite to the selection's position.
        menu_selector.set_y(ms_orign_y + (pause_selection - 1) * 20);

        // Choose user selection.
        if (bn::keypad::a_held())
        {
            // Wait until user no longer holding A to avoid firing laser
            // from the user pressing A to resume.
            while (bn::keypad::a_held()) { bn::core::update(); }

            // Return which mission was selected.
            return pause_selection;
        }

        bn::core::update();
    }
}
