#include "heads_up_display.h"

#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_first_attributes.h"
#include "bn_sprite_third_attributes.h"
#include "bn_sprite_position_hbe_ptr.h"
#include "bn_sprite_first_attributes_hbe_ptr.h"
#include "bn_sprite_third_attributes_hbe_ptr.h"
#include "bn_sprite_affine_second_attributes.h"
#include "bn_sprite_regular_second_attributes.h"
#include "bn_sprite_affine_second_attributes_hbe_ptr.h"
#include "bn_sprite_regular_second_attributes_hbe_ptr.h"

#include <math.h>
#include "bn_math.h"
#include "bn_string.h"
#include "bn_log.h"

#include "bn_sprite_text_generator.h"

#include "gameplay.h"
#include "player_ship.h"

heads_up_display::heads_up_display()
{
    // Flip sprites on the right side of the screen that are horizontal mirrors of left side HUD sprites.
    spr_shield_tgt.set_horizontal_flip(true);
    spr_hull_tgt.set_horizontal_flip(true);
    spr_heat_utility.set_horizontal_flip(true);
}

void heads_up_display::draw_hud(player_ship &player_ship, bn::fixed x_lim, bn::fixed y_lim)
{
    // Clear HUD text.
    hud_text.clear();

    // Reset alignment of text.
    text_generator_compact_green.set_left_alignment();
    text_generator_compact_blue_light.set_left_alignment();

    // Player Shields
    if (player_ship.shields / player_ship.shields_max == 1)
    {
        text_generator_compact_blue_light.generate(-118, -76, "100", hud_text);
    }
    else
    {
        text_generator_compact_blue_light.generate(-118, -76, bn::to_string<13>((player_ship.shields / player_ship.shields_max) * 100), hud_text);
    }

    // Player Health
    if (player_ship.hull / player_ship.hull_max == 1)
    {
        text_generator_compact_green.generate(-118, -68, "100", hud_text);
    }
    else
    {
        text_generator_green.generate(-118, -68, bn::to_string<13>((player_ship.hull / player_ship.hull_max) * 100), hud_text);
    }

    // Ally health (hardcoded for now).
    text_generator_compact_green.generate(-116, -37, "100", hud_text);

    // Movement Speed
    bn::fixed speed_display_value = bn::fixed((player_ship.directional_speed / 2) * 60);
    text_generator_compact_green.generate(14, -76, bn::to_string<8>(speed_display_value.floor_integer()) + "M/S", hud_text);
    bn::fixed speed_display_sprite = (player_ship.directional_speed / player_ship.speed_max) * 30;
    spr_speed.set_tiles(bn::sprite_items::spr_hud_speed.tiles_item().create_tiles(bn::min(speed_display_sprite.floor_integer(),30)));

    // Movement Direction
    int display_dir_mov;
    if (player_ship.mov_angle.integer() <= 90)
    {
        display_dir_mov = 90 - player_ship.mov_angle.integer();
    }
    else if (player_ship.mov_angle.integer() <= 0)
    {
        display_dir_mov = 90 + bn::abs(player_ship.mov_angle.integer());
    }
    else
    {
        display_dir_mov = 270 + 180 - player_ship.mov_angle.integer();
    }
    text_generator_compact_green.generate(14, -68, bn::to_string<6>(display_dir_mov) + "DEG", hud_text);

    // Target's shields and health (draws hardcoded values for now until targeting is implemented).
    text_generator_compact_green.set_right_alignment();
    text_generator_compact_blue_light.set_right_alignment();
    text_generator_compact_blue_light.generate(119, -76, "100", hud_text);
    text_generator_compact_green.generate(119, -68, "100", hud_text);

    // Implement update of engine and utility statuses.


    // Coordinates Text
    text_generator_compact_green.set_right_alignment();
    text_generator_compact_green.generate(119, 22, "(" + bn::to_string<13>(player_ship.x.round_integer()) + "," +
                                    bn::to_string<13>(player_ship.y.round_integer()) + ")", hud_text);

    // Radar update needs to be implemented.


    // Map position update.
    spr_map_position.set_x(spr_map.x() + (player_ship.x / x_lim) * 25);
    spr_map_position.set_y(spr_map.y() + (player_ship.y / y_lim) * 25);
    //spr_map_position.set_rotation_angle(angle);
}
