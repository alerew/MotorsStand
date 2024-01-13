#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void showMenu() {
  if (!lcdTmr.isReady()) return;
  page = constrain(page, 0, 1);
  arrowPos = constrain(arrowPos, 0, 1);

  lcd.home();
  if (page == 0) {
    switch (arrowPos) {
      case 0:
        printData("Thrust", data.thrust);
        lcd.setCursor(0, 1);
        printData("Power", data.amperage * data.voltage);
        break;
      case 1:
        printData("Temp", data.temp, 223);
        lcd.setCursor(0, 1);
        printData("Vibration", data.vibration);
        break;
    }
  } else if (page == 1) {
    printData(0, "Motor", settings.motor ? "On" : "Off");
    lcd.setCursor(0, 1);
    printData(1, "Value", settings.value);
  }
}

template<typename T>
void printData(const String& name, T data) {    // lcd.print($"{name}: {data}    ")
  lcd.print(build(-1, name, (String)data, ' '));
}
template<typename T>
void printData(const String& name, T data, char end) {    // lcd.print($"{name}: {data}{end}    ")
  lcd.print(build(-1, name, (String)data, end));
}
template<typename T>
void printData(byte pos, const String& name, T data) {    // lcd.print($"{pos==arrowPos ? '>' : ' '}{name}: {data}    ")
  lcd.print(build(pos, name, (String)data, ' '));
}

String build(int8_t pos, const String& name, const String& data, char end){
  String s = "";
  if(pos >= 0) s += (pos == arrowPos) ? cursor : ' ';
  s += name;
  s += ": ";
  s += data;
  s += end;
  s += "    ";
  return s;
}