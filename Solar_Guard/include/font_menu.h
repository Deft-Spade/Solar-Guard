/*
 * Copyright (c) 2020-2021 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef FIXED_8x16_SPRITE_FONT_H
#define FIXED_8x16_SPRITE_FONT_H

#include "bn_sprite_font.h"
#include "bn_sprite_items_font_menu.h"

constexpr const bn::string_view font_menu_utf8_characters[] = {
    "Á", "É", "Í", "Ó", "Ú", "Ü", "Ñ", "á", "é", "í", "ó", "ú", "ü", "ñ", "¡", "¿"
};

constexpr const bn::sprite_font font_menu(
        bn::sprite_items::font_menu, font_menu_utf8_characters);

#endif
