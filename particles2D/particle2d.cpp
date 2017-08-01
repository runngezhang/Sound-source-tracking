#include "particle2d.h"
#include <QObject>
#include <cmath>
#include <QTime>

//some cmath doesn't include M_PI
#ifndef M_PI
#define M_PI 3.1415926f
#endif

namespace particleFilter
{

#define TRANS_PROB 0.05  //tansfer probability to compute the apriori prob of existence in particle2Dfilter
#define SHORT_APRIORI 0.5  //the apriori prob to renew the prob of exitence in particle2Dfilter
#define NUM_TO_NOISE_THRESH 50  //the threshold to decide if a new potential source appears

const float P_ind_Of_0_Int = 1.0f / 2.0f / M_PI;  //given assignment function f,the apriori prob of O is false observation
const float initStandardDeviation = 0.2f;  //standard deviation to init particle positions
const float stdEmprc = 0.268;  //standard deviation for computing likelihood function
const float stdEmprc_1 = 1.0f / stdEmprc;
const double randNorm = 1.0 / RAND_MAX;  //rand normalization factor
const float degree2rad = M_PI / 180.0f;  //radian2degree factor
const float rad2degree = 180.0f / M_PI;
const float radius = 1.0f;  //the radius of the circle that the particle moves along
const float deltaT = (double)InterV / Fs;  //renew every deltaT
const float initVStandDev = 0.2f;  //standard deviation to init V
const float initWeight = 1.0f / numParticle;  //init weight
const float P_new = 0.02;  //the apriori that a new source appears
const float P_false = 0.05;  //the apriori of false observation


//generate norm distribution with std 1
inline float randn()
{
float u = ((float) qrand() / (RAND_MAX)) * 2 - 1;
float v = ((float) qrand() / (RAND_MAX)) * 2 - 1;
float r = u * u + v * v;
if (r == 0 || r > 1) return randn();
double c = sqrt(-2 * log(r) / r);
return u * c;
}

//transfer the particle position to degree
inline short x2Doa(float x, float y)
{

    short temp = atan2(x, y) * rad2degree;
    if(temp < 0)
        temp = 360 + temp;
    return temp;
}

//find the range that x is in within vector cumul
inline int find_range(float x, const std::vector<float> &cumul)
{
    int low=0;
    int high=cumul.size()-1;
    int cur = high>>1;
    while (1)
    {
        if (cumul[cur] > x)
        {
            if (cur == 0 || cumul[cur-1] <= x)
            {
                break;
            } else {
                high = cur-1;
                cur = (low+cur) >> 1;
            }
        } else {
            low = cur;
            cur = (high+cur+1) >> 1;
            if (cur==high)
                break;
        }
    }
    return cur;
}

//sum
inline float sum(float input[], int Num)
{
    float result = 0;
    for(int i = 0; i < Num; i++)
        result += input[i];
    return result;
}

}


using namespace particleFilter;

//init particles
particle2d::particle2d(float pos[2])
{

    x[0] = pos[0];
    x[1] = pos[1];
    v[0] = randn() * initVStandDev;
    v[1] = randn() * initVStandDev;
    doa = x2Doa(pos[0], pos[1]);
    weight = initWeight;

}

particle2d::particle2d()
{

    x[0] = 0;
    x[1] = 1;
    v[0] = randn() * initVStandDev;
    v[1] = randn() * initVStandDev;
    doa = x2Doa(x[0], x[1]);
    weight = initWeight;
    float temp = qrand() * randNorm;
    if(temp < 0.05)
        state = Stopped;
    else if(temp < 0.4)
        state = ConstVelocity;
    else
        state = Excitation;

}


particle2d::particle2d(const particle2d& copParticle)
{

    x[0] = copParticle.x[0];
    x[1] = copParticle.x[1];
    v[0] = copParticle.v[0];
    v[1] = copParticle.v[1];
    doa = copParticle.doa;
    weight = copParticle.weight;
    state = copParticle.state;

}

