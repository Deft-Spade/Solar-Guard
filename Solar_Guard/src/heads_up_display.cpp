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

void heads_up_display::draw_hud_shields(player_ship &player_ship)
{
    // Player Shields
    spr_shield.set_tiles(bn::sprite_items::spr_hud_shield.tiles_item().create_tiles(bn::max(0,bn::min(player_ship.shields.ceil_integer() / 4 +
                                                                                                      bn::min(player_ship.shields.ceil_integer() % 4, 1), 25))));
    spr_shield_text.set_tiles(bn::sprite_items::spr_hud_number_shield.tiles_item().create_tiles(bn::max(0,bn::min(player_ship.shields.ceil_integer(), 100))));
}

void heads_up_display::draw_hud_hull(player_ship &player_ship)
{
    // Player Hull
    spr_hull.set_tiles(bn::sprite_items::spr_hud_hull.tiles_item().create_tiles(bn::max(0,bn::min(player_ship.hull.ceil_integer() / 4 +
                                                                                                  bn::min(player_ship.hull.ceil_integer() % 4, 1), 25))));
    spr_hull_text.set_tiles(bn::sprite_items::spr_hud_number_hull.tiles_item().create_tiles(bn::max(0,bn::min(player_ship.hull.ceil_integer(), 100))));
}

void heads_up_display::draw_hud_speed(player_ship &player_ship)
{
    // Clear HUD text.
    hud_text_speed.clear();

    // Movement Speed
    bn::fixed speed_display_value = (player_ship.directional_speed / 2) * 60;
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(91, -76, bn::to_string<8>(speed_display_value.floor_integer()) + "M/S", hud_text_speed);
    bn::fixed speed_display_sprite = (player_ship.directional_speed / player_ship.speed_max[player_ship.type]) * 30;
    spr_speed.set_tiles(bn::sprite_items::spr_hud_speed.tiles_item().create_tiles(bn::min(speed_display_sprite.floor_integer(),30)));
}

void heads_up_display::draw_hud_direction(player_ship &player_ship)
{
    // Clear HUD text.
    //hud_text_direction.clear();

    // Movement Direction
    bn::fixed display_dir_mov;
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

    //text_generator_compact.set_left_alignment();
    //text_generator_compact.generate(20, -68, bn::to_string<6>(display_dir_mov) + "DEG", hud_text_direction);

    spr_direction.set_tiles(bn::sprite_items::spr_hud_direction.tiles_item().create_tiles(bn::min(bn::fixed((display_dir_mov.to_double() / 360) * 40).round_integer(),39)));
}

void heads_up_display::draw_hud_target()
{
    // Target's shields and health.
    // Write code to manage this here when targeting implemented.
}

void heads_up_display::draw_hud_objective(int mission, int progress)
{
    // Objective display on HUD.
    switch (mission)
    {
        case 1: spr_objective.set_tiles(bn::sprite_items::spr_hud_objective1.tiles_item().create_tiles(progress)); break;
        case 2: spr_objective.set_tiles(bn::sprite_items::spr_hud_objective2.tiles_item().create_tiles(progress)); break;
        case 3: spr_objective.set_tiles(bn::sprite_items::spr_hud_objective3.tiles_item().create_tiles(progress)); break;
        case 4: spr_objective.set_tiles(bn::sprite_items::spr_hud_objective4.tiles_item().create_tiles(progress)); break;
        case 5: spr_objective.set_tiles(bn::sprite_items::spr_hud_objective5.tiles_item().create_tiles(progress)); break;
        default: break;
    }
}

void heads_up_display::draw_hud_engine_status(player_ship &player_ship)
{
    // Update of engine status.
    if (player_ship.engine_fuel.ceil_integer() == 0)
    {
        // No fuel indicator on HUD.
        spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(5));
    }
    else if (player_ship.engine_overheated)
    {
        // Overheat indicator on HUD.
        spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(4));
    }
    else if (bn::keypad::r_held())
    {
        if (bn::keypad::l_held())
        {
            // Reverse indicator on HUD.
            spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(2));
        }
        else
        {
            // Active indicator on HUD.
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
        spr_engine.set_tiles(bn::sprite_items::spr_hud_engine.tiles_item().create_tiles(1));
    }
}

void heads_up_display::draw_hud_engine_fuel(player_ship &player_ship)
{
    // Engine Fuel
    bn::fixed fuel_division = player_ship.engine_fuel / player_ship.engine_fuel_max[player_ship.type];
    bn::fixed fuel_display_value = fuel_division * 100;

    bn::fixed fuel_display_sprite;
    if (fuel_display_value.ceil_integer() > 60)
    {
        fuel_display_sprite = 14 + ((fuel_display_value.ceil_integer() - 60) / (bn::fixed)40) * 9;
    }
    else if (fuel_display_value.ceil_integer() > 20)
    {
        fuel_display_sprite = 5 + ((fuel_display_value.ceil_integer() - 20) / (bn::fixed)40) * 9;
    }
    else
    {
        fuel_display_sprite = (fuel_display_value.ceil_integer() / (bn::fixed)20) * 5;
    }

    spr_fuel.set_tiles(bn::sprite_items::spr_hud_fuel.tiles_item().create_tiles(bn::max(0,bn::min(fuel_display_sprite.ceil_integer(), 23))));
    spr_fuel_text.set_tiles(bn::sprite_items::spr_hud_number_fuel.tiles_item().create_tiles(fuel_display_value.ceil_integer()));
}

