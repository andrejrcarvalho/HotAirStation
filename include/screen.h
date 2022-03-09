#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include "config.h"
#include "settings.h"
#include "helper.h"


class Screen {
 private:
  Adafruit_SSD1306 _display = Adafruit_SSD1306(128, 64);
  Settings* _settings;

  void bootScreen();
  void mainMenu();
  void mainScreen(String* status);
  void powerMenu();
  void modeMenu();
  void timeMenu();
  void printCentered(uint16_t y, String text);

 public:
  void begin(Settings* settings);
  void tic(String* status);
};

struct MenuItem {
  String name;
  void (Screen::*callback)();
};

#endif