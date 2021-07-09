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

#ifndef PIRATE_SHIP_H
#define PIRATE_SHIP_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_spr_pirate_ship.h"

class pirate_ship
{
public:
    bn::fixed shields = 100;
    bn::fixed shields_max = 100;
    bn::fixed shield_recharge_rate = 1;
    bn::fixed shield_recharge_amount = 100;
    bn::fixed hull = 100;
    bn::fixed hull_max = 100;
    bn::fixed hull_recharge_rate = 6;
    bn::fixed hull_recharge_amount = 20;
    bn::fixed x = 0;
    bn::fixed y = 0;
    bn::fixed direction = 0;
    bn::fixed speed_x = 0;
    bn::fixed speed_y = 0;
    bn::fixed speed_max = 5;
    bn::fixed directional_speed = 0;
    bn::fixed mov_angle = 0;
    bn::fixed engine_fuel = 40;
    bn::fixed engine_fuel_max = 40;
    bn::fixed engine_heat = 0;
    bn::fixed engine_heat_max = 100;
    bool engine_overheated = false;
    int alternate_ab_frame = 0;
    int gun_ammo = 200;
    int gun_ammo_max = 200;
    bn::fixed gun_heat = 0;
    int missile_ammo = 0;
    int missile_ammo_max = 0;

    pirate_ship();
};

#endif // PIRATE_SHIP_H
