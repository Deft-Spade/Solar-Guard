#include "hud_ally.h"

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

hud_ally::hud_ally(int ally_type, int ally_number)
{
    /* Set correct sprite outline according to ally_type's value.
     * 0: Transport
     * 1: Station
     * 2: Carrier
     * 3: Civillian
     */
    spr_ally_outline.set_tiles(bn::sprite_items::spr_hud_ally_outline.tiles_item().create_tiles(ally_type));

    // Reposition sprite if not the first ally.
    if (ally_number != 0)
    {
        spr_ally_outline.set_y(spr_ally_outline.y() + 16);
        spr_ally_hull.set_y(spr_ally_hull.y() + 16);
        spr_ally_hull_text.set_y(spr_ally_hull_text.y() + 16);
    }
}

void hud_ally::update(int ally_hull, int ally_hull_max)
{
    bn::fixed hull_division = ally_hull / ally_hull_max;
    spr_ally_hull.set_tiles(bn::sprite_items::spr_hud_ally_hull.tiles_item().create_tiles(bn::fixed(hull_division * 15).ceil_integer()));
    spr_ally_hull_text.set_tiles(bn::sprite_items::spr_hud_number_hull.tiles_item().create_tiles(bn::fixed(hull_division * 100).ceil_integer()));
}
