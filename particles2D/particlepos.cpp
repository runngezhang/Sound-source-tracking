#include "particlepos.h"
#include "stdafx.h"

using namespace std;

particlePos::particlePos()
{
    state = 1;
    pos = new vector <short> (numParticle);
}

particlePos::~particlePos()
{
    delete pos;
    pos = NULL;
}

//renew current state
void particlePos::getposFromFilter(particle2dFilter *newpos)
{
    for(int i = 0; i < numParticle; i++)
        (*pos)[i] = (newpos->particles)[i].doa;
}

void particlePos::getposFromMixture(particle2dMixture *Mixture)
{
    state = Mixture->existFlag;
    if(state)
    {
        meanDoa = Mixture->filter->getdoa();
        for(int i = 0; i < numParticle; i++)
        {
            (*pos)[i] = (Mixture->filter->particles)[i].doa;
        }
    }
}
