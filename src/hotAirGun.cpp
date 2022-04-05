#include "hotAirGun.h"

void HotAirGun::begin(Settings* settings) { _settings = settings; }

void HotAirGun::fanSpeed(uint8_t speed) { analogWrite(FUN_CONTROL, speed); }

void HotAirGun::heaterOn() {
  fanSpeed(map(_settings->airFlow, 0, 100, 0, 255));
  heaterStatus = 1;
}

void HotAirGun::heaterOff() {
  if (_lastestReadTemp > 50)
   fanSpeed(map(_settings->standbyFunSpeed, 0, 100, 0, 255));
  else
    fanSpeed(0);
  
  heaterStatus = 0;
}

bool HotAirGun::heaterIsOn() { return heaterStatus > 0; }

double HotAirGun::getTemperature() {
  unsigned long time = millis();
  if (_nextRead < time) {
    _lastestReadTemp = _max6675.readCelsius();
    _nextRead = time + _tempReadInterval;
    // Serial.println(_lastestReadTemp);
  }
  return _lastestReadTemp;
}

bool HotAirGun::getSwitchStatus() { return digitalRead(GUN_SWITCH); }