#ifndef HEADS_UP_DISPLAY_H
#define HEADS_UP_DISPLAY_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_actions.h"

#include "bn_sprite_items_spr_hud_shield.h"
#include "bn_sprite_items_spr_hud_hull.h"
#include "bn_sprite_items_spr_hud_outline_corner.h"
#include "bn_sprite_items_spr_hud_speed.h"
#include "bn_sprite_items_spr_hud_ally_outline.h"
#include "bn_sprite_items_spr_hud_ally_hull.h"
#include "bn_sprite_items_spr_hud_engine.h"
#include "bn_sprite_items_spr_hud_ultility.h"
#include "bn_sprite_items_spr_hud_fuel.h"
#include "bn_sprite_items_spr_hud_ammo.h"
#include "bn_sprite_items_spr_hud_energy.h"
#include "bn_sprite_items_spr_hud_heat.h"
#include "bn_sprite_items_spr_hud_heat_overheat.h"
#include "bn_sprite_items_spr_hud_radar.h"
#include "bn_sprite_items_spr_hud_map.h"
#include "bn_sprite_items_spr_hud_map_position.h"

#include "font_hud_red.h"
#include "font_hud_orange.h"
#include "font_hud_yellow.h"
#include "font_hud_yellow_green.h"
#include "font_hud_green.h"
#include "font_hud_green_pale.h"
#include "font_hud_blue_light.h"
#include "font_hud_blue_medium.h"
#include "font_hud_blue_dark.h"
#include "font_hud_purple.h"
#include "font_hud_pink.h"
#include "font_hud_white.h"
#include "font_hud_compact_red.h"
#include "font_hud_compact_orange.h"
#include "font_hud_compact_yellow.h"
#include "font_hud_compact_yellow_green.h"
#include "font_hud_compact_green.h"
#include "font_hud_compact_green_pale.h"
#include "font_hud_compact_blue_light.h"
#include "font_hud_compact_blue_medium.h"
#include "font_hud_compact_blue_dark.h"
#include "font_hud_compact_purple.h"
#include "font_hud_compact_pink.h"
#include "font_hud_compact_white.h"

#include "bn_sprite_text_generator.h"
#include "player_ship.h"

class heads_up_display
{
public:
    heads_up_display();

    // HUD Sprites
    bn::sprite_ptr spr_shield = bn::sprite_items::spr_hud_shield.create_sprite(-78,-75);
    bn::sprite_ptr spr_hull = bn::sprite_items::spr_hud_hull.create_sprite(-78,-67);
    bn::sprite_ptr spr_outline_corner = bn::sprite_items::spr_hud_outline_corner.create_sprite(-78,-71);
    bn::sprite_ptr spr_speed = bn::sprite_items::spr_hud_speed.create_sprite(-12,-71);
    bn::sprite_ptr spr_shield_tgt = bn::sprite_items::spr_hud_shield.create_sprite(80,-75);
    bn::sprite_ptr spr_hull_tgt = bn::sprite_items::spr_hud_hull.create_sprite(80,-67);
    bn::sprite_ptr spr_outline_corner_target = bn::sprite_items::spr_hud_outline_corner.create_sprite(80,-71);
    //bn::sprite_ptr spr_ally_outline = bn::sprite_items::spr_hud_ally_outline.create_sprite(-94,-40);
    //bn::sprite_ptr spr_ally_hull = bn::sprite_items::spr_hud_ally_hull.create_sprite(-87,-36);
    bn::sprite_ptr spr_engine = bn::sprite_items::spr_hud_engine.create_sprite(-95,0);
    bn::sprite_ptr spr_fuel = bn::sprite_items::spr_hud_fuel.create_sprite(-55,-24);
    bn::sprite_ptr spr_heat_engine = bn::sprite_items::spr_hud_heat.create_sprite(-55,24);
    bn::sprite_ptr spr_utility = bn::sprite_items::spr_hud_ultility.create_sprite(95,0);
    bn::sprite_ptr spr_ammo_energy = bn::sprite_items::spr_hud_ammo.create_sprite(56,-24);
    bn::sprite_ptr spr_heat_utility = bn::sprite_items::spr_hud_heat.create_sprite(55,24);
    bn::sprite_ptr spr_radar = bn::sprite_items::spr_hud_radar.create_sprite(-92,52);
    const bn::sprite_ptr spr_map = bn::sprite_items::spr_hud_map.create_sprite(93,53);
    bn::sprite_ptr spr_map_position = bn::sprite_items::spr_hud_map_position.create_sprite(93,53);

    // Create text generators.
    bn::sprite_text_generator text_generator_red = bn::sprite_text_generator(font_hud_red);
    bn::sprite_text_generator text_generator_orange = bn::sprite_text_generator(font_hud_orange);
    bn::sprite_text_generator text_generator_yellow = bn::sprite_text_generator(font_hud_yellow);
    bn::sprite_text_generator text_generator_yellow_green = bn::sprite_text_generator(font_hud_yellow_green);
    bn::sprite_text_generator text_generator_green = bn::sprite_text_generator(font_hud_green);
    bn::sprite_text_generator text_generator_green_pale = bn::sprite_text_generator(font_hud_green_pale);
    bn::sprite_text_generator text_generator_blue_light = bn::sprite_text_generator(font_hud_blue_light);
    //bn::sprite_text_generator text_generator_blue_medium = bn::sprite_text_generator(font_hud_blue_medium);
    //bn::sprite_text_generator text_generator_blue_dark = bn::sprite_text_generator(font_hud_blue_dark);
    //bn::sprite_text_generator text_generator_purple = bn::sprite_text_generator(font_hud_purple);
    //bn::sprite_text_generator text_generator_pink = bn::sprite_text_generator(font_hud_pink);
    //bn::sprite_text_generator text_generator_white = bn::sprite_text_generator(font_hud_white);
    bn::sprite_text_generator text_generator_compact_red = bn::sprite_text_generator(font_hud_compact_red);
    bn::sprite_text_generator text_generator_compact_orange = bn::sprite_text_generator(font_hud_compact_orange);
    bn::sprite_text_generator text_generator_compact_yellow = bn::sprite_text_generator(font_hud_compact_yellow);
    //bn::sprite_text_generator text_generator_compact_yellow_green = bn::sprite_text_generator(font_hud_compact_yellow_green);
    bn::sprite_text_generator text_generator_compact_green = bn::sprite_text_generator(font_hud_compact_green);
    bn::sprite_text_generator text_generator_compact_green_pale = bn::sprite_text_generator(font_hud_compact_green_pale);
    bn::sprite_text_generator text_generator_compact_blue_light = bn::sprite_text_generator(font_hud_compact_blue_light);
    //bn::sprite_text_generator text_generator_compact_blue_medium = bn::sprite_text_generator(font_hud_compact_blue_medium);
    //bn::sprite_text_generator text_generator_compact_blue_dark = bn::sprite_text_generator(font_hud_compact_blue_dark);
    //bn::sprite_text_generator text_generator_compact_purple = bn::sprite_text_generator(font_hud_compact_purple);
    //bn::sprite_text_generator text_generator_compact_pink = bn::sprite_text_generator(font_hud_compact_pink);
    //bn::sprite_text_generator text_generator_compact_white = bn::sprite_text_generator(font_hud_compact_white);

    // Vector for hud text.
    bn::vector<bn::sprite_ptr, 64> hud_text;

    // Functions
    void draw_hud(player_ship &player_ship, bn::fixed x_lim, bn::fixed y_lim);
};

#endif // HEADS_UP_DISPLAY_H
