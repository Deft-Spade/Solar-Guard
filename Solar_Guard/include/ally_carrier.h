#ifndef ALLY_CARRIER_H
#define ALLY_CARRIER_H

#include "bn_fixed.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_spr_space_carrier.h"

class ally_carrier
{
public:
    bn::fixed hull = 1000;
    bn::fixed hull_max = 1000;
    bn::fixed x = 1000;
    bn::fixed y = 1000;

    bn::sprite_ptr carrier_sprite1 = bn::sprite_items::spr_space_carrier.create_sprite(x, y, 0);
    bn::sprite_ptr carrier_sprite2 = bn::sprite_items::spr_space_carrier.create_sprite(x, y + 64, 1);
    bn::sprite_ptr carrier_sprite3 = bn::sprite_items::spr_space_carrier.create_sprite(x, y + 128, 2);

    ally_carrier();
};

#endif // ALLY_CARRIER_H
