#include <FastLED.h>

#include "LEDGrid.h"



// Compute the LED Grid "width", in normalized coordinates where each cell
// has width 1 and height 1
const float LEDGrid::gridWidth = N_COLS + (N_COLS - 1) * REL_COL_BORDER_WIDTH;
const float LEDGrid::gridHeight = N_ROWS + (N_ROWS - 1) * REL_ROW_BORDER_WIDTH;

// Constructor: Initialize LEDs on each data pin, set all LEDs to black, and
// Set the initial color function.
LEDGrid::LEDGrid(byte ledDataPins[], ColorFunction func) {
  for (uint8_t r = 0; r < N_ROWS; ++r) {
    FastLED.addLeds<WS2812B, ledDataPins[r]>(leds[r], N_COLS * N_LEDS_PER_STRIP);
  }
  clear();
  setColorFunction(func);
}

// Pick the color function that will be used to update the LEDGrid's
// colors.
void LEDGrid::setColorFunction(ColorFunction func) {
  colorFunction = func;
}


void LEDGrid::update(float t) {
  // ColorFunctions compute a function on a spatial range of [-1, 1] in Y and
  // [-1, 1] in X. We need to interpolate that into actual LED positions.
  // LEDGrid::update does so by assuming:
  //   1. The top-left interior corner of the LED grid is (-1, -1).
  //   2. The bottom right interior corner of the LED grid is (1, 1).
  //   3. Grid cells are squares with identical interior measurements and identical borders.
  //   4. LED relative placement in each grid cell (normalized to the range [0,1]) is the
  //      same in each grid cell and defined in LED_REL_POS_X and LED_REL_POS_Y.

  // Update the LEDs according to the color functions
  float yNow, xNow;
  for (uint8_t r = 0; r < N_ROWS; ++r) {
    for (uint8_t c = 0; c < N_COLS; ++c) {
      for (uint8_t i = 0; i < N_LEDS_PER_STRIP; ++i) {
        // Compute the current LED's (y,x) coordinate and store it in (yNow, xNow)
        yxFromIndex(r, c, i, &yNow, &xNow);
        // Pass (y,x), time t, and history to compute the new color for this LED
        leds[r][c * N_LEDS_PER_STRIP + i] = colorFunction(
          yNow, xNow, t, historyBuffer[r][c][i]);
        // Shift the history buffer
        for (int b = HISTORY_BUFFER_DEPTH - 1; b > 0; --b) {
          historyBuffer[r][c][i][b] = historyBuffer[r][c][i][b-1];
        }
        // Update latest history with newest value
        historyBuffer[r][c][i][0] = leds[r][c * N_LEDS_PER_STRIP + i];
      }
    }
  }

  FastLED.show();
}

// Compute the approximate (y, x) position of an LED from its index within
// the grid cell at row `row` and column `col`.
void LEDGrid::yxFromIndex(uint8_t row, uint8_t col, uint8_t idx, float *y, float *x) {
  // Compute the (y, x) location (within [-1,1]x[-1,1]) of the top-left
  // corner of the cell at row `row` and column `col`.

  //  Get unnormalized LED position as
  // Cell anchor absolute position + LED relative position
  *y = row * (1 + REL_ROW_BORDER_WIDTH) + LED_REL_POS_Y[idx];
  *x = col * (1 + REL_COL_BORDER_WIDTH) + LED_REL_POS_X[idx];
  // Normalize to [0, 1] then to [-1, 1]
  *y = 2 * *y / gridHeight - 1;
  *x = 2 * *x / gridWidth - 1;
}

void LEDGrid::clear() {
  // Clearing the LEDs and the history buffer
  for (uint8_t r = 0; r < N_ROWS; ++r) {
    for (uint8_t c = 0; c < N_COLS; ++c) {
      for (uint8_t i = 0; i < N_LEDS_PER_STRIP; ++i) {
        leds[r][c * N_LEDS_PER_STRIP + i] = CRGB::Black;
        for (uint8_t b = 0; b < HISTORY_BUFFER_DEPTH; ++b) {
          historyBuffer[r][c][i][b] = CRGB::Black;
        }
      }
    }
  }

  FastLED.show();
}
