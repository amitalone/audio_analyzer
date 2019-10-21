#define LOG_OUT 0 // use the log output function
#define LIN_OUT 1
#define FFT_N 128// set to 128 point fft
#include <FFT.h> // include the library

#include "Animation.h"
#include "ColorFunctions.h"
#include "Inputs.h"

#define DATA_PIN 6
#define ROWS 12
#define COLUMNS 24
#define NUM_LEDS ROWS * COLUMNS
#define START_FREQENCY_BAND_POSITION 2
#define DEBUG 1

CRGB leds[NUM_LEDS];
uint8_t peaks[COLUMNS];


//PROGMEM const uint8_t testPeaks[24] = {5, 10, 12, 4, 6, 11, 5, 10, 12, 4, 6, 11, 5, 10, 12, 4, 6, 2, 3, 10, 11, 6, 3, 8};

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(16);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 20000);
  
  analogReference(EXTERNAL);
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0
  DIDR0 = 0x01; // turn off the digital input for adc0
  if(DEBUG) {
    Serial.begin(115200);
  }

  delay(50);
  FastLED.clear();
  setMatrix(leds, COLUMNS, ROWS);
  inputSetup();
  
}

void loop() {
  
 while(true){
   
  // upDownSweep(peaks, COLUMNS, 5, rainbow);
  // halfScreenupDownSweep(peaks, COLUMNS, 5, rainbow);
  // midFramColumnPattern(peaks, COLUMNS, 25, rainbow);

  handleBrightnessChange();
  byte currentPattern = handlePatternChange();
  byte currentColor = handleColorChange();
  auto colorFunction = rainbow;
  
  switch (currentColor) {
    case 0:
      colorFunction = rainbow;
      //colorFunction = colorBand4;
      break;
    case 1:
      colorFunction = colorRBBlend;
      break;
    case 2:
      colorFunction = colorBlueScale;
      break;
    case 3:
      colorFunction = colorBand1;
      break;
    case 4:
      colorFunction = colorBand2;
      break;
    case 5:
      colorFunction = colorBand3;
      break;
    case 6:
      colorFunction = colorBand4;
      break;
    case 7:
      colorFunction = colorBand5;
      break;
    case 8:
      colorFunction = colorBand6;
      break;
        case 9:
      colorFunction = colorBand7;
      break;
    case 10:
      colorFunction = colorBand8;
      break;
    default:
      colorFunction = rainbow;
      break;
  } 
  
  getSamples();
 
  auto animFunction = upDownSweep;
  switch (currentPattern) {
    case 0:
      animFunction = upDownSweep;
      //animFunction = columnGraph;
      break;
    case 1:
      animFunction = halfScreenupDownSweep;
      break;
    case 2:
      animFunction = midFramColumnPattern;
      break;
    case 3:
      animFunction = fallingDrops;
      break;
    case 4:
      animFunction = fallingDropsWhite;
      break;
    case 5:
      animFunction = lineGraph;
      break;
    case 6:
      animFunction = lineGraphUpDown;
      break;
    case 7:
      animFunction = columnGraph;
      break;
    case 8:
      animFunction = upDownSweepBG;
      break;
    default:
      animFunction = upDownSweep;
      break;
  }    

  animFunction(peaks, COLUMNS, 10, colorFunction);
 }
}
void getSamples() {
  cli();  // UDRE interrupt slows this way down on arduino1.0
  TIMSK0 = 0;
  for (int i = 0 ; i < FFT_N *2; i += 2) { // save 256 samples
    while (!(ADCSRA & 0x10)); // wait for adc to be ready
    ADCSRA = 0xf5; // restart adc
    byte m = ADCL; // fetch adc data
    byte j = ADCH;
   
    int k = (j << 8) | m; // form into an int
    k -= 0x0200; // form into a signed int
    k <<= 6; // form into a 16b signed int
     
    fft_input[i] = k; // put real data into even bins
    fft_input[i + 1] = 0; // set odd bins to 0
  }
  fft_window(); // window the data for better frequency response
  fft_reorder(); // reorder the data before doing the fft
  fft_run(); // process the data in the fft
  fft_mag_lin();
  TIMSK0 = 1;
  sei();
  if(DEBUG) {
   /*for(int n = START_FREQENCY_BAND_POSITION; n < COLUMNS+START_FREQENCY_BAND_POSITION; n++){
    Serial.print(fft_lin_out[n+1]);
    Serial.print("\t");
    }
    Serial.println(""); */


  }
  
  int x =0;
  for(uint8_t i = START_FREQENCY_BAND_POSITION; i <= COLUMNS+START_FREQENCY_BAND_POSITION; i++){
          x=fft_lin_out[i+1]/1;
          x = constrain(x, 5, 100);
          uint8_t index = i-START_FREQENCY_BAND_POSITION;
          x = map(x, 5, 100, 0, 11);
          peaks[index] = x;
    }
}

