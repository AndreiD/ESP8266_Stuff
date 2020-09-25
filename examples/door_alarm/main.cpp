#include <Arduino.h>
#include <FastLED.h>
#include <EasyButton.h>

#include "Arduino.h"

// Round Led Strip Settings
#define NUM_LEDS 24
#define DATA_PIN 3

// Deactivate Alarm Button Settings
#define DEACTIVATE_BTN 0
uint8 debounce = 10;
bool pullup = true;
bool invert = false;

CRGB leds[NUM_LEDS];
EasyButton deactivateButton(DEACTIVATE_BTN, debounce, pullup, invert);

void deactivateAlarm()
{
  Serial.println("Alarm is deactivated for 5 seconds");
  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Green;
    FastLED.show();
    delay(200);
    leds[whiteLed] = CRGB::Black;
  }
}

void setup()
{
  Serial.begin(115200);
  delay(300);
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);

  deactivateButton.begin();
  deactivateButton.onPressed(deactivateAlarm);
}

void loop()
{
  Serial.print(".");

  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds[whiteLed] = CRGB::Red;
    FastLED.show();
    deactivateButton.read();
    delay(50);
    leds[whiteLed] = CRGB::Black;
  }
}
