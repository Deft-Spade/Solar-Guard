#include "player_ship.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_sg_ship_1.h"
#include "bn_sprite_items_spr_sg_ship_2.h"
#include "bn_sprite_items_spr_sg_ship_3.h"
#include "bn_sprite_items_spr_sg_ship_4.h"
#include "bn_sprite_items_spr_sg_ship_5.h"
#include "bn_sprite_items_spr_sg_ship_6.h"
#include "bn_sprite_items_spr_sg_ship_7.h"
#include "bn_sprite_items_spr_sg_ship_8.h"

player_ship::player_ship(int arg_type)
{
    type = arg_type;

    // Set the player ship sprite to that of the selected ship.
    switch (arg_type)
    {
        case 1: player_sprite = bn::sprite_items::spr_sg_ship_1.create_sprite(0,0); break;
        case 2: player_sprite = bn::sprite_items::spr_sg_ship_2.create_sprite(0,0); break;
        case 3: player_sprite = bn::sprite_items::spr_sg_ship_3.create_sprite(0,0); break;
        case 4: player_sprite = bn::sprite_items::spr_sg_ship_4.create_sprite(0,0); break;
        case 5: player_sprite = bn::sprite_items::spr_sg_ship_5.create_sprite(0,0); break;
        case 6: player_sprite = bn::sprite_items::spr_sg_ship_6.create_sprite(0,0); break;
        case 7: player_sprite = bn::sprite_items::spr_sg_ship_7.create_sprite(0,0); break;
        case 8: player_sprite = bn::sprite_items::spr_sg_ship_8.create_sprite(0,0); break;
    }
}

void player_ship::movement()
{

}
