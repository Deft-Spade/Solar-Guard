#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_timer.h"
#include "bn_timers.h"
#include "bn_blending.h"
#include "bn_fixed.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_splash_screen_deft_spade.h"
#include "bn_regular_bg_items_bg_splash_screen_gba_jam_2021.h"

#include "splash_screens.h"

void splash_screen(bn::regular_bg_ptr splash_screen)
{
    // Enable blending for the background.
    splash_screen.set_blending_enabled(true);

    // Timer for tracking time.
    bn::timer timer = bn::timer();

    // Variable to track the current alpha level.
    bn::fixed alpha_level = bn::fixed(1);

    // Wait 5 seconds or until any key is pressed.
    while (timer.elapsed_ticks() < 5 * 60 * bn::timers::ticks_per_frame() && !bn::keypad::any_pressed())
    {
        alpha_level = bn::max(bn::fixed(0), alpha_level - 0.02);
        bn::blending::set_fade_alpha(alpha_level);
        bn::core::update();
    }

    // Fade out.
    while (alpha_level.integer() != 1)
    {
        alpha_level = bn::min(bn::fixed(1), alpha_level + 0.02);
        bn::blending::set_fade_alpha(alpha_level);
        bn::core::update();
    }
}

void splash_screen_developer()
{
    // Splash screen background.
    bn::regular_bg_ptr background_splash_screen_developer = bn::regular_bg_items::bg_splash_screen_deft_spade.create_bg(0, 0);
    splash_screen(background_splash_screen_developer);
}

void splash_screen_event()
{
    // Splash screen background.
    bn::regular_bg_ptr background_splash_screen_event = bn::regular_bg_items::bg_splash_screen_gba_jam_2021.create_bg(0, 0);
    splash_screen(background_splash_screen_event);
}
