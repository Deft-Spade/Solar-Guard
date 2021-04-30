#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "fixed_8x8_sprite_font.h"
#include "fixed_8x16_sprite_font.h"
#include "variable_8x8_sprite_font.h"
#include "variable_8x16_sprite_font.h"

namespace
{
    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    void text_scene_1()
    {
        bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, 0, "Currently Using Butano's Text Example", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START To Switch Text/Scene", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }

    void text_scene_2()
    {
        bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
        text_generator.generate(0, -5, "For Now Scenes Just", text_sprites);
        text_generator.generate(0, 5, "Have Different Text", text_sprites);
        text_generator.generate(0, text_y_limit, "Press START To Switch Text/Scene", text_sprites);

        while(! bn::keypad::start_pressed())
        {
            bn::core::update();
        }
    }
}

int main()
{
    bn::core::init();

    while(true)
    {
        text_scene_1();
        bn::core::update();

        text_scene_2();
        bn::core::update();
    }
}
