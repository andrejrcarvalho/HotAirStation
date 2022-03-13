#ifndef HOTAIRGUN_H
#define HOTAIRGUN_H

#include <Arduino.h>
#include "max6675.h"
#include "config.h"
#include "settings.h"

class HotAirGun {
 private:
  MAX6675 _max6675 = MAX6675(MAX6675_SCK, MAX6675_CS, MAX6675_SO);
  unsigned long _tempReadInterval = 200; //Milliseconds
  unsigned long _nextRead = 0;
  double _lastestReadTemp = 0.0;
  Settings * _settings;
  short heaterStatus = 0;

 public:
  void begin(Settings * settings);

  void fanSpeed(uint8_t speed);
  bool getSwitchStatus();

  void heaterOn();
  void heaterOff();
  bool heaterIsOn();

  double getTemperature();
};

#endif