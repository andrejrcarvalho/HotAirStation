#include "hotAirGun.h"

void HotAirGun::begin(Settings * settings) {
  _settings = settings;
}

void HotAirGun::fanSpeed(uint8_t speed) { analogWrite(FUN_CONTROL, speed); }

void HotAirGun::heaterOn() { heaterStatus = 1; }

void HotAirGun::heaterOff() { heaterStatus = 0; }

bool HotAirGun::heaterIsOn() { return heaterStatus > 0; }

double HotAirGun::getTemperature() { 
  unsigned long time = millis();
  if (_nextRead < time) {
    _lastestReadTemp = _max6675.readCelsius();
    _nextRead = time + _tempReadInterval;
  }
  return _lastestReadTemp;
 }

bool HotAirGun::getSwitchStatus() { return digitalRead(GUN_SWITCH); }