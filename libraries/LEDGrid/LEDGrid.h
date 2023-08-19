/* LEDGrid.h
Header for the LEDGrid class, which abstracts the illumination of a grid of WS2812B LED strips.

Users specify grid configuration information in config.h in the project root folder.

*/
#ifndef LEDGRID_H
#define LEDGRID_H

#include <FastLED.h>

// Main project config
#include "../../config.h"


class LEDGrid {
public:
  // Function that takes in a (y, x) position in [-1, 1]x[-1, 1], the
  // time t in seconds since viz initialization, and a history
  // buffer for position (y,x).
  typedef CRGB (*ColorFunction)(float y, float x, float t, CRGB history[HISTORY_BUFFER_DEPTH]);
  
  static const float gridWidth;
  static const float gridHeight;

  LEDGrid(byte ledDataPins[], ColorFunction func);
  void setColorFunction(ColorFunction func);
  void update(float t);
  void clear();

private:
  // Approximate relative X and Y positions of LEDs within a grid cell.
  static const float LED_REL_POS_X[N_LEDS_PER_STRIP];
  static const float LED_REL_POS_Y[N_LEDS_PER_STRIP];
  CRGB leds[N_ROWS][N_COLS*N_LEDS_PER_STRIP];
  ColorFunction colorFunction;
  CRGB historyBuffer[N_ROWS][N_COLS][N_LEDS_PER_STRIP][HISTORY_BUFFER_DEPTH];
  
  void yxFromIndex(uint8_t row, uint8_t col, uint8_t idx, float *y, float *x);
};

#endif // LEDGRID_H

