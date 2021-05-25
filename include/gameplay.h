#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"

void gameplay_hud_draw(bn::sprite_text_generator &text_generator, bn::vector<bn::sprite_ptr, 64> &text_sprites, bn::sprite_ptr &player_sprite);
void gameplay_player_control(bn::sprite_ptr &player_sprite);

#endif // GAMEPLAY_H
