#ifndef ALLY_CIVILLIAN_H
#define ALLY_CIVILLIAN_H

#include "bn_fixed.h"

class ally_civillian
{
public:
    bn::fixed hull = 1000;
    bn::fixed hull_max = 1000;
    bn::fixed x = 0;
    bn::fixed y = 0;

    ally_civillian();
};

#endif // ALLY_CIVILLIAN_H
