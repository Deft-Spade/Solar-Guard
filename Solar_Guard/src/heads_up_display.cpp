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
    //spr_shield_tgt.set_horizontal_flip(true);
    //spr_hull_tgt.set_horizontal_flip(true);
    spr_heat_utility.set_horizontal_flip(true);
}

void heads_up_display::draw_hud(player_ship &player_ship, bn::fixed x_lim, bn::fixed y_lim)
{
    // Clear HUD text.
    hud_text.clear();

    // Player Shields
    text_generator_compact_blue_light.set_left_alignment();
    bn::fixed shields_display_value = player_ship.shields / player_ship.shields_max;
    bn::fixed shields_display_sprite = shields_display_value * 25;
    spr_shield.set_tiles(bn::sprite_items::spr_hud_shield.tiles_item().create_tiles(bn::max(0,bn::min(shields_display_sprite.floor_integer(), 25))));
    if (shields_display_value.floor_integer() == 1)
    {
        text_generator_compact_blue_light.generate(-118, -76, "100", hud_text);
    }
    else
    {
        text_generator_blue_light.generate(-118, -76, bn::to_string<3>(bn::fixed(shields_display_value * 100).floor_integer()), hud_text);
    }

    // Player Health
    text_generator_compact_green.set_left_alignment();
    bn::fixed hull_display_value = player_ship.hull / player_ship.hull_max;
    bn::fixed hull_display_sprite = hull_display_value * 25;
    spr_hull.set_tiles(bn::sprite_items::spr_hud_hull.tiles_item().create_tiles(bn::max(0,bn::min(hull_display_sprite.floor_integer(), 25))));
    if (hull_display_value.floor_integer() == 1)
    {
        text_generator_compact_green.generate(-118, -68, "100", hud_text);
    }
    else
    {
        text_generator_green.generate(-118, -68, bn::to_string<3>(bn::fixed(hull_display_value * 100).floor_integer()), hud_text);
    }

    // Ally health (hardcoded for now).
    //text_generator_compact_green.generate(-116, -37, "100", hud_text);

    // Movement Speed
    bn::fixed speed_display_value = (player_ship.directional_speed / 2) * 60;
    text_generator_compact_green.generate(20, -76, bn::to_string<8>(speed_display_value.floor_integer()) + "M/S", hud_text);
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
    text_generator_compact_green.generate(20, -68, bn::to_string<6>(display_dir_mov) + "DEG", hud_text);

    // Target's shields and health (draws hardcoded values for now until targeting is implemented).
    text_generator_green.set_right_alignment();
    text_generator_compact_green.set_right_alignment();
    text_generator_compact_blue_light.set_right_alignment();
    text_generator_green.generate(119, -76, "NO", hud_text);
    text_generator_compact_green.generate(119, -68, "TGT", hud_text);

    // Implement update of engine and utility statuses.
    if (bn::keypad::r_held())
    {
        if (bn::keypad::l_held())
        {
            // Afterburner indicator on HUD.
            spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(1));
        }
        else
        {
            // Engaged indicator on HUD.
            spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(0));
        }
    }
    else if (bn::keypad::l_held())
    {
        // Halt indicator on HUD.
        spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(3));
    }
    else
    {
        // Idle indicator on HUD.
        spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(2));
    }

    // Overheat status override.
    if (player_ship.engine_overheated)
    {
        // Overheat indicator on HUD.
        spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(4));
    }

    // No fuel status override.
    if (player_ship.engine_fuel.ceil_integer() == 0)
    {
        // No fuel indicator on HUD.
        spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(5));
    }


    // Text alignment for engine fuel and engine heat display text.
    text_generator_compact_green_pale.set_right_alignment();
    text_generator_compact_yellow.set_right_alignment();
    text_generator_compact_orange.set_right_alignment();
    text_generator_compact_red.set_right_alignment();

    // Engine Fuel
    bn::fixed fuel_display_sprite = (player_ship.engine_fuel / player_ship.engine_fuel_max) * 23;
    spr_fuel.set_tiles(bn::sprite_items::spr_hud_fuel.tiles_item().create_tiles(bn::max(0,bn::min(fuel_display_sprite.ceil_integer(),23))));
    bn::fixed fuel_display_value = (player_ship.engine_fuel / player_ship.engine_fuel_max) * 100;
    if (player_ship.engine_fuel.ceil_integer() > 0)
    {
        if (fuel_display_sprite.ceil_integer() > 14)
        {
            text_generator_compact_yellow.generate(-71, -12, "FUEL", hud_text);
            text_generator_compact_yellow.generate(-71, -6, bn::to_string<8>(fuel_display_value.ceil_integer()) + "%", hud_text);
        }
        else if (fuel_display_sprite.ceil_integer() > 5)
        {
            text_generator_compact_orange.generate(-71, -12, "FUEL", hud_text);
            text_generator_compact_orange.generate(-71, -6, bn::to_string<8>(fuel_display_value.ceil_integer()) + "%", hud_text);
        }
        else
        {
            text_generator_compact_red.generate(-71, -12, "FUEL", hud_text);
            text_generator_compact_red.generate(-71, -6, bn::to_string<8>(fuel_display_value.ceil_integer()) + "%", hud_text);
        }
    }
    else
    {
        text_generator_compact_red.generate(-71, -12, "NONE", hud_text);
        text_generator_compact_red.generate(-71, -6, bn::to_string<8>(fuel_display_value.ceil_integer()) + "%", hud_text);
    }

    // Engine Heat
    bn::fixed engine_heat_display_sprite = (player_ship.engine_heat / player_ship.engine_heat_max) * 23;
    spr_heat_engine.set_tiles(bn::sprite_items::spr_hud_heat.tiles_item().create_tiles((24 * player_ship.engine_overheated) +
                                                                                       bn::max(0,bn::min(engine_heat_display_sprite.floor_integer(),23))));
    bn::fixed engine_heat_display_value = (player_ship.engine_heat / player_ship.engine_heat_max) * 100;
    if (!player_ship.engine_overheated)
    {
        if (engine_heat_display_sprite.floor_integer() <= 8)
        {
            text_generator_compact_green_pale.generate(-71, 4, "HEAT", hud_text);
            text_generator_compact_green_pale.generate(-71, 10, bn::to_string<8>(engine_heat_display_value.floor_integer()) + "%", hud_text);
        }
        else if (engine_heat_display_sprite.floor_integer() <= 13)
        {
            text_generator_compact_yellow.generate(-71, 4, "HEAT", hud_text);
            text_generator_compact_yellow.generate(-71, 10, bn::to_string<8>(engine_heat_display_value.floor_integer()) + "%", hud_text);
        }
        else if (engine_heat_display_sprite.floor_integer() <= 18)
        {
            text_generator_compact_orange.generate(-71, 4, "HEAT", hud_text);
            text_generator_compact_orange.generate(-71, 10, bn::to_string<8>(engine_heat_display_value.floor_integer()) + "%", hud_text);
        }
        else
        {
            text_generator_compact_red.generate(-71, 4, "HEAT", hud_text);
            text_generator_compact_red.generate(-71, 10, bn::to_string<8>(engine_heat_display_value.floor_integer()) + "%", hud_text);
        }
    }
    else
    {
        text_generator_compact_red.generate(-71, 4, "OVER", hud_text);
        text_generator_compact_red.generate(-71, 10, bn::to_string<8>(engine_heat_display_value.floor_integer()) + "%", hud_text);
    }


    // Coordinates Text
    text_generator_compact_green.set_right_alignment();
    text_generator_compact_green.generate(66, 75, "(" + bn::to_string<16>(player_ship.x.round_integer()) + "," +
                                    bn::to_string<16>(player_ship.y.round_integer()) + ")", hud_text);

    // Radar update needs to be implemented.


    // Map position update.
    spr_map_position.set_x(spr_map.x() + (player_ship.x / x_lim) * 25);
    spr_map_position.set_y(spr_map.y() + (player_ship.y / y_lim) * 25);
    //spr_map_position.set_rotation_angle(angle);
}
