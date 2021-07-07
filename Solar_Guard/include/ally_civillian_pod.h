#ifndef ALLY_CIVILLIAN_POD_H
#define ALLY_CIVILLIAN_POD_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_spr_escape_pod.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"
#include "ally_carrier.h"

class ally_civillian_pod
{
public:
    /* Status variable, similar to other entities' active variable but with more states than
     * simply either being not destroyed or destroyed. Hence the int instead of bool.
     * 0: Destroyed
     * 1: Normal
     * 2: Being carried by the player ship.
     * 3: Returned to the Solar Guard space carrier.
     */
    int status = 1;

    bn::fixed hull = 20;
    bn::fixed hull_max = 20;
    bn::fixed x = 0;
    bn::fixed y = 0;
    bn::fixed x_speed = 0;
    bn::fixed y_speed = 0;

    bn::sprite_ptr sprite = bn::sprite_items::spr_escape_pod.create_sprite(x, y, 0);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,1);
    bn::sprite_ptr sprite_map_dot = bn::sprite_items::spr_hud_map_position.create_sprite(93,53,1);

    ally_civillian_pod(int init_x, int init_y, bn::camera_ptr &camera, double init_x_speed, double init_y_speed);
    void movement(player_ship &player_ship);
    void state_update(player_ship &player_ship, bool &player_carrying_pod, ally_carrier &ally_carrier, int &pods_left);
    void radar_dot(player_ship &player_ship);
    void map_dot(int x_lim, int y_lim);
};

#endif // ALLY_CIVILLIAN_POD_H
