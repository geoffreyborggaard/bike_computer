#include <avr/sleep.h>

#include "myconfig.h"
#include "speed.h"
#include "menu.h"
#include "screen.h"


// Milliseconds that pass before we go to sleep.
#define SLEEP_MILLIS 30000

/*
 * TODO:
 *  - HR Display
 *  - HR Graph
 *  - Solder headphone jack for wheel and crank sensors.
 *  - Solder joystick controller.
 *  - Connect heart rate sensor
 *  - Display heart rate.
 */



void setup()   {
  Serial.begin(9600);
  Serial.println("Hello world");
  init_config();
  init_screen();
  init_heartrate();
  init_speed();
  init_menu();
  drawScreen();
}  


int loopCounter = 0;

void loop() {  
  if (loopCounter++ % 2 == 0) {
    calculate();
    drawScreen();
  }
  check_buttons();
  check_sleep();
  check_heartrate();
  delay(200);
}

void check_sleep() {
  if (millis() - lastWheelRead > SLEEP_MILLIS) {
    sleep_enable();  // sleep_disable() is called on wheelInterrupt().
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();
    sleep_disable();
  }
}





