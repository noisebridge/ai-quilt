#include <HCSR04.h>
#include <VariableTimedAction.h>
#include "FastLED.h"

#define NUM_LEDS 20
#define DISTANCE_THRESHOLD 50 // We can change this in the future.
#define DATA_PIN 3
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
CRGB ROULETTE[] = {CRGB::Beige, CRGB::Blue, CRGB::Red, CRGB::Yellow, CRGB::Green, CRGB::DarkCyan, CRGB::Magenta, CRGB::DarkBlue, CRGB::Maroon, CRGB::MediumPurple};
int startInteger = 0;
size_t roulette_length = sizeof(ROULETTE)/sizeof(ROULETTE[0])-1;
CRGB color;
bool dim = false;

unsigned char incomingBytes[4];
unsigned char storePacket[10];
const char HEADER[] = {'a', 'z'};
unsigned long duration = 1000;
unsigned long msBeatTime = 0;
size_t colorIndex = 0;

#define N_SENSORS 1

struct HcResult {
  bool objectDetected[N_SENSORS];
};
/*
 * @param sensors : Object representing the sensor array
 * @param threshold : Threshold below which an object is detected
 * @return For each sensor, whether an object is detected there.
 */
HcResult detectObject(const HCSR04& sensors, float threshold) {
  HcResult output;
  for (int i = 0; i < N_SENSORS; ++i) {
    float distance = sensors.dist(i);
    output.objectDetected[i] = (
      distance > 0 &&
      distance < threshold
    );
  }
  return output;
}

 
// Non-class strobe function
size_t change_color() {
  return random(0, roulette_length);
}

void strobe(const unsigned long currentTime, const unsigned long lastBeatMs, const unsigned long duration, size_t color) {
    CRGB output = ROULETTE[color];
    double fraction_of_strobe = double(currentTime - lastBeatMs) / duration;
    uint8_t fade = min(int(fraction_of_strobe*256), 255); // Amount to fade, maximum being total darkness.
    output.fadeToBlackBy(fade);
    for (int i = 0; i<NUM_LEDS; ++i) {
      leds[i] = output;
      leds[i].fadeToBlackBy(120);
    }
}


class LED : public VariableTimedAction {
public:

  //this method will be called at your specified interval
  unsigned long run() override {
    unsigned long currentTime = millis();  
    // Change color if next beat.
    while ((currentTime - msBeatTime)  > duration) {
      colorIndex = change_color();
      msBeatTime += duration;
    }
  
    strobe(currentTime, msBeatTime, duration, colorIndex);
  
    FastLED.show();
  }
  unsigned long lastUpdate = 0;

};

LED led;
HcResult sensorResults;
int j;
unsigned long lastUpdate;
HCSR04 hc(6, new int[N_SENSORS] {11}, N_SENSORS); //initialisation class HCSR04 (trig pin , echo pin, number of sensor)
void setup() { 
  FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS); 
//  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS); 
  Serial.begin(115200);
  j=0;
  lastUpdate = 0;
}


void loop() {  
  sensorResults = detectObject(hc, DISTANCE_THRESHOLD);
  if (sensorResults.objectDetected[0] && millis() - lastUpdate > 100) {
  Serial.println("Update");
    for (int i = 0; i < NUM_LEDS; i++) {
     leds[i] = ROULETTE[j];
    }
    FastLED.show();
    j = (j + 1) % roulette_length;
    lastUpdate = millis();
  } else if (!sensorResults.objectDetected[0]) {
    Serial.println("==========");
  }
}
