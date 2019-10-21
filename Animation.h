#ifndef Animation_h
#define Animation_h

#include "Arduino.h"
#include <FastLED.h>

uint8_t getMax(uint8_t rawArray[], uint8_t size);
int getPosition(uint8_t x, uint8_t y);
void setMatrix(CRGB *leds, uint8_t coloumns, uint8_t rows);
void putPixel(uint8_t column, uint8_t row, CRGB color);
void midFramColumnPattern(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void halfScreenupDownSweep(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void upDownSweep(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void fallingDrops(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void fallingDropsWhite(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void dropEffect(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t), bool white);
void lineGraph(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void lineGraphUpDown(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void columnGraph(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void upDownSweepBG(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t));
void upDownSweepFn(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t), bool background);
#endif
