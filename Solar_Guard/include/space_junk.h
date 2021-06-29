#ifndef SPACE_JUNK_H
#define SPACE_JUNK_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_cameras.h"

#include "bn_sprite_items_spr_space_junk.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "player_ship.h"

class space_junk
{
public:
    bool active = true;
    bn::fixed hull = 20;
    bn::fixed hull_max = 20;
    bn::fixed x = 0;
    bn::fixed y = 0;

    space_junk(int start_x, int start_y, bn::camera_ptr &camera, int junk_type);
    void destroy();
    void radar_dot(player_ship &player_ship);

    bn::sprite_ptr sprite = bn::sprite_items::spr_space_junk.create_sprite(0,0);
    bn::sprite_ptr sprite_radar_dot = bn::sprite_items::spr_hud_map_position.create_sprite(-92,53,3);
};

#endif // SPACE_JUNK_H
