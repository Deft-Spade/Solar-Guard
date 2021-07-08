#ifndef HUD_ALLY_H
#define HUD_ALLY_H

// Butano includes.
#include "bn_sprite_ptr.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_text_generator.h"

// Includes for sprites.
#include "bn_sprite_items_spr_hud_ally_outline.h"
#include "bn_sprite_items_spr_hud_ally_hull.h"
#include "bn_sprite_items_spr_hud_number_hull.h"

class hud_ally
{
public:
    bn::sprite_ptr spr_ally_outline = bn::sprite_items::spr_hud_ally_outline.create_sprite(-94,-22);
    bn::sprite_ptr spr_ally_hull = bn::sprite_items::spr_hud_ally_hull.create_sprite(-87,-18);
    bn::sprite_ptr spr_ally_hull_text = bn::sprite_items::spr_hud_number_hull.create_sprite(-110,-18);

    hud_ally(int ally_type);
    void update(bn::fixed ally_hull);
};

#endif // HUD_ALLY_H
