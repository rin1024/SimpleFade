/**
 * Simple fade control class
 */
#include "SimpleFade.h"

/**
 * コンストラクタ
 */
SimpleFade::SimpleFade() {
  startMillis = 0;
  durationMillis = 0;
  ellapsedMillis = 0;

  currentValue = 0;
  currentPer = 0.0;

  startValue = 0;
  targetValue = 0;
  
  debugType = DEBUG_TYPE_NONE;
}

/**
 * 初期化
 */
void SimpleFade::setup(int _targetValue, uint32_t _durationMillis) {
  targetValue = _targetValue;
  durationMillis = _durationMillis;
}

/**
 * アップデート関数
 */
int SimpleFade::update() {
  // startMillisが0のときはイベント無視
  // かつ、startMillisに遅延を入れる場合も考慮して、millisより超えている時にスタートにしておく
  if (startMillis != 0 && millis() > startMillis) {
    ellapsedMillis = millis() - startMillis;
    
    // 現在の位置をセット
    currentPer = (float)((float)ellapsedMillis / (float)durationMillis);
    currentValue = startValue + (int)round((float)(targetValue - startValue) * currentPer);

    // 終了時
    if (millis() - startMillis > durationMillis) {
      startMillis = 0;

      // 強制的に最後の値をセット
      currentValue = targetValue;
    }

    if (debugType == DEBUG_TYPE_PRINT) {
      debugPrint();
    }
    else if (debugType == DEBUG_TYPE_PLOT) {
      debugPlot();
    }
  }

  return currentValue;
}

/**
 * タイマー開始(遅延を入れる場合)
 */
void SimpleFade::start(uint32_t _startMillis) {
  startMillis = _startMillis;
  startValue = currentValue;
}

/**
 * タイマー開始(デフォルト)
 */
void SimpleFade::start() {
  start(millis());
}

/**
 *
 */
void SimpleFade::pause() {
  // TODO: implement here
}

/**
 * タイマーを停止
 */
void SimpleFade::stop() {
  startMillis = 0;
}

/**
 * デバッグ表示を有効化
 */
void SimpleFade::enableDebug(int _debugType) {
  debugType = _debugType;
}

/**
 * デバッグ表示を無効化
 */
void SimpleFade::disableDebug() {
  debugType = DEBUG_TYPE_NONE;
}

/**
 * デバッグ表示をする
 */
void SimpleFade::debugPrint() {
  Serial.print("[currentPer: ");
  Serial.print(currentPer);
  Serial.print("]\t");

  Serial.print("currentValue: ");
  Serial.print(currentValue);
  Serial.print("(");
  Serial.print(startValue);
  Serial.print(" to ");
  Serial.print(targetValue);
  Serial.print(")\t");
  
  Serial.print("ellapsedMillis: ");
  Serial.print(ellapsedMillis);
  Serial.print("(");
  Serial.print(durationMillis);
  Serial.print(")\t");

  Serial.println();
}

/**
 * プロット用のデバッグ表示をする
 */
void SimpleFade::debugPlot() {
  //Serial.print(currentPer);
  //Serial.print("\t");

  Serial.print(currentValue);
  Serial.print("\t");
  Serial.print(startValue);
  Serial.print("\t");
  Serial.print(targetValue);
  //Serial.print("\t");
  
  //Serial.print(ellapsedMillis);
  //Serial.print("\t");
  //Serial.print(durationMillis);
  //Serial.print("\t");

  Serial.println();
}
