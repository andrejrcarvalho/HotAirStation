#include <Arduino.h>
#include "max6675.h" 

#define MAX6675_SO 9
#define MAX6675_CS 11
#define MAX6675_SCK 10

#define GUN_SWITCH 12
#define FUN_CONTROL 13


MAX6675 module(MAX6675_SCK, MAX6675_CS, MAX6675_SO);
int status = LOW;

void setup() {
  pinMode(GUN_SWITCH, INPUT_PULLUP);
  pinMode(FUN_CONTROL, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Starting....");
  // put your setup code here, to run once:
}

void loop() {
  float temperature = module.readCelsius(); 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(F("°C "));   
  
  Serial.print("GUN: ");
  Serial.println(digitalRead(GUN_SWITCH));
  status = status == LOW ? HIGH : LOW;
  digitalWrite(FUN_CONTROL, status);
  delay(1000);
}