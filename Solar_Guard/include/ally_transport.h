#ifndef ALLY_TRANSPORT_H
#define ALLY_TRANSPORT_H

#include "bn_fixed.h"

class ally_transport
{
public:
    bn::fixed hull = 1000;
    bn::fixed hull_max = 1000;
    bn::fixed x = 0;
    bn::fixed y = 0;

    ally_transport();
};

#endif // ALLY_TRANSPORT_H
