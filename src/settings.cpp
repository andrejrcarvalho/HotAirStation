#include "settings.h"

void Settings::loadFromEEPROM(){
  temperature = 0;
  airFlow = 100;
  standbyFunSpeed = 25;
  pid = {2.0,3.0,1.0};
}

