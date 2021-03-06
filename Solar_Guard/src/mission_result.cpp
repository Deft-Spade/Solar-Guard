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
#include "bn_regular_bg_items_bg_briefing_base.h"
#include "bn_regular_bg_items_bg_briefing_base_red.h"

#include "font_menu.h"
#include "font_menu.h"
#include "font_hud.h"
#include "font_hud_red.h"
#include "font_hud_compact.h"
#include "font_hud_compact_red.h"
#include "bn_sprite_items_menu_arrow.h"

#include "music.h"
#include "briefings.h"

void mission_success(int mission_success_number)
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_briefing_base.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw debriefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION SUCCESS", briefing_title);

    // Play briefing music.
    bgm_tactical.play();

    // Draw debriefing text.
    switch (mission_success_number)
    {
        case 1:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "ALL NEARBY SPACE JUNK HAS BEEN DESTROYED. THIS SHOULD", briefing_text);
            text_generator_compact.generate(-106, 34, "HELP KEEP TRANSIT TO AND FROM EARTH SAFE.", briefing_text);
            text_generator_compact.generate(-106, 43, "", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 2:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "THE TRANSPORT WAS SUCCESSFULLY ESCORTED THROUGH THE", briefing_text);
            text_generator_compact.generate(-106, 34, "ASTEROID FIELD. GOOD WORK.", briefing_text);
            text_generator_compact.generate(-106, 43, "", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 3:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "SOLAR GUARD STATION SUCCESSFULLY DEFENDED.", briefing_text);
            text_generator_compact.generate(-106, 34, "", briefing_text);
            text_generator_compact.generate(-106, 43, "", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 4:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "PIRATE SPACE STATIONS SUCCESSFULLY SCANNED.", briefing_text);
            text_generator_compact.generate(-106, 34, "INTEL ACQUIRED FROM THIS MISSION WILL HELP WITH", briefing_text);
            text_generator_compact.generate(-106, 43, "TRACKING PIRATE ACTIVITY IN THE SOLAR SYSTEM.", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 5:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "ALL CIVILLIANS SUCCESSFULLY RESCUED.", briefing_text);
            text_generator_compact.generate(-106, 34, "THE SHIP HAS BREACHED THE NO-FLY ZONE AND WILL", briefing_text);
            text_generator_compact.generate(-106, 43, "EVENTUALLY COMPLETLY DISINTEGRATE.", briefing_text);
            text_generator_compact.generate(-106, 52, "SOLAR GUARD MEDICAL OFFICERS ARE ASSESSING THE", briefing_text);
            text_generator_compact.generate(-106, 61, "CIVILLIANS; IT APPEARS THAT THEY'LL BE ALRIGHT.", briefing_text);
            text_generator_compact.generate(-106, 70, "GOOD WORK PILOT.", briefing_text);
            break;

        default:
            break;
    }

    // Loop until exit.
    while (!bn::keypad::a_pressed())
    {
        // Update while waiting for A to be pressed.
        bn::core::update();
    }
}

void mission_failure(int mission_failure_number)
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_briefing_base_red.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud_red);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact_red);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION FAILURE", briefing_title);

    // Play mission 4 music because it's the best track out of the existing tracks for mission failure due to it's somber style.
    bgm_solar_somber.play();

    // Draw debriefing text.
    switch (mission_failure_number)
    {
        case 1:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "REPORTING LOSS OF SOLAR GUARD FIGHTER DURING", briefing_text);
            text_generator_compact.generate(-106, 34, "OPERATION TO CLEAR SPACE JUNK.", briefing_text);
            text_generator_compact.generate(-106, 43, "", briefing_text);
            text_generator_compact.generate(-106, 52, "PILOT CRASHED INTO TOO MUCH SPACE JUNK CAUSING", briefing_text);
            text_generator_compact.generate(-106, 61, "CRTICIAL HULL FAILURE FROM THE ACCUMULATED DAMAGE.", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 21:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "THE SOLAR GUARD FIGHTER WAS LOST DURING THE ESCORT", briefing_text);
            text_generator_compact.generate(-106, 34, "OPERATION DUE TO CRITICAL HULL FAILURE ARISING FROM", briefing_text);
            text_generator_compact.generate(-106, 43, "FROM DAMAGE SUSTAINED FROM ASTEROID COLLISIONS.", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "ESCORT MISSION FAILED.", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 22:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "THE ESCORTED TRANSPORT WAS LOST DURING THE ESCORT", briefing_text);
            text_generator_compact.generate(-106, 34, "OPERATION DUE TO CRITICAL HULL FAILURE ARISING", briefing_text);
            text_generator_compact.generate(-106, 43, "FROM DAMAGE SUSTAINED FROM ASTEROID COLLISIONS.", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "ESCORT MISSION FAILED.", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 3:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "EITHER THE BASE OR FIGHTER WAS LOST.", briefing_text);
            text_generator_compact.generate(-106, 34, "", briefing_text);
            text_generator_compact.generate(-106, 43, "", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 4:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "THE SOLAR GUARD PILOT'S COVER WAS BLOWN.", briefing_text);
            text_generator_compact.generate(-106, 34, "RECON MISSION FAILED.", briefing_text);
            text_generator_compact.generate(-106, 43, "", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        case 5:
            text_generator_compact.set_left_alignment();
            text_generator_compact.generate(-106, 25, "A CIVILLIAN ESCAPE POD WAS LOST.", briefing_text);
            text_generator_compact.generate(-106, 34, "IT FLEW OUTSIDE OF THE MISSION BOUNDS, INTO THE", briefing_text);
            text_generator_compact.generate(-106, 43, "NO-FLY ZONE AROUND THE SUN.", briefing_text);
            text_generator_compact.generate(-106, 52, "", briefing_text);
            text_generator_compact.generate(-106, 61, "RESCUE MISSION FAILED.", briefing_text);
            text_generator_compact.generate(-106, 70, "", briefing_text);
            break;

        default:
            break;
    }

    // Loop until exit.
    while (!bn::keypad::a_pressed())
    {
        // Update while waiting for A to be pressed.
        bn::core::update();
    }
}
