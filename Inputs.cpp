#include "Inputs.h"
#include <FastLED.h>

byte brightness = 0;
byte brightnessbuttonState = 0;
byte brightnesslastButtonState = 0;

byte currentPattern = 0;
byte patternbuttonState = 0;
byte patternlastButtonState = 0;

byte currentColor = 0;
byte colorbuttonState = 0;
byte colorlastButtonState = 0;



void inputSetup(){
   pinMode(BRIGHTNESS_INPUT_PIN, INPUT);
   pinMode(PATTERN_SWITCH_INPUT_PIN, INPUT);
   pinMode(COLOR_SWITCH_INPUT_PIN, INPUT);
   pinMode(INPUT_CHANGED_OUTPUT_PIN, OUTPUT);
   
   
   digitalWrite(BRIGHTNESS_INPUT_PIN, HIGH);
   digitalWrite(PATTERN_SWITCH_INPUT_PIN, HIGH);
   digitalWrite(COLOR_SWITCH_INPUT_PIN, HIGH);
   digitalWrite(INPUT_CHANGED_OUTPUT_PIN, LOW);
}

int handleColorChange(){
  colorbuttonState = digitalRead(COLOR_SWITCH_INPUT_PIN);
  if (colorbuttonState != colorlastButtonState) {
    if (colorbuttonState == LOW) {
       currentColor++;
       digitalWrite(INPUT_CHANGED_OUTPUT_PIN, HIGH);
       if(currentColor == 12) {
        currentColor = 0;
       }
    }
    colorlastButtonState = colorbuttonState;
    digitalWrite(INPUT_CHANGED_OUTPUT_PIN, LOW);
  }
  return currentColor;
}

int handlePatternChange(){
  patternbuttonState = digitalRead(PATTERN_SWITCH_INPUT_PIN);
  if (patternbuttonState != patternlastButtonState) {
    if (patternbuttonState == LOW) {
       currentPattern++;
       digitalWrite(INPUT_CHANGED_OUTPUT_PIN, HIGH);
       if(currentPattern == 9) {
        currentPattern = 0;
       }
    }
    patternlastButtonState = patternbuttonState;
    digitalWrite(INPUT_CHANGED_OUTPUT_PIN, LOW);
  }
  return currentPattern;
}

void handleBrightnessChange(){
  brightnessbuttonState = digitalRead(BRIGHTNESS_INPUT_PIN);
  if (brightnessbuttonState != brightnesslastButtonState) {
    if (brightnessbuttonState == LOW) {
       //Serial.println(brightness);
       brightness++;
       digitalWrite(INPUT_CHANGED_OUTPUT_PIN, HIGH);
       if(brightness == 255) {
        brightness = 0;
       }
       FastLED.setBrightness(brightness);
    }
    brightnesslastButtonState = brightnessbuttonState;
    digitalWrite(INPUT_CHANGED_OUTPUT_PIN, LOW);
  }
}

