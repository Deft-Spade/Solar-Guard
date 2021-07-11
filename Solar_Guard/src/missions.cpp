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

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"

#include "bn_regular_bg_items_bg_mission_1.h"
#include "bn_regular_bg_items_bg_stars_blue_background.h"
#include "bn_regular_bg_items_bg_stars_blue_foreground.h"
#include "bn_regular_bg_items_bg_mission_3.h"
#include "bn_regular_bg_items_bg_mission_4.h"
#include "bn_regular_bg_items_bg_mission_5.h"
#include "bn_regular_bg_items_bg_mission_5_background.h"

#include "font_menu.h"
#include "font_menu.h"
#include "font_hud.h"
#include "font_hud_compact.h"
#include "bn_sprite_items_spr_sg_ship_1.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

#include "bn_camera_ptr.h"
#include "bn_camera_actions.h"

#include "missions.h"
#include "music.h"
#include "gameplay.h"
#include "heads_up_display.h"
#include "hud_ally.h"
#include "pause_menu.h"

#include "player_ship.h"
#include "pirate_ship.h"
#include "ally_carrier.h"
#include "ally_civillian.h"
#include "ally_civillian_pod.h"
#include "ally_station.h"
#include "ally_transport.h"
#include "asteroid.h"
#include "space_junk.h"
#include "laser_player.h"

