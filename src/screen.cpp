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

void Screen::tic(double temperature, double power) {
  if (_selectedMenu[0] == 0) {
    long btnPressTime = readButtonPressTime();
    if (btnPressTime > 50 && btnPressTime < 1000) {
      setMenu(1);
    } else if (_selectedMenu[0] == 0 && btnPressTime >= 1000) {
      setMenu(2);
    }
  }
  uint8_t menu = _selectedMenu[0] * 10 + _selectedMenu[1];
  switch (menu) {
    case 10:
      temperatureMenu();
      break;

    case 20:
      mainMenu();
      break;
    case 21:
      airFlowMenu();
      break;
    case 22:
      pidMenu();
      break;

    default:
      _selectedMenu[0] = 0;
      _selectedMenu[1] = 0;
      mainScreen(temperature, power);
      break;
  }
}

void Screen::mainScreen(double temperature, double power) {
  _display.clearDisplay();
  _display.setTextColor(WHITE);

  _display.setTextSize(1);
  _display.setCursor(0, 4);
  _display.print("Set:");
  _display.print(round(_settings->temperature));

  _display.setTextSize(1);
  _display.setCursor(60, 4);
  char buffer[20];
  sprintf(buffer, "Power: %ld", round(power));
  printRight(4, buffer);

  _display.setTextSize(3);
  _display.setCursor(0, 20);
  sprintf(buffer, "%ld", round(temperature));
  printCenter(25, buffer);
  _display.setTextSize(1);
  _display.print('o');

  _display.display();
}


void Screen::mainMenu() {
  char items[][10] = {"> Fun", "> PID", "< Back"};
  size_t menuSize = 3;

  if (readButtonPressTime() > 50) {
    if (_menuSelector == menuSize - 1) {
      goBack();
    } else {
      setSubMenu(_menuSelector+1);
    }
    _menuSelector = 0;
    return;
  }

  int step = readEncoder(1);
  if ((step + _menuSelector) >= 0 && (step + _menuSelector) < menuSize)
    _menuSelector += step;


  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(BLACK, WHITE);
  printCenter(0, "Main Menu");

  for (size_t i = 0; i < menuSize; i++) {
    if (_menuSelector == i)
      _display.setTextColor(BLACK, WHITE);
    else
      _display.setTextColor(WHITE, BLACK);
    printCenter(16 + i * 10, items[i]);
  }
  _display.display();
}

void Screen::airFlowMenu() {
  if (_temp == 0) {
    _temp = _settings->airFlow;
  }

  int step = readEncoder(5);
  if ((step + _temp) >= 0 && (step + _temp) <= 100)
    _temp += step;


  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(BLACK, WHITE);
  printCenter(0, "Air Flow:");

  _display.setTextSize(3);
  _display.setTextColor(WHITE, BLACK);
  char buffer[5];
  sprintf(buffer, "%d%%", _temp);
  printCenter(25, buffer);
  _display.display();

  if (readButtonPressTime() > 50) {
    goBack();
    _settings->airFlow = _temp;
    _temp = 0;
  }
}

void Screen::temperatureMenu() {
  if (_temp == 0) {
    _temp = _settings->temperature;
  }

  int step = readEncoder(5);
  if ((step + _temp) >= 0 && (step + _temp) <= 400)
    _temp += step;

  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(BLACK, WHITE);
  printCenter(0, "Temperature");
  _display.drawLine(0, 8, 84, 8, BLACK);

  _display.setTextSize(3);
  _display.setTextColor(WHITE, BLACK);
  char buffer[10];
  sprintf(buffer, "%d", _temp);
  printCenter(25, buffer);
  _display.setTextSize(1);
  _display.print("o");
  _display.display();

  if (readButtonPressTime() > 50) {
    goBack();
    _settings->temperature = _temp;
    _temp = 0;
  }
}

void Screen::pidMenu() {
  long btnPressed = readButtonPressTime();
  if ( btnPressed > 50 && btnPressed < 1000) {
    if(_menuSelector >= 2)
      _menuSelector = 0;
    else
      _menuSelector++;
  }else if ( btnPressed > 1000) {
    goBack();
  }
  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(BLACK, WHITE);
  printCenter(0, "PID Menu");
  
  char buffer[10];

  double * var;
  if(_menuSelector == 0)
    var = &(_settings->pid.Kp);
  else if(_menuSelector == 1)
    var = &(_settings->pid.Ki);
  else
    var = &(_settings->pid.Kd);

  int step = readEncoder(1);
  if ((step + _temp) >= 0 && (step + _temp) <= 400)
    *var +=step ;

  _display.setTextColor(WHITE, BLACK);
  printCenter(12,20, "Kp");
  sprintf(buffer, "%ld", round(_settings->pid.Kp));
  if(_menuSelector == 0) _display.setTextColor(BLACK, WHITE);
  printCenter(12,35, buffer);

  _display.setTextColor(WHITE,BLACK);
  printCenter(64,20, "Ki");
  sprintf(buffer, "%ld", round(_settings->pid.Ki));
  if(_menuSelector == 1) _display.setTextColor(BLACK, WHITE);
  printCenter(64,35, buffer);

  _display.setTextColor(WHITE,BLACK);
  printCenter(106,20, "Kd");
  sprintf(buffer, "%ld", round(_settings->pid.Kd));
  if(_menuSelector == 2) _display.setTextColor(BLACK, WHITE);
  printCenter(106,35, buffer);

  _display.display();
}



void Screen::setMenu(uint8_t menu) {
  if (menu <= 0) return;
  debug("Go menu: ");
  debug(_selectedMenu[0]);
  debug(_selectedMenu[1]);
  _selectedMenu[0] = menu;
  debug("->");
  debug(_selectedMenu[0]);
  debugln(_selectedMenu[1]);
}

void Screen::setSubMenu(uint8_t menu) {
  if (menu <= 0) return;
  _selectedMenu[1] = menu;
}

void Screen::goBack() {
  debug("Go back: ");
  debug(_selectedMenu[0]);
  debug(_selectedMenu[1]);
  for (size_t i = 1; i >= 0; i--) {
    if (_selectedMenu[i] > 0) {
      _selectedMenu[i] = 0;
      break;
    }
  }
  debug("->");
  debug(_selectedMenu[0]);
  debugln(_selectedMenu[1]);
}


void Screen::printCenter(uint16_t y, char* text) {
  uint8_t center = _display.width() / 2;
  uint16_t fontWidth = 0;
  _display.getTextBounds(text, 0, 0, 0, 0, &fontWidth, 0);

  _display.setCursor(center - (fontWidth / 2), y);
  _display.print(text);
}

void Screen::printCenter(uint16_t x, uint16_t y, char* text) {
  uint16_t fontWidth = 0;
  _display.getTextBounds(text, 0, 0, 0, 0, &fontWidth, 0);

  _display.setCursor(x - (fontWidth / 2), y);
  _display.print(text);
}

void Screen::printRight(uint16_t y, char* text) {
  uint8_t right = _display.width();
  uint16_t fontWidth = 0;
  _display.getTextBounds(text, 0, 0, 0, 0, &fontWidth, 0);

  _display.setCursor(right - fontWidth, y);
  _display.print(text);
}