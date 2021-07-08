#ifndef ALLY_TRANSPORT_H
#define ALLY_TRANSPORT_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_spr_transport.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"

class ally_transport
{
public:
    bn::fixed hull = 100;
    bn::fixed x = -4900;
    bn::fixed y = 4900;
    int rotation = 45;

    bn::sprite_ptr sprite = bn::sprite_items::spr_transport.create_sprite(x, y, 0);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,1);
    bn::sprite_ptr sprite_map_dot = bn::sprite_items::spr_hud_map_position.create_sprite(93,53,1);

    ally_transport();
    void move();

    void radar_dot(player_ship &player_ship);
    void map_dot(int x_lim, int y_lim);
};

#endif // ALLY_TRANSPORT_H