int mission_1(int ship_selection)
{
    // Mission constands.
    const bn::fixed x_limit = 1024;
    const bn::fixed y_limit = 1024;

    // Set a parallax two-layer background.
    bn::regular_bg_ptr gameplay_bg_rear = bn::regular_bg_items::bg_mission_5_background.create_bg(0, 0);
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_1.create_bg(0, 0);

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);

    // Object Creation ----------------------------------------------------------- //

    // Orbital junk.
    const int array_orbital_junk_size = 20;
    int array_orbital_junk_left = 20;
    bn::array<space_junk, array_orbital_junk_size> array_orbital_junk = {
        space_junk(245,-50,camera,0),
        space_junk(865,273,camera,1),
        space_junk(-395,487,camera,2),
        space_junk(330,-148,camera,0),
        space_junk(500,282,camera,2),
        space_junk(272,79,camera,2),
        space_junk(799,100,camera,0),
        space_junk(850,442,camera,2),
        space_junk(975,463,camera,1),
        space_junk(-267,376,camera,0),
        space_junk(-100,100,camera,1),
        space_junk(-387,-7,camera,2),
        space_junk(-115,194,camera,0),
        space_junk(-436,487,camera,2),
        space_junk(-568,461,camera,1),
        space_junk(-233,140,camera,2),
        space_junk(-814,151,camera,0),
        space_junk(-800,325,camera,2),
        space_junk(-838,491,camera,1),
        space_junk(-461,316,camera,2)
    };

    // Player lasers.
    const int array_player_lasers_size = 5;
    int next_laser = 0;
    bn::array<laser_player, 5> array_player_lasers = {
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera)
    };
    player_ship player_ship(ship_selection - 1, 0, 0);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;

    // --------------------------------------------------------------------------- //

    // Attach camera to the player ship.
    player_ship.player_sprite.set_camera(camera);

    // Play the non-combat gameplay music.
    bgm_solar_patrol.play();

    // Replace the map with the mission specific map.
    HUD.spr_map.set_tiles(bn::sprite_items::spr_hud_map_mission1.tiles_item().create_tiles(0));
    HUD.spr_map.set_palette(bn::sprite_items::spr_hud_map_mission1.palette_item());

    // Game loop.
    while(true)
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD.draw_hud_objective(1, 20 - array_orbital_junk_left);

        // Gravitational acceleration downward.
        if (player_ship.directional_speed.floor_integer() < player_ship.speed_max[player_ship.type].floor_integer())
        player_ship.speed_y -= 0.002;

        // Player operations.
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);
        player_ship.movement();
        player_ship.animation();
        player_ship.shield_regeneration();
        player_ship.hull_repair();

        // Player laser operations.
        for (int i = 0; i < array_player_lasers_size; i++)
        {
            // Only operate if active.
            if (array_player_lasers[i].active)
            {
                // Move the lasers forward.
                array_player_lasers[i].move();

                // Check for collision with every piece of orbital junk.
                for (int j = 0; j < array_orbital_junk_size; j++)
                {
                    // Collision with bounding box 16x16 pixels.
                    if (array_player_lasers[i].check_collision(array_orbital_junk[j].x.round_integer() - 6,
                                                               array_orbital_junk[j].y.round_integer() - 6, 14, 14)
                                                               && array_orbital_junk[j].active)
                    {
                        // Make the junk take damage.
                        array_orbital_junk[j].hull -= 5;

                        // Remove the laser since it has hit.
                        array_player_lasers[i].hit();

                        // Play laser hit sound.
                        bn::sound_items::sfx_laser_hit.play();

                        // Check if junk's hull is 0.
                        if (array_orbital_junk[j].hull.ceil_integer() == 0)
                        {
                            // Destroy the junk (set it inactive).
                            array_orbital_junk[j].destroy();

                            // Reduce amount of junk left.
                            array_orbital_junk_left -= 1;
                        }
                    }
                }
            }
        }

        // Space junk operation.
        for (int i = 0; i < array_orbital_junk_size; i++)
        {
            array_orbital_junk[i].radar_dot(player_ship);
            array_orbital_junk[i].map_dot(x_limit.round_integer(), y_limit.round_integer());

            // Only check for collision if active.
            if (array_orbital_junk[i].active)
            {
                // Check for collision with player.
                if (array_orbital_junk[i].check_collision(player_ship.x.round_integer() - 8, player_ship.y.round_integer() - 8, 16, 16))
                {
                    // Destroy the asteroid.
                    array_orbital_junk[i].hull = 0;
                    array_orbital_junk[i].active = false;
                    array_orbital_junk[i].sprite.set_visible(false);

                    // Do damage to the player.
                    player_ship.damage(30);

                    // Play collision sound.
                    bn::sound_items::sfx_collision.play();

                    // Reduce amount of junk left.
                    array_orbital_junk_left -= 1;
                }
            }
        }

        // Remove player ship's momentum if they touch mission bounds.
        if (player_ship.x.ceil_integer() > x_limit.round_integer() || player_ship.x.floor_integer() < -x_limit.round_integer() ||
            player_ship.y.ceil_integer() > y_limit.round_integer() || player_ship.y.floor_integer() < -y_limit.round_integer())
        {
            player_ship.speed_x = 0;
            player_ship.speed_y = 0;
        }

        // Keep player's position within mission bounds.
        player_ship.x = bn::min(bn::max(-x_limit, player_ship.x), x_limit);
        player_ship.y = bn::min(bn::max(-y_limit, player_ship.y), y_limit);

        // Update camera position (preventing it from moving beyond the big background's boundaries).
        bn::fixed cam_x_pos = bn::max(bn::fixed(bn::min(player_ship.x, x_limit - 120)), -x_limit + 120);
        bn::fixed cam_y_pos = bn::max(bn::fixed(bn::min(player_ship.y, y_limit - 80)), -y_limit + 80);
        camera.set_position(cam_x_pos, cam_y_pos);

        // Rear background scrolling at slower speed for parallax.
        gameplay_bg_rear.set_x(-camera.x() / 2);
        gameplay_bg_rear.set_y(-camera.y() / 2);

        // Check for mission completion.
        if (array_orbital_junk_left == 0)
        {
            return 1;
        }

        // Check for mission failure.
        if (player_ship.hull.ceil_integer() == 0)
        {
            return -1;
        }

        // Check for START key, activate pause if pressed.
        if (bn::keypad::start_pressed())
        {
            int pause_selection = pause_menu();

            if (pause_selection == 2)
            {
                return 0;
            }
        }

        bn::core::update();
    }
}

