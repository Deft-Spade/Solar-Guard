/*
 * Copyright (c) 2020-2021 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef FONT_HUD_COMPACT_H
#define FONT_HUD_COMPACT_H

#include "bn_sprite_font.h"
#include "bn_sprite_items_spr_font_hud_compact.h"

constexpr const bn::string_view font_hud_compact_utf8_characters[] = {
    "Á", "É", "Í", "Ó", "Ú", "Ü", "Ñ", "á", "é", "í", "ó", "ú", "ü", "ñ", "¡", "¿"
};

constexpr const int8_t font_hud_compact_character_widths[] = {
    4,  // 32
    4,  // 33 !
    4,  // 34 "
    4,  // 35 #
    4,  // 36 $
    4,  // 37 %
    4,  // 38 &
    4,  // 39 '
    4,  // 40 (
    4,  // 41 )
    4,  // 42 *
    4,  // 43 +
    4,  // 44 ,
    4,  // 45 -
    4,  // 46 .
    4,  // 47 /
    4,  // 48 0
    4,  // 49 1
    4,  // 50 2
    4,  // 51 3
    4,  // 52 4
    4,  // 53 5
    4,  // 54 6
    4,  // 55 7
    4,  // 56 8
    4,  // 57 9
    4,  // 58 :
    4,  // 59 ;
    4,  // 60 <
    4,  // 61 =
    4,  // 62 >
    4,  // 63 ?
    4,  // 64 @
    4,  // 65 A
    4,  // 66 B
    4,  // 67 C
    4,  // 68 D
    4,  // 69 E
    4,  // 70 F
    4,  // 71 G
    4,  // 72 H
    4,  // 73 I
    4,  // 74 J
    5,  // 75 K
    4,  // 76 L
    6,  // 77 M
    4,  // 78 N
    4,  // 79 O
    4,  // 80 P
    4,  // 81 Q
    4,  // 82 R
    4,  // 83 S
    4,  // 84 T
    4,  // 85 U
    4,  // 86 V
    6,  // 87 W
    4,  // 88 X
    4,  // 89 Y
    4,  // 90 Z
    4,  // 91 [
    4,  // 92
    4,  // 93 ]
    4,  // 94 ^
    4,  // 95 _
    4,  // 96 `
    4,  // 97 a
    4,  // 98 b
    4,  // 99 c
    4,  // 100 d
    4,  // 101 e
    4,  // 102 f
    4,  // 103 g
    4,  // 104 h
    4,  // 105 i
    4,  // 106 j
    4,  // 107 k
    4,  // 108 l
    4,  // 109 m
    4,  // 110 n
    4,  // 111 o
    4,  // 112 p
    4,  // 113 q
    4,  // 114 r
    4,  // 115 s
    4,  // 116 t
    4,  // 117 u
    4,  // 118 v
    4,  // 119 w
    4,  // 120 x
    4,  // 121 y
    4,  // 122 z
    4,  // 123 {
    4,  // 124 |
    4,  // 125 }
    4,  // 126 ~
    4,  // Á
    4,  // É
    4,  // Í
    4,  // Ó
    4,  // Ú
    4,  // Ü
    4,  // Ñ
    4,  // á
    4,  // é
    4,  // í
    4,  // ó
    4,  // ú
    4,  // ü
    4,  // ñ
    4,  // ¡
    4,  // ¿
};

constexpr const bn::sprite_font font_hud_compact(
        bn::sprite_items::spr_font_hud_compact, font_hud_compact_utf8_characters,
        font_hud_compact_character_widths);

#endif
