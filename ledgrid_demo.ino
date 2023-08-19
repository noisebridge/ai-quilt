#include <cmath>

#include <FastLED.h>

#include "libraries/LEDGrid/LEDGrid.h"
#include "config.h"

// Define a sample ColorFunction that just returns a radially-varying hue.
const CRGB colorFunction(float y, float x, float t, CRGB history[HISTORY_BUFFER_DEPTH]) {
  return CHSV(uint8_t(fmod(80 * (y * y + x * x) + 10 * t, 256.)), 255, 255);
}

LEDGrid ledGrid(LED_DATA_PINS, colorFunction);
unsigned long startTime;

void setup() {
  // Start time
  startTime = millis();
}

void loop() {
  float t = (millis() - startTime) / 1000.0; // Time in seconds since the sketch started running

  // Update the LED grid with the current time
  ledGrid.update(t);
  delay(20); // Optional delay to control refresh rate
}

