#include "screen.h"

void Screen::begin(Settings* settings) {
  _settings = settings;
  _display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  _display.clearDisplay();
  bootScreen();
}

void Screen::bootScreen() {
  _display.setTextSize(2);
  _display.setTextColor(BLACK, WHITE);
  _display.setCursor(10, 10);
  _display.print("HELLO!");
  _display.display();
  _display.clearDisplay();
  delay(1000);
}

void Screen::tic(String* status) {
  long pressedTime = readButtonPressTime();
  if (pressedTime > 50 ) {
    temperatureMenu();
  }else {
    mainScreen(status);
  }
}

void Screen::mainScreen(String* status) {
  _display.clearDisplay();
  _display.setTextColor(WHITE);
  
  _display.setTextSize(1);
  _display.setCursor(0, 4);
  _display.print("SET:");
  _display.print(_settings->temperature);
  
  _display.setTextSize(3);
  _display.setCursor(0, 20);
  printCentered(20, *status);
  _display.setTextSize(1);
    _display.print("o");
  //_display.setCursor(13, 23);
  //_display.print(String(_settings->pulsePower) + "%");

  // _display.setCursor(50, 15);
  // _display.print("TIME");
  // _display.setCursor(50, 23);
  // if (_settings->mode == MODE_TIME_PULSE) {
  //   _display.print(String(_settings->pulseTime) + "ms");
  // } else {
  //   _display.print("----");
  // }

  // _display.setCursor(3, 40);
  // _display.setTextSize(1);
  // _display.print("Status:" + *status);
  _display.display();
}

void Screen::airFlowMenu() {
  int airFlow = _settings->airFlow;
  int tmpAirFlow = 0;

  while (readButtonPressTime() < 50) {
    int step = readEncoder(5);
    if ((step + airFlow) >= 5 && (step + airFlow) <= 100) airFlow += step;

    if (step == 0 && tmpAirFlow == airFlow) continue;

    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(BLACK, WHITE);
    printCentered(0, "Air Flow:");
    _display.drawLine(0, 8, 84, 8, BLACK);

    _display.setTextSize(2);
    _display.setTextColor(BLACK, WHITE);
    printCentered(25, String(airFlow) + "%");
    _display.display();
    tmpAirFlow = airFlow;
  }
  _settings->airFlow = airFlow;
}

void Screen::temperatureMenu() {
  unsigned long temperature =  _settings->temperature;
  unsigned long tmpTemperature = 0;

  while (readButtonPressTime() < 50) {
    int step = readEncoder(1);
    if ((step + temperature) >= 0 && (step + temperature) <= 100) temperature += step;

    if (step == 0 && tmpTemperature == temperature) continue;

    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(BLACK, WHITE);
    printCentered(0, "Temperature");
    _display.drawLine(0, 8, 84, 8, BLACK);

    _display.setTextSize(3);
    _display.setTextColor(WHITE, BLACK);
    _display.setCursor(25, 25);
    printCentered(25, String(temperature));
    _display.setTextSize(1);
    _display.print("o");
    _display.display();
    tmpTemperature = temperature;
  }
   _settings->temperature = temperature;
}

void Screen::printCentered(uint16_t y, String text) {
  uint8_t center = _display.width() / 2;
  uint16_t fontWidth = 0;
  _display.getTextBounds(text, 0, 0, 0, 0, &fontWidth, 0);

  _display.setCursor(center - (fontWidth / 2), y);
  _display.print(text);
}