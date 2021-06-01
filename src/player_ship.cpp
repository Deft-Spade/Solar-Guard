#include "player_ship.h"
#include "bn_keypad.h"
#include "bn_math.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_sg_ship_1.h"
#include "bn_sprite_items_spr_sg_ship_2.h"
#include "bn_sprite_items_spr_sg_ship_3.h"
#include "bn_sprite_items_spr_sg_ship_4.h"
#include "bn_sprite_items_spr_sg_ship_5.h"
#include "bn_sprite_items_spr_sg_ship_6.h"
#include "bn_sprite_items_spr_sg_ship_7.h"
#include "bn_sprite_items_spr_sg_ship_8.h"

#include <math.h>

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
        if (dir_facing.ceil_integer() != 359)
        {
            dir_facing += 1;
        }
        else
        {
            dir_facing = 0;
        }
    }
    else if(bn::keypad::right_held())
    {
        if (dir_facing.ceil_integer() != 0)
        {
            dir_facing -= 1;
        }
        else
        {
            dir_facing = 359;
        }
    }

    // Update sprite rotation.
    player_sprite.set_rotation_angle(dir_facing);

    // Speed up and slow down.
    if(bn::keypad::up_held())
    {
        // Determine new x and y speeds.
        bn::fixed combined_x_speed = speed * bn::degrees_cos(dir_moving) + 0.1 * bn::degrees_cos(dir_facing);
        bn::fixed combined_y_speed = speed * bn::degrees_sin(dir_moving) + 0.1 * bn::degrees_sin(dir_facing);

        // Determine directional speed.
        // https://www.onlinemathlearning.com/vector-magnitude.html
        speed = bn::min(bn::fixed(bn::sqrt(combined_x_speed * combined_x_speed + combined_y_speed * combined_y_speed)), speed_max);

        // Determine angle.
        // https://www.cplusplus.com/reference/cmath/atan2/
        dir_moving = atan2f(combined_y_speed.to_float(),combined_x_speed.to_float()) * 180 / 3.14159265;
    }
    else if(bn::keypad::down_held())
    {
        // Simple deceleration.
        speed = bn::max(bn::fixed(0), speed - 0.01);
    }

    // Apply Movement
    // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
    x += speed * bn::degrees_cos(dir_moving);   // Adding the vector * cos() part.
    y -= speed * bn::degrees_sin(dir_moving);   // Subtracting the vector * sin() part because y coordinate decreases when going upwards.

    // Update the sprite's position.
    player_sprite.set_x(x);
    player_sprite.set_y(y);
}
