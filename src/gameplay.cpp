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

void gameplay_hud_draw(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites, bn::sprite_ptr &player_sprite)
{
    text_sprites.clear();

    // Conversion of numerical integers to characters.
    // https://www.delftstack.com/howto/cpp/how-to-convert-int-to-char-array-in-cpp/
    std::string coord_string = "COORDINATES: (" + std::to_string(player_sprite.x().round_integer()) + "," + std::to_string(player_sprite.y().round_integer()) + ")";
    char const *coord_chars = coord_string.c_str();

    text_generator.generate(-120, -75, coord_chars, text_sprites);
}

void gameplay_player_control(bn::sprite_ptr &player_sprite)
{   
    // Turn ship.
    if(bn::keypad::left_held())
    {        
        if (player_sprite.rotation_angle().ceil_integer() != 359)
        {
            player_sprite.set_rotation_angle(player_sprite.rotation_angle().ceil_integer() + 1);
        }
        else
        {
            player_sprite.set_rotation_angle(0);
        }
    }
    else if(bn::keypad::right_held())
    {
        if (player_sprite.rotation_angle().ceil_integer() != 0)
        {
            player_sprite.set_rotation_angle(player_sprite.rotation_angle().ceil_integer() - 1);
        }
        else
        {
            player_sprite.set_rotation_angle(359);
        }
    }

    // Move forth and back.
    // https://www.physicsclassroom.com/Class/vectors/u3l1e.cfm
    if(bn::keypad::up_held())
    {
        // Adding the vector * cos() part.
        player_sprite.set_x(player_sprite.x() + 1 * bn::degrees_cos(player_sprite.rotation_angle()));

        // Subtracting the vector * sin() part because y coordinate decreases when going upwards.
        player_sprite.set_y(player_sprite.y() - 1 * bn::degrees_sin(player_sprite.rotation_angle()));
    }
    else if(bn::keypad::down_held())
    {
        player_sprite.set_x(player_sprite.x() - 1 * bn::degrees_cos(player_sprite.rotation_angle()));
        player_sprite.set_y(player_sprite.y() + 1 * bn::degrees_sin(player_sprite.rotation_angle()));
    }
}
