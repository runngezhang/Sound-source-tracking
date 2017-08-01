
#pragma  once


#include <iostream>
#include <stdio.h>


#define PI 3.14159265358f
#define C_speed 340
#define FFT_LENGTH 1024
#define FRAMELENGTH 1024
#define FRAMESHIFT 256
#define NN 513  // number of FFT points
#define Fs 16000
#define Mic_Num 5
#define N_scan_angle 360  //number of scanning angles
#define F_min 100  //frequency range
#define F_max 4000
#define Data_Buffer_L 1024 * 2  //buffer length for DOA data
#define TT 3  //time length for noise estimation
#define SMOOTH_FACTOR 0.87f  //smoothing factor for noise estimation
#define NOISE_ESTIMATION_FAC 4.0f  //param for noise estimation
#define ALPHA 1.5f
#define GAMA 0.5f
#define InterV 768  //doing DOA estimation evry InverV points
#define SHORT_TO_FLOAT 3.05175e-05f
#define INV_PI 0.318309886183791  //inv of PI

#define N_coarse 36
#define N_int 10

#define numParticle 100            //number of particles for tracking
