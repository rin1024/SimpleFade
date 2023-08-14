/**
 * MP3-Triggerの音量をソフトウェアシリアルで制御するテスト
 * 
 * 音声ファイル
 * モノ / サンプルレート: 22kHz / mp3ファイル
 */
#include <SimpleFade.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 7); // RX, TX
SimpleFade simpleFade;

int currentTrackNo = 0;
uint32_t updateTimer = 0;

void setup() {
  Serial.begin(38400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  mySerial.begin(38400);
}

void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }

  if (Serial.available()) {
    int val = Serial.read();
    if (val == '0') {
      // 音量をmaxに戻す
      mySerial.write('v');
      mySerial.write('0');

      // 強制的に初期値に戻しておく
      simpleFade.setCurrentValue(0);

      // 立て続けに送ると無視されることがあるので、delayはさむ
      delay(50);

      // 楽曲再生
      int trackNo = currentTrackNo;
      while (currentTrackNo == trackNo) {
        trackNo = random(1, 5);
      }
      mySerial.write('t');
      mySerial.write((byte)trackNo);

      currentTrackNo = trackNo;

      //Serial.print("trackNo: ");
      //Serial.println(trackNo);
    }
    // fade out
    else if (val == '1') {
      int targetValue = 100;
      uint32_t durationMillis = 2000;
      simpleFade.setup(targetValue, durationMillis);
      simpleFade.enableDebug(DEBUG_TYPE_PRINT);
      simpleFade.start();
    }
    // fade in
    else if (val == '2') {
      int targetValue = 0;
      uint32_t durationMillis = 2000;
      simpleFade.setup(targetValue, durationMillis);
      simpleFade.enableDebug(DEBUG_TYPE_PRINT);
      simpleFade.start();
    }
  }

  if (simpleFade.isActive()) {
    if (millis() - updateTimer > 150) {
      // 0になるにつれて音が出るっぽい(たぶん100でミュート)
      byte currentVolume = byte(simpleFade.update());
      mySerial.write('v');
      mySerial.write(currentVolume);
      updateTimer = millis();
    }
  }
}