int mission_2(int ship_selection)
{
    // Mission constants.
    const bn::fixed x_limit = 5000;
    const bn::fixed y_limit = 5000;

    // Set a parallax two-layer background.
    bn::regular_bg_ptr gameplay_bg_rear = bn::regular_bg_items::bg_stars_blue_foreground.create_bg(0, 0);
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_stars_blue_background.create_bg(0, 0);

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);

    // Object Creation ----------------------------------------------------------- //

    // Asteroids
    const int array_asteroids_size = 40;
    int array_asteroids_left = 40;
    bn::array<asteroid, array_asteroids_size> array_asteroids = {
        asteroid(657,-634,camera,0),
        asteroid(-743,-758,camera,1),
        asteroid(3095,-3013,camera,1),
        asteroid(3490,-3460,camera,0),
        asteroid(3242,-3256,camera,0),
        asteroid(2166,-877,camera,1),
        asteroid(-3881,762,camera,0),
        asteroid(347,-548,camera,0),
        asteroid(241,-552,camera,1),
        asteroid(2166,-2100,camera,0),
        asteroid(1331,4045,camera,1),
        asteroid(-1494,-158,camera,1),
        asteroid(-455,-684,camera,0),
        asteroid(4525,-731,camera,1),
        asteroid(753,120,camera,1),
        asteroid(3995,-4056,camera,0),
        asteroid(450,-347,camera,0),
        asteroid(-743,794,camera,1),
        asteroid(-256,214,camera,1),
        asteroid(67,-75,camera,0),
        asteroid(1104,-1858,camera,0),
        asteroid(-2344,2454,camera,1),
        asteroid(3432,-3642,camera,1),
        asteroid(-3127,3196,camera,0),
        asteroid(-909,879,camera,0),
        asteroid(1241,-1200,camera,1),
        asteroid(3264,-3222,camera,0),
        asteroid(1119,-1100,camera,0),
        asteroid(2359,-2431,camera,1),
        asteroid(333,-377,camera,0),
        asteroid(-100,150,camera,1),
        asteroid(2247,-2347,camera,1),
        asteroid(2007,-1900,camera,0),
        asteroid(2758,-2769,camera,1),
        asteroid(1894,-1954,camera,1),
        asteroid(-1981,2001,camera,0),
        asteroid(48,-68,camera,0),
        asteroid(-2322,2333,camera,1),
        asteroid(4691,-4652,camera,1),
        asteroid(3245,-3187,camera,0)
    };

    // Transport
    ally_transport ally_transport;

    // Player lasers.
    const int array_player_lasers_size = 5;
    int next_laser = 0;
    bn::array<laser_player, 5> array_player_lasers = {
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera)
    };

    // Player Ship
    player_ship player_ship(ship_selection - 1, -4800, 4900);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;
    hud_ally HUD_Transport(0);

    // --------------------------------------------------------------------------- //

    // Attach camera to the player ship and transport.
    player_ship.player_sprite.set_camera(camera);
    ally_transport.sprite.set_camera(camera);

    // Play the non-combat gameplay music.
    bgm_escort.play();

    // Game loop.
    while(true)
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD.draw_hud_objective(2, 50 + bn::fixed(50 * (ally_transport.x / 4900)).round_integer());
        HUD_Transport.update(ally_transport.hull);

        // Player operations.
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);
        player_ship.movement();
        player_ship.animation();
        player_ship.shield_regeneration();
        player_ship.hull_repair();

        // Transport operations.
        ally_transport.move();
        ally_transport.radar_dot(player_ship);
        ally_transport.map_dot(x_limit.round_integer(), y_limit.round_integer());

        // Asteroid operations.
        for (int i = 0; i < array_asteroids_size; i++)
        {
            // Dot on radar.
            array_asteroids[i].radar_dot(player_ship);
            //array_asteroids[i].map_dot(x_limit.round_integer(), y_limit.round_integer());

            // Only check collisions against player and lasers if near player.
            if (array_asteroids[i].check_smallest_axis_distance(player_ship.x.round_integer(), player_ship.y.round_integer()) < 150 &&
                array_asteroids[i].active)
            {
                // Check for collision with player.
                if (array_asteroids[i].check_collision(player_ship.x.round_integer(), player_ship.y.round_integer(), 25, 25))
                {
                    // Destroy the asteroid.
                    array_asteroids[i].hull = 0;
                    array_asteroids[i].active = false;
                    array_asteroids[i].sprite.set_visible(false);
                    array_asteroids_left -= 1;

                    // Do damage to the player.
                    player_ship.damage(80);

                    // Play collision sound.
                    bn::sound_items::sfx_collision.play();
                }

                // Check for collision with lasers.
                // Lasers have limited range, therefore their check only needs to run when player is close.
                for (int j = 0; j < array_player_lasers_size; j++)
                {
                    // Collision with bounding box 16x16 pixels.
                    if (array_asteroids[i].active &&
                        array_player_lasers[j].check_collision(array_asteroids[i].x.round_integer(),
                                                               array_asteroids[i].y.round_integer(), 20, 20))
                    {
                        // Make the junk take damage.
                        array_asteroids[i].hull -= 5;

                        // Remove the laser since it has hit.
                        array_player_lasers[j].hit();

                        // Check if asteroid's hull is 0.
                        if (array_asteroids[i].hull.ceil_integer() == 0)
                        {
                            // Destroy the asteroid (set it inactive).
                            array_asteroids[i].active = false;
                            array_asteroids[i].sprite.set_visible(false);
                        }

                        // Play collision sound.
                        bn::sound_items::sfx_collision.play();
                    }
                }
            }

            // Only check collisions against transport if near transport.
            if (array_asteroids[i].check_smallest_axis_distance(ally_transport.x.round_integer(), ally_transport.y.round_integer()) < 150 &&
                array_asteroids[i].active)
            {
                // Check for collision with transport.
                if (array_asteroids[i].check_collision(ally_transport.x.round_integer(), ally_transport.y.round_integer(), 25, 25))
                {
                    // Destroy the asteroid.
                    array_asteroids[i].hull = 0;
                    array_asteroids[i].active = false;
                    array_asteroids[i].sprite.set_visible(false);
                    array_asteroids_left -= 1;

                    // Do damage to the transport.
                    ally_transport.hull -= 15;
                    if (ally_transport.hull.to_double() < 0) ally_transport.hull = 0;

                    // Play collision sound if player is nearby.
                    if (array_asteroids[i].check_smallest_axis_distance(player_ship.x.round_integer(), player_ship.y.round_integer()) < 200)
                    {
                        bn::sound_items::sfx_collision.play();
                    }
                }
            }
        }

        // Player laser operations.
        for (int i = 0; i < array_player_lasers_size; i++)
        {
            // Only operate if active.
            if (array_player_lasers[i].active)
            {
                // Move the lasers forward.
                array_player_lasers[i].move();   
            }
        }

        // Remove player ship's momentum if they touch mission bounds.
        if (player_ship.x.ceil_integer() > x_limit.round_integer() || player_ship.x.floor_integer() < -x_limit.round_integer() ||
            player_ship.y.ceil_integer() > y_limit.round_integer() || player_ship.y.floor_integer() < -y_limit.round_integer())
        {
            player_ship.speed_x = 0;
            player_ship.speed_y = 0;
        }

        // Keep player's position within mission bounds.
        player_ship.x = bn::min(bn::max(-x_limit, player_ship.x), x_limit);
        player_ship.y = bn::min(bn::max(-y_limit, player_ship.y), y_limit);

        // Update camera position (preventing it from moving beyond the big background's boundaries).
        bn::fixed cam_x_pos = bn::max(bn::fixed(bn::min(player_ship.x, x_limit - 120)), -x_limit + 120);
        bn::fixed cam_y_pos = bn::max(bn::fixed(bn::min(player_ship.y, y_limit - 80)), -y_limit + 80);
        camera.set_position(cam_x_pos, cam_y_pos);

        // Rear background scrolling at slower speed for parallax.
        gameplay_bg_rear.set_x(-camera.x() / 2);
        gameplay_bg_rear.set_y(-camera.y() / 2);

        // Check for mission completion.
        if (ally_transport.x.floor_integer() == 4900)
        {
            return 1;
        }

        // Check for mission failure.
        if (player_ship.hull.ceil_integer() == 0)
        {
            return -1;
        }

        if (ally_transport.hull.ceil_integer() == 0)
        {
            return -2;
        }

        // Check for START key, activate pause if pressed.
        if (bn::keypad::start_pressed())
        {
            int pause_selection = pause_menu();

            if (pause_selection == 2)
            {
                return 0;
            }
        }

        bn::core::update();
    }
}

