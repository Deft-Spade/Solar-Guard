#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_earth_and_sun.h"

#include "music.h"

int main()
{
    bn::core::init();

    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_earth_and_sun.create_bg(0, 15);

    while(true)
    {
        music_scene_1();
        bn::core::update();

        music_scene_2();
        bn::core::update();

        music_scene_3();
        bn::core::update();

        music_scene_4();
        bn::core::update();

        music_scene_5();
        bn::core::update();

        music_scene_6();
        bn::core::update();

        music_scene_7();
        bn::core::update();
    }
}
