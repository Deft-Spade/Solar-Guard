#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_grid.h"

#include "font_menu.h"
#include "variable_8x16_sprite_font.h"

#include "bn_music_item.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"

#include "music.h"

namespace
{
    constexpr const bn::fixed screen_y_limit = (bn::display::height() / 2);
}

void switch_track(bn::music_item track_to_play)
{
    bn::music::stop();
    track_to_play.play();
    bn::core::update();
}

void scene_music_playback()
{
    // Menu operation variables.
    int selected_track = 1;
    const int max_tracks = 9;

    // The background.
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_grid.create_bg(0, -20);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(variable_8x16_sprite_font);
    text_generator.set_center_alignment();
    bn::vector<bn::sprite_ptr, 32> text_menu;
    bn::vector<bn::sprite_ptr, 32> text_song;

    // Menu title and controls text.
    text_generator.generate(0, -screen_y_limit + 10, "Music Playback", text_menu);
    text_generator.generate(0, screen_y_limit - 30, "Press LEFT/RIGHT to Switch Tracks", text_menu);
    text_generator.generate(0, screen_y_limit - 20, "Press A to Pause/Resume Playback", text_menu);
    text_generator.generate(0, screen_y_limit - 10, "Press B to Return to Main Menu", text_menu);

    while (true)
    {
        // Switch music track.
        switch (selected_track)
        {
            case 1:
                switch_track(bgm_theme_title);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Title Screen Track", text_song);
                break;

            case 2:
                switch_track(bgm_theme_menu);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Main Menu Track", text_song);
                break;

            case 3:
                switch_track(bgm_theme_upbeat);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Information Track", text_song);
                break;

            case 4:
                switch_track(bgm_tactical);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Mission Briefing Track", text_song);
                break;

            case 5:
                switch_track(bgm_solar_patrol);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Mission 1 Track", text_song);
                break;

            case 6:
                switch_track(bgm_escort);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Mission 2 Track", text_song);
                break;

            case 7:
                switch_track(bgm_solar_conflict);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Mission 3 Track", text_song);
                break;

            case 8:
                switch_track(bgm_solar_somber);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Mission 4 Track", text_song);
                break;

            case 9:
                switch_track(bgm_rescue);
                text_song.clear();
                text_generator.generate(0, 0, "Now Playing Mission 5 Track", text_song);
                break;

            default:
                // Do nothing.
                break;
        }

        while (true)
        {
            // Play/pause track.
            if(bn::keypad::a_pressed())
            {
                if(bn::music::paused())
                {
                    bn::music::resume();
                }
                else
                {
                    bn::music::pause();
                }
            }

            // Switch to previous track.
            if(bn::keypad::left_pressed())
            {
                if (selected_track == 1)
                {
                    selected_track = max_tracks;
                }
                else
                {
                    selected_track--;
                }

                break;
            }

            // Switch to next track.
            if(bn::keypad::right_pressed())
            {
                if (selected_track == max_tracks)
                {
                    selected_track = 1;
                }
                else
                {
                    selected_track++;
                }

                break;
            }

            // Return to main menu.
            if (bn::keypad::b_pressed()) return;

            bn::core::update();
        }
    }
}
