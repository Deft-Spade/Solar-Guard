#ifndef ALLY_STATION_H
#define ALLY_STATION_H

#include "bn_fixed.h"

class ally_station
{
public:
    bn::fixed hull = 1000;
    bn::fixed hull_max = 1000;

    ally_station();
};

#endif // ALLY_STATION_H
