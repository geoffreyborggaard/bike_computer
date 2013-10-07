#ifndef SPEED_H
#define SPEED_H

volatile unsigned long wheelCounter = 0;
volatile unsigned int lastWheelRead = 0;
volatile unsigned int lastCrankRead = 0;

volatile float currentSpeed = 24.5;
unsigned long startTime = 0;

float averageSpeed = 18.4;
int currentRpm = 72;

void init_speed();
void calculate();

#endif
