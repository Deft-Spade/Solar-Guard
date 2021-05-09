#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_earth_horizon.h"

#include "fixed_8x16_sprite_font.h"
#include "variable_8x16_sprite_font.h"

#include "bn_music_item.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"

#include "music.h"

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

    constexpr const bn::fixed text_y_inc = 14;
    constexpr const bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;
}

void scene_music_playback()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_earth_horizon.create_bg(0, -20);

    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
    text_generator.set_center_alignment();
    bn::vector<bn::sprite_ptr, 32> text_sprites;
    text_generator.generate(0, -text_y_limit, "Project: SOLAR GUARD", text_sprites);
    text_generator.generate(0, -6, "Press A to Switch", text_sprites);
    text_generator.generate(0, 6, "to Next Music Track", text_sprites);
    text_generator.generate(0, text_y_limit -10, "Press B to Exit", text_sprites);
    text_generator.generate(0, text_y_limit, "to the Main Menu", text_sprites);

    bn::music::stop();
    bn::music_items::bgm_theme_title.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }

    bn::music::stop();
    bn::music_items::bgm_theme_menu.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }

    bn::music::stop();
    bn::music_items::bgm_theme_upbeat.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }

    bn::music::stop();
    bn::music_items::bgm_tactical.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }

    bn::music::stop();
    bn::music_items::bgm_solar_patrol.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }

    bn::music::stop();
    bn::music_items::bgm_solar_conflict.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }

    bn::music::stop();
    bn::music_items::bgm_solar_somber.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }

    bn::music::stop();
    bn::music_items::bgm_rescue.play();
    bn::core::update();

    while(true) {
        if (bn::keypad::a_pressed()) break;
        if (bn::keypad::b_pressed()) return;
        bn::core::update();
    }
}
