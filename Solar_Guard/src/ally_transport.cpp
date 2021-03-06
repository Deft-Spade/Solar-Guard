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
 * developed as fast as possible within 3 months for a game jam.
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

#include "ally_transport.h"

#include "bn_math.h"

ally_transport::ally_transport()
{

}

void ally_transport::move()
{
    // Move along until other corner of map area reached.
    // At this point, mission success should trigger anyway.
    if (x.round_integer() < 4900)
    {
        x += x_speed;
        y -= y_speed;
    }

    // Acceleration at start of mission 2.
    if (x_speed.to_float() != 1)
    {
        x_speed += 0.005;
        y_speed += 0.005;

        if (x_speed.to_double() > 1) x_speed = 1;
        if (y_speed.to_double() > 1) y_speed = 1;
    }

    // Update sprite.
    sprite.set_x(x);
    sprite.set_y(y);
    sprite.set_rotation_angle(rotation);
}

void ally_transport::radar_dot(player_ship &player_ship)
{
    bn::fixed radar_rel_x = (x - player_ship.x) / 20;
    bn::fixed radar_rel_y = (y - player_ship.y) / 20;
    bn::fixed radar_dis = bn::sqrt(bn::abs(radar_rel_x.round_integer() * radar_rel_x.round_integer()) +
                                   bn::abs(radar_rel_y.round_integer() * radar_rel_y.round_integer()));

    if (radar_dis.round_integer() <= 23)
    {
        sprite_radar_dot.set_visible(true);
        sprite_radar_dot.set_bg_priority(0);
        sprite_radar_dot.set_x(radar_rel_x - 92);
        sprite_radar_dot.set_y(radar_rel_y + 52);
    }
    else
    {
        sprite_radar_dot.set_visible(false);
    }
}

void ally_transport::map_dot(int x_lim, int y_lim)
{
    // Map position update.
    sprite_map_dot.set_bg_priority(0);
    sprite_map_dot.set_x(93 + (x / x_lim) * 24);
    sprite_map_dot.set_y(53 + (y / y_lim) * 24);
}
