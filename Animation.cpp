#include "Animation.h"

CRGB *matrix;
uint8_t COLUMNS = 0;
uint8_t ROWS = 0;


void midFramColumnPattern(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  uint8_t maxYValue = getMax(peaks, peaksSize) /2;
  uint8_t midYAxis = (ROWS/2)-1;
  
  for (uint8_t yPosition = 0; yPosition <= maxYValue; yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if (yPosition <= peaks[xPosition] /2) {
       putPixel(xPosition, midYAxis + yPosition, (*upColorFunc)(xPosition, midYAxis + yPosition));
       putPixel(xPosition, midYAxis - yPosition, (*upColorFunc)(xPosition, midYAxis - yPosition));
      }
    }
   // FastLED.setBrightness( peaks[random(6,12)]);
    FastLED.show(); 
    delay(speed);
  }
  
  for (uint8_t yPosition = 0; yPosition <= maxYValue; yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
     if (yPosition < peaks[xPosition] ) {
        putPixel(xPosition,  (midYAxis+peaks[xPosition] /2) - yPosition, CRGB::Black);
        putPixel(xPosition,  (midYAxis-peaks[xPosition] /2) + yPosition, CRGB::Black);
       //putPixel(xPosition, midYAxis + yPosition, (*upColorFunc)(xPosition, midYAxis + yPosition).fadeToBlackBy( 0 ));
       //putPixel(xPosition, midYAxis - yPosition, (*upColorFunc)(xPosition, midYAxis - yPosition).fadeToBlackBy( 0 ));
        
     }
    }
     FastLED.show();
      delay(speed);
  }
}

void halfScreenupDownSweep(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  for (uint8_t yPosition = 0; yPosition < ROWS; yPosition++) {
    byte y = 0, xpos = 0;
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
       if(xPosition > 11) {
          y = 11 - yPosition;
          xpos = 23 - xPosition;
        }else {
           y = yPosition;
           xpos = xPosition;
        }
        
      if (yPosition <= peaks[xpos]) {
       
         putPixel(xPosition, y, (*upColorFunc)(xPosition+1, y+1));
      }
      /*if (y> 0 && y == peaks[xpos]) {
         putPixel(xPosition, y, CRGB(100, 100, 90).fadeToBlackBy( 10 ));
      }*/
    }
    
   FastLED.show();
   
   delay(speed);
  }
  
   for (uint8_t yPosition = 0; yPosition < ROWS; yPosition++) {
    byte y = 0;
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if(xPosition > 11) {
          y =  yPosition;
        }else {
           y = 11 - yPosition;
        }
       putPixel(xPosition,  y, CRGB::Black);
    }
    
   FastLED.show();
   delay(speed);
  }
}

void upDownSweep(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  upDownSweepFn(peaks, peaksSize, speed, upColorFunc, false);
}

void upDownSweepBG(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  upDownSweepFn(peaks, peaksSize, speed, upColorFunc, true);
}

void upDownSweepFn(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t), bool background) {
  for (uint8_t yPosition = 0; yPosition < ROWS; yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if (yPosition <= peaks[xPosition]) {
         putPixel(xPosition, yPosition, (*upColorFunc)(xPosition+1, yPosition+1));
      }
    }
   FastLED.show();
   delay(speed);
  }
   for (uint8_t yPosition = 0; yPosition < ROWS; yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if(background) {
        putPixel(xPosition, 11- yPosition, CRGB(100, 100, 100));
      }else {
       putPixel(xPosition, 11- yPosition, CRGB::Black); 
      }
    }
   FastLED.show();
   delay(speed);
  }
}


void fallingDrops(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  dropEffect(peaks,peaksSize, speed, upColorFunc, false);
}
void fallingDropsWhite(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  dropEffect(peaks,peaksSize, speed, upColorFunc, true);
}

