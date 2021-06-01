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
    directional_speed = bn::sqrt(speed_x * speed_x + speed_y * speed_y);             // https://www.onlinemathlearning.com/vector-magnitude.html
    mov_angle = atan2(speed_y.to_double(), speed_x.to_double()) * 180 / 3.14159265;  // https://www.cplusplus.com/reference/cmath/atan2/

    // Speed up and slow down.
    if(bn::keypad::up_held())
    {
        // Determine new x and y speeds.
        // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
        speed_x += 0.1 * bn::degrees_cos(direction);
        speed_y += 0.1 * bn::degrees_sin(direction);

        // Keep speed in check.
        if (directional_speed.ceil_integer() > speed_max.floor_integer())
        {
            // Retain direction but reset magnitude to maximum allowed speed.
            // https://stackoverflow.com/questions/41317291/setting-the-magnitude-of-a-2d-vector
            speed_x = speed_x * speed_max / directional_speed;
            speed_y = speed_y * speed_max / directional_speed;
        }
    }
    else if(bn::keypad::down_held())
    {
        // Check if current overall speed is greater than deceleration amount.
        if (directional_speed.to_double() > 0.05)
        {
            // Retain direction but reduce magnitude by a deceleration amount.
            // https://stackoverflow.com/questions/41317291/setting-the-magnitude-of-a-2d-vector
            speed_x = speed_x * (directional_speed - 0.05) / directional_speed;
            speed_y = speed_y * (directional_speed - 0.05) / directional_speed;
        }
        else
        {
            // In the event that the current overall speed is as large or smaller than deceleration amount, set speed
            // to 0 to properly stop ship and avoid a slow drift from a flipped speed value that's small but not zero.
            speed_x = 0;
            speed_y = 0;
        }
    }

    // Apply Movement
    x += speed_x;
    y -= speed_y;   // Subtracting because y coordinate decreases when going upwards.

    // Update the sprite's position.
    player_sprite.set_x(x);
    player_sprite.set_y(y);
}
