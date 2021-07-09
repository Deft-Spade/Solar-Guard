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

#include "font_menu.h"
#include "font_menu.h"

#include "splash_screens.h"
#include "menus.h"
#include "music.h"
#include "bn_sound_items.h"
#include "information.h"
#include "ship_select.h"

#include "briefings.h"
#include "missions.h"
#include "mission_result.h"

void title_screen()
{
    // Title screen background.
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_title_screen.create_bg(0, 0);

    // Play the title screen music.
    bgm_theme_title.play();

    // Draw the text.
    bn::sprite_text_generator text_generator(font_menu);
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
    //bn::sound_items::sfx_menu_select.play();
    bn::core::update();

    while(true)
    {
        int current_scene = main_menu();
        int selected_ship = 0;
        bn::core::update();

        switch (current_scene) {
            case 0:
                title_screen();
                //bn::sound_items::sfx_menu_select.play();
                bn::core::update();
                break;

            case 11:
                // Play the briefing music (in main loop so it doesn't restart
                // when going back to briefing screen from ship select screen).
                bgm_tactical.play();

                bn::sound_items::sfx_menu_select.play();

                while (true)
                {
                    if (briefing_1() == 0)
                    {
                        bn::sound_items::sfx_menu_back.play();
                        bn::core::update();
                        break;
                    }

                    bn::sound_items::sfx_menu_select.play();

                    selected_ship = ship_selection();
                    bn::core::update();

                    if (selected_ship > 0)
                    {
                        break;
                    }

                    bn::sound_items::sfx_menu_back.play();
                }

                if (selected_ship > 0)
                {
                    int mission_result = mission_1(selected_ship);
                    bn::core::update();

                    switch (mission_result)
                    {
                        case 1:
                            mission_success(1);
                            bn::core::update();
                            break;
                        case 0:
                            break;
                        case -1:
                            mission_failure(1);
                            bn::core::update();
                            break;
                        default: break;
                    }

                    bn::core::update();
                }

                break;

            case 12:
                // Play the briefing music (in main loop so it doesn't restart
                // when going back to briefing screen from ship select screen).
                bgm_tactical.play();

                bn::sound_items::sfx_menu_select.play();

                while (true)
                {
                    if (briefing_2() == 0)
                    {
                        bn::sound_items::sfx_menu_back.play();
                        bn::core::update();
                        break;
                    }

                    bn::sound_items::sfx_menu_select.play();

                    selected_ship = ship_selection();
                    bn::core::update();

                    if (selected_ship > 0)
                    {
                        break;
                    }

                    bn::sound_items::sfx_menu_back.play();
                }

                if (selected_ship > 0)
                {
                    int mission_result = mission_2(selected_ship);
                    bn::core::update();

                    switch (mission_result)
                    {
                        case 1:
                            mission_success(2);
                            bn::core::update();
                            break;
                        case 0:
                            break;
                        case -1:
                            mission_failure(21);
                            bn::core::update();
                            break;
                        case -2:
                            mission_failure(22);
                            bn::core::update();
                            break;
                        default: break;
                    }

                    bn::core::update();
                }

                break;

            case 13:
                // Play the briefing music (in main loop so it doesn't restart
                // when going back to briefing screen from ship select screen).
                bgm_tactical.play();

                bn::sound_items::sfx_menu_select.play();

                while (true)
                {
                    if (briefing_3() == 0)
                    {
                        bn::sound_items::sfx_menu_back.play();
                        bn::core::update();
                        break;
                    }

                    bn::sound_items::sfx_menu_select.play();

                    selected_ship = ship_selection();
                    bn::core::update();

                    if (selected_ship > 0)
                    {
                        break;
                    }

                    bn::sound_items::sfx_menu_back.play();
                }

                if (selected_ship > 0)
                {
                    int mission_result = mission_3(selected_ship);
                    bn::core::update();

                    switch (mission_result)
                    {
                        case 1:
                            mission_success(3);
                            bn::core::update();
                            break;
                        case 0:
                            break;
                        case -1:
                            mission_failure(3);
                            bn::core::update();
                            break;
                        default: break;
                    }

                    bn::core::update();
                }

                break;

            case 14:
                // Play the briefing music (in main loop so it doesn't restart
                // when going back to briefing screen from ship select screen).
                bgm_tactical.play();

                bn::sound_items::sfx_menu_select.play();

                while (true)
                {
                    if (briefing_4() == 0)
                    {
                        bn::sound_items::sfx_menu_back.play();
                        bn::core::update();
                        break;
                    }

                    bn::sound_items::sfx_menu_select.play();

                    selected_ship = ship_selection();
                    bn::core::update();

                    if (selected_ship > 0)
                    {
                        break;
                    }

                    bn::sound_items::sfx_menu_back.play();
                }

                if (selected_ship > 0)
                {
                    int mission_result = mission_4(selected_ship);
                    bn::core::update();

                    switch (mission_result)
                    {
                        case 1:
                            mission_success(4);
                            bn::core::update();
                            break;
                        case 0:
                            break;
                        case -1:
                            mission_failure(4);
                            bn::core::update();
                            break;
                        default: break;
                    }

                    bn::core::update();
                }

                break;

            case 15:
                // Play the briefing music (in main loop so it doesn't restart
                // when going back to briefing screen from ship select screen).
                bgm_tactical.play();

                bn::sound_items::sfx_menu_select.play();

                while (true)
                {
                    if (briefing_5() == 0)
                    {
                        bn::sound_items::sfx_menu_back.play();
                        bn::core::update();
                        break;
                    }

                    bn::sound_items::sfx_menu_select.play();

                    selected_ship = ship_selection();
                    bn::core::update();

                    if (selected_ship > 0)
                    {
                        break;
                    }

                    bn::sound_items::sfx_menu_back.play();
                }

                if (selected_ship > 0)
                {
                    int mission_result = mission_5(selected_ship);
                    bn::core::update();

                    switch (mission_result)
                    {
                        case 1:
                            mission_success(5);
                            bn::core::update();
                            break;
                        case 0:
                            break;
                        case -1:
                            mission_failure(5);
                            bn::core::update();
                            break;
                        default: break;
                    }

                    bn::core::update();
                }

                break;

            case 2:
                bn::sound_items::sfx_menu_select.play();
                scene_music_playback();
                bn::sound_items::sfx_menu_back.play();
                bn::core::update();
                break;

            case 31:
                bn::sound_items::sfx_menu_select.play();
                scene_controls();
                bn::sound_items::sfx_menu_back.play();
                bn::core::update();
                break;

            case 32:
                bn::sound_items::sfx_menu_select.play();
                scene_credits();
                bn::sound_items::sfx_menu_back.play();
                bn::core::update();
                break;

            case 33:
                bn::sound_items::sfx_menu_select.play();
                scene_art_ack();
                bn::sound_items::sfx_menu_back.play();
                bn::core::update();
                break;

            default:
                BN_ERROR("Invalid scene number: ", current_scene);
                break;
        }
    }
}
