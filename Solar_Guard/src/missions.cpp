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

#include "player_ship.h"
#include "pirate_ship.h"
#include "ally_carrier.h"
#include "ally_civillian.h"
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
    bn::array<space_junk, 20> array_orbital_junk = {
        space_junk(655,-950,camera,0),
        space_junk(1260,273,camera,1),
        space_junk(-1695,587,camera,2),
        space_junk(330,-1065,camera,0),
        space_junk(500,482,camera,2),
        space_junk(2457,-1787,camera,2),
        space_junk(1160,100,camera,0),
        space_junk(850,542,camera,2),
        space_junk(975,463,camera,1),
        space_junk(-1922,376,camera,0),
        space_junk(-100,100,camera,1),
        space_junk(-200,-1847,camera,2),
        space_junk(-1013,894,camera,0),
        space_junk(-400,587,camera,2),
        space_junk(-1919,461,camera,1),
        space_junk(-233,140,camera,2),
        space_junk(-1726,1722,camera,0),
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
    player_ship player_ship(ship_selection, 0, 0);

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
        if (player_ship.directional_speed.floor_integer() < player_ship.speed_max.floor_integer())
        player_ship.speed_y -= 0.002;

        // Player operations.
        player_ship.movement();
        player_ship.animation();
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);

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
        if (player_ship.hull == 0)
        {
            return -1;
        }

        // Check for SELECT key indicating user exit.
        if (bn::keypad::select_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

void mission_2(int ship_selection)
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
    const int array_asteroids_size = 20;
    int array_asteroids_left = 20;
    bn::array<asteroid, 20> array_asteroids = {
        asteroid(-1473,-1595,camera,0),
        asteroid(1981,1959,camera,1),
        asteroid(-1036,-1213,camera,1),
        asteroid(353,-1105,camera,0),
        asteroid(909,-1976,camera,0),
        asteroid(-1241,1690,camera,1),
        asteroid(1609,789,camera,0),
        asteroid(-1119,40,camera,0),
        asteroid(759,-86,camera,1),
        asteroid(-1182,671,camera,0),
        asteroid(-1992,-159,camera,1),
        asteroid(1002,-611,camera,1),
        asteroid(1449,-293,camera,0),
        asteroid(-790,-194,camera,1),
        asteroid(-58,61,camera,1),
        asteroid(0,469,camera,0),
        asteroid(-450,-1334,camera,0),
        asteroid(800,100,camera,1),
        asteroid(-1731,1153,camera,1),
        asteroid(333,877,camera,0)
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
    player_ship player_ship(ship_selection, -4800, 4900);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;
    hud_ally HUD_Transport(0, 0);

    // --------------------------------------------------------------------------- //

    // Attach camera to the player ship and transport.
    player_ship.player_sprite.set_camera(camera);
    ally_transport.sprite.set_camera(camera);

    // Play the non-combat gameplay music.
    bgm_escort.play();

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD.draw_hud_objective(2, 50 + bn::fixed(50 * (ally_transport.x / 4900)).round_integer());
        HUD_Transport.update(ally_transport.hull.ceil_integer(), ally_transport.hull_max.ceil_integer());

        // Player operations.
        player_ship.movement();
        player_ship.animation();
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);

        // Transport operations.
        ally_transport.move();
        ally_transport.radar_dot(player_ship);
        ally_transport.map_dot(x_limit.round_integer(), y_limit.round_integer());

        // Asteroid operations.
        for (int i = 0; i < array_asteroids_size; i++)
        {
            array_asteroids[i].radar_dot(player_ship);
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

        bn::core::update();
    }
}

void mission_3(int ship_selection)
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
    player_ship player_ship(ship_selection, 0, 0);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;
    hud_ally HUD_Station(1, 0);

    // --------------------------------------------------------------------------- //

    // Attach camera to the player ship.
    player_ship.player_sprite.set_camera(camera);

    // Play the non-combat gameplay music.
    bgm_solar_conflict.play();

    // Replace the map with the mission specific map.
    HUD.spr_map.set_tiles(bn::sprite_items::spr_hud_map_mission3.tiles_item().create_tiles(0));
    HUD.spr_map.set_palette(bn::sprite_items::spr_hud_map_mission3.palette_item());

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD_Station.update(100,100);

        // Player operations.
        player_ship.movement();
        player_ship.animation();
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);

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

        // Keep player's position within mission bounds.
        player_ship.x = bn::min(bn::max(-x_limit, player_ship.x), x_limit);
        player_ship.y = bn::min(bn::max(-y_limit, player_ship.y), y_limit);

        // Update camera position (preventing it from moving beyond the big background's boundaries).
        bn::fixed cam_x_pos = bn::max(bn::fixed(bn::min(player_ship.x, x_limit - 120)), -x_limit + 120);
        bn::fixed cam_y_pos = bn::max(bn::fixed(bn::min(player_ship.y, y_limit - 80)), -y_limit + 80);
        camera.set_position(cam_x_pos, cam_y_pos);

        bn::core::update();
    }
}

void mission_4(int ship_selection)
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
    player_ship player_ship(ship_selection, 0, 0);

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
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);

        // Player operations.
        player_ship.movement();
        player_ship.animation();
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);

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

        // Keep player's position within mission bounds.
        player_ship.x = bn::min(bn::max(-x_limit, player_ship.x), x_limit);
        player_ship.y = bn::min(bn::max(-y_limit, player_ship.y), y_limit);

        // Update camera position (preventing it from moving beyond the big background's boundaries).
        bn::fixed cam_x_pos = bn::max(bn::fixed(bn::min(player_ship.x, x_limit - 120)), -x_limit + 120);
        bn::fixed cam_y_pos = bn::max(bn::fixed(bn::min(player_ship.y, y_limit - 80)), -y_limit + 80);
        camera.set_position(cam_x_pos, cam_y_pos);

        bn::core::update();
    }
}

void mission_5(int ship_selection)
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
    ally_carrier ally_carrier(x_limit.round_integer(), y_limit.round_integer());

    // Player Ship
    player_ship player_ship(ship_selection, 1500, 1520);

    // Create HUD last so it 'naturally' sits above other sprites.
    heads_up_display HUD;
    hud_ally HUD_Carrier(2, 0);
    hud_ally HUD_Civillian(3, 1);

    // --------------------------------------------------------------------------- //

    // Play the non-combat gameplay music.
    bgm_rescue.play();

    // Replace the map with the mission specific map.
    HUD.spr_map.set_tiles(bn::sprite_items::spr_hud_map_mission5.tiles_item().create_tiles(0));
    HUD.spr_map.set_palette(bn::sprite_items::spr_hud_map_mission5.palette_item());

    // Attach camera to the player ship.
    player_ship.player_sprite.set_camera(camera);

    // Attach the camera to the carrier sprites.
    ally_carrier.sprite1.set_camera(camera);
    ally_carrier.sprite2.set_camera(camera);
    ally_carrier.sprite3.set_camera(camera);

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD_Carrier.update(ally_carrier.hull.ceil_integer(), ally_carrier.hull_max.ceil_integer());
        HUD_Civillian.update(100,100); 

        // Player operations.
        player_ship.movement();
        player_ship.animation();
        player_ship.fire_control(next_laser, array_player_lasers_size, array_player_lasers);

        // Carrier operations.
        ally_carrier.radar_dot(player_ship);

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

        bn::core::update();
    }
}
