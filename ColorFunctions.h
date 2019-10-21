#ifndef ColorFunctions_h
#define ColorFunctions_h

#include <FastLED.h>

CRGB colorRBBlend(uint8_t x, uint8_t y); //1
CRGB colorBlack(uint8_t x, uint8_t y);
byte * Wheel(byte WheelPos) ;
CRGB rainbow(uint8_t x, uint8_t y); //0
CRGB colorBlueScale(uint8_t x, uint8_t y); // 2
CRGB colorBand1(uint8_t x, uint8_t y); // 3
CRGB colorBand2(uint8_t x, uint8_t y); //4
CRGB colorBand3(uint8_t x, uint8_t y); //5
CRGB colorBand4(uint8_t x, uint8_t y); //6
CRGB colorBand5(uint8_t x, uint8_t y); //7
CRGB colorBand6(uint8_t x, uint8_t y); //8
CRGB colorBand7(uint8_t x, uint8_t y); //9
CRGB colorBand8(uint8_t x, uint8_t y); //10

CRGB palletePattern(CRGBPalette16 pallette, uint8_t x, uint8_t y);
#endif
