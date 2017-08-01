/*
 * class to pass particles and DOAs between the tracking thread and GUI
 */
#ifndef PARTICLEPOS_H
#define PARTICLEPOS_H

#include <vector>
#include "stdafx.h"
#include "particle2d.h"


class particlePos
{
public:
    std::vector <short> *pos;  //vectors for the particle positions
    short meanDoa;  //doa after particle filtering
    bool state;  //particle state
public:
    particlePos();
    ~particlePos();
    void getposFromFilter(particle2dFilter *newpos);  //renew current state
    void getposFromMixture(particle2dMixture *mixture);
};

#endif // PARTICLEPOS_H
