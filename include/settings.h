#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

#define MODE_TIME_PULSE 0
#define MODE_PULSE 1

class Settings {
 public:
  unsigned long temperature = 0;
  uint8_t airFlow = 0;

  int power = 0;

  void loadFromEEPROM();
};

#endif