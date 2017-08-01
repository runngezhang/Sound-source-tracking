# Sound-source-tracking
A C++ demo of the sound source tracking paper Robust Localization and Tracking of Simultaneous Moving
Sound Sources Using Beamforming and Particle Filtering 
https://jmvalin.ca/papers/valin_localization.pdf

## You should see things like
 ![Alt text](https://github.com/zhr1201/Sound-source-tracking/blob/master/printscreen.PNG)

## Requirements
  QT5 and run that in QT5 directly. The programe will read data from a raw five channel audio data, and show the
  tracking results.
  
## Some other things
  * The original paper uses a spherical array and we use a 5 element circular microphone array, and only the horizontal angle       is tracked. 
  * The localization part is a static link libarary and the code is not open to the public.
  * The tracking part using particle filtering is open and only deals with one speaker.
  * After launching the GUI, only Quit, Start, Pause button can be pushed and the functionality of other pushbuttons are not
    fully implemented.
