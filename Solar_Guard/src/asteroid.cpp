#include "asteroid.h"

#include "bn_math.h"

asteroid::asteroid(int start_x, int start_y, bn::camera_ptr &camera, int asteroid_type)
{
    // Set position.
    x = start_x;
    y = start_y;
    sprite.set_x(x);
    sprite.set_y(y);

    // Set sprite.
    sprite.set_tiles(bn::sprite_items::spr_asteroid.tiles_item().create_tiles(asteroid_type));

    // Set camera.
    sprite.set_camera(camera);
}

void asteroid::radar_dot(player_ship &player_ship)
{
    // Dot only appears on radar if active.
    if (active)
    {
        bn::fixed radar_rel_x = (x - player_ship.x) / 20;
        bn::fixed radar_rel_y = (y - player_ship.y) / 20;
        bn::fixed radar_dis = bn::sqrt(bn::abs(radar_rel_x.round_integer() * radar_rel_x.round_integer()) +
                                       bn::abs(radar_rel_y.round_integer() * radar_rel_y.round_integer()));

        if (radar_dis.round_integer() <= 23)
        {
            sprite_radar_dot.set_visible(true);
            sprite_radar_dot.set_bg_priority(0);
            sprite_radar_dot.set_x(radar_rel_x - 92);
            sprite_radar_dot.set_y(radar_rel_y + 52);
        }
        else
        {
            sprite_radar_dot.set_visible(false);
        }
    }
    else
    {
        sprite_radar_dot.set_visible(false);
    }
}

/*void asteroid::map_dot(int x_lim, int y_lim)
{
    if (active)
    {
        // Map position update.
        sprite_map_dot.set_bg_priority(0);
        sprite_map_dot.set_x(93 + (x / x_lim) * 24);
        sprite_map_dot.set_y(53 + (y / y_lim) * 24);
    }
    else
    {
        // Remove dot from map.
        sprite_map_dot.set_visible(false);
    }
}*/

bool asteroid::check_collision(int x_position, int y_position, int half_width, int half_height)
{
    if (bn::abs(x.round_integer() - x_position) <= half_width && bn::abs(y.round_integer() - y_position) <= half_height)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int asteroid::check_smallest_axis_distance(int x_position, int y_position)
{
    return bn::min(bn::abs(x.round_integer() - x_position), bn::abs(y.round_integer() - y_position));
}
