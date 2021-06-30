#ifndef HEADS_UP_DISPLAY_H
#define HEADS_UP_DISPLAY_H

// Butano includes.
#include "bn_sprite_ptr.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_text_generator.h"

// Includes for sprites.
#include "bn_sprite_items_spr_hud_shield.h"
#include "bn_sprite_items_spr_hud_number_shield.h"
#include "bn_sprite_items_spr_hud_hull.h"
#include "bn_sprite_items_spr_hud_number_hull.h"
#include "bn_sprite_items_spr_hud_outline_corner.h"
#include "bn_sprite_items_spr_hud_outline_corner_no_tgt.h"

#include "bn_sprite_items_spr_hud_speed.h"
#include "bn_sprite_items_spr_hud_direction.h"

#include "bn_sprite_items_spr_hud_objective1.h"
#include "bn_sprite_items_spr_hud_objective2.h"

#include "bn_sprite_items_spr_hud_engine.h"
#include "bn_sprite_items_spr_hud_ultility.h"
#include "bn_sprite_items_spr_hud_fuel.h"
#include "bn_sprite_items_spr_hud_number_fuel.h"

#include "bn_sprite_items_spr_hud_energy.h"
#include "bn_sprite_items_spr_hud_number_energy.h"
#include "bn_sprite_items_spr_hud_heat.h"
#include "bn_sprite_items_spr_hud_number_heat.h"

#include "bn_sprite_items_spr_hud_radar.h"

#include "bn_sprite_items_spr_hud_map.h"
#include "bn_sprite_items_spr_hud_map_mission1.h"
#include "bn_sprite_items_spr_hud_map_mission3.h"
#include "bn_sprite_items_spr_hud_map_mission4.h"
#include "bn_sprite_items_spr_hud_map_mission5.h"
#include "bn_sprite_items_spr_hud_map_position.h"

// Includes for font graphics.
#include "font_hud.h"
#include "font_hud_compact.h"

// Code includes.
#include "player_ship.h"

class heads_up_display
{
public:
    heads_up_display();

    // HUD Sprites
    bn::sprite_ptr spr_shield = bn::sprite_items::spr_hud_shield.create_sprite(-78,-75);
    bn::sprite_ptr spr_shield_text = bn::sprite_items::spr_hud_number_shield.create_sprite(-112,-75);
    bn::sprite_ptr spr_hull = bn::sprite_items::spr_hud_hull.create_sprite(-78,-67);
    bn::sprite_ptr spr_hull_text = bn::sprite_items::spr_hud_number_hull.create_sprite(-112,-67);
    bn::sprite_ptr spr_outline_corner = bn::sprite_items::spr_hud_outline_corner.create_sprite(-78,-71);

    bn::sprite_ptr spr_speed = bn::sprite_items::spr_hud_speed.create_sprite(-13,-71);
    bn::sprite_ptr spr_direction = bn::sprite_items::spr_hud_direction.create_sprite(33,-68);

    bn::sprite_ptr spr_shield_tgt = bn::sprite_items::spr_hud_shield.create_sprite(78,-74);
    bn::sprite_ptr spr_hull_tgt = bn::sprite_items::spr_hud_hull.create_sprite(78,-66);
    bn::sprite_ptr spr_outline_corner_target = bn::sprite_items::spr_hud_outline_corner.create_sprite(79,-70);
    bn::sprite_ptr spr_tgt_none = bn::sprite_items::spr_hud_outline_corner_no_tgt.create_sprite(114,-70);

    bn::sprite_ptr spr_objective = bn::sprite_items::spr_hud_objective1.create_sprite(-86, -46);

    bn::sprite_ptr spr_engine = bn::sprite_items::spr_hud_engine.create_sprite(-95,0);
    bn::sprite_ptr spr_fuel = bn::sprite_items::spr_hud_fuel.create_sprite(-55,-24);
    bn::sprite_ptr spr_fuel_text = bn::sprite_items::spr_hud_number_fuel.create_sprite(-79,-8);
    bn::sprite_ptr spr_heat_engine = bn::sprite_items::spr_hud_heat.create_sprite(-55,24);
    bn::sprite_ptr spr_heat_engine_text = bn::sprite_items::spr_hud_number_heat.create_sprite(-79,8);

    bn::sprite_ptr spr_utility = bn::sprite_items::spr_hud_ultility.create_sprite(95,0);
    bn::sprite_ptr spr_ammo_energy = bn::sprite_items::spr_hud_energy.create_sprite(56,-24);
    bn::sprite_ptr spr_ammo_energy_text = bn::sprite_items::spr_hud_number_energy.create_sprite(80,-8);
    bn::sprite_ptr spr_heat_utility = bn::sprite_items::spr_hud_heat.create_sprite(55,24);
    bn::sprite_ptr spr_heat_utility_text = bn::sprite_items::spr_hud_number_heat.create_sprite(80,8);

    bn::sprite_ptr spr_radar = bn::sprite_items::spr_hud_radar.create_sprite(-92,52);

    bn::sprite_ptr spr_map = bn::sprite_items::spr_hud_map.create_sprite(93,53);
    bn::sprite_ptr spr_map_position = bn::sprite_items::spr_hud_map_position.create_sprite(93,53);

    // Create text generators.
    bn::sprite_text_generator text_generator = bn::sprite_text_generator(font_hud);
    bn::sprite_text_generator text_generator_compact = bn::sprite_text_generator(font_hud_compact);

    // Vector for hud text.
    bn::vector<bn::sprite_ptr, 6> hud_text_speed;
    bn::vector<bn::sprite_ptr, 6> hud_text_direction;
    bn::vector<bn::sprite_ptr, 29> hud_text_objectives;
    bn::vector<bn::sprite_ptr, 32> hud_text_coordinates;

    // Functions
    void draw_hud_shields(player_ship &player_ship);
    void draw_hud_hull(player_ship &player_ship);
    void draw_ally_hull();
    void draw_hud_speed(player_ship &player_ship);
    void draw_hud_direction(player_ship &player_ship);
    void draw_hud_target();
    void draw_hud_objective(int mission, int progress);
    void draw_hud_engine_status(player_ship &player_ship);
    void draw_hud_engine_fuel(player_ship &player_ship);
    void draw_hud_engine_heat(player_ship &player_ship);
    void draw_hud_gun_energy(player_ship &player_ship);
    void draw_hud_gun_heat(player_ship &player_ship);
    void draw_hud_map(player_ship &player_ship, bn::fixed x_lim, bn::fixed y_lim);

    void draw_hud(player_ship &player_ship, bn::fixed x_lim, bn::fixed y_lim);

};

#endif // HEADS_UP_DISPLAY_H
