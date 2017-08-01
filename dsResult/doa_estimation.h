/*
 * class noise_estimator: estimate stationary noise
 * class doa_estimator: estimate DOA
 */

#pragma once
#include "fft.h"
#include <list>
#include <vector>

class Noise_estimator{
public:
    short numToNoise;
protected:
    float current_noise[NN];  //estimated noise
private:
    float t[NN];  //current spectrum
    float p[NN][TT * Fs / FRAMESHIFT] ;  //all the spectrom with time TT
    int Noise_flag;  //index to store current noise spect
    float hamming[FRAMELENGTH];  //hamming window
    short p_max_index;
    FFT fft1;
public:
    Noise_estimator();
    ~Noise_estimator();
    void noise_update(audio_reader &audioX);  //update noise
private:
    void hamming_init();
    void tp_init();

friend class doa_estimator;
};


class doa_estimator{
public:
    short doa;  //estimated doa
    std::vector<short> doas;  //all the DOA peaks
    std::vector<float> probs;  //probability correspond to the peaks
private:
    float doa_scan[N_scan_angle];  //scaned doa angles
    float wdb[NN];  //scaned frequencies
    float scan_vec_base_real[Mic_Num][NN][N_scan_angle];  //steering vec
    float scan_vec_base_imag[Mic_Num][NN][N_scan_angle];
    float element_position[2][Mic_Num];  //mic positions
    FFT fft1;  //fft computer
public:
    doa_estimator();
    ~doa_estimator();
    void ds_doa2(audio_reader &audioX, Noise_estimator &Noise_E);  //doa estimate func
private:
    void scan_angle_generation();  //init scanning angle
    void scan_digital_freq_generation();  //init scanning frequencies
    void scan_generation();  //init steering vec
};