void dropEffect(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t), bool white) {
    for (uint8_t yPosition = 0; yPosition < getMax(peaks, COLUMNS); yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if (yPosition <= peaks[xPosition]) {
         putPixel(xPosition, yPosition, (*upColorFunc)(xPosition+1, yPosition+1));
      }
    }
   FastLED.show();
   delay(speed);
  }
  FastLED.clear();
  
  for (uint8_t yPosition = 0; yPosition < getMax(peaks, COLUMNS); yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
        if (yPosition <= peaks[xPosition]) {
          CRGB color = (*upColorFunc)(xPosition+1, yPosition+1);
          if(white) {
             color = CRGB::White;
          }
          putPixel(xPosition, peaks[xPosition]- yPosition, color);
        }
        CRGB color = (*upColorFunc)(xPosition+1, peaks[xPosition]);
        if(white) {
           color = CRGB::White;
        }
        putPixel(xPosition, peaks[xPosition], color);
    }
    FastLED.show();
    delay(speed);
    FastLED.clear();
 }

}

void lineGraph(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  FastLED.clear();
  for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
    putPixel(xPosition, peaks[xPosition], (*upColorFunc)(xPosition+1, peaks[xPosition]+1));
  }
  FastLED.show();
  delay(150);
}

void lineGraphUpDown(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  speed = 30;
  for (uint8_t yPosition = 0; yPosition < getMax(peaks, COLUMNS); yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if (yPosition <= peaks[xPosition]) {
         putPixel(xPosition, yPosition, (*upColorFunc)(xPosition+1, yPosition+1));
      }
    }
    FastLED.show();
    delay(speed);
    FastLED.clear();
  }

  for (uint8_t yPosition = 0; yPosition < getMax(peaks, COLUMNS); yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if (yPosition <= peaks[xPosition]) {
        putPixel(xPosition, peaks[xPosition]- yPosition, (*upColorFunc)(xPosition+1, yPosition+1));
      }
    }
    FastLED.show();
    delay(speed);
    FastLED.clear();
 }
 /* 
   for (uint8_t yPosition = 0; yPosition < ROWS; yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
       putPixel(xPosition, 11- yPosition, CRGB::Black);
    }
   FastLED.show();
   delay(speed);
  }*/
}

//uint8_t frame1[24] = {0};
void columnGraph(uint8_t peaks[], uint8_t peaksSize, int speed, CRGB (*upColorFunc)(uint8_t, uint8_t)) {
  for (uint8_t yPosition = 0; yPosition < ROWS; yPosition++) {
    for (uint8_t xPosition = 0; xPosition < COLUMNS; xPosition++) {
      if (yPosition > peaks[xPosition]) {
         putPixel(xPosition, yPosition, CRGB::Black);
      }else {
        putPixel(xPosition, yPosition, (*upColorFunc)(xPosition+1, yPosition+1));
      }
    }
  }
  FastLED.show();
  delay(speed);

  /*for(uint8_t x =0; x<COLUMNS; x++ ) {
    uint8_t delta = frame1[x] - peaks[x];
      if(delta < 0) {
        for(uint8_t y=frame1[x]+1; y<=peaks[x]; y++) {
          putPixel(x, y, (*upColorFunc)(x+1, y+1));
        }
      }
      if(delta > 0) {
        for(uint8_t y=peaks[x]+1; y<=frame1[x]; y++) {
          putPixel(x, y, CRGB::Black);
        }
      }
    }

    for(uint8_t x =0; x<COLUMNS; x++ ) {
      frame1[x] = peaks[x];
    }
  FastLED.show();
  delay(speed);*/
}

void setMatrix(CRGB *leds, uint8_t coloumns, uint8_t rows) {
  matrix = leds;
  COLUMNS = coloumns;
  ROWS = rows;
 
}

void putPixel(uint8_t column, uint8_t row, CRGB color) {
   matrix[getPosition(column, row)] = color;
}

int getPosition(uint8_t x, uint8_t y) {
  return (y * (COLUMNS)) + (x);
}

uint8_t getMax(uint8_t rawArray[], uint8_t size) {
  uint8_t max_v = 0;
  for ( uint8_t i = 0; i < size; i++ )
  {
    if ( rawArray[i] > max_v )
    {
      max_v = rawArray[i];
    }
  }
  return max_v;
}
