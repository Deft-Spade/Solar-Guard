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

#include "ally_civillian.h"

#include "bn_math.h"

ally_civillian::ally_civillian(bn::camera_ptr &camera)
{
    // Set camera.
    sprite.set_camera(camera);
}

void ally_civillian::movement()
{
    // Update Position
    x += x_speed;
    y += y_speed;

    // Update Sprite Position to Match Actual Position
    sprite.set_x(x);
    sprite.set_y(y);

    // Set rotation.
    sprite.set_rotation_angle(30);
}

void ally_civillian::radar_dot(player_ship &player_ship)
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

void ally_civillian::map_dot(int x_lim, int y_lim)
{
    // Map position update.
    sprite_map_dot.set_bg_priority(0);
    sprite_map_dot.set_x(93 + (x / x_lim) * 24);
    sprite_map_dot.set_y(53 + (y / y_lim) * 24);
}
