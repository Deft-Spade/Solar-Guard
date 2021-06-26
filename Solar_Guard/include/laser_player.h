#ifndef LASER_PLAYER_H
#define LASER_PLAYER_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"

#include "bn_sprite_items_spr_laser.h"

class laser_player
{
public:
    bn::fixed x = 0;
    bn::fixed y = 0;
    bn::fixed x_speed = 0;
    bn::fixed y_speed = 0;
    int distance = 0;
    const int max_distance = 50;

    int active = 0;

    bn::sprite_ptr sprite = bn::sprite_items::spr_laser.create_sprite(0,0);

    laser_player(bn::camera_ptr &camera);
    void fire(int colour, int start_x, int start_y, bn::fixed shooter_x_speed, bn::fixed shooter_y_speed, bn::fixed shooter_direction);
    void move();
    bool check_collision(int x_position, int y_position, int x_left, int y_top, int x_right, int y_bottom);
};

#endif // LASER_PLAYER_H
