#include "speed.h"
#include "pins.h"

#define BUFFER_SIZE 10

#define CONVERT_TO_MPH  2.2369

    
volatile unsigned long wheelTimes[BUFFER_SIZE];
volatile unsigned long crankTimes[BUFFER_SIZE];

volatile int nextWheelPosToWrite = 0;
volatile int nextWheelPosToRead = 0;

volatile int nextCrankPosToWrite = 0;
volatile int nextCrankPosToRead = 0;

void init_speed() {
  pinMode(WHEEL_PIN, INPUT);
  pinMode(CRANK_PIN, INPUT);
  attachInterrupt(0, wheelInterrupt, FALLING);
  attachInterrupt(1, crankInterrupt, FALLING);
  
  startTime = millis();
}

void wheelInterrupt() {
  sleep_disable();
  wheelTimes[nextWheelPosToWrite++] = millis();
  nextWheelPosToWrite %= BUFFER_SIZE;
}

void crankInterrupt() {
  crankTimes[nextCrankPosToWrite++] = millis();
  nextCrankPosToWrite %= BUFFER_SIZE;
}

void calculate() {
  calculateSpeed();
  calculateRpm();
}

void calculateSpeed() {
  while (nextWheelPosToRead != nextWheelPosToWrite) {
    unsigned long wheelTime = wheelTimes[nextWheelPosToRead];
    unsigned long delta = wheelTime - lastWheelRead;
    float mPerS = ((float) (config.wheel_circumference)) / ((float)delta);
    currentSpeed = CONVERT_TO_MPH * mPerS;
    
    lastWheelRead = wheelTime;
    
    unsigned long distanceMm = config.wheel_circumference * wheelCounter;
    float mPs = ((float) distanceMm) / ((float) millis());
    averageSpeed = mPs * CONVERT_TO_MPH;

    nextWheelPosToRead++;
    nextWheelPosToRead %= BUFFER_SIZE;
    wheelCounter++;
  }
}

void calculateRpm() {
  while (nextCrankPosToRead != nextCrankPosToWrite) {
    unsigned long crankTime = crankTimes[nextCrankPosToRead];
    unsigned long delta = crankTime - lastCrankRead;
    currentRpm = ((float)60000) / ((float) delta);
    lastCrankRead = crankTime;
    nextCrankPosToRead++;
    nextCrankPosToRead %= BUFFER_SIZE;
  }
}


