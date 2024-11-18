#include "data.h"

#define TENZO 1
#define TEMP 1
#define LCD 1
#define SERIAL 1

void setup() {
  Serial.begin(9600);
  initSensors();      // инициализация датчиков
  initLcd();          // инициализация дисплея
  initMotor();        // инициализация мотора
  //calibration();
}

void loop() {
  readSensors();      // чтение показаний с датчиков
  send();             // отправка показаний с датчиков
  parsing();          // парсинг данных с компьютера
  readEnc();          // энкодер и логика курсора
  showMenu();         // вывод на дисплей
  motorTick();        // вращение мотора
}
