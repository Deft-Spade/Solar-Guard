#include "information.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_string.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_spr_logo_green.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_items_bg_information.h"
#include "bn_regular_bg_items_bg_oga_page1.h"
#include "bn_regular_bg_items_bg_oga_page2.h"
#include "bn_regular_bg_items_bg_oga_page3.h"
#include "bn_regular_bg_items_bg_oga_page4.h"
#include "bn_regular_bg_items_bg_oga_page5.h"
#include "bn_regular_bg_items_bg_oga_page6.h"

#include "bn_sprite_text_generator.h"
#include "font_menu.h"
#include "variable_8x16_sprite_font.h"
#include "font_hud.h"

#include "bn_music_item.h"
#include "bn_music_items.h"
#include "bn_music_actions.h"
#include "music.h"

namespace
{
    constexpr const bn::fixed screen_y_limit = (bn::display::height() / 2);
}

void scene_controls()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_information.create_bg(0, 0);

    bgm_theme_upbeat.play();

    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 128> text_sprites;

    text_generator.set_center_alignment();
    text_generator.generate(0, - 65, "CONTROLS", text_sprites);
    text_generator.set_left_alignment();
    text_generator.generate(-106, - 15, "LEFT/RIGHT > TURN SHIP", text_sprites);
    text_generator.generate(-106, - 5, "R > ENGAGE ENGINE", text_sprites);
    text_generator.generate(-106, + 5, "L > REDUCE SPEED", text_sprites);
    text_generator.generate(-106, + 15, "L + R > ENGAGE AFTERBURNER", text_sprites);

    while (!bn::keypad::b_pressed())
    {
        bn::core::update();
    }
}

void scene_credits()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_information.create_bg(0, 0);

    bgm_theme_upbeat.play();

    // Create the logo sprite.
    bn::sprite_ptr sprite_logo = bn::sprite_items::spr_logo_green.create_sprite(0, -15);

    bn::sprite_text_generator text_generator(font_hud);
    bn::vector<bn::sprite_ptr, 128> text_sprites;

    text_generator.set_center_alignment();
    text_generator.generate(0, + 10, "BY DEFT SPADE", text_sprites);
    text_generator.generate(0, + 20, "USING BUTANO BY GVALIENTE", text_sprites);
    text_generator.generate(0, + 30, "FOR GBA JAM 2021", text_sprites);

    while (!bn::keypad::b_pressed())
    {
        bn::core::update();
    }
}

int loop_oga_credits()
{
    while (true)
    {
        if (bn::keypad::right_pressed())
        {
            return 1;
        }

        if (bn::keypad::left_pressed())
        {
            return -1;
        }

        if (bn::keypad::b_pressed())
        {
            return 0;
        }

        bn::core::update();
    }
}

int scene_oga_credits_page1()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_oga_page1.create_bg(0, 0);
    return loop_oga_credits();
}

int scene_oga_credits_page2()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_oga_page2.create_bg(0, 0);
    return loop_oga_credits();
}

int scene_oga_credits_page3()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_oga_page3.create_bg(0, 0);
    return loop_oga_credits();
}

int scene_oga_credits_page4()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_oga_page4.create_bg(0, 0);
    return loop_oga_credits();
}

int scene_oga_credits_page5()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_oga_page5.create_bg(0, 0);
    return loop_oga_credits();
}

int scene_oga_credits_page6()
{
    const bn::regular_bg_ptr regular_bg = bn::regular_bg_items::bg_oga_page6.create_bg(0, 0);
    return loop_oga_credits();
}

void scene_oga_credits()
{
    // Menu operation variables.
    int current_page = 1;
    const int number_of_pages = 6;

    bgm_theme_upbeat.play();

    while (true)
    {
        int user_input;

        // Switch page.
        switch (current_page)
        {
            case 1: user_input = scene_oga_credits_page1(); break;
            case 2: user_input = scene_oga_credits_page2(); break;
            case 3: user_input = scene_oga_credits_page3(); break;
            case 4: user_input = scene_oga_credits_page4(); break;
            case 5: user_input = scene_oga_credits_page5(); break;
            case 6: user_input = scene_oga_credits_page6(); break;
            default: BN_ERROR("CURRENT PAGE VALUE INVALID: " + bn::to_string<16>(current_page)); break;
        }

        if (user_input == 0)
        {
            return;
        }
        else
        {
            if (user_input == 1)
            {
                if (current_page == number_of_pages)
                {
                    current_page = 1;
                }
                else
                {
                    current_page += 1;
                }
            }
            else
            {
                if (current_page == 1)
                {
                    current_page = number_of_pages;
                }
                else
                {
                    current_page -= 1;
                }
            }
        }

        bn::core::update();
    }
}
