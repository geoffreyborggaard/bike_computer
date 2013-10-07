#include "pins.h"
#include "menu.h"
#include "screen.h"

int buttonPressed = 0;
int button_pins[5] = {BUTTON_UP_PIN, BUTTON_DOWN_PIN, BUTTON_LEFT_PIN, BUTTON_RIGHT_PIN, BUTTON_IN_PIN};

void init_menu() {
  for (int i = 0; i < 5; i++) {
    pinMode(button_pins[i], INPUT);
    digitalWrite(button_pins[i], HIGH);
  }
}


void check_buttons() {
  boolean buttonDown = false;
  for (int i = 0; i < 5; i++) {
    int state = digitalRead(button_pins[i]);
    if (state == LOW) {  // Pins normally HIGH.
      buttonDown = true;
      buttonPressed = i;
    }
  }
  /*
  Serial.print("Button Pressed:");
  Serial.print(buttonPressed);
  Serial.print("Button Pressed:");
  Serial.print(buttonDown);
  Serial.print(" contrast: ");
  Serial.println(contrast);  
  */
  if (buttonDown) {
    switch (buttonPressed) {
       case BUTTON_UP_PIN:
         config.contrast++;
         set_contrast(config.contrast);
         break;
       case BUTTON_DOWN_PIN:
         config.contrast--;
         set_contrast(config.contrast);
         break;
       case BUTTON_IN_PIN:
         change_menu_mode();
         break;  
    }
    
    Serial.print("Contrast set: ");
    Serial.println(config.contrast);
    buttonDown = false;
    buttonPressed = 0;
  } 
}
    
    
void change_menu_mode() {
  if (menu_mode == MODE_HUD) {
    menu_mode = MODE_MENU;
  } else {
    menu_mode = MODE_HUD;
  }
}
