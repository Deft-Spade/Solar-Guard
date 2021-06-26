#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_spr_sg_ship_1.h"

#include "laser_player.h"

class player_ship
{

public:
    player_ship(int ship_type, int x_pos, int y_pos);

    int type = 0;
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0);

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
    bn::fixed engine_fuel = 100;
    bn::fixed engine_fuel_max = 100;
    bn::fixed engine_heat = 0;
    bn::fixed engine_heat_max = 100;
    bool engine_overheated = false;
    int alternate_ab_frame = 0;
    int gun_firing_cooldown = 0;
    const int gun_cooldown_time = 15;
    bn::fixed gun_energy = 100;
    bn::fixed gun_energy_max = 100;
    bn::fixed gun_heat = 0;
    bn::fixed gun_heat_max = 100;
    bool gun_overheated = false;

    void movement();
    void animation();
    void fire_control(int &next_laser, const int &number_of_lasers, bn::array<laser_player, 5> &player_lasers);
};

#endif // PLAYER_SHIP_H
