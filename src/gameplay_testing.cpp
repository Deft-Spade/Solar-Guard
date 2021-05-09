#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_title_screen.h"
#include "bn_regular_bg_items_bg_earth_and_sun.h"
#include "bn_regular_bg_items_bg_earth_horizon.h"
#include "bn_regular_bg_items_bg_seamless_stars.h"

#include "fixed_8x16_sprite_font.h"
#include "variable_8x16_sprite_font.h"
#include "bn_sprite_items_spr_player.h"

#include "bn_music_item.h"
#include "bn_music_actions.h"

#include "bn_camera_ptr.h"
#include "bn_camera_actions.h"

#include "gameplay_testing.h"

namespace
{
    constexpr const bn::music_item bgm_solar_conflict(0);
    constexpr const bn::music_item bgm_solar_patrol(1);
    constexpr const bn::music_item bgm_solar_somber(2);
    constexpr const bn::music_item bgm_tactical(3);
    constexpr const bn::music_item bgm_theme_menu(4);
    constexpr const bn::music_item bgm_theme_title(5);
    constexpr const bn::music_item bgm_theme_upbeat(6);
}

void scene_gameplay_testing()
{
    // Set a background for the main menu.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_seamless_stars.create_bg(0, 0);

    // Create the player sprite.
    bn::sprite_ptr player_sprite = bn::sprite_items::spr_player.create_sprite(0,0);

    // Play the non-combat gameplay music.
    bgm_solar_patrol.play();

    // Setup camera.
    bn::camera_ptr camera = bn::camera_ptr::create(0, 0);
    gameplay_bg.set_camera(camera);
    player_sprite.set_camera(camera);

    // Menu operation loop.
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