particle2d& particle2d::operator = (const particle2d& copParticle)
{
    doa = copParticle.doa;
    weight = copParticle.weight;
    state = copParticle.state;
    x[0] = copParticle.x[0];
    x[1] = copParticle.x[1];
    v[0] = copParticle.v[0];
    v[1] = copParticle.v[1];
    return *this;
}

particle2d::~particle2d()
{

}

//coordinate pertubation
void particle2d::setxIncrement(float newX, float newY)
{
    x[0] += newX;
    x[1] += newY;
    float norm_1 = (float)1 / sqrt(x[0]*x[0] + x[1]*x[1]);
    x[0] *= norm_1; x[1] *= norm_1;
    doa = x2Doa(x[0], x[1]);
}

//predit the position of the particles
void particle2d::predictPosition()
{

    //change the state of the particls with some probability
    float betaX;
    float vX;
    float aX, bX;
    if(qrand()<.05)
    {
        float x = qrand();
        if (x<.05)
           state = Stopped;
        else if (x<.5)
           state = ConstVelocity;
        else
           state = Excitation;
    }
    if(state==Excitation)
    {
        betaX = .5f;
        vX = .4;
    } else if (state == ConstVelocity)
    {
        betaX = .05f;
        vX = .3;
    } else {
        betaX = 2.f;
        vX = .1;
    }
    aX = exp(-betaX*deltaT);
    bX = 3.0f * vX * sqrt(1-aX*aX);
    v[0] = aX*v[0] + bX*randn();
    v[1] = aX*v[1] + bX*randn();
    x[0] += deltaT*v[0];
    x[1] += deltaT*v[1];

    //normalization
    float norm_1 = (float)1 / sqrt(x[0]*x[0] + x[1]*x[1]);
//    float norm_1 = 1 - .5*((x[0]*x[0] + x[1]*x[1])-1);
    x[0] *= norm_1; x[1] *= norm_1;


    float cos_prod = x[0]*v[0] + x[1]*v[1];
    v[0] -= x[0]*cos_prod;
    v[1] -= x[1]*cos_prod;

    doa = x2Doa(x[0], x[1]);

}


//compute the likelihood of particle position given observation pos
// std_1 is the reciprocal of std
float particle2d::prob(float pos[2], float std_1)
{
    float dist = (x[0] - pos[0]) * (x[0] - pos[0]) + (x[1] - pos[1]) * (x[1] - pos[1]);
    dist = -std_1*std_1*dist;
    if (dist > -70)
        return 1e-30+.8f*exp(4*dist)+.18f*exp(.4*dist)+.02f*exp(.1*dist);
    else
        return 1e-30;
}

//update particle weight, pos is the peaks, N is the number of the peaks, P_qj is the prob of assigning function
void particle2d::updateWeight(float pos[][2], int N, float std_1, float P_qj[][2])
{
    float tempWeight = 0;
    for(int i = 0; i < N; i++)
        tempWeight += P_qj[i][1] * prob(pos[i], std_1);
    weight = tempWeight;
}


particle2dFilter::particle2dFilter(float pos[2], float initE, float initA, float initPj, float std) :
    currentDoa(x2Doa(pos[0], pos[1])),
    currentE(initE),
    lastE(initE),
    currentA(initA),
    lastA(initA),
    lastPj(initPj)
{
    particles = std::vector<particle2d>(numParticle, pos);
    for (int i = 0; i < particles.size(); i++)
    {
  //      particles[i] = particle2d(pos);                 //有些编译器不支持vector类型两参数直接初始化
        particles[i].setxIncrement(std * randn(), std * randn());
    }

}

particle2dFilter::~particle2dFilter()
{

}

//get current pos by averaging the particles
short particle2dFilter::getdoa()
{
    float meanX[2];
    for(int i = 0; i < particles.size(); i++)
    {
        meanX[0] += particles[i].x[0];
        meanX[1] += particles[i].x[1];
    }
    return x2Doa(meanX[0], meanX[1]);
}

//predict step for all the particls
void particle2dFilter::predict()
{
    for(int i = 0; i < particles.size(); i++)
        particles[i].predictPosition();
}

