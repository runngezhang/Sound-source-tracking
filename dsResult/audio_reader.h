/*
 * class audio_reader, using C style string as input
 * bool nextFrame(): read next frame audio
 */
#pragma once


#include "stdafx.h"
#include "audio_reader.h"

class audio_reader{
protected:
    float Current_Data_Buffer[Mic_Num][FRAMELENGTH];  //current_data
    float **Data_Buffer;  //data for DOA estimation
private:
    FILE *fp;
    short inputFileChannelNum;
    int sampleRate;
    short sampleBitLen;
    int sampleNumPerChannel;
    int sampleTimePerChannel;
    short sampleByteLen;
    int byteRatePerSecond;
    short formatType;
    int fileFormat;
    float dataIn[Mic_Num][FRAMELENGTH];  //new data frame
    short N_move_num;  // hop size
    short data_in_flag;
public:
    audio_reader(const char * filename);
    ~audio_reader();
    bool next_frame();  //read next frame data
private:
    bool AudioReadFileOpen(const char * filename);  //constructor using filename

friend class Noise_estimator;
friend class doa_estimator;

};
