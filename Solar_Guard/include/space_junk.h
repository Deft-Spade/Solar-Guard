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

#ifndef SPACE_JUNK_H
#define SPACE_JUNK_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_cameras.h"

#include "bn_sprite_items_spr_space_junk.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"

class space_junk
{
public:
    bool active = true;
    bn::fixed hull = 20;
    bn::fixed hull_max = 20;
    bn::fixed x = 0;
    bn::fixed y = 0;

    bn::sprite_ptr sprite = bn::sprite_items::spr_space_junk.create_sprite(0,0);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,3);
    bn::sprite_ptr sprite_map_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,3);

    space_junk(int start_x, int start_y, bn::camera_ptr &camera, int junk_type);
    void destroy();
    void radar_dot(player_ship &player_ship);
    void map_dot(int x_lim, int y_lim);
    bool check_collision(int x_position, int y_position, int width, int height);
};

#endif // SPACE_JUNK_H
