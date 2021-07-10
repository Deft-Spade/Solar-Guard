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

#include "information.h"

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
#include "bn_regular_bg_items_bg_art_ack_page1.h"
#include "bn_regular_bg_items_bg_art_ack_page2.h"
#include "bn_regular_bg_items_bg_art_ack_page3.h"
#include "bn_regular_bg_items_bg_art_ack_page4.h"
#include "bn_regular_bg_items_bg_art_ack_page5.h"
#include "bn_regular_bg_items_bg_art_ack_page6.h"
#include "bn_regular_bg_items_bg_art_ack_page7.h"
#include "bn_regular_bg_items_bg_art_ack_page8.h"
#include "bn_regular_bg_items_bg_art_ack_page9.h"
#include "bn_regular_bg_items_bg_art_ack_page10.h"
#include "bn_regular_bg_items_bg_art_ack_page11.h"
#include "bn_regular_bg_items_bg_art_ack_page12.h"
#include "bn_regular_bg_items_bg_art_ack_page13.h"
#include "bn_regular_bg_items_bg_art_ack_page13_image.h"
#include "bn_regular_bg_items_bg_art_ack_page14.h"

#include "bn_sprite_text_generator.h"
#include "font_menu.h"
#include "font_menu.h"
#include "font_hud.h"
#include "font_hud_compact.h"

#include "bn_music_item.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"
#include "music.h"
#include "bn_sound_items.h"

namespace
{
    constexpr const bn::fixed screen_y_limit = (bn::display::height() / 2);
}

void scene_controls()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_information.create_bg(0, 0);

    bgm_theme_upbeat.play();

    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 128> text_sprites;

    text_generator.set_center_alignment();
    text_generator.generate(0, - 65, "CONTROLS", text_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-106, - 20, "LEFT/RIGHT > TURN SHIP", text_sprites);
    text_generator.generate(-106, - 10, "A > FIRE LASER", text_sprites);
    text_generator.generate(-106, 0, "R > ENGAGE ENGINES", text_sprites);
    text_generator.generate(-106, + 10, "L > REDUCE SPEED", text_sprites);
    text_generator.generate(-106, + 20, "L + R > ENGAGE REVERSE ENGINES", text_sprites);

    while (!bn::keypad::b_pressed())
    {
        bn::core::update();
    }
}

void scene_known_issues()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_information.create_bg(0, 0);

    bgm_theme_upbeat.play();

    bn::sprite_text_generator text_generator(font_hud);
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 128> text_sprites;

    text_generator.set_center_alignment();
    text_generator.generate(0, - 65, "KNOWN ISSUES", text_sprites);
    text_generator.set_left_alignment();
    text_generator_compact.generate(-108, - 50, "> FIRING LASERS IN MISSION 2 CAUSES CPU OVERLOAD.", text_sprites);
    text_generator_compact.generate(-108, - 40, "  THIS IS DUE TO THE ADDITIONAL COLLISION CHECKING.", text_sprites);
    text_generator_compact.generate(-108, - 30, "  THIS RESULTS IN TEMPORARY GAME SLOW DOWN.", text_sprites);
    text_generator_compact.generate(-108, - 20, "", text_sprites);
    text_generator_compact.generate(-108, - 10, "> THE AMOUNT OF ASTEROIDS IN MISSION 2 IS NOT AS MANY", text_sprites);
    text_generator_compact.generate(-108, +  0, "  AS INTENDED DUE TO SPRITE QUANTITIY LIMITATIONS.", text_sprites);
    text_generator_compact.generate(-108, + 10, "  CAN'T JUST PLACE A BUNCH OF C++ OBJECTS AROUND.", text_sprites);
    text_generator_compact.generate(-108, + 20, "  NEED A BETTER WAY OF MAKING MANY ASTEROIDS EXIST.", text_sprites);
    text_generator_compact.generate(-108, + 30, "", text_sprites);
    text_generator_compact.generate(-108, + 40, "> MISSIONS 3 AND 4 CURRENTLY HAVE NO FUNCTIONALITY.", text_sprites);
    text_generator_compact.generate(-108, + 50, "  ALL THE PLAYER CAN DO IS JUST FLY AROUND.", text_sprites);

    while (!bn::keypad::b_pressed())
    {
        bn::core::update();
    }
}

