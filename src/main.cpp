#include "bn_core.h"

#include "music.h"

int main()
{
    bn::core::init();

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
