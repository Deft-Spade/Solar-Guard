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

#ifndef ALLY_CIVILLIAN_POD_H
#define ALLY_CIVILLIAN_POD_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_spr_escape_pod.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"
#include "ally_carrier.h"

class ally_civillian_pod
{
public:
    /* Status variable, similar to other entities' active variable but with more states than
     * simply either being not destroyed or destroyed. Hence the int instead of bool.
     * 0: Destroyed
     * 1: Normal
     * 2: Being carried by the player ship.
     * 3: Returned to the Solar Guard space carrier.
     */
    int status = 1;

    bn::fixed hull = 20;
    bn::fixed hull_max = 20;
    bn::fixed x = 0;
    bn::fixed y = 0;
    bn::fixed x_speed = 0;
    bn::fixed y_speed = 0;

    bn::sprite_ptr sprite = bn::sprite_items::spr_escape_pod.create_sprite(x, y, 0);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,1);
    bn::sprite_ptr sprite_map_dot = bn::sprite_items::spr_hud_map_position.create_sprite(93,53,1);

    ally_civillian_pod(int init_x, int init_y, bn::camera_ptr &camera, double init_x_speed, double init_y_speed);
    void movement(player_ship &player_ship);
    void state_update(player_ship &player_ship, bool &player_carrying_pod, ally_carrier &ally_carrier, int &pods_left);
    void radar_dot(player_ship &player_ship);
    void map_dot(int x_lim, int y_lim);
};

#endif // ALLY_CIVILLIAN_POD_H
