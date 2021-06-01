#include "player_ship.h"
#include "bn_keypad.h"
#include "bn_math.h"
#include <math.h>

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_sg_ship_1.h"
#include "bn_sprite_items_spr_sg_ship_2.h"
#include "bn_sprite_items_spr_sg_ship_3.h"
#include "bn_sprite_items_spr_sg_ship_4.h"
#include "bn_sprite_items_spr_sg_ship_5.h"
#include "bn_sprite_items_spr_sg_ship_6.h"
#include "bn_sprite_items_spr_sg_ship_7.h"
#include "bn_sprite_items_spr_sg_ship_8.h"

player_ship::player_ship(int arg_type)
{
    type = arg_type;

    // Set the player ship sprite to that of the selected ship.
    switch (arg_type)
    {
        case 1: player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0); break;
        case 2: player_sprite = bn::sprite_items::spr_sg_ship_2.create_sprite(0,0); break;
        case 3: player_sprite = bn::sprite_items::spr_sg_ship_3.create_sprite(0,0); break;
        case 4: player_sprite = bn::sprite_items::spr_sg_ship_4.create_sprite(0,0); break;
        case 5: player_sprite = bn::sprite_items::spr_sg_ship_5.create_sprite(0,0); break;
        case 6: player_sprite = bn::sprite_items::spr_sg_ship_6.create_sprite(0,0); break;
        case 7: player_sprite = bn::sprite_items::spr_sg_ship_7.create_sprite(0,0); break;
        case 8: player_sprite = bn::sprite_items::spr_sg_ship_8.create_sprite(0,0); break;
    }
}

void player_ship::movement()
{
    // Turn ship.
    if(bn::keypad::left_held())
    {
        if (direction.ceil_integer() != 359)
        {
            direction += 1;
        }
        else
        {
            direction = 0;
        }
    }
    else if(bn::keypad::right_held())
    {
        if (direction.ceil_integer() != 0)
        {
            direction -= 1;
        }
        else
        {
            direction = 359;
        }
    }

    // Update sprite rotation.
    player_sprite.set_rotation_angle(direction);

    // Determine curent magnitude and direction for refrence.
    int directional_speed = bn::sqrt(speed_x * speed_x + speed_y * speed_y).floor_integer();
    bn::fixed mov_angle = atan2f(speed_y.to_float(), speed_x.to_float()) * 180 / 3.14159265;

    // Speed up and slow down.
    if(bn::keypad::up_held())
    {
        // Determine new x and y speeds.
        // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
        speed_x += 0.1 * bn::degrees_cos(direction);
        speed_y += 0.1 * bn::degrees_sin(direction);

        // Keep speed in check.
        if (directional_speed > speed_max.floor_integer())
        {
            speed_x = speed_max * bn::degrees_cos(mov_angle);
            speed_y = speed_max * bn::degrees_sin(mov_angle);
        }
    }
    else if(bn::keypad::down_held())
    {
        // Deceleration
        speed_x -= 0.05 * bn::degrees_cos(mov_angle);
        speed_y -= 0.05 * bn::degrees_sin(mov_angle);
    }

    // Apply Movement
    x += speed_x;
    y -= speed_y;   // Subtracting because y coordinate decreases when going upwards.

    // Update the sprite's position.
    player_sprite.set_x(x);
    player_sprite.set_y(y);
}
