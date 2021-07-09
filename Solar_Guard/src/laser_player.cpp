/* Solar Guard by Deft Spade
 * Using Butano by GValiente
 * Made for GBA JAM 2021
 * Source Code and Assets Licensed Under GPL-3.0
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

#include "laser_player.h"

#include "bn_math.h"

laser_player::laser_player(bn::camera_ptr &camera)
{
    // Set camera.
    sprite.set_camera(camera);

    // Make laser invisible since it is inactive.
    sprite.set_visible(false);
}

void laser_player::fire(int colour, int start_x, int start_y, bn::fixed shooter_x_speed, bn::fixed shooter_y_speed, bn::fixed shooter_direction)
{
    // Set this laser to being active.
    active = true;
    sprite.set_visible(true);

    // Reset remaining distance.
    distance = max_distance;

    // Set position and speed.
    x = start_x;
    y = start_y;
    x_speed = shooter_x_speed;
    y_speed = shooter_y_speed;

    // Set sprite rotation.
    sprite.set_rotation_angle(shooter_direction);

    // Determine new x and y speeds.
    // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
    x_speed += 2 * bn::degrees_cos(shooter_direction.round_integer());
    y_speed += 2 * bn::degrees_sin(shooter_direction.round_integer());
}

void laser_player::move()
{
    // Laser only moves if active.
    if (active)
    {
        // Apply Movement
        x += x_speed;
        y -= y_speed;   // Subtracting because y coordinate decreases when going upwards.

        // Update sprite position.
        sprite.set_x(x);
        sprite.set_y(y);

        // Subtract from distance remaining.
        distance -= 1;

        // Check if max distance reached and deactivate if so.
        if (distance == 0)
        {
            active = false;
            sprite.set_visible(false);
        }
    }
}

bool laser_player::check_collision(int x_position, int y_position, int width, int height)
{
    if (x.round_integer() >= x_position && x.round_integer() <= x_position + width - 1 &&
        y.round_integer() >= y_position && y.round_integer() <= y_position + height - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void laser_player::hit()
{
    active = false;
    sprite.set_visible(false);
}
