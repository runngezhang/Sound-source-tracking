/*
 * FFT computer，FFT_LENGTH must be defined
 */
#pragma once


class FFT{
private:
    unsigned long MDFFFTLog2N;
    unsigned long MDFFFTButter[FFT_LENGTH/4];
    unsigned long MDFFFTBitSwap[FFT_LENGTH/2];
    float MDFFFTPhi[FFT_LENGTH/2];
    float FFTGain[FFT_LENGTH];
public:
    FFT();
    void rfft(float *x, float *y);  //FFT
    void irfft(float *x, float *y);  //inverse FFT
};
