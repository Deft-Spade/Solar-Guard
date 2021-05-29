#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_math.h"

#include <string>

#include "gameplay.h"
#include "player_ship.h"

void gameplay_hud_draw(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites, bn::fixed x, bn::fixed y)
{
    text_sprites.clear();

    // Conversion of numerical integers to characters.
    // https://www.delftstack.com/howto/cpp/how-to-convert-int-to-char-array-in-cpp/
    std::string coord_string = "COORDINATES: (" + std::to_string(x.round_integer()) + "," + std::to_string(y.round_integer()) + ")";
    char const *coord_chars = coord_string.c_str();

    text_generator.generate(-120, -75, coord_chars, text_sprites);
}

void gameplay_player_control(player_ship &player_ship)
{   
    // Turn ship.
    if(bn::keypad::left_held())
    {        
        if (player_ship.dir_facing.ceil_integer() != 359)
        {
            player_ship.dir_facing += 1;
        }
        else
        {
            player_ship.dir_facing = 0;
        }
    }
    else if(bn::keypad::right_held())
    {
        if (player_ship.dir_facing.ceil_integer() != 0)
        {
            player_ship.dir_facing -= 1;
        }
        else
        {
            player_ship.dir_facing = 359;
        }
    }

    // Update sprite rotation.
    player_ship.player_sprite.set_rotation_angle(player_ship.dir_facing);

    // Move forth and back.
    // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
    if(bn::keypad::up_held())
    {
        // Adding the vector * cos() part.
        player_ship.x += 1 * bn::degrees_cos(player_ship.dir_facing);

        // Subtracting the vector * sin() part because y coordinate decreases when going upwards.
        player_ship.y -= 1 * bn::degrees_sin(player_ship.dir_facing);
    }
    else if(bn::keypad::down_held())
    {
        player_ship.x -= 1 * bn::degrees_cos(player_ship.dir_facing);
        player_ship.y += 1 * bn::degrees_sin(player_ship.dir_facing);
    }

    // Update the sprite's position.
    player_ship.player_sprite.set_x(player_ship.x);
    player_ship.player_sprite.set_y(player_ship.y);
}
