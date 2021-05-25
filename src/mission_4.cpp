#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_seamless_stars.h"

#include "fixed_8x16_sprite_font.h"
#include "variable_8x16_sprite_font.h"
#include "font_hud.h"
#include "font_hud_compact.h"
#include "bn_sprite_items_spr_sg_ship_4.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

#include "bn_camera_ptr.h"
#include "bn_camera_actions.h"

#include "mission_4.h"
#include "music.h"
#include "gameplay.h"

void mission_4()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_seamless_stars.create_bg(0, 0);

    // Create the player sprite.
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_sg_ship_4.create_sprite(0,0);

    // Play the non-combat gameplay music.
    bgm_solar_somber.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_sprite.set_camera(camera);

    // Draw a basic text-based HUD.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 64> text_sprites;

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Draw HUD.
        gameplay_hud_draw(text_generator, text_sprites, player_sprite);

        // Player input.
        gameplay_player_control(player_sprite);

        // Update camera position.
        camera.set_position(player_sprite.x(), player_sprite.y());

        bn::core::update();
    }
}
