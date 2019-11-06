# Audio Analyzer

Audio Visualizer creates a 24 band frequency analyzer, with given analog audio input. You can use any audio source to produce various patterns, based on the peak value of frequency band.
Code uses Arduino’s ADC capability to read analog signal from external audio source and convert it into digital signal. Since the audio signal is in time domain and we are looking to find peak values of different frequency band, we will use Fourier transform to convert audio signal to frequency domain. 
Primary user of this project is my 3 year old who just wanted to see “dancing lights”. This project is intended for general audio / Arduino / WS2812b hobbyist. 
This code is scalable to larger WS2812b matrix, each pixel takes 3 bytes, I am using 12X24 leds. Further FFT computation is memory intensive, I am using 128 bin FFT which takes around 512 bytes (http://wiki.openmusiclabs.com/wiki/ArduinoFFT).  Thus, code takes more than 75% of available 2k Arduino SRAM.  If you are planning to use larger matrix & more frequency band, it is recommended to go with Teensy or other board with more SRAM.

## List of components 
1.	2 registers 
2.	Power supply 
3.	ws2812b led strip
4.	3.5 audio jacks 
5.	Tactile switches 3

## Schematic diagram

## Building Display Screen

To build a display from LED strip you need arrange them in a matrix form, such that each row & column represents a vector position on strip. Following diagram shows sample arrangements.

![Led Matrix Board](https://github.com/amitalone/audio_analyzer/blob/master/led-matrix.png =250x)

