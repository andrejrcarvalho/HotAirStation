#include "settings.h"

void Settings::loadFromEEPROM(){
  temperature = 100;
  pulsePower = 75;
  mode = MODE_PULSE;
}