void scene_credits()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_information.create_bg(0, 0);

    bgm_theme_upbeat.play();

    // Create the logo sprite.
    bn::sprite_ptr sprite_logo = bn::sprite_items::spr_logo_green.create_sprite(0, -15);

    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 128> text_sprites;

    text_generator.set_center_alignment();
    text_generator.generate(0, + 10, "BY DEFT SPADE", text_sprites);
    text_generator.generate(0, + 20, "USING BUTANO BY GVALIENTE", text_sprites);
    text_generator.generate(0, + 30, "FOR GBA JAM 2021", text_sprites);

    while (!bn::keypad::b_pressed())
    {
        bn::core::update();
    }
}

int loop_art_ack_credits()
{
    while (true)
    {
        if (bn::keypad::right_pressed())
        {
            return 1;
        }

        if (bn::keypad::left_pressed())
        {
            return -1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        if (bn::keypad::a_pressed())
        {
            return 2;
        }

        bn::core::update();
    }
}

int scene_art_ack_page1()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page1.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page2()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page2.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page3()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page3.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page4()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page4.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page5()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page5.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page6()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page6.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page7()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page7.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page8()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page8.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page9()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page9.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page10()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page10.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page11()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page11.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page12()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page12.create_bg(0, 0);
    return loop_art_ack_credits();
}

int page13_image()
{
    bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page13_image.create_bg(0, 50);
    int scroll_position = 0;

    bn::sound_items::sfx_menu_select.play();

    while (true)
    {
        if (bn::keypad::up_held() && scroll_position > 0)
        {
            regular_bg.set_y(regular_bg.y() + 1);
            scroll_position -= 1;
        }

        if (bn::keypad::down_held() && scroll_position < 100)
        {
            regular_bg.set_y(regular_bg.y() - 1);
            scroll_position += 1;
        }

        if (bn::keypad::b_pressed())
        {
            return -2;
        }

        bn::core::update();
    }
}

int scene_art_ack_page13()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page13.create_bg(0, 0);
    return loop_art_ack_credits();
}

int scene_art_ack_page14()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_art_ack_page14.create_bg(0, 0);
    return loop_art_ack_credits();
}

void scene_art_ack()
{
    // Menu operation variables.
    int current_page = 1;
    const int number_of_pages = 14;

    bgm_theme_upbeat.play();

    while (true)
    {
        int user_input;

        // Switch page.
        switch (current_page)
        {
            case 1: user_input = scene_art_ack_page1(); break;
            case 2: user_input = scene_art_ack_page2(); break;
            case 3: user_input = scene_art_ack_page3(); break;
            case 4: user_input = scene_art_ack_page4(); break;
            case 5: user_input = scene_art_ack_page5(); break;
            case 6: user_input = scene_art_ack_page6(); break;
            case 7: user_input = scene_art_ack_page7(); break;
            case 8: user_input = scene_art_ack_page8(); break;
            case 9: user_input = scene_art_ack_page9(); break;
            case 10: user_input = scene_art_ack_page10(); break;
            case 11: user_input = scene_art_ack_page11(); break;
            case 12: user_input = scene_art_ack_page12(); break;
            case 13: user_input = scene_art_ack_page13(); break;
            case 113: user_input = page13_image(); bn::sound_items::sfx_menu_back.play(); break;
            case 14: user_input = scene_art_ack_page14(); break;
            default: BN_ERROR("CURRENT PAGE VALUE INVALID: " + bn::to_string<32>(current_page)); break;
        }

        switch (user_input)
        {
            case -2: current_page -= 100; break;

            case -1:
                if (current_page > 1)
                {
                    current_page -= 1;
                }
                else
                {
                    current_page = number_of_pages;
                }
                bn::sound_items::sfx_menu_move.play();
                break;

            case 0: return; break;

            case 1:
                if (current_page < number_of_pages)
                {
                    current_page += 1;
                }
                else
                {
                    current_page = 1;
                }
                bn::sound_items::sfx_menu_move.play();
                break;

            case 2: current_page += 100; break;

            default: BN_ERROR("USER INPUT VALUE INVALID: " + bn::to_string<32>(user_input)); break;
        }

        bn::core::update();
    }
}
