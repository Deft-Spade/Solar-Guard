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

#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_spr_sg_ship_1.h"
#include "bn_sprite_items_spr_sg_ship_2.h"
#include "bn_sprite_items_spr_sg_ship_3.h"
#include "bn_sprite_items_spr_sg_ship_4.h"
#include "bn_sprite_items_spr_sg_ship_5.h"
#include "bn_sprite_items_spr_sg_ship_6.h"
#include "bn_sprite_items_spr_sg_ship_7.h"
#include "bn_sprite_items_spr_sg_ship_8.h"

#include "bn_sound_items.h"

#include "laser_player.h"

#define number_of_ships 8

class player_ship
{

public:
    player_ship(int ship_type, int x_pos, int y_pos);

    int type = 0;
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0);

    bn::fixed shields = 100;
    const bn::array<bn::fixed, number_of_ships> shields_damage_factor = { 1, 1, 1, 1, 1, 1, 1, 1 };
    int shields_recharge_timer = 0;
    const bn::array<int, number_of_ships> shields_recharge_rate = { 5, 5, 5, 5, 5, 5, 5, 5 };
    int shields_recharge_delay = 0;
    const bn::array<int, number_of_ships> shields_recharge_delay_max = { 360, 360, 360, 360, 360, 360, 360, 360 };

    bn::fixed hull = 100;
    const bn::array<bn::fixed, number_of_ships> hull_damage_factor = { 2, 2/3, 1, 1, 2/3, 1, 0.5, 0.5 };
    const bn::array<bn::fixed, number_of_ships> hull_damage_divider = { 0.5, 1.5, 1, 1, 1.5, 1, 2, 2 };
    int hull_recharge_timer = 0;
    const bn::array<int, number_of_ships> hull_recharge_rate = { 0, 0, 300, 180, 60, 0, 0, 0 };
    const bn::array<int, number_of_ships> hull_recharge_portion = { 0, 0, 20, 20, 20, 0, 0, 0 };

    bn::fixed x = 0;
    bn::fixed y = 0;

    bn::fixed direction = 90;
    const bn::array<bn::fixed, number_of_ships> turn_rate = { 1.5, 1, 2, 3, 1.5, 1, 0.5, 1 };
    bn::fixed speed_x = 0;
    bn::fixed speed_y = 0;
    const bn::array<bn::fixed, number_of_ships> speed_max = { 4, 4, 6, 7, 5, 10, 8, 3 };
    // A value of 0.1 doesn't apply any movement change and 0.02/0.03 apply the same movement/
    // I suspect this is due to precision limitations.
    const bn::array<bn::fixed, number_of_ships> accel_front = { 0.05, 0.04, 0.06, 0.07, 0.05, 0.10, 0.08, 0.04 };
    const bn::array<bn::fixed, number_of_ships> accel_back = { 0.04, 0.02, 0.04, 0.07, 0.05, 0.04, 0.02, 0.02 };
    const bn::array<bn::fixed, number_of_ships> decel_brake = { 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02 };
    bn::fixed directional_speed = 0;
    bn::fixed mov_angle = 0;

    bn::fixed engine_fuel = 0;
    const bn::array<bn::fixed, number_of_ships> engine_fuel_max = { 30, 50, 40, 40, 60, 40, 50, 100 };
    const bn::array<bn::fixed, number_of_ships> engine_fuel_front_burn = { 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01 };
    const bn::array<bn::fixed, number_of_ships> engine_fuel_rear_burn = { 0.005, 0.005, 0.005, 0.01, 0.01, 0.005, 0.005, 0.005 };
    bn::fixed engine_heat = 0;
    const bn::array<bn::fixed, number_of_ships> engine_heat_max = { 100, 100, 100, 100, 100, 100, 100, 100 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_front_increase_rate = { 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_rear_increase_rate = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_cooldown_rate = { 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_cooldown_threshold = { 0, 0, 0, 0, 0, 0, 0, 0 };
    bool engine_overheated = false;

    int alternate_ab_frame = 0;

    const int gun_cooldown_time = 15;
    int gun_firing_cooldown = gun_cooldown_time;
    bn::fixed gun_energy = 0;
    const bn::array<bn::fixed, number_of_ships> gun_energy_max = { 200, 200, 300, 300, 400, 300, 300, 300 };
    bn::fixed gun_heat = 0;
    const bn::array<bn::fixed, number_of_ships> gun_heat_max = { 100, 100, 100, 100, 100, 100, 100, 100 };
    const bn::array<bn::fixed, number_of_ships> gun_heat_increase_rate = { 10, 10, 8, 6, 4, 6, 6, 6 };
    const bn::array<bn::fixed, number_of_ships> gun_heat_cooldown_rate = { 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2 };
    bool gun_overheated = false;

    //bn::sound_item sound_laser_fire =

    void movement();
    void animation();
    void fire_control(int &next_laser, const int &number_of_lasers, bn::array<laser_player, 5> &player_lasers);
    void shield_regeneration();
    void hull_repair();
    void damage(bn::fixed amount);
};

#endif // PLAYER_SHIP_H
