#include <Arduino.h>

#include "config.h"
#include "screen.h"
#include "hotAirGun.h"

Screen screen;
Settings settings;
HotAirGun hotAirgun;

bool zeroCross = false;

void zeroCrossing();

void setup() {
  Serial.begin(9600);
  Serial.println("Starting....");
  
  setupPinModes();
  
  // Stop interrupts for till make the settings
  noInterrupts();

  // Setup Timer
  TCCR2A = 0;
  TCCR2A |= (1 << WGM21);  // set the CTC (Clear Timer on Compare) mode for
                           // timer0 with OCRA as top
  TCCR2B = 0;
  TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22);  // Set prescaler to 1024
  TIMSK2 |= (1 << OCIE2A);  // activate timer compare match interrupt for OCR0A
                            // and OCR0B

  // Setup Interrupt to detect zero crossing
  attachInterrupt(digitalPinToInterrupt(ZEROCORSS_PIN), zeroCrossing, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), encoderInterrupt, CHANGE);
  // Activate again the interrupt
  interrupts();

  
  settings.loadFromEEPROM();

  screen.begin(&settings);
  hotAirgun.begin(&settings);

  hotAirgun.heaterOn();
  
}

  String temp = "";
void loop() {
  temp = String(hotAirgun.getTemperature());
  screen.tic(&temp);


}



// external interrupt, occurs after every zero crossing point
void zeroCrossing() {
  if(hotAirgun.heaterIsOn() ) {
    TCNT2 = 0;  // clear timer2 counter
    OCR2A = map(settings.temperature, 100, 0, 18,
                157);  // set OCR2B value between 10 and 156 (0.64ms - 9.98ms)
                       // according to the potentiometer value
    zeroCross = true;     // set zero crossing point flag to 1
  }
}

ISR(TIMER2_COMPA_vect) {  // compare match interrupt for OCR0A
  if (zeroCross) {
    digitalWrite(TRIAC_PIN, HIGH);
    delayMicroseconds(100);
    digitalWrite(TRIAC_PIN, LOW);
    zeroCross = false;
  }
}