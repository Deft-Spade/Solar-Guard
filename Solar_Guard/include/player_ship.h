#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_spr_sg_ship_1.h"

#include "laser_player.h"

#define number_of_ships 8

class player_ship
{

public:
    player_ship(int ship_type, int x_pos, int y_pos);

    int type = 0;
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0);

    bn::fixed shields = 0;
    const bn::array<bn::fixed, number_of_ships> shields_max = { 100, 100, 100, 100, 100, 100, 100, 100 };
    const bn::array<bn::fixed, number_of_ships> shield_recharge_rate = { 1, 1, 1, 1, 1, 1, 1, 1 };
    const bn::array<bn::fixed, number_of_ships> shield_recharge_delay = { 100, 100, 100, 100, 100, 100, 100, 100 };

    bn::fixed hull = 0;
    const bn::array<bn::fixed, number_of_ships> hull_max = { 100, 100, 100, 100, 100, 100, 100, 100 };
    const bn::array<bn::fixed, number_of_ships> hull_recharge_rate = { 60, 60, 60, 60, 60, 60, 60, 60 };
    const bn::array<bn::fixed, number_of_ships> hull_recharge_amount = { 20, 20, 20, 20, 20, 20, 20, 20 };

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
    const bn::array<bn::fixed, number_of_ships> engine_fuel_rear_burn = { 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005 };
    bn::fixed engine_heat = 0;
    const bn::array<bn::fixed, number_of_ships> engine_heat_max = { 100, 100, 100, 100, 100, 100, 100, 100 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_front_increase_rate = { 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_rear_increase_rate = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_cooldown_rate = { 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3 };
    const bn::array<bn::fixed, number_of_ships> engine_heat_cooldown_threshold = { 0, 0, 0, 0, 0, 0, 0, 0 };
    bool engine_overheated = false;

    int alternate_ab_frame = 0;

    int gun_firing_cooldown = 0;
    const int gun_cooldown_time = 15;
    bn::fixed gun_energy = 0;
    const bn::array<bn::fixed, number_of_ships> gun_energy_max = { 400, 400, 400, 400, 400, 400, 400, 400 };
    bn::fixed gun_heat = 0;
    const bn::array<bn::fixed, number_of_ships> gun_heat_max = { 100, 100, 100, 100, 100, 100, 100, 100 };
    const bn::array<bn::fixed, number_of_ships> gun_heat_increase_rate = { 10, 10, 8, 6, 4, 6, 6, 6 };
    const bn::array<bn::fixed, number_of_ships> gun_heat_cooldown_rate = { 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2 };
    bool gun_overheated = false;

    void movement();
    void animation();
    void fire_control(int &next_laser, const int &number_of_lasers, bn::array<laser_player, 5> &player_lasers);
};

#endif // PLAYER_SHIP_H
