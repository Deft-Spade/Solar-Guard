#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include <string>

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
#include "variable_8x16_sprite_font.h"
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
#include "player_ship.h"
#include "pirate_ship.h"
#include "ally_carrier.h"
#include "ally_civillian.h"
#include "ally_station.h"
#include "ally_transport.h"
#include "heads_up_display.h"
#include "hud_ally.h"

void mission_1(int ship_selection)
{
    // Mission constands.
    const bn::fixed x_limit = 1024;
    const bn::fixed y_limit = 1024;

    // Set a parallax two-layer background.
    bn::regular_bg_ptr gameplay_bg_rear = bn::regular_bg_items::bg_mission_5_background.create_bg(0, 0);
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_1.create_bg(0, 0);

    // Create the objects.
    player_ship player_ship(ship_selection, 0, 0);
    heads_up_display HUD;

    // Play the non-combat gameplay music.
    bgm_solar_patrol.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_ship.player_sprite.set_camera(camera);

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);

        // Gravitational acceleration downward.
        if (player_ship.directional_speed.floor_integer() < player_ship.speed_max.floor_integer())
        player_ship.speed_y -= 0.002;

        // Player movement (input and logic is handled in player object).
        player_ship.movement();

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

void mission_2(int ship_selection)
{
    // Mission constants.
    const bn::fixed x_limit = 20480;
    const bn::fixed y_limit = 20480;

    // Set a parallax two-layer background.
    bn::regular_bg_ptr gameplay_bg_rear = bn::regular_bg_items::bg_stars_blue_foreground.create_bg(0, 0);
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_stars_blue_background.create_bg(0, 0);

    // Create the objects.
    player_ship player_ship(ship_selection, 0, 0);
    heads_up_display HUD;
    hud_ally HUD_Transport(0, 0);

    // Play the non-combat gameplay music.
    bgm_escort.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_ship.player_sprite.set_camera(camera);

    // Draw a basic text-based HUD.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 64> text_sprites;

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD_Transport.update(100,100);

        // Player movement (input and logic is handled in player object).
        player_ship.movement();

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

    // Create the objects.
    player_ship player_ship(ship_selection, 0, 0);
    heads_up_display HUD;
    hud_ally HUD_Station(1, 0);

    // Play the non-combat gameplay music.
    bgm_solar_conflict.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_ship.player_sprite.set_camera(camera);

    // Draw a basic text-based HUD.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 64> text_sprites;

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD_Station.update(100,100);

        // Player movement (input and logic is handled in player object).
        player_ship.movement();

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

    // Create the objects.
    player_ship player_ship(ship_selection, 0, 0);
    heads_up_display HUD;

    // Play the non-combat gameplay music.
    bgm_solar_somber.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_ship.player_sprite.set_camera(camera);

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);

        // Player movement (input and logic is handled in player object).
        player_ship.movement();

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

    // Create the objects.
    ally_carrier ally_carrier;
    player_ship player_ship(ship_selection, 1000, 1020);
    heads_up_display HUD;
    hud_ally HUD_Carrier(2, 0);
    hud_ally HUD_Civillian(3, 1);

    // Play the non-combat gameplay music.
    bgm_rescue.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_ship.player_sprite.set_camera(camera);
    ally_carrier.carrier_sprite1.set_camera(camera);
    ally_carrier.carrier_sprite2.set_camera(camera);
    ally_carrier.carrier_sprite3.set_camera(camera);

    // Draw a basic text-based HUD.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 64> text_sprites;

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);
        HUD_Carrier.update(ally_carrier.hull.ceil_integer(), ally_carrier.hull_max.ceil_integer());
        HUD_Civillian.update(100,100);

        // Player movement (input and logic is handled in player object).
        player_ship.movement();

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
