#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "player_ship.h"

void gameplay_hud_draw(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites, bn::fixed x, bn::fixed y);
void gameplay_player_control(player_ship &player_ship);

#endif // GAMEPLAY_H