int mission_3(int ship_selection)
{
    // Mission constants.
    const bn::fixed x_limit = 2048;
    const bn::fixed y_limit = 2048;

    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_3.create_bg(0, 0);

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);

    // Object Creation ----------------------------------------------------------- //

    // Player lasers.
    const int array_player_lasers_size = 5;
    int next_laser = 0;
    bn::array<laser_player, 5> array_player_lasers = {
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera)
    };

    // Player Ship
    player_ship player_ship(ship_selection - 1, 0, 0);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;
    hud_ally HUD_Station(1);

    // --------------------------------------------------------------------------- //

    // Attach camera to the player ship.
    player_ship.player_sprite.set_camera(camera);

    // Play the non-combat gameplay music.
    bgm_solar_conflict.play();

    // Replace the map with the mission specific map.
    HUD.spr_map.set_tiles(bn::sprite_items::spr_hud_map_mission3.tiles_item().create_tiles(0));
    HUD.spr_map.set_palette(bn::sprite_items::spr_hud_map_mission3.palette_item());

    // Game loop.
    while(true)
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD.draw_hud_objective(3, 0);
        HUD_Station.update(100);

        // Player operations.
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);
        player_ship.movement();
        player_ship.animation();
        player_ship.shield_regeneration();
        player_ship.hull_repair();

        // Player laser operations.
        for (int i = 0; i < array_player_lasers_size; i++)
        {
            // Only operate if active.
            if (array_player_lasers[i].active)
            {
                // Move the lasers forward.
                array_player_lasers[i].move();

                // Check for collision...
                /*for (int j = 0; j < array_orbital_junk_size; j++)
                {
                    // Collision with bounding box 16x16 pixels.
                    if (array_player_lasers[i].check_collision(array_orbital_junk[j].x.round_integer() - 6, array_orbital_junk[j].y.round_integer() - 6, 14, 14))
                    {
                        // Make the junk take damage.
                        array_orbital_junk[j].hull -= 5;

                        // Remove the laser since it has hit.
                        array_player_lasers[i].hit();

                        // Check if junk's hull is 0.
                        if (array_orbital_junk[j].hull.ceil_integer() == 0)
                        {
                            // Destroy the junk (set it inactive).
                            array_orbital_junk[j].destroy();
                        }
                    }
                }*/
            }
        }

        // Remove player ship's momentum if they touch mission bounds.
        if (player_ship.x.ceil_integer() > x_limit.round_integer() || player_ship.x.floor_integer() < -x_limit.round_integer() ||
            player_ship.y.ceil_integer() > y_limit.round_integer() || player_ship.y.floor_integer() < -y_limit.round_integer())
        {
            player_ship.speed_x = 0;
            player_ship.speed_y = 0;
        }

        // Keep player's position within mission bounds.
        player_ship.x = bn::min(bn::max(-x_limit, player_ship.x), x_limit);
        player_ship.y = bn::min(bn::max(-y_limit, player_ship.y), y_limit);

        // Update camera position (preventing it from moving beyond the big background's boundaries).
        bn::fixed cam_x_pos = bn::max(bn::fixed(bn::min(player_ship.x, x_limit - 120)), -x_limit + 120);
        bn::fixed cam_y_pos = bn::max(bn::fixed(bn::min(player_ship.y, y_limit - 80)), -y_limit + 80);
        camera.set_position(cam_x_pos, cam_y_pos);

        // Check for START key, activate pause if pressed.
        if (bn::keypad::start_pressed())
        {
            int pause_selection = pause_menu();

            if (pause_selection == 2)
            {
                return 0;
            }
        }

        bn::core::update();
    }
}

