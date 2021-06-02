#ifndef MUSIC_H
#define MUSIC_H

#include "bn_music_item.h"

namespace
{
    constexpr const bn::music_item bgm_escort(0);
    constexpr const bn::music_item bgm_rescue(1);
    constexpr const bn::music_item bgm_solar_conflict(2);
    constexpr const bn::music_item bgm_solar_patrol(3);
    constexpr const bn::music_item bgm_solar_somber(4);
    constexpr const bn::music_item bgm_tactical(5);
    constexpr const bn::music_item bgm_theme_menu(6);
    constexpr const bn::music_item bgm_theme_title(7);
    constexpr const bn::music_item bgm_theme_upbeat(8);
}

void scene_music_playback();

#endif // MUSIC_H
