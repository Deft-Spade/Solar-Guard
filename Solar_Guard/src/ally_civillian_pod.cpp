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

#include "ally_civillian_pod.h"

#include "bn_math.h"

ally_civillian_pod::ally_civillian_pod(int init_x, int init_y, bn::camera_ptr &camera, double init_x_speed, double init_y_speed)
{
    // Set initial position.
    x = init_x;
    y = init_y;

    // Set initial drift.
    x_speed = init_x_speed;
    y_speed = init_y_speed;

    // Set camera.
    sprite.set_camera(camera);
}

void ally_civillian_pod::movement(player_ship &player_ship)
{
    // Movement will depend on the status.
    switch (status)
    {
        // If destroyed, no movement required.
        case 0: break;

        // If normal, move as per usual.
        case 1:
            x += x_speed;
            y += y_speed;
        break;

        // If carried by player ship, move with player.
        case 2:
            x = player_ship.x;
            y = player_ship.y;
        break;

        // If returned to carrier, no movement required.
        case 3: break;
    }

    // Update sprite position.
    sprite.set_x(x);
    sprite.set_y(y);
};

/* Return Values
 * -1: Destroyed
 * 0: No change of state.
 * 1: Change from normal to carried by player.
 * 2: Change from carried by player to being placed at Solar Guard space carrier.
 */
void ally_civillian_pod::state_update(player_ship &player_ship, bool &player_carrying_pod, ally_carrier &ally_carrier, int &pods_left)
{
    switch (status)
    {
        // Once destroyed, won't change state again.
        case 0: break;

        case 1:
            // Check for no hull integrity.
            if (hull.ceil_integer() == 0)
            {
                status = 0;
            }

            // Check that player is not already carrying another escape pod.
            if (!player_carrying_pod)
            {
                // If the player is colliding.
                if (x.round_integer() <= player_ship.x.round_integer() + 10 && x.round_integer() >= player_ship.x.round_integer() - 10 &&
                    y.round_integer() <= player_ship.y.round_integer() + 10 && y.round_integer() >= player_ship.y.round_integer() - 10)
                {
                    // Player has picked up escape pod.
                    status = 2;
                    player_carrying_pod = true;
                }
            }
        break;

        case 2:
            // If the player is colliding with the carrier.
            if (ally_carrier.x.round_integer() <= player_ship.x.round_integer() + 32 && ally_carrier.x.round_integer() >= player_ship.x.round_integer() - 32 &&
                ally_carrier.y.round_integer() <= player_ship.y.round_integer() + 64 && ally_carrier.y.round_integer() >= player_ship.y.round_integer() - 64)
            {
                // Player has given the escape pod to the carrier.
                status = 3;
                player_carrying_pod = false;
                pods_left -= 1;
            }
        break;

        // Once returned, won't change state again.
        case 3: break;
    }
}

void ally_civillian_pod::radar_dot(player_ship &player_ship)
{
    // Dot only appears on radar if not destroyed.
    if (status != 0)
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

void ally_civillian_pod::map_dot(int x_lim, int y_lim)
{
    // Dot only appears on map if not destroyed.
    if (status != 0)
    {
        // Map position update.
        sprite_map_dot.set_bg_priority(0);
        sprite_map_dot.set_x(93 + (x / x_lim) * 24);
        sprite_map_dot.set_y(53 + (y / y_lim) * 24);
    }
}
