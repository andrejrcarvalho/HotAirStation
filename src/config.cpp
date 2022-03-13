#include "config.h"

void setupPinModes(){
  pinMode(TRIAC_PIN, OUTPUT);
  digitalWrite(TRIAC_PIN, LOW);
  pinMode(ZEROCORSS_PIN, INPUT_PULLUP);
  pinMode(ENCODER_SWT, INPUT);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(GUN_SWITCH, INPUT_PULLUP);
  pinMode(FUN_CONTROL, OUTPUT);
  digitalWrite(FUN_CONTROL, LOW);
}