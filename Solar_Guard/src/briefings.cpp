#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_items_spr_logo.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_items_bg_mission_briefing.h"

#include "font_menu.h"
#include "variable_8x16_sprite_font.h"
#include "font_hud.h"
#include "font_hud_compact.h"
#include "bn_sprite_items_menu_arrow.h"

#include "music.h"
#include "briefings.h"

int briefing_1()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_briefing.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 1: ORBIT TYDING", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-112, 25, "REPORTS HAVE COME IN FROM CIVILLIAN AND CORPORATE", briefing_text);
    text_generator_compact.generate(-112, 34, "TRANSPORTS THAT SPACE JUNK ACCUMULATING WITHIN", briefing_text);
    text_generator_compact.generate(-112, 43, "EARTH'S ORBIT IS MAKING TRANSIT DIFFICULT.", briefing_text);
    text_generator_compact.generate(-112, 52, "", briefing_text);
    text_generator_compact.generate(-112, 61, "WE ARE DEPLOYING RESERVE FIGHTERS ACROSS EARTH'S ORBIT.", briefing_text);
    text_generator_compact.generate(-112, 70, "TO DESTROY THE EXCESS JUNK. PREPARE FOR DEPLOYMENT.", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_2()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_briefing.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 2: CLEAR THE WAY", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-112, 25, "A TRANSPORT HAS REQUESTED ASSISTANCE IN NAVIGATING", briefing_text);
    text_generator_compact.generate(-112, 34, "THROUGH AN ASTEROID FIELD.", briefing_text);
    text_generator_compact.generate(-112, 43, "", briefing_text);
    text_generator_compact.generate(-112, 52, "ESCORT THE TRANSPORT THROUGH THE FIELD AND DESTROY", briefing_text);
    text_generator_compact.generate(-112, 61, "ANY DRIFITING ASTEROIDS THAT THREATEN THE TRANSPORT.", briefing_text);
    text_generator_compact.generate(-112, 70, "", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_3()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_briefing.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 3: SWIFT DEFENSE", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-112, 25, "WARNING! NO-FLY-ZONE PERIMETER BREACHED!", briefing_text);
    text_generator_compact.generate(-112, 34, "ENEMY SHIPS ATTACKING!", briefing_text);
    text_generator_compact.generate(-112, 43, "IDENTIFIED AS PIRATE ACTIVITY!", briefing_text);
    text_generator_compact.generate(-112, 52, "ALL FIGHTERS SCRAMBLE!", briefing_text);
    text_generator_compact.generate(-112, 61, "ORDERS ARE TO ENGAGE AND DESTROY ENEMY FIGHTERS!", briefing_text);
    text_generator_compact.generate(-112, 70, "", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_4()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_briefing.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 4: COUNTER PROBE", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-112, 25, "MILITARY INTELLIGENCE BELIEVES THE PIRATES MAY BE", briefing_text);
    text_generator_compact.generate(-112, 34, "OPERATING AN OUTPOST WITHIN THE ASTEROID BELT.", briefing_text);
    text_generator_compact.generate(-112, 43, "", briefing_text);
    text_generator_compact.generate(-112, 52, "ORDERS ARE TO PERFORM STEALTH RECON.", briefing_text);
    text_generator_compact.generate(-112, 61, "IT IS IMPORTANT TO AVOID DETECTION.", briefing_text);
    text_generator_compact.generate(-112, 70, "DO NOT ENGAGE. STAY OUT OF SIGHT.", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int briefing_5()
{
    // Set a background.
    bn::regular_bg_ptr gameplay_bg = bn::regular_bg_items::bg_mission_briefing.create_bg(0, 0);

    // Setup drawing text.
    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 32> briefing_title;
    bn::sprite_text_generator text_generator_compact(font_hud_compact);
    bn::vector<bn::sprite_ptr, 64> briefing_text;

    // Draw briefing title.
    text_generator.set_center_alignment();
    text_generator.generate(0, -72, "MISSION 5: DISTANT REACH", briefing_title);

    // Draw briefing text.
    text_generator_compact.set_left_alignment();
    text_generator_compact.generate(-112, 25, "WE HAVE PICKED UP A DISTRESS CALL FROM A CIVILLIAN", briefing_text);
    text_generator_compact.generate(-112, 34, "CRAFT. IT APPEARS THAT THE SHIP'S ENGINES HAVE FAILED", briefing_text);
    text_generator_compact.generate(-112, 43, "NEAR THE SUN, WHICH IT IS NOW DRIFTING TOWARDS. FLY", briefing_text);
    text_generator_compact.generate(-112, 52, "TO THE STRICKEN CRAFT AND RESCUE ANY OCCUPANTS,", briefing_text);
    text_generator_compact.generate(-112, 61, "RETURNING THEM TO THE CARRIER. TIME IS LIMITED.", briefing_text);
    text_generator_compact.generate(-112, 70, "", briefing_text);

    // Briefing loop.
    while(true)
    {
        if (bn::keypad::a_pressed())
        {
            return 1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}
