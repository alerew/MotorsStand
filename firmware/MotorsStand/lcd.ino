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
  arrowPos = constrain(arrowPos, 0, page == 0 ? 3 : 1);

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
  printData(arrowPos * 2, ' ');
  lcd.setCursor(0, 1);
  printData(arrowPos * 2 + 1, ' ');
  /*switch (arrowPos) {
    case 0:
      printData(F("Thrust"), data.thrust);
      lcd.setCursor(0, 1);
      printData(F("Power"), (float)(data.amperage * data.voltage));
      break;
    case 1:
      printData(F("Temp"), data.temp, 223);
      lcd.setCursor(0, 1);
      printData(F("Vibration"), data.vibration);
      break;
    case 2:
      printData(F("RPM"), data.rpm);
      lcd.setCursor(0, 1);
      printData(F("Amperage"), data.amperage);
      break;
    case 3:
      printData(F("Voltage"), data.voltage);
      lcd.setCursor(0, 1);
      lcd.print(F("                "));
      break;
  }*/
}
void settingsMenu() {
  //printData(0, F("Motor"), settings.motor ? F("On") : F("Off"));
  //lcd.setCursor(0, 1);
  //printData(1, F("Value"), settings.value);
}
/*
template<typename T>
void printData(const String& name, T data) {  // lcd.print($"{name}: {data}    ")
  printData(-1, name, (String)data, ' ');
}
template<typename T>
void printData(const String& name, T data, char end) {  // lcd.print($"{name}: {data}{end}    ")
  printData(-1, name, (String)data, end);
}
template<typename T>
void printData(int8_t pos, const String& name, T data) {  // lcd.print($"{pos==arrowPos ? '>' : ' '}{name}: {data}    ")
  printData(pos, name, (String)data, ' ');
}
void printData(int8_t pos, const String& name, const String& data, char end) {
  String s;
  build(s, pos, name, data, end);
  lcd.print(s);
}*/

void printData(uint8_t pos, char end) {
  String s;
  //if (pos >= 0) s += (pos == arrowPos) ? cursors[controlState] : ' ';
  if (pos < NUM_DATA) {
    namesFromP(s, pos);
    s += ": ";
    MtypeToStr(s, dataValues[pos], dataTypes[pos]);
    s += end;
    s += "        ";
  }
  else s = "               ";
  lcd.print(s);
}

void build(String& s, int8_t pos, const String& name, const String& data, char end) {
  if (pos >= 0) s += (pos == arrowPos) ? cursors[controlState] : ' ';
  s += name;
  s += ": ";
  s += data;
  s += end;
  s += "        ";
}

#endif

void MtypeToStr(String& s, void* var, Mdata_t type) {
  if (!var) {
    s += '0';
    return;
  }
  switch (type) {
    case M_STR:
      s += *(String*)var;
      break;
    case M_CSTR:
      s += (char*)var;
      break;

    case M_BOOL:
      s += *(bool*)var;
      break;

    case M_INT8:
      s += *(int8_t*)var;
      break;

    case M_UINT8:
      s += *(uint8_t*)var;
      break;

    case M_INT16:
      s += *(int16_t*)var;
      break;
    case M_UINT16:
      s += *(uint16_t*)var;
      break;

    case M_INT32:
      s += *(int32_t*)var;
      break;
    case M_UINT32:
      s += *(uint32_t*)var;
      break;

    case M_FLOAT:
      s += *(float*)var;
      break;
    case M_DOUBLE:
      s += *(double*)var;
      break;

    case M_NULL:
      s += '0';
      break;
  }
}
void namesFromP(String& s, uint8_t num) {
  char buffer[16];
  uint16_t ptr = pgm_read_word(&(dataNames[num]));
  uint8_t i = 0;

  do {
    buffer[i] = (char)(pgm_read_byte(ptr++));
  } while (buffer[i++] != NULL);
  s += buffer;
}