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
    active = 1;
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
            active = 0;
            sprite.set_visible(false);
        }
    }
}

bool laser_player::check_collision(int x_position, int y_position, int x_left, int y_top, int x_right, int y_bottom)
{
    if (x_position >= x_left && x_position <= x_right && y_position >= y_top && y_position <= y_bottom)
    {
        return true;
    }
    else
    {
        return false;
    }
}