int mission_4(int ship_selection)
{
    // Mission constants.
    const bn::fixed x_limit = 2048;
    const bn::fixed y_limit = 2048;

    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_4.create_bg(0, 0);

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);

    // Object Creation ----------------------------------------------------------- //

    // Player lasers.
    const int array_player_lasers_size = 5;
    int next_laser = 0;
    bn::array<laser_player, 5> array_player_lasers = {
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera)
    };

    // Player Ship
    player_ship player_ship(ship_selection - 1, 0, 0);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;

    // --------------------------------------------------------------------------- //

    // Attach camera to the player ship.
    player_ship.player_sprite.set_camera(camera);

    // Play the non-combat gameplay music.
    bgm_solar_somber.play();

    // Replace the map with the mission specific map.
    HUD.spr_map.set_tiles(bn::sprite_items::spr_hud_map_mission4.tiles_item().create_tiles(0));
    HUD.spr_map.set_palette(bn::sprite_items::spr_hud_map_mission4.palette_item());

    // Game loop.
    while(true)
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD.draw_hud_objective(4, 0);

        // Player operations.
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);
        player_ship.movement();
        player_ship.animation();
        player_ship.shield_regeneration();
        player_ship.hull_repair();

        // Player laser operations.
        for (int i = 0; i < array_player_lasers_size; i++)
        {
            // Only operate if active.
            if (array_player_lasers[i].active)
            {
                // Move the lasers forward.
                array_player_lasers[i].move();

                // Check for collision...
                /*for (int j = 0; j < array_orbital_junk_size; j++)
                {
                    // Collision with bounding box 16x16 pixels.
                    if (array_player_lasers[i].check_collision(array_orbital_junk[j].x.round_integer() - 6, array_orbital_junk[j].y.round_integer() - 6, 14, 14))
                    {
                        // Make the junk take damage.
                        array_orbital_junk[j].hull -= 5;

                        // Remove the laser since it has hit.
                        array_player_lasers[i].hit();

                        // Check if junk's hull is 0.
                        if (array_orbital_junk[j].hull.ceil_integer() == 0)
                        {
                            // Destroy the junk (set it inactive).
                            array_orbital_junk[j].destroy();
                        }
                    }
                }*/
            }
        }

        // Remove player ship's momentum if they touch mission bounds.
        if (player_ship.x.ceil_integer() > x_limit.round_integer() || player_ship.x.floor_integer() < -x_limit.round_integer() ||
            player_ship.y.ceil_integer() > y_limit.round_integer() || player_ship.y.floor_integer() < -y_limit.round_integer())
        {
            player_ship.speed_x = 0;
            player_ship.speed_y = 0;
        }

        // Keep player's position within mission bounds.
        player_ship.x = bn::min(bn::max(-x_limit, player_ship.x), x_limit);
        player_ship.y = bn::min(bn::max(-y_limit, player_ship.y), y_limit);

        // Update camera position (preventing it from moving beyond the big background's boundaries).
        bn::fixed cam_x_pos = bn::max(bn::fixed(bn::min(player_ship.x, x_limit - 120)), -x_limit + 120);
        bn::fixed cam_y_pos = bn::max(bn::fixed(bn::min(player_ship.y, y_limit - 80)), -y_limit + 80);
        camera.set_position(cam_x_pos, cam_y_pos);

        // Check for START key, activate pause if pressed.
        if (bn::keypad::start_pressed())
        {
            int pause_selection = pause_menu();

            if (pause_selection == 2)
            {
                return 0;
            }
        }

        bn::core::update();
    }
}

