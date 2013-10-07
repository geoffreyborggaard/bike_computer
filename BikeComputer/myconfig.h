#ifndef MYCONFIG_H
#define MYCONFIG_H

#include <avr/eeprom.h>


struct config_struct {
  uint16_t wheel_circumference;
  uint8_t contrast;
} config;


void init_config();
void store_config();
  

#endif
