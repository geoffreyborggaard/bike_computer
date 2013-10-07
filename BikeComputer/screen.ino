#include "screen.h"
#include "myconfig.h"
#include "heartrate.h"

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(19, 18, 17, 15, 16);

void init_screen() {
  display.begin();
  display.setContrast(config.contrast);
  display.clearDisplay();   // clears the screen and buffer
}

void p(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        display.print(tmp);
}


void drawScreen() {
  if (menu_mode == MODE_HUD) {
    drawHud();
  } else {
    drawMenu();
  }
}

void drawHud() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  
  int whole = (int) currentSpeed;
  int dec = (int) (currentSpeed * 100.0) - ((float) whole * 100);
  p("%2d", whole);
  display.setCursor(19, 0);
  p(".");
  display.setCursor(28, 0);
  p("%02d", dec);
  
 
  display.setTextSize(1);
  display.setCursor(53,0);
  whole = (int) averageSpeed;
  dec = (int) (averageSpeed * 100.0) - ((float) whole * 100);
  p("%d.%d\n", whole, dec);
  
  display.setCursor(50, 8);
  p("%3d\n", currentRpm);

  display.setTextSize(1);
  unsigned long elapsed = millis() - startTime;
  int seconds = (elapsed / 1000) % 60;
  int minutes = (elapsed / 60000) % 60;
  int hours = (elapsed / 3600000);
  p("%02d:%02d:%02d", hours, minutes, seconds);
  
  drawHeartRateGraph();
  display.display();
}

void drawHeartRateGraph() {
  display.drawLine(23, 27, 23, 47, 1);
  display.drawLine(23, 47, 83, 47, 1);
  for ( int i = 0; i < HEART_RATE_HISTORY; i++) {
    int y = heart_rate_history[i] - 100;
    if (y > 100) {
      y = 100;
    } else if (y > 200) {
      y = 200;
    }
    
    y = y / 5;
    
    display.drawPixel(23 + i, 47 - y, 1);
    display.setCursor(0, 27);
    p("%03d\n", current_heart_rate);
    p(" %s", heart_rate_state ? "V" : "");
  }
}


void drawMenu() {
  p("Menu goes here");
}


void set_contrast(uint8_t contrast) {
  display.setContrast(config.contrast);
}


