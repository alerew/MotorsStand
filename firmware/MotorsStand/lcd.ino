#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void show() {
  if (lcdTmr.isReady()) {
    String str = "";
    str += F("Thrust: ");
    str += data.thrust;
    str += F(" Power: ");
    str += (data.amperage * data.voltage);
    str += F("\nTemp: ");
    str += data.temp;
    lcd.home();
    lcd.print(str);
  }
}