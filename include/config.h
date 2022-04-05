#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define MAX6675_SO 9
#define MAX6675_CS 8
#define MAX6675_SCK 7

#define GUN_SWITCH 12
#define FUN_CONTROL 10

#define ENCODER_CLK 3
#define ENCODER_DT 5
#define ENCODER_SWT 6

#define ZEROCORSS_PIN 2
#define TRIAC_PIN 4

void setupPinModes();

#endif