//get all the likelihood for all particles and sum, pos[2] is position, std is standard deviation
float particle2dFilter::prob(float pos[2], float std)
{
    float weightSum = 0;
    float std_1 = 1./std;
    for(int i = 0; i < particles.size();i++)
    {
        weightSum += particles[i].weight * particles[i].prob(pos, std_1);
    }
    return weightSum;
}

//resample
void particle2dFilter::resample()
{
    std::vector<particle2d> tmp;
    tmp = std::vector<particle2d>(particles.size());
    for(int i = 0; i < particles.size(); i++)
        tmp[i] = particles[i];

    std::vector<float> cumul(tmp.size());  //cumulation vector for sampling
    std::vector<float> weightVec(tmp.size());  //weight vector fot sebastian's resampling wheel

    //initialization
    cumul[0] = tmp[0].weight;
    weightVec[0] = tmp[0].weight;

    float maxWeight;  //max weight
    maxWeight = tmp[0].weight;
    for (int i = 1; i < particles.size(); i++)
    {
       cumul[i] = cumul[i-1]+particles[i].weight;
       weightVec[i] = particles[i].weight;
       if(maxWeight < particles[i].weight)
           maxWeight = particles[i].weight;
    }

    float sum_weights = 0;

#if 0
    //simple implementation of resampling
    for (int i = 0; i < particles.size(); i++)
    {
       float r = qrand() * randNorm * cumul[particles.size() - 1] ;
       int j;
       j=find_range(r,cumul);
       particles[i] = tmp[j];
       particles[i].weight = 1;
       sum_weights += particles[i].weight;
    }

#else
    //Sebastian resampling wheel
    float beta = 0;
    int index;
    index = (int)qrand() * randNorm * particles.size();
    for(int i = 0; i < particles.size(); i++)
    {
        beta += qrand() * randNorm * 2 * maxWeight;
        while(beta > weightVec[index])
        {
            beta = beta - weightVec[index];
            index++;
            if(index >= particles.size()) index -=  particles.size();
        }
         particles[i] = tmp[index];
         particles[i].weight = 1;
         sum_weights += particles[i].weight;
    }

#endif


    sum_weights = 1.f / sum_weights;

    for (int i = 0; i < particles.size(); i++)
    {
       particles[i].weight *= sum_weights;
    }

}

//update active prob
void particle2dFilter::updateA()
{
    float P1 = lastPj;
    lastA = currentA;

    float p0 = lastA * TRANS_PROB + (1 - TRANS_PROB)*(1 - lastA);
    float p1 = lastA * (1 - TRANS_PROB) + TRANS_PROB * lastA;
    float temp = 0.15 + 0.85 * P1;

    p0 = p0 * (1 - temp) / (1 - SHORT_APRIORI);
    p1 = p1 * temp / SHORT_APRIORI;
    currentA = p1 / (p1 + p0);
    if(currentA > 0.98)
        currentA = 0.98;
}

//update prob of existence
void particle2dFilter::updateE()
{
    float P1 = lastPj;
    float P0 = 0.2;
    lastE = currentE;
    currentE = P1 + (1 - P1) * P0 * lastE / (1 - (1 - P0) * lastE);
    if(currentE > 0.98)
        currentE = 0.98;
}

//renew the weight, pos is the peaks' positions, N the numeber of peaks
//std_1 reciprocal of std, P_qj prob of assignment
void particle2dFilter::updateParticleWeight(float pos[][2], int N, float std_1, float P_qj[][2])
{
    for(int i = 0; i < particles.size(); i++)
    {
        particles[i].updateWeight(pos, N, std_1, P_qj);
    }
    float tempSumWeight = accumulateWeight();
    for(int i = 0; i < particles.size(); i++)
    {
        float tempWeight = (1 - lastPj) / particles.size()
                + lastPj * particles[i].weight / tempSumWeight;

        particles[i].setWeight(tempWeight);
    }

}

//sum the weights
float particle2dFilter::accumulateWeight()
{
    float tempWeight = 0;
    for(int i = 0; i < particles.size(); i++)
        tempWeight += particles[i].weight;

    return tempWeight;
}


