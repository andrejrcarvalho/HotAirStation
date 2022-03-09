#include <Arduino.h>

#include "config.h"
#include "max6675.h"
#include "screen.h"

MAX6675 max6675(MAX6675_SCK, MAX6675_CS, MAX6675_SO);
unsigned long targetTime = 0;
Screen screen;
Settings settings;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting....");
  setupPinModes();
  targetTime = millis() + 1000;
  settings.loadFromEEPROM();
  screen.begin(&settings);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), encoderInterrupt, CHANGE);
}

void loop() {
  String a = "asdasd";
  screen.tic(&a);
  if (targetTime > millis()) {
    float temperature = max6675.readCelsius();
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(F("°C "));
    targetTime = millis() + 1000;
  }

  short gunStatus = digitalRead(GUN_SWITCH);
  if(gunStatus == HIGH){
    analogWrite(FUN_CONTROL,128);
  }else{
    analogWrite(FUN_CONTROL,0);
  }

}