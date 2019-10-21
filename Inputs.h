#ifndef Inputs_h
#define Inputs_h

#define BRIGHTNESS_INPUT_PIN 2
#define PATTERN_SWITCH_INPUT_PIN 3
#define COLOR_SWITCH_INPUT_PIN 4
#define INPUT_CHANGED_OUTPUT_PIN 5

void inputSetup();
void handleBrightnessChange();
int handlePatternChange();
int handleColorChange();
#endif
