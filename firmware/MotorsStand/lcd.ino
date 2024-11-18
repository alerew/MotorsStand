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
  if (lcdTmr.isReady()) {
    page = constrain(page, 0, 1);
    arrowPos = constrain(arrowPos, 0, page == 0 ? 3 : 1);     // ограничиваем положение указателя

    lcd.home();
    if (page == 0) {
      mainMenu();       // главное меню
    } else if (page == 1) {
      settingsMenu();   // меню настроек
    }
  }
#endif
}

#if LCD == 1

void mainMenu() {
  switch (arrowPos) {
    case 0:
      printData(F("Thrust"), TO_STR(data.thrust));
      lcd.setCursor(0, 1);
      printData(F("Power"), TO_STR(data.power));
      break;
    case 1:
      printData(F("Temp"), TO_STR(data.temp), 223);
      lcd.setCursor(0, 1);
      printData(F("Vibration"), TO_STR(data.vibration));
      break;
    case 2:
      printData(F("RPM"), TO_STR(data.rpm));
      lcd.setCursor(0, 1);
      printData(F("Amperage"), TO_STR(data.amperage));
      break;
    case 3:
      printData(F("Voltage"), TO_STR(data.voltage));
      lcd.setCursor(0, 1);
      printData(F("Efficiency"), TO_STR(data.efficiency));
      break;
    case 4:
      printData(F("Volume"), TO_STR(data.volume));
      break;
  }
}
void settingsMenu() {
  printData(0, F("Motor"), (settings.motor ? F("On") : F("Off")));
  lcd.setCursor(0, 1);
  printData(1, F("Value"), TO_STR(settings.value));
}


void printData(const String& name, const String& data) {  // lcd.print($"{name}: {data}    ")
  printData(-1, name, data, ' ');
}
void printData(const String& name, const String& data, char end) {  // lcd.print($"{name}: {data}{end}    ")
  printData(-1, name, data, end);
}
void printData(int8_t pos, const String& name, const String& data) {  // lcd.print($"{pos==arrowPos ? '>' : ' '}{name}: {data}    ")
  printData(pos, name, data, ' ');
}
void printData(int8_t pos, const String& name, const String& data, char end) {
  String s;
  build(s, pos, name, data, end);
  lcd.print(s);
}

void build(String& s, int8_t pos, const String& name, const String& data, char end) {
  if (pos >= 0) s += (pos == arrowPos) ? cursors[controlState] : ' ';
  s += name;
  s += F(": ");
  s += data;
  s += end;
  s += F("       ");
}

#endif
