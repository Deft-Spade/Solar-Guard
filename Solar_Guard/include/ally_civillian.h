#ifndef ALLY_CIVILLIAN_H
#define ALLY_CIVILLIAN_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_spr_civillian.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"

class ally_civillian
{
public:
    bn::fixed hull = 1000;
    bn::fixed hull_max = 1000;
    bn::fixed x = -400;
    bn::fixed y = -400;
    bn::fixed x_speed = -0.05;
    bn::fixed y_speed = -0.05;

    bn::sprite_ptr sprite = bn::sprite_items::spr_civillian.create_sprite(x, y);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,3);
    bn::sprite_ptr sprite_map_dot = bn::sprite_items::spr_hud_map_position.create_sprite(93,53,3);

    ally_civillian(bn::camera_ptr &camera);
    void movement();
    void radar_dot(player_ship &player_ship);
    void map_dot(int x_lim, int y_lim);
};

#endif // ALLY_CIVILLIAN_H
