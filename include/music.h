#ifndef MUSIC_H
#define MUSIC_H

#include "bn_music_item.h"

namespace
{
    constexpr const bn::music_item bgm_rescue(0);
    constexpr const bn::music_item bgm_solar_conflict(1);
    constexpr const bn::music_item bgm_solar_patrol(2);
    constexpr const bn::music_item bgm_solar_somber(3);
    constexpr const bn::music_item bgm_tactical(4);
    constexpr const bn::music_item bgm_theme_menu(5);
    constexpr const bn::music_item bgm_theme_title(6);
    constexpr const bn::music_item bgm_theme_upbeat(7);
}

void scene_music_playback();

#endif // MUSIC_H
