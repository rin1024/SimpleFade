#include <SimpleFade.h>

#define __M_COMPILE_DATE__ __DATE__ " " __TIME__
#define __M_FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/////////////// serial
#define BAUD_RATE 115200

#define NUM_POS 2
#define NUM_VAL 10

char mVal[NUM_POS][NUM_VAL];
int mPosIndex = 0;
int mValIndex = 0;

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
}

void loop() {
  getSerialData();

  simpleFade.update();
}

void getSerialData() {
  // Serial Event
  while (Serial.available() > 0) {
    int serialData = Serial.read();

    // SP
    if(serialData == 32) {
      if (mPosIndex < NUM_POS) {
        mValIndex = 0;
        mPosIndex++;
      }
    } 
    else if (serialData < 48 || serialData > 70) {
      continue;
    }
    // 0-9
    else if ((serialData >= 48 && serialData <= 57) || (serialData >= 65 && serialData <= 70)) {
      if (mValIndex < NUM_VAL) {
        mVal[mPosIndex][mValIndex++] = serialData;
      }
    }
    // :
    else if(serialData == 58) {
      int targetValue = atoi(mVal[0]);
      int durationMillis = atoi(mVal[1]);

      Serial.print("[serial received]");
      Serial.print(targetValue);
      Serial.print("\t");
      Serial.print(durationMillis);
      Serial.println("\t");

      simpleFade.setup(targetValue, durationMillis);
      simpleFade.enableDebug(DEBUG_TYPE_PLOT);
      simpleFade.start();

      for(int i=0;i<NUM_POS;i++) {
        for(int j=0;j<NUM_VAL;j++) {
          mVal[i][j] = '\0';
        }
      }
      mPosIndex   = 0;
      mValIndex = 0;
    }
  }
}