void heads_up_display::draw_hud_engine_heat(player_ship &player_ship)
{
    // Engine Heat
    bn::fixed engine_heat_division = player_ship.engine_heat / player_ship.engine_heat_max[player_ship.type];
    bn::fixed engine_heat_display_value = engine_heat_division * 100;

    bn::fixed engine_heat_display_sprite;
    if (engine_heat_display_value.floor_integer() >= 80)
    {
        engine_heat_display_sprite = 19 + ((engine_heat_display_value.floor_integer() - 80) / (bn::fixed)20) * 5;
        if (engine_heat_display_sprite.floor_integer() == 24) engine_heat_display_sprite = 23;
    }
    else if (engine_heat_display_value.floor_integer() >= 60)
    {
        engine_heat_display_sprite = 14 + ((engine_heat_display_value.floor_integer() - 60) / (bn::fixed)20) * 5;
    }
    else if (engine_heat_display_value.floor_integer() >= 40)
    {
        engine_heat_display_sprite = 9 + ((engine_heat_display_value.floor_integer() - 40) / (bn::fixed)20) * 5;
    }
    else
    {
        engine_heat_display_sprite = (engine_heat_display_value.floor_integer() / (bn::fixed)40) * 9;
    }

    spr_heat_engine.set_tiles(bn::sprite_items::spr_hud_heat.tiles_item().create_tiles((24 * player_ship.engine_overheated) +
                                                                                       bn::max(0,bn::min(engine_heat_display_sprite.floor_integer(),23))));
    spr_heat_engine_text.set_tiles(bn::sprite_items::spr_hud_number_heat.tiles_item().create_tiles(
                                       engine_heat_display_value.floor_integer() + player_ship.engine_overheated * 100));
}

void heads_up_display::draw_hud_gun_energy(player_ship &player_ship)
{
    // Engine Fuel
    bn::fixed energy_division = player_ship.gun_energy / player_ship.gun_energy_max[player_ship.type];
    bn::fixed energy_display_value = energy_division * 100;

    bn::fixed energy_display_sprite;
    if (energy_display_value.ceil_integer() > 60)
    {
        energy_display_sprite = 14 + ((energy_display_value.ceil_integer() - 60) / (bn::fixed)40) * 9;
    }
    else if (energy_display_value.ceil_integer() > 20)
    {
        energy_display_sprite = 5 + ((energy_display_value.ceil_integer() - 20) / (bn::fixed)40) * 9;
    }
    else
    {
        energy_display_sprite = (energy_display_value.ceil_integer() / (bn::fixed)20) * 5;
    }

    spr_ammo_energy.set_tiles(bn::sprite_items::spr_hud_energy.tiles_item().create_tiles(bn::max(0,bn::min(energy_display_sprite.ceil_integer(), 23))));
    spr_ammo_energy_text.set_tiles(bn::sprite_items::spr_hud_number_energy.tiles_item().create_tiles(energy_display_value.ceil_integer()));
}

void heads_up_display::draw_hud_gun_heat(player_ship &player_ship)
{
    // Gun Heat
    bn::fixed gun_heat_division = player_ship.gun_heat / player_ship.gun_heat_max[player_ship.type];
    bn::fixed gun_heat_display_value = gun_heat_division * 100;

    bn::fixed gun_heat_display_sprite;
    if (gun_heat_display_value.floor_integer() >= 80)
    {
        gun_heat_display_sprite = 19 + ((gun_heat_display_value.floor_integer() - 80) / (bn::fixed)20) * 5;
        if (gun_heat_display_sprite.floor_integer() == 24) gun_heat_display_sprite = 23;
    }
    else if (gun_heat_display_value.floor_integer() >= 60)
    {
        gun_heat_display_sprite = 14 + ((gun_heat_display_value.floor_integer() - 60) / (bn::fixed)20) * 5;
    }
    else if (gun_heat_display_value.floor_integer() >= 40)
    {
        gun_heat_display_sprite = 9 + ((gun_heat_display_value.floor_integer() - 40) / (bn::fixed)20) * 5;
    }
    else
    {
        gun_heat_display_sprite = (gun_heat_display_value.floor_integer() / (bn::fixed)40) * 9;
    }

    spr_heat_utility.set_tiles(bn::sprite_items::spr_hud_heat.tiles_item().create_tiles((24 * player_ship.gun_overheated) +
                                                                                       bn::max(0,bn::min(gun_heat_display_sprite.floor_integer(),23))));
    spr_heat_utility_text.set_tiles(bn::sprite_items::spr_hud_number_heat.tiles_item().create_tiles(
                                       gun_heat_display_value.floor_integer() + player_ship.gun_overheated * 100));
}

void heads_up_display::draw_hud_map(player_ship &player_ship, bn::fixed x_lim, bn::fixed y_lim)
{
    // Clear HUD text.
    //hud_text_coordinates.clear();

    // Coordinates Text
    //text_generator_compact.set_right_alignment();
    //text_generator_compact.generate(66, 75, "(" + bn::to_string<16>(player_ship.x.round_integer()) + "," +
    //                                bn::to_string<16>(player_ship.y.round_integer()) + ")", hud_text_coordinates);

    // Map position update.
    spr_map_position.set_x(spr_map.x() + (player_ship.x / x_lim) * 24);
    spr_map_position.set_y(spr_map.y() + (player_ship.y / y_lim) * 24);
    //spr_map_position.set_rotation_angle(player_ship.direction);
}

void heads_up_display::draw_hud(player_ship &player_ship, bn::fixed x_lim, bn::fixed y_lim)
{
    draw_hud_shields(player_ship);
    draw_hud_hull(player_ship);
    draw_hud_speed(player_ship);
    draw_hud_direction(player_ship);
    draw_hud_target();
    draw_hud_engine_status(player_ship);
    draw_hud_engine_fuel(player_ship);
    draw_hud_engine_heat(player_ship);
    draw_hud_gun_energy(player_ship);
    draw_hud_gun_heat(player_ship);
    draw_hud_map(player_ship, x_lim, y_lim);
}
