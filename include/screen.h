#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "config.h"
#include "settings.h"
#include "helper.h"

#define DEBUG

#ifdef DEBUG
  #define debugln(x) Serial.println(x);
  #define debug(x) Serial.print(x);
#else
  #define debugln(x)
  #define debug(x)
#endif


class Screen {
 private:
  Adafruit_SSD1306 _display = Adafruit_SSD1306(128, 64);
  Settings* _settings;

  void bootScreen();
  void mainScreen(double temperature, double power);
  void temperatureMenu();
  void airFlowMenu();
  void mainMenu();

  void pidMenu();


  void printCenter(uint16_t y, char * text);
  void printCenter(uint16_t x, uint16_t y, char* text);
  void printRight(uint16_t y, char * text);

  void setMenu(uint8_t menu);
  void setSubMenu(uint8_t menu);
  void goBack();

  uint8_t _selectedMenu[2] =  {0,0};
  uint16_t _temp = 0;
  uint8_t _menuSelector = 0;

 public:
  void begin(Settings* settings);
  void tic(double temperature, double power);
};

struct MenuItem {
  char * name;
  void (Screen::*callback)();
};

#endif