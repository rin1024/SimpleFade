#include <FastLED.h>
#include <SimpleFade.h>

#define __M_COMPILE_DATE__ __DATE__ " " __TIME__
#define __M_FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/////////////// serial
#define BAUD_RATE 115200

/////////////// fade
SimpleFade simpleFade;

/////////////// faseLed
#define DATA_PIN     3
#define NUM_LEDS   144

#define TARGET_HUE        100
#define TARGET_SATURATION 255

CRGBArray<NUM_LEDS> leds;

////////////////////////////////////////
void setup() {
  Serial.begin(BAUD_RATE);
  delay(1000);

  Serial.println();
  Serial.print("[");
  Serial.print(__M_COMPILE_DATE__);
  Serial.print("]");
  Serial.println(__M_FILENAME__);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void loop() {
  while (Serial.available() > 0) {
    int val = Serial.read();

    // only works '1'
    if (val == '1') {
      int targetBrightness = (int)random(0, 255);
      uint32_t durationMillis = 3000;//(uint32_t)random(0, 10000);
      simpleFade.setup(targetBrightness, durationMillis);
      simpleFade.enableDebug(DEBUG_TYPE_PRINT);

      Serial.print("targetBrightness: ");
      Serial.print(targetBrightness);
      Serial.print(", durationMillis: ");
      Serial.print(durationMillis);
      Serial.println();

      simpleFade.start();
    }
  }

  int currentBrightness = simpleFade.update();
  fill_solid(leds, NUM_LEDS, CHSV(TARGET_HUE, TARGET_SATURATION, currentBrightness));
  FastLED.show();
}
