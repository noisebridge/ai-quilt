#include "LEDGrid.h"

LEDGrid::LEDGrid(byte ledDataPins[]) {
  for (uint8_t r = 0; r < N_ROWS; ++r) {
    FastLED.addLeds<WS2812B, ledDataPins[r]>(leds[r], N_COLS * N_LEDS_PER_STRIP);
  }
  clear();
}

void LEDGrid::setStripFunction(uint8_t row, uint8_t col, ColorFunction func) {
  functions[row][col] = func;
}

void LEDGrid::update(float t) {

  // Update the LEDs according to the color functions
  for (uint8_t r = 0; r < N_ROWS; ++r) {
    for (uint8_t c = 0; c < N_COLS; ++c) {
      for (uint8_t i = 0; i < N_LEDS_PER_STRIP; ++i) {
        leds[r][c * N_LEDS_PER_STRIP + i] = functions[r][c](i, t, historyBuffer[r][c]);
        // Shift the history buffer
        for (int b = HISTORY_BUFFER_DEPTH - 1; b > 0; --b) {
          historyBuffer[r][c][b][i] = historyBuffer[r][c][b-1][i];
        }
        // Update latest history with newest value
        historyBuffer[r][c][0][i] = leds[r][c * N_LEDS_PER_STRIP + i];
      }
    }
  }

  FastLED.show();
}

void LEDGrid::clear() {
  // Clearing the LEDs and the history buffer
  for (uint8_t r = 0; r < N_ROWS; ++r) {
    for (uint8_t c = 0; c < N_COLS; ++c) {
      for (uint8_t i = 0; i < N_LEDS_PER_STRIP; ++i) {
        leds[r][c * N_LEDS_PER_STRIP + i] = CRGB::Black;
        for (uint8_t b = 0; b < HISTORY_BUFFER_DEPTH; ++b) {
          historyBuffer[r][c][b][i] = CRGB::Black;
        }
      }
    }
  }

  FastLED.show();
}
