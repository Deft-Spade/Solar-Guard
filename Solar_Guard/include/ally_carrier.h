#ifndef ALLY_CARRIER_H
#define ALLY_CARRIER_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_spr_space_carrier.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"

class ally_carrier
{
public:
    bn::fixed hull = 1000;
    bn::fixed hull_max = 1000;
    bn::fixed x = 1500;
    bn::fixed y = 1500;

    bn::sprite_ptr sprite1 = bn::sprite_items::spr_space_carrier.create_sprite(x, y - 64, 0);
    bn::sprite_ptr sprite2 = bn::sprite_items::spr_space_carrier.create_sprite(x, y, 1);
    bn::sprite_ptr sprite3 = bn::sprite_items::spr_space_carrier.create_sprite(x, y + 64, 2);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,1);
    bn::sprite_ptr sprite_map_dot = bn::sprite_items::spr_hud_map_position.create_sprite(93,53,1);

    ally_carrier(int x_lim, int y_lim, bn::camera_ptr &camera);
    void radar_dot(player_ship &player_ship);
};

#endif // ALLY_CARRIER_H
