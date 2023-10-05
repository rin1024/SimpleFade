/**
 * Simple fade control class
 */
#ifndef SIMPLE_FADE_h
#define SIMPLE_FADE_h

/*******************************************
 * include
 *******************************************/
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <avr/pgmspace.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*******************************************
 * const
 *******************************************/
// TODO: to be enum
//#define FADE_BY_DURATION 1
//#define FADE_BY_SPEED    2

#define DEBUG_TYPE_NONE  0
#define DEBUG_TYPE_PRINT 1
#define DEBUG_TYPE_PLOT  2

/**************************************************************************************
 * Simple fade controller
 **************************************************************************************/
class SimpleFade {
  public:
    SimpleFade();

    void setup(int _targetValue, uint32_t _durationMillis);
    int update();

    void start(uint32_t _startMillis);
    void start();
    void pause();
    void stop();

    bool isActive();

    int getCurrentValue();    
    void setCurrentValue(int _currentValue);

    void enableDebug(int _debugType);
    void disableDebug();
    
  private:
    // TODO: implement here
    //uint8_t fadeType;

    // by durationMillis
    uint32_t startMillis;
    uint32_t durationMillis;
    uint32_t ellapsedMillis;

    // TODO: implement here
    // by speed
    // int speed;

    float currentPer;
    int currentValue;
    
    int startValue;  // 開始時にcurrentValue
    int targetValue; // ゴールの(?)currentValue
    
    int debugType;
    
    void debugPrint();
    void debugPlot();
};

#endif
