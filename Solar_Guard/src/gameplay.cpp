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
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_math.h"

#include <string>

#include "gameplay.h"
#include "player_ship.h"

void gameplay_hud_draw(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites, bn::fixed x, bn::fixed y)
{
    // Draw HUD sprites.



    // Coordinates Text
    text_sprites.clear();

    // Conversion of numerical integers to characters.
    // https://www.delftstack.com/howto/cpp/how-to-convert-int-to-char-array-in-cpp/
    std::string coord_string = "COORDINATES: (" + std::to_string(x.round_integer()) + "," + std::to_string(y.round_integer()) + ")";
    char const *coord_chars = coord_string.c_str();

    text_generator.generate(-120, -75, coord_chars, text_sprites);
}
