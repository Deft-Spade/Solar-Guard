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

#ifndef HUD_ALLY_H
#define HUD_ALLY_H

// Butano includes.
#include "bn_sprite_ptr.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_text_generator.h"

// Includes for sprites.
#include "bn_sprite_items_spr_hud_ally_outline.h"
#include "bn_sprite_items_spr_hud_ally_hull.h"
#include "bn_sprite_items_spr_hud_number_hull.h"

class hud_ally
{
public:
    bn::sprite_ptr spr_ally_outline = bn::sprite_items::spr_hud_ally_outline.create_sprite(-94,-22);
    bn::sprite_ptr spr_ally_hull = bn::sprite_items::spr_hud_ally_hull.create_sprite(-87,-18);
    bn::sprite_ptr spr_ally_hull_text = bn::sprite_items::spr_hud_number_hull.create_sprite(-110,-18);

    hud_ally(int ally_type);
    void update(bn::fixed ally_hull);
};

#endif // HUD_ALLY_H
