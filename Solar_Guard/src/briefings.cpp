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
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_items_spr_logo.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_briefing1.h"
#include "bn_regular_bg_items_bg_briefing2.h"
#include "bn_regular_bg_items_bg_briefing3.h"
#include "bn_regular_bg_items_bg_briefing4.h"
#include "bn_regular_bg_items_bg_briefing5.h"

#include "font_menu.h"
#include "font_menu.h"
#include "font_hud.h"
#include "font_hud_compact.h"
#include "bn_sprite_items_menu_arrow.h"

#include "music.h"
#include "briefings.h"

int briefing_1()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_briefing1.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 1: ORBIT TYDING", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-106, 25, "SPACE JUNK HAS BEEN ACCUMULATING WITHIN EARTH'S", briefing_text);
    text_generator_compact.generate(-106, 34, "ORBIT. THIS PRESENTS A HAZARD TO LOCAL SOLAR TRAFFIC.", briefing_text);
    text_generator_compact.generate(-106, 43, "WE ARE DEPLOYING FIGHTERS TO DESTROY THE EXCESS JUNK.", briefing_text);
    text_generator_compact.generate(-106, 52, "PREPARE FOR DEPLOYMENT.", briefing_text);
    text_generator_compact.generate(-106, 61, "", briefing_text);
    text_generator_compact.generate(-106, 70, "", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_2()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_briefing2.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 2: CLEAR THE WAY", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-106, 25, "A TRANSPORT HAS REQUESTED ASSISTANCE ESCORT THROUGH", briefing_text);
    text_generator_compact.generate(-106, 34, "AN ASTEROID FIELD. DESTROY ANY ASTEROIDS IN THE WAY.", briefing_text);
    text_generator_compact.generate(-106, 43, "", briefing_text);
    text_generator_compact.generate(-106, 52, "KNOWN ISSUE: THE CPU MAY BE OVERLOADED WHEN LASERS", briefing_text);
    text_generator_compact.generate(-106, 61, "ARE FIRED DUE TO THE ADDITIONAL COLLISION CHECKING.", briefing_text);
    text_generator_compact.generate(-106, 70, "GAME SLOWDOWN MAY OCCUR WHILE LASERS ARE PRESENT.", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_3()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_briefing3.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 3: SWIFT DEFENSE", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-106, 25, "WARNING! ENEMY SHIPS ATTACKING!", briefing_text);
    text_generator_compact.generate(-106, 34, "IDENTIFIED AS SPACE PIRATES", briefing_text);
    text_generator_compact.generate(-106, 43, "ALL SOLAR GUARD FIGHTERS SCRAMBLE AND ENGAGE!", briefing_text);
    text_generator_compact.generate(-106, 52, "", briefing_text);
    text_generator_compact.generate(-106, 61, "NOTE: THIS MISSION IS NOT IMPLEMENTED.", briefing_text);
    text_generator_compact.generate(-106, 70, "", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_4()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_briefing4.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 4: COUNTER PROBE", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-106, 25, "SOLAR GUARD COMMAND BELIEVES THE PIRATES MAY BE", briefing_text);
    text_generator_compact.generate(-106, 34, "OPERATING AN OUTPOST WITHIN THE ASTEROID BELT.", briefing_text);
    text_generator_compact.generate(-106, 43, "PERFORM STEALTH RECONNAISSANCE OF THE BASE.", briefing_text);
    text_generator_compact.generate(-106, 52, "", briefing_text);
    text_generator_compact.generate(-106, 61, "NOTE: THIS MISSION IS NOT IMPLEMENTED.", briefing_text);
    text_generator_compact.generate(-106, 70, "", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_5()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_briefing5.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 5: DISTANT REACH", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-106, 25, "WE HAVE PICKED UP A DISTRESS CALL FROM A CIVILLIAN", briefing_text);
    text_generator_compact.generate(-106, 34, "CRAFT. IT APPEARS THAT THE SHIP'S ENGINES HAVE FAILED", briefing_text);
    text_generator_compact.generate(-106, 43, "NEAR THE SUN, WHICH IT IS NOW DRIFTING TOWARDS. FLY", briefing_text);
    text_generator_compact.generate(-106, 52, "TO THE STRICKEN CRAFT AND RESCUE ANY OCCUPANTS", briefing_text);
    text_generator_compact.generate(-106, 61, "IN ESCAPE PODS, RETURNING THEM TO THE CARRIER.", briefing_text);
    text_generator_compact.generate(-106, 70, "", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}
