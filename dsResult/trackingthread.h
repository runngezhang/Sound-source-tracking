/*
 * thread for tracking
 * using signal and slot to send particle positions to GUI
 */

#ifndef TRACKINGTHREAD_H
#define TRACKINGTHREAD_H
#include "audio_reader.h"
#include "doa_estimation.h"
#include "particle2d.h"
#include <cstring>
#include <fstream>
#include <QThread>
#include "particlePos.h"


class trackingThread: public QThread
{
    Q_OBJECT
public:
    short doa_result;  //DOA results for current frame
private:
    std::fstream *result_file;
    int N_Loc;  //Doing doa estimation every N_loc frames
    short doa_count;  //counter for frame hop times
    doa_estimator *Doa1;  //DOA estimator
    Noise_estimator *Est1;  //noise estimator
    audio_reader *audio1;  //audio reader
    volatile bool stopped;  //variable to control the thread
    particlePos *posGroup1;  //class containing all the particle positions
public:
    trackingThread();
    ~trackingThread();
    void setStart();
    void setStop();
protected:
    void run();  //things running in the thread

signals:
    void signalDoa(short doa);  //Signal for single DOA estimation
    void signalParticlePos(particlePos *posGroup);  //pass all the particle positions
    void signalTerminate();  //termintate signal

};

#endif // TRACKINGTHREAD_H
