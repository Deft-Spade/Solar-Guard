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