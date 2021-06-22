#include "space_junk.h"

space_junk::space_junk(int start_x, int start_y, bn::camera_ptr &camera, int junk_type)
{
    // Set position.
    x = start_x;
    y = start_y;
    sprite.set_x(x);
    sprite.set_y(y);

    // Set sprite.
    sprite.set_tiles(bn::sprite_items::spr_space_junk.tiles_item().create_tiles(junk_type));

    // Set camera.
    sprite.set_camera(camera);
}
