#if LCD == 1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#endif

void initLcd() {
#if LCD == 1
  lcd.init();
  lcd.backlight();
  lcd.clear();
#endif
}
void showMenu() {
#if LCD == 1
  if (!lcdTmr.isReady()) return;
  page = constrain(page, 0, 1);
  arrowPos = constrain(arrowPos, 0, 1);

  lcd.home();
  if (page == 0) {
    mainMenu();
  } else if (page == 1) {
    settingsMenu();
  }
#endif
}

#if LCD == 1

void mainMenu() {
  switch (arrowPos) {
    case 0:
      printData(F("Thrust"), data.thrust);
      lcd.setCursor(0, 1);
      printData(F("Power"), data.amperage * data.voltage);
      break;
    case 1:
      printData(F("Temp"), data.temp, 223);
      lcd.setCursor(0, 1);
      printData(F("Vibration"), data.vibration);
      break;
  }
}
void settingsMenu() {
  printData(0, F("Motor"), settings.motor ? F("On") : F("Off"));
  lcd.setCursor(0, 1);
  printData(1, F("Value"), settings.value);
}
template<typename T>
void printData(const String& name, T data) {  // lcd.print($"{name}: {data}    ")
  printData(-1, name, (String)data, ' ');
}
template<typename T>
void printData(const String& name, T data, char end) {  // lcd.print($"{name}: {data}{end}    ")
  printData(-1, name, (String)data, end);
}
template<typename T>
void printData(byte pos, const String& name, T data) {  // lcd.print($"{pos==arrowPos ? '>' : ' '}{name}: {data}    ")
  printData(pos, name, (String)data, ' ');
}
void printData(byte pos, const String& name, const String& data, char end) {
  String s;
  build(s, pos, name, data, end);
  lcd.print(s);
}

void build(String& s, int8_t pos, const String& name, const String& data, char end) {
  if (pos >= 0) s += (pos == arrowPos) ? cursors[controlState] : ' ';
  s += name;
  s += ": ";
  s += data;
  s += end;
  s += "    ";
}
#endif