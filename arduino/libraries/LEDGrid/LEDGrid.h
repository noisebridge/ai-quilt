#include <FastLED.h>

// LED Grid layout constants
#define N_ROWS 6
#define N_COLS 6
#define N_LEDS_PER_STRIP 27
#define HISTORY_BUFFER_DEPTH 10

class LEDGrid {
public:
  typedef CRGB (*ColorFunction)(int x, float t, const CRGB history[HISTORY_BUFFER_DEPTH][N_LEDS_PER_STRIP]);

  LEDGrid(byte ledDataPins[]);
  void setStripFunction(uint8_t row, uint8_t col, ColorFunction func);
  void update(float t);
  void clear();

private:
  CRGB leds[N_ROWS][N_COLS*N_LEDS_PER_STRIP];
  ColorFunction cellFunctions[N_ROWS][N_COLS];
  CRGB historyBuffer[N_ROWS][N_COLS][HISTORY_BUFFER_DEPTH][N_LEDS_PER_STRIP];
};
