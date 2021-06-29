#ifndef ASTEROID_H
#define ASTEROID_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_sprite_items_spr_asteroid.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"

class asteroid
{
public:
    bool active = true;
    bn::fixed hull = 40;
    bn::fixed hull_max = 40;
    bn::fixed x = 0;
    bn::fixed y = 0;

    bn::sprite_ptr sprite = bn::sprite_items::spr_asteroid.create_sprite(0,0);

    asteroid(int start_x, int start_y, bn::camera_ptr &camera, int asteroid_type);
    void radar_dot(player_ship &player_ship);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,3);
};

#endif // ASTEROID_H
