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
#include "bn_regular_bg_items_bg_mission_5.h"
#include "bn_regular_bg_items_bg_mission_5_background.h"

#include "fixed_8x16_sprite_font.h"
#include "variable_8x16_sprite_font.h"
#include "font_hud_green.h"
#include "bn_sprite_items_spr_sg_ship_5.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

#include "bn_camera_ptr.h"
#include "bn_camera_actions.h"

#include "mission_5.h"
#include "music.h"
#include "gameplay.h"
#include "player_ship.h"
#include "heads_up_display.h"

void mission_5()
{
    // Mission constants.
    const bn::fixed x_limit = 2048;
    const bn::fixed y_limit = 2048;

    // Set a parallax two-layer background.
    // Rear background is in front this time to make the background start viewable 'through' the sunlight.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_5.create_bg(0, 0);
    bn::regular_bg_ptr gameplay_bg_rear = bn::regular_bg_items::bg_mission_5_background.create_bg(0, 0);

    // Create the objects.
    player_ship player_ship(5);
    heads_up_display HUD;

    // Play the non-combat gameplay music.
    bgm_rescue.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_ship.player_sprite.set_camera(camera);

    // Draw a basic text-based HUD.
    bn::sprite_text_generator text_generator(font_hud_green);
    bn::vector<bn::sprite_ptr, 64> text_sprites;

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        HUD.draw_hud(player_ship, x_limit, y_limit);

        // Player movement (input and logic is handled in player object).
        player_ship.movement();

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
