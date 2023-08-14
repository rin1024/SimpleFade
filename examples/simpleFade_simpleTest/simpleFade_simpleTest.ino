#include <SimpleFade.h>

#define __M_COMPILE_DATE__ __DATE__ " " __TIME__
#define __M_FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/////////////// serial
#define BAUD_RATE 115200

/////////////// fade
SimpleFade simpleFade;

////////////////////////////////////////
void setup() {
  Serial.begin(BAUD_RATE);
  delay(1000);

  Serial.println();
  Serial.print("[");
  Serial.print(__M_COMPILE_DATE__);
  Serial.print("]");
  Serial.println(__M_FILENAME__);

  int targetValue = 80;
  int durationMillis = 5000;
  simpleFade.setup(targetValue, durationMillis);
  simpleFade.enableDebug(DEBUG_TYPE_PLOT);

  Serial.print("targetValue: ");
  Serial.print(targetValue);
  Serial.print(", durationMillis: ");
  Serial.print(durationMillis);
  Serial.println();
}

void loop() {
  while (Serial.available() > 0) {
    Serial.read(); // just read and trush
    simpleFade.start();
  }

  simpleFade.update();
}
