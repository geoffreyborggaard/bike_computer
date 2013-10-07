#include "heartrate.h"
#include "pins.h"

unsigned int current_heart_rate = 130;
unsigned int heart_rate_minute = 0;
unsigned long heart_rate_start_time = millis();
unsigned int beats_this_minute = 0;

unsigned int heart_rate_fast_counter = 0;
unsigned long heart_rate_fast_time = millis();

void init_heartrate() {
  pinMode(HEARTRATE_PIN, INPUT);
  digitalWrite(HEARTRATE_PIN, HIGH);
  
  for (int i = 0; i < HEART_RATE_HISTORY; i++) {
    // heart_rate_history[i] = 0;
    heart_rate_history[i] = 100 + i;
  } 
}

void check_heartrate() {
   int state = digitalRead(HEARTRATE_PIN);
   
   unsigned long elapsed = millis() - heart_rate_start_time;
   unsigned int minute = elapsed / 60000;
   if (minute != heart_rate_minute) {
      heart_rate_minute = minute;
      for (int i = HEART_RATE_HISTORY - 1; i > 0; i++) {
       heart_rate_history[i] = heart_rate_history[i - 1];
      }

      heart_rate_history[0] = beats_this_minute;
      current_heart_rate = beats_this_minute;
      beats_this_minute = 0;
   }
   
   if (heart_rate_state != state) {
     state = heart_rate_state;
     beats_this_minute++;
   }
   
   heart_rate_fast_counter++;   
   if (heart_rate_fast_counter == 10) {
     unsigned long delta = millis() - heart_rate_fast_time;
     float beatsPerSecond = ((float) delta) / 10000.0;
     current_heart_rate = (int) beatsPerSecond * 60.0;
     heart_rate_fast_counter = 0;
     heart_rate_fast_time = millis();
   }
 }
 
 void shuffle_heart_rate() {
  
 }
