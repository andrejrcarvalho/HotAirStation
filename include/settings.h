#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

#define MODE_TIME_PULSE 0
#define MODE_PULSE 1

class Settings {
 public:
  uint8_t temperature = 0;
  uint8_t pulsePower = 0;
  unsigned short mode = 0;

  void loadFromEEPROM();
};

#endif