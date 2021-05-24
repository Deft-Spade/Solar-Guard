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
#include "bn_sprite_items_spr_player.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

#include "bn_camera_ptr.h"
#include "bn_camera_actions.h"

#include "mission_5.h"
#include "music.h"

void mission_5()
{
    // Set a background for the main menu.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_seamless_stars.create_bg(0, 0);

    // Create the player sprite.
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_player.create_sprite(0,0);

    // Play the non-combat gameplay music.
    bgm_rescue.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_sprite.set_camera(camera);

    // Draw a basic text-based HUD.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 64> text_sprites;
    text_generator.set_left_alignment();
    text_generator.generate(-120, -75, "HUD TEXT TESTING", text_sprites);
    text_generator.generate(-120, -65, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ", text_sprites);
    text_generator.generate(-120, -55, "`~!@#$%^&*()-=_+[]{}\\|;':\",./<>?", text_sprites);

    bn::sprite_text_generator small_text_generator(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> small_text_sprites;
    text_generator.set_left_alignment();
    small_text_generator.generate(-120, 55, "HUD TEXT TESTING", small_text_sprites);
    small_text_generator.generate(-120, 65, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ", small_text_sprites);
    small_text_generator.generate(-120, 75, "`~!@#$%^&*()-=_+[]{}\\|;':\",./<>?", small_text_sprites);

    // Game loop.
    while(! bn::keypad::select_pressed())
    {
        // Move the player.
        if(bn::keypad::left_held())
        {
            player_sprite.set_x(player_sprite.x() - 1);
        }
        else if(bn::keypad::right_held())
        {
            player_sprite.set_x(player_sprite.x() + 1);
        }

        if(bn::keypad::up_held())
        {
            player_sprite.set_y(player_sprite.y() - 1);
        }
        else if(bn::keypad::down_held())
        {
            player_sprite.set_y(player_sprite.y() + 1);
        }

        // Update camera position.
        camera.set_position(player_sprite.x(), player_sprite.y());

        bn::core::update();
    }
}
