#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_sg_ship_1.h"

class player_ship
{

public:
    player_ship(int arg_type);

    int type = 0;
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0);

    bn::fixed shields = 0;
    bn::fixed shield_recharge_rate = 0;
    bn::fixed shield_recharge_amount = 0;
    bn::fixed hull = 0;
    bn::fixed hull_recharge_rate = 0;
    bn::fixed hull_recharge_amount = 0;
    bn::fixed x = 0;
    bn::fixed y = 0;
    bn::fixed dir_facing = 0;
    bn::fixed dir_moving = 0;
    bn::fixed speed = 0;
    bn::fixed engine_fuel = 0;
    bn::fixed engine_heat = 0;
    bn::fixed gun_ammo = 0;
    bn::fixed gun_ammo_max = 0;
    bn::fixed gun_heat = 0;
    bn::fixed missile_ammo = 0;
    bn::fixed missile_ammo_max = 0;

    void movement();

};

#endif // PLAYER_SHIP_H
