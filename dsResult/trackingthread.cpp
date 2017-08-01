#include "stdafx.h"
#include "trackingthread.h"
#include <fstream>
#include "myexception.h"
#include <unistd.h>

trackingThread::trackingThread()
{

    N_Loc = InterV / FRAMESHIFT;
    doa_count = 1;
    Doa1 = new doa_estimator;  //init a doa estimator
    Est1 = new Noise_estimator;  //init a noise estimator
    posGroup1 = new particlePos;
    stopped = false;

    //recorded audio
    char *doa_file_name = ".\\resources\\109_1_tracking_fast_s.wav";

    try	{
            audio1 = new audio_reader(doa_file_name);

    }
    catch(audio_read_exception &err)
    {
            err.except_sol();
            this->terminate();
    }

    //need TT s to init the noise estimator
    for(int i = 1; i < (TT * Fs / FRAMESHIFT); i++)
    {
        audio1->next_frame();
        Est1->noise_update(*audio1);
    }



}

trackingThread::~trackingThread()
{
    delete Doa1;
    Doa1 = NULL;
    delete posGroup1;
    posGroup1 = NULL;
    delete Est1;
    Est1 = NULL;
    delete audio1;
    audio1 = NULL;
}

void trackingThread::run()
{

    float pos[2] = {0, 1};

    particle2dMixture *Mixture = new particle2dMixture;  //particle management class
    while(audio1->next_frame() && !stopped)  //read next frame data
    {
        Est1->noise_update(*audio1);  //update noise estimator
        if (doa_count == N_Loc)  //condition for a DOA estimation
        {
            doa_count = 0;
            Doa1->ds_doa2(*audio1, *Est1);  //Do DOA estimation
            doa_result = Doa1->doa;  //get result

            //predict and resample for the particle filter
            Mixture->predict();
            Mixture->update(Doa1->doas, Doa1->probs, Est1->numToNoise);
            Mixture->resample();

            //update the particle postions in the GUI
            posGroup1->getposFromMixture(Mixture);

            //pass to the main thread
            emit signalParticlePos(posGroup1);
            emit signalDoa(doa_result);
        }
        doa_count++;
        usleep(30000);    //running too fast using off line data, wait for 30000 us
    }


    emit signalTerminate();
    stopped = false;
}

void trackingThread::setStart()
{
    stopped = false;
}

void trackingThread::setStop()
{
    stopped = true;
}