int mission_5(int ship_selection)
{
    // Mission constants.
    const bn::fixed x_limit = 2048;
    const bn::fixed y_limit = 2048;

    // Set a parallax two-layer background.
    // Rear background is in front this time to make the background start viewable 'through' the sunlight.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_5.create_bg(0, 0);
    bn::regular_bg_ptr gameplay_bg_rear = bn::regular_bg_items::bg_mission_5_background.create_bg(0, 0);

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);

    // Object Creation ----------------------------------------------------------- //

    // Civliian Ship
    ally_civillian ally_civ = ally_civillian(camera);

    // Escape Pods
    const int ally_civillian_pods_size = 3;
    int ally_civillian_pods_left = 3;
    bool player_carrying_pod = false;
    bn::array<ally_civillian_pod, 3> ally_civillian_pods = {
        ally_civillian_pod(-1300, 300, camera, -0.1, -0.3),
        ally_civillian_pod(-1000, -800, camera, -0.2, -0.2),
        ally_civillian_pod(1100, -500, camera, -0.3, -0.1)
    };

    // Player lasers.
    const int array_player_lasers_size = 5;
    int next_laser = 0;
    bn::array<laser_player, 5> array_player_lasers = {
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera),
        laser_player(camera)
    };

    // Solar Guard Carrier
    ally_carrier ally_carrier(x_limit.round_integer(), y_limit.round_integer(), camera);

    // Player Ship
    player_ship player_ship(ship_selection - 1, 1500, 1520);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;
    hud_ally HUD_Carrier(2);

    // --------------------------------------------------------------------------- //

    // Play the non-combat gameplay music.
    bgm_rescue.play();

    // Replace the map with the mission specific map.
    HUD.spr_map.set_tiles(bn::sprite_items::spr_hud_map_mission5.tiles_item().create_tiles(0));
    HUD.spr_map.set_palette(bn::sprite_items::spr_hud_map_mission5.palette_item());

    // Attach camera to the player ship.
    player_ship.player_sprite.set_camera(camera);

    // Game loop.
    while(true)
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD.draw_hud_objective(5, ally_civillian_pods_size - ally_civillian_pods_left);
        HUD_Carrier.update(ally_carrier.hull);

        // Player operations.
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);
        player_ship.movement();
        player_ship.animation();
        player_ship.shield_regeneration();
        player_ship.hull_repair();

        // Carrier operations.
        ally_carrier.radar_dot(player_ship);

        // Civillian ship operations.
        ally_civ.movement();
        ally_civ.radar_dot(player_ship);
        ally_civ.map_dot(x_limit.round_integer(), y_limit.round_integer());

        // Escape pod operations.
        for (int i = 0; i < ally_civillian_pods_size; i++)
        {
            ally_civillian_pods[i].movement(player_ship);
            ally_civillian_pods[i].state_update(player_ship, player_carrying_pod, ally_carrier, ally_civillian_pods_left);
            ally_civillian_pods[i].radar_dot(player_ship);
            ally_civillian_pods[i].map_dot(x_limit.round_integer(), y_limit.round_integer());
        }

        // Player laser operations.
        for (int i = 0; i < array_player_lasers_size; i++)
        {
            // Only operate if active.
            if (array_player_lasers[i].active)
            {
                // Move the lasers forward.
                array_player_lasers[i].move();

                // Check for collision...
                /*for (int j = 0; j < array_orbital_junk_size; j++)
                {
                    // Collision with bounding box 16x16 pixels.
                    if (array_player_lasers[i].check_collision(array_orbital_junk[j].x.round_integer() - 6, array_orbital_junk[j].y.round_integer() - 6, 14, 14))
                    {
                        // Make the junk take damage.
                        array_orbital_junk[j].hull -= 5;

                        // Remove the laser since it has hit.
                        array_player_lasers[i].hit();

                        // Check if junk's hull is 0.
                        if (array_orbital_junk[j].hull.ceil_integer() == 0)
                        {
                            // Destroy the junk (set it inactive).
                            array_orbital_junk[j].destroy();
                        }
                    }
                }*/
            }
        }

        // Remove player ship's momentum if they touch mission bounds.
        if (player_ship.x.ceil_integer() > x_limit.round_integer() || player_ship.x.floor_integer() < -x_limit.round_integer() ||
            player_ship.y.ceil_integer() > y_limit.round_integer() || player_ship.y.floor_integer() < -y_limit.round_integer())
        {
            player_ship.speed_x = 0;
            player_ship.speed_y = 0;
        }

        // Keep player's position within mission bounds.
        player_ship.x = bn::min(bn::max(-x_limit, player_ship.x), x_limit);
        player_ship.y = bn::min(bn::max(-y_limit, player_ship.y), y_limit);

        // Update camera position (preventing it from moving beyond the big background's boundaries).
        bn::fixed cam_x_pos = bn::max(bn::fixed(bn::min(player_ship.x, x_limit - 120)), -x_limit + 120);
        bn::fixed cam_y_pos = bn::max(bn::fixed(bn::min(player_ship.y, y_limit - 80)), -y_limit + 80);
        camera.set_position(cam_x_pos, cam_y_pos);

        // Rear background scrolling at slower speed for parallax.
        gameplay_bg_rear.set_x(-camera.x() / 2);
        gameplay_bg_rear.set_y(-camera.y() / 2);

        // Check for mission completion.
        if (ally_civillian_pods_left == 0)
        {
            return 1;
        }

        // Check for mission failure.
        for (int i = 0; i < ally_civillian_pods_size; i++)
        {
            // Don't register mission failure if a player hits the mission bounds, only if the escape pod drifts out of mission bounds on its own.
            if (ally_civillian_pods[i].status == 1)
            {
                // If an escape pod flies outside of the mission bounds, that results in mission failure.
                if (ally_civillian_pods[i].x.ceil_integer() > x_limit.round_integer() || ally_civillian_pods[i].x.floor_integer() < -x_limit.round_integer() ||
                    ally_civillian_pods[i].y.ceil_integer() > y_limit.round_integer() || ally_civillian_pods[i].y.floor_integer() < -y_limit.round_integer())
                {
                    return -1;
                }
            }
        }

        // Check for START key, activate pause if pressed.
        if (bn::keypad::start_pressed())
        {
            int pause_selection = pause_menu();

            if (pause_selection == 2)
            {
                return 0;
            }
        }

        bn::core::update();
    }
}
