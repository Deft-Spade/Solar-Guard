/* Solar Guard by Deft Spade
 * Using Butano by GValiente
 * Made for GBA JAM 2021
 * Source Code and Assets Licensed Under GPL-3.0
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

#include "ship_select.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_string.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_logo_green.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_items_bg_information.h"
#include "bn_regular_bg_items_bg_ship_select_1.h"
#include "bn_regular_bg_items_bg_ship_select_2.h"
#include "bn_regular_bg_items_bg_ship_select_3.h"
#include "bn_regular_bg_items_bg_ship_select_4.h"
#include "bn_regular_bg_items_bg_ship_select_5.h"
#include "bn_regular_bg_items_bg_ship_select_6.h"
#include "bn_regular_bg_items_bg_ship_select_7.h"
#include "bn_regular_bg_items_bg_ship_select_8.h"

#include "bn_sprite_text_generator.h"
#include "font_menu.h"
#include "font_menu.h"
#include "font_hud.h"

#include "bn_music_item.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"
#include "music.h"
#include "bn_sound_items.h"

namespace
{
    constexpr const bn::fixed screen_y_limit = (bn::display::height() / 2);
}

int loop_ship_select(int current_ship)
{
    // Extra update to process another frame to set A to not pressed
    // to avoid ship selection activation in the same frame as the
    // progression from the briefing to the ship select screen.
    bn::core::update();

    while (true)
    {
        if (bn::keypad::right_pressed())
        {
            return -1;
        }

        if (bn::keypad::left_pressed())
        {
            return -2;
        }

        if (bn::keypad::a_pressed())
        {
            return current_ship;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int scene_ship_select_1()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_1.create_bg(0, 0);
    return loop_ship_select(1);
}

int scene_ship_select_2()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_2.create_bg(0, 0);
    return loop_ship_select(2);
}

int scene_ship_select_3()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_3.create_bg(0, 0);
    return loop_ship_select(3);
}

int scene_ship_select_4()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_4.create_bg(0, 0);
    return loop_ship_select(4);
}

int scene_ship_select_5()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_5.create_bg(0, 0);
    return loop_ship_select(5);
}

int scene_ship_select_6()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_6.create_bg(0, 0);
    return loop_ship_select(6);
}

int scene_ship_select_7()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_7.create_bg(0, 0);
    return loop_ship_select(7);
}

int scene_ship_select_8()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_ship_select_8.create_bg(0, 0);
    return loop_ship_select(8);
}

int ship_selection()
{
    // Menu operation variables.
    int current_page = 1;
    const int number_of_pages = 8;

    //bgm_theme_upbeat.play();

    while (true)
    {
        int user_input;

        // Switch page.
        switch (current_page)
        {
            case 1: user_input = scene_ship_select_1(); break;
            case 2: user_input = scene_ship_select_2(); break;
            case 3: user_input = scene_ship_select_3(); break;
            case 4: user_input = scene_ship_select_4(); break;
            case 5: user_input = scene_ship_select_5(); break;
            case 6: user_input = scene_ship_select_6(); break;
            case 7: user_input = scene_ship_select_7(); break;
            case 8: user_input = scene_ship_select_8(); break;
            default: BN_ERROR("CURRENT PAGE VALUE INVALID: " + bn::to_string<16>(current_page)); break;
        }

        if (user_input > -1)
        {
            return user_input;
        }
        else
        {
            if (user_input == -1)
            {
                if (current_page == number_of_pages)
                {
                    current_page = 1;
                }
                else
                {
                    current_page += 1;
                }
            }
            else
            {
                if (current_page == 1)
                {
                    current_page = number_of_pages;
                }
                else
                {
                    current_page -= 1;
                }
            }

            bn::sound_items::sfx_menu_move.play();
        }

        bn::core::update();
    }
}
