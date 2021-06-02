#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_spr_sg_ship_1.h"

class player_ship
{

public:
    player_ship(int arg_type);

    int type = 0;
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0);

    int shields = 100;
    int shields_max = 100;
    int shield_recharge_rate = 1;
    int shield_recharge_amount = 100;
    int hull = 100;
    int hull_max = 100;
    int hull_recharge_rate = 6;
    int hull_recharge_amount = 20;
    bn::fixed x = 0;
    bn::fixed y = 0;
    bn::fixed direction = 0;
    bn::fixed speed_x = 0;
    bn::fixed speed_y = 0;
    bn::fixed speed_max = 5;
    bn::fixed directional_speed = 0;
    bn::fixed mov_angle = 0;
    bn::fixed engine_fuel = 0;
    bn::fixed engine_heat = 0;
    int gun_ammo = 200;
    int gun_ammo_max = 200;
    bn::fixed gun_heat = 0;
    int missile_ammo = 0;
    int missile_ammo_max = 0;

    void movement();

};

#endif // PLAYER_SHIP_H
