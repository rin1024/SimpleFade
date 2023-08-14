# SimpleFade

Fadeの時間管理を簡素化するためのutilクラス

## Usage

```
#include <SimpleFade.h>

SimpleFade simpleFade;

void setup() {
  Serial.begin(115200);

  int targetValue = 80;
  int durationMillis = 5000;
  simpleFade.setup(targetValue, durationMillis);
  simpleFade.enableDebug(DEBUG_TYPE_PRINT);
}

void loop() {
  while (Serial.available() > 0) {
    Serial.read(); // just read and trush
    simpleFade.start();
  }

  simpleFade.update();
}
```

## Requirement

- Arduino IDE

## Usage

## Author

[@rin1024](https://twitter.com/rin1024)

## License

[MIT](http://b4b4r07.mit-license.org)

