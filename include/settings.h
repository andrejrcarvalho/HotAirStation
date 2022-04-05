#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>

#define MODE_TIME_PULSE 0
#define MODE_PULSE 1

struct PID_CONSTS {
    double Kp;
    double Ki;
    double Kd;
  };

class Settings {
 public:
  double temperature = 0;
  uint16_t airFlow = 0;
  uint8_t standbyFunSpeed = 0;
  struct PID_CONSTS  pid = {0.0,0.0,0.0};
  
  void loadFromEEPROM();
};




#endif