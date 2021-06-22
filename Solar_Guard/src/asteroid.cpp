#include "asteroid.h"

asteroid::asteroid(int start_x, int start_y, bn::camera_ptr &camera, int asteroid_type)
{
    // Set position.
    x = start_x;
    y = start_y;
    sprite.set_x(x);
    sprite.set_y(y);

    // Set sprite.
    sprite.set_tiles(bn::sprite_items::spr_asteroid.tiles_item().create_tiles(asteroid_type));

    // Set camera.
    sprite.set_camera(camera);
}