particle2dMixture::particle2dMixture() :
    existFlag(false),
    potentialExistFlag(false)
{
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);  //set seed for rand
}


particle2dMixture::~particle2dMixture()
{
   if(potentialExistFlag == true)
   {
       delete filter;
   }
}

//resmaple if exits
void particle2dMixture::resample()
{
    if(potentialExistFlag == true)
    {
        filter->resample();
    }
}

//predict if exits
void particle2dMixture::predict()
{
    if(potentialExistFlag == true)
    {
        filter->predict();
    }
}

//update the state of the particle filters
void particle2dMixture::update(std::vector<short> doas, std::vector<float> probs, int numToNoise)
{
    if(potentialExistFlag == true)
    {
        short n_Peaks = doas.size();
        //number of the assignment functions, 1~N_peaks for the corresponding source, the last one means all wrong
        short n_Assign_Function = n_Peaks + 1;
        //the aposteriori for assigning qj, the 2nd dimention: 0 wrong, 1 right
        float P_qj[n_Peaks][2];
        //the aposteriori for assigning functions
        float P_fO[n_Assign_Function];
        for(int i = 0; i < n_Assign_Function; i++)
        {
            P_fO[i] = 1;
        }
        //given a single assigning funcion, the apriori the observation occurs, the 2nd dimention definition is the same as above
        float P_ind_Of[n_Peaks][2];
        //the apriori that the single assignment function is right
        float P_ind_f[n_Peaks][2];
        //update the particle filter
        filter->updateA();
        filter->updateE();


        //compute the probs
        float pos[n_Peaks][2];
        for(int i = 0; i < n_Peaks; i++)
        {
            pos[i][0] = radius * sin((float)doas[i] * degree2rad);
            pos[i][1] = radius * cos((float)doas[i] * degree2rad);
        }

        for(int i = 0; i < n_Peaks; i++)
        {
            P_ind_Of[i][0] = P_ind_Of_0_Int;
            P_ind_Of[i][1] = filter->prob(pos[i], stdEmprc);

            P_ind_f[i][0] = (1 - filter->lastPj) * P_false + filter->lastPj * P_new;
            P_ind_f[i][1] = probs[i] * filter->currentA * filter->currentE;
        }

        for(int i = 0; i < n_Assign_Function; i++)
        {
            for(int j = 0; j < n_Peaks; j++)
            {
                if(i == j)
                    P_fO[i] *= P_ind_Of[j][1] * P_ind_f[j][1];
                else
                    P_fO[i] *= P_ind_Of[j][0] * P_ind_f[j][0];
            }
        }

        float NormProb_1 = 1.0f / sum(P_fO, n_Assign_Function);
        for(int i = 0; i < n_Assign_Function; i++)
            P_fO[i] *= NormProb_1;

        for(int i = 0; i < n_Peaks; i++)
        {
            P_qj[i][0] = 1 - P_fO[i];
            P_qj[i][1] = P_fO[i];
        }

        //the probs of the source been observed
        float P1;
        for(int i = 0; i < n_Peaks; i++)
        {
            P1 += P_qj[i][1];
        }

        filter->setPj(P1);
        filter->updateParticleWeight(pos, n_Peaks, stdEmprc_1, P_qj);
        if(filter->currentE > 0.95)
        {
            //the source is sure to exit
            existFlag = true;
        }

        if(filter->currentE < 0.05)
        {
            //the source disappears
            existFlag = false;
            potentialExistFlag = false;
            delete filter;
            filter = NULL;
        }


    }
    else
    {
        if(numToNoise > NUM_TO_NOISE_THRESH)
        {
            //potential source exits
            float pos[2];
            pos[0] = radius * sin((float)doas[0] * degree2rad);
            pos[1] = radius * cos((float)doas[0] * degree2rad);
            filter = new particle2dFilter(pos, 0.3, 0.3, 0.2, initStandardDeviation);
            potentialExistFlag = true;
        }
    }

}

