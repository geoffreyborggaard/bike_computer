#include "myconfig.h"

#define START_CONFIG 0

const uint8_t magic_num = 43;

void init_config() {
    // See if our magic number is in the start position.
    unsigned int pos = START_CONFIG;
    uint8_t magic = eeprom_read_byte((const uint8_t *)pos);
    pos += 1;
    if (magic != magic_num) {
      // Set defaults.
      config.wheel_circumference = 2095;
      config.contrast = 50;
      store_config();
    } else {
      eeprom_read_block((void *) &config, (void *) pos, sizeof(config_struct));
      Serial.print("Config: ");
      Serial.print(config.contrast);
    }
  }      
  
  void store_config() {
    unsigned int pos = START_CONFIG;
    eeprom_write_byte((uint8_t *)pos, magic_num);
    pos += 1;
    eeprom_write_block((const void *) &config, (void *) pos, sizeof(config_struct));
    Serial.println("Storing");
  }
 
