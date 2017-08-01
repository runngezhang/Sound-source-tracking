/*
 * class particle2d: particle states and its predict & update functions
 *
 * class partile2dFilter: a sound source currently tracking and the particles
 *     to track it
 *
 * class particle2dMixture: create new tracking filters for new source and manage
 *     all the filters
 */

#ifndef PARTICLE2D_H
#define PARTICLE2D_H
#include <vector>
#include <map>
#include "stdafx.h"

class particle2d
{
public:
    //particle params
     short doa;
     float weight;
     enum State {Stopped=0, ConstVelocity=1, Excitation=2};

private:
     State state;

protected:
     //motion params
     float x[2];
     float v[2];

public:
    particle2d();
    particle2d(float pos[2]);
    particle2d(const particle2d& copParticle);
    particle2d& operator = (const particle2d& copParticle);
    void predictPosition();
    ~particle2d();   
    float prob(float pos[2], float std_1);  //likelihood function
    void updateWeight(float pos[][2], int N, float std_1, float P_qj[][2]);  //update weight
    void setWeight(float w) {weight = w;}
    void setxIncrement(float newX, float newY);  //coordinate pertubation and set position

private:

friend class particle2dFilter;
};


class particle2dFilter
{
public:
    float currentE;  //current probability of existence
    float lastE;  //probability of existence of last frame
    float currentA;  //probability of the source is now currently active
    float lastA;
    int ID;
    float lastPj;  //the aposteriari probability of the source of the last frame
    std::vector<particle2d> particles;  //particles for tracking
    short currentDoa;  //current position

public:
    explicit particle2dFilter(float pos[2], float initE, float initA, float initPj, float std);
    ~particle2dFilter();
    short getdoa();  //get mean doa of particles
    void predict();  //predict step of particle filter
    void resample();  //resample
    void setPj(float newPj) {lastPj = newPj;}  //set probability
    float prob(float pos[2], float std);  //sum of the likelihood of all the particles
    void updateE();  //update existence probability
    void updateA();  //update active probability
    void updateParticleWeight(float pos[][2], int N, float std_1, float P_qj[][2]);  //update weigh according to observation
    float accumulateWeight();  //sum the weights

};


class particle2dMixture
{

public:
    bool potentialExistFlag;  //if it is a potential source for tracking
    bool existFlag;  //if the source exits
    particle2dFilter* filter;  //particlefiter to track the source
public:
    particle2dMixture();
    ~particle2dMixture();
    void resample();  //resample all the particle filters
    void predict();  //predict
    void update(std::vector<short> doas, std::vector<float> probs, int numToNoise);  //update all the particle filters using observation
};

#endif // PARTICLE2D_H
