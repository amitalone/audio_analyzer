#include "ColorFunctions.h"

CRGB colorRBBlend(uint8_t x, uint8_t y) {
  return CRGB((y * 256 / 12),  0, y*10);
}

CRGB colorBlueScale(uint8_t x, uint8_t y) {
  return CRGB(5*sq(y), 0, 50*sq(y));
}

CRGB colorBlack(uint8_t x, uint8_t y){
  return CRGB::Black;
}

CRGB colorBand1(uint8_t x, uint8_t y) {
  const PROGMEM CRGB colors[4] = {0x00ffff, 0x0000ff, 0x8000ff, 0xff00bf};
  byte colorIndex  = ceil((x)%4);
  return colors[colorIndex].nscale8_video(18 * y);
}

CRGB colorBand2(uint8_t x, uint8_t y) {
  const PROGMEM CRGB colors[4] = {CRGB::Blue, CRGB::DarkBlue, CRGB::SkyBlue, CRGB::LightBlue};
  byte colorIndex  = ceil((x)%4);
  return colors[colorIndex];
}

CRGB colorBand3(uint8_t x, uint8_t y) {
  const PROGMEM CRGB colors[4] = {CRGB::Maroon, CRGB::DarkRed, CRGB::Orange, CRGB::White};
  byte colorIndex  = ceil((x)%4);
  return colors[colorIndex];
}

CRGB colorBand4(uint8_t x, uint8_t y) {
  return palletePattern(OceanColors_p, x, y);
}

CRGB colorBand5(uint8_t x, uint8_t y) {
  return palletePattern(ForestColors_p, x, y);
}

CRGB colorBand6(uint8_t x, uint8_t y) {
  return palletePattern(RainbowColors_p, x, y);
}

CRGB colorBand7(uint8_t x, uint8_t y) {
  return palletePattern(PartyColors_p, x, y);
}

CRGB colorBand8(uint8_t x, uint8_t y) {
  return  palletePattern(HeatColors_p, x, y);
}

CRGB palletePattern(CRGBPalette16 pallette, uint8_t x, uint8_t y) {
  byte colorIndex  = ceil((x)% 16);
  return pallette[colorIndex];
}

CRGB rainbow(uint8_t x, uint8_t y) {
  byte *c;
  c=Wheel(((y * 256 / 12) + y) & 255);
  
 return CRGB(*c , *(c+1), *(c+2));
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
 
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
