/* Solar Guard by Deft Spade
 * Using Butano by GValiente
 * Made for GBA JAM 2021
 * Source Code and Assets Licensed Under GPL-3.0
 * 
 * This source code has known issues. No promises are made as to the
 * quality/reliability of anything in this source code. Such issues
 * include and are not necessarily limited to code repetition, magic
 * numbers, undocumented conventions for what certain variable values
 * mean, etc. Lots of refactoring and commenting/documenting is needed
 * to bring the overall code quality up-to-scratch, after all, this was
 * developed as fast as possible within 3 months for a game jam. Also,
 * there are no guarantees about how much I'll further develop this
 * game after GBA JAM 2021. This means I may never get around to fully
 * fixing/completing everything.
 */

/*
    Solar Guard
    Copyright (C) 2021  Deft Spade

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "player_ship.h"
#include "laser_player.h"
#include "bn_keypad.h"
#include "bn_math.h"
#include <math.h>

player_ship::player_ship(int ship_type, int x_pos, int y_pos)
{
    // Record the ship type in the relevant variable.
    type = ship_type;

    // Set the player ship sprite to that of the selected ship.
    switch (type)
    {
        case 0: player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0); break;
        case 1: player_sprite = bn::sprite_items::spr_sg_ship_2.create_sprite(0,0); break;
        case 2: player_sprite = bn::sprite_items::spr_sg_ship_3.create_sprite(0,0); break;
        case 3: player_sprite = bn::sprite_items::spr_sg_ship_4.create_sprite(0,0); break;
        case 4: player_sprite = bn::sprite_items::spr_sg_ship_5.create_sprite(0,0); break;
        case 5: player_sprite = bn::sprite_items::spr_sg_ship_6.create_sprite(0,0); break;
        case 6: player_sprite = bn::sprite_items::spr_sg_ship_7.create_sprite(0,0); break;
        case 7: player_sprite = bn::sprite_items::spr_sg_ship_8.create_sprite(0,0); break;

        default:
            break;
    }

    // Set various parameters to their maximum.
    gun_energy = gun_energy_max[type];
    engine_fuel = engine_fuel_max[type];

    // Set the player's initial position.
    x = x_pos;
    y = y_pos;
}

void player_ship::movement()
{
    // Turn ship.
    if(bn::keypad::left_held())
    {
        if (bn::fixed(direction + turn_rate[type]).to_double() < 360)
        {
            direction += turn_rate[type];
        }
        else
        {
            direction = direction + turn_rate[type] - 360;
        }
    }
    else if(bn::keypad::right_held())
    {
        if (bn::fixed(direction - turn_rate[type]).to_double() > 0)
        {
            direction -= turn_rate[type];
        }
        else
        {
            direction = direction - turn_rate[type] + 360;
        }
    }

    // Determine curent magnitude and direction for refrence.
    directional_speed = bn::sqrt(speed_x * speed_x + speed_y * speed_y);             // https://www.onlinemathlearning.com/vector-magnitude.html
    mov_angle = atan2(speed_y.to_double(), speed_x.to_double()) * 180 / 3.14159265;  // https://www.cplusplus.com/reference/cmath/atan2/

    // Speed up and slow down.
    if(bn::keypad::r_held() && !engine_overheated && engine_fuel.ceil_integer() > 0)
    {
        // Check for L also being held, engage reverse if so.
        if (bn::keypad::l_held())
        {
            // Determine new x and y speeds.
            // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
            speed_x += accel_back[type] * bn::degrees_cos(direction + 180 % 360);
            speed_y += accel_back[type] * bn::degrees_sin(direction + 180 % 360);

            // Fuel consumption.
            engine_fuel = bn::max(bn::fixed(0), engine_fuel -= engine_fuel_rear_burn[type]);

            // Engine heating.
            engine_heat = bn::min(engine_heat += engine_heat_rear_increase_rate[type], engine_heat_max[type]);
        }
        else
        {
            // Determine new x and y speeds.
            // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
            speed_x += accel_front[type] * bn::degrees_cos(direction);
            speed_y += accel_front[type] * bn::degrees_sin(direction);

            // Fuel consumption.
            engine_fuel = bn::max(bn::fixed(0), engine_fuel -= engine_fuel_front_burn[type]);

            // Engine heating.
            engine_heat = bn::min(engine_heat += engine_heat_front_increase_rate[type], engine_heat_max[type]);
        }

        // Keep speed in check.
        if (directional_speed.ceil_integer() > speed_max[type].floor_integer())
        {
            // Retain direction but reset magnitude to maximum allowed speed.
            // https://stackoverflow.com/questions/41317291/setting-the-magnitude-of-a-2d-vector
            speed_x = speed_x * speed_max[type] / directional_speed;
            speed_y = speed_y * speed_max[type] / directional_speed;
        }
    }
    else
    {
        // Engine cooldown.
        engine_heat = bn::max(bn::fixed(0), engine_heat -= engine_heat_cooldown_rate[type]);

        if(bn::keypad::l_held() && !bn::keypad::r_held())
        {
            // Check if current overall speed is greater than deceleration amount.
            if (directional_speed.to_double() > decel_brake[type].to_double())
            {
                // Apply force that opposes current momentum.
                // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
                speed_x += decel_brake[type] * bn::degrees_cos(mov_angle + 180 % 360);
                speed_y += decel_brake[type] * bn::degrees_sin(mov_angle + 180 % 360);
            }
            else
            {
                // In the event that the current overall speed is as large or smaller than deceleration amount, set speed
                // to 0 to properly stop ship and avoid a slow drift from a flipped speed value that's small but not zero.
                speed_x = 0;
                speed_y = 0;
            }
        }
    }

    // Switch to overheated if engine heat reaches 100%.
    if (!engine_overheated && engine_heat.floor_integer() == engine_heat_max[type].floor_integer())
    {
        engine_overheated = true;
    }

    // Switch back to not being overheated once engine cools down to 0%.
    if (engine_overheated && engine_heat.ceil_integer() == 0)
    {
        engine_overheated = false;
    }

    // Apply Movement
    x += speed_x;
    y -= speed_y;   // Subtracting because y coordinate decreases when going upwards.

    // Update the sprite's position.
    player_sprite.set_x(x);
    player_sprite.set_y(y);
}

void player_ship::animation()
{
    // Swap alternate frame variable for animation.
    if (alternate_ab_frame < 3)
    {
        alternate_ab_frame += 1;
    }
    else
    {
        alternate_ab_frame = 0;
    }

    // Update sprite rotation.
    player_sprite.set_rotation_angle(direction);

    // Engine sprite animation.
    int engine_state_sprite_frame = 0;
    if (!engine_overheated && engine_fuel.ceil_integer() > 0)
    {
        if (bn::keypad::l_held() && bn::keypad::r_held())
        {
            engine_state_sprite_frame = 3 + alternate_ab_frame / 2;
        }
        else if (bn::keypad::r_held())
        {
            engine_state_sprite_frame = 1 + alternate_ab_frame / 2;
        }
    }

    switch (type)
    {
        case 0: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_1.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        case 1: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_2.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        case 2: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_3.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        case 3: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_4.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        case 4: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_5.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        case 5: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_6.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        case 6: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_7.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        case 7: player_sprite.set_tiles(bn::sprite_items::spr_sg_ship_8.tiles_item().create_tiles(engine_state_sprite_frame)); break;
        default: break;
    }
}

void player_ship::fire_control(int &next_laser, const int &number_of_lasers, bn::array<laser_player, 5> &player_lasers)
{
    // Reduce cooldown value.
    if (gun_firing_cooldown != 0)
    {
        gun_firing_cooldown -= 1;
    }

    // Reduce gun heat.
    if (gun_heat.to_double() > gun_heat_cooldown_rate[type].to_double())
    {
        gun_heat -= gun_heat_cooldown_rate[type];
    }
    else
    {
        gun_heat = 0;
    }

    // Set gun to no longer being overheated if it is and heat reaches the cooldown threshold.
    if (gun_overheated && gun_heat.ceil_integer() == engine_heat_cooldown_threshold[type].round_integer())
    {
        gun_overheated = false;
    }

    // Check for necessary conditions.
    if (bn::keypad::a_held() && gun_energy.ceil_integer() > 0 && gun_firing_cooldown == 0 && !gun_overheated)
    {
        // Set cooldown back to full delay;
        gun_firing_cooldown = gun_cooldown_time;

        // Reduce player ship's energy.
        gun_energy -= 1;

        // Play laser sound.
        bn::sound_items::sfx_laser_fire.play();

        // Increase gun heat.
        if (gun_heat.to_double() + gun_heat_increase_rate[type].to_double() < gun_heat_max[type].to_double())
        {
            gun_heat += gun_heat_increase_rate[type];
        }
        else
        {
            gun_heat = gun_heat_max[type];
        }

        // Check if gun heat has reached 100%, set to overheated if so.
        if (gun_heat.to_double() >= gun_heat_max[type].to_double())
        {
            gun_overheated = true;
            gun_heat = gun_heat_max[type];
        }

        // Set the laser active.
        player_lasers[next_laser].fire(0, x.round_integer(), y.round_integer(), speed_x, speed_y, direction);

        // Indicate to use the laser after the recently used one next time.
        if (next_laser != number_of_lasers - 1)
        {
            next_laser += 1;
        }
        else
        {
            next_laser = 0;
        }
    }
}

void player_ship::shield_regeneration()
{    
    if (shields.to_double() < 100 && shields_recharge_delay == 0)
    {
        if (shields_recharge_timer == 0)
        {
            shields += 1;
            shields_recharge_timer = shields_recharge_rate[type];

            if (shields.round_integer() % 5 == 0)
            bn::sound_items::sfx_recharge.play();
        }
        else
        {
            shields_recharge_timer -= 1;
        }
    }
    else
    {
        shields_recharge_delay -= 1;
    }
}

void player_ship::hull_repair()
{
    if (hull_recharge_portion[type] != 0)
    {
        if ((hull.floor_integer() % hull_recharge_portion[type]) != 0)
        {
            if (hull_recharge_timer == 0)
            {
                hull += 1;
                hull_recharge_timer = hull_recharge_rate[type];
            }
            else
            {
                hull_recharge_timer -= 1;
            }
        }
    }
}

void player_ship::damage(bn::fixed amount)
{
    if (shields.to_double() >= amount.to_double())
    {
        shields -= amount;
    }
    else
    {
        if (shields.floor_integer() > 0)
        {
            hull -= (amount - shields) / hull_damage_divider[type].to_double();
            shields = 0;
        }
        else
        {
            hull -= amount / hull_damage_divider[type].to_double();
        }

        if (hull.to_double() < 0)
        {
            hull = 0;
        }
    }

    shields_recharge_delay = shields_recharge_delay_max[type];
    shields_recharge_timer = 0;
    hull_recharge_timer = hull_recharge_rate[type];
}
