/* Solar Guard by Deft Spade
 * Using Butano by GValiente
 * Made for GBA JAM 2021
 * Source Code and Assets Licensed Under GPL-3.0
 */

/*
    Solar Guard
    Copyright (C) 2021  Deft Spade

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
