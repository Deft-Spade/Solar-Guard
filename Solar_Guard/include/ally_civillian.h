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

#ifndef ALLY_CIVILLIAN_H
#define ALLY_CIVILLIAN_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_spr_civillian.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"

class ally_civillian
{
public:
    bn::fixed hull = 100;
    bn::fixed x = -400;
    bn::fixed y = -400;
    bn::fixed x_speed = -0.05;
    bn::fixed y_speed = -0.05;

    bn::sprite_ptr sprite = bn::sprite_items::spr_civillian.create_sprite(x, y);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,3);
    bn::sprite_ptr sprite_map_dot = bn::sprite_items::spr_hud_map_position.create_sprite(93,53,3);

    ally_civillian(bn::camera_ptr &camera);
    void movement();
    void radar_dot(player_ship &player_ship);
    void map_dot(int x_lim, int y_lim);
};

#endif // ALLY_CIVILLIAN_H
