#if TENZO == 1

#include "HX711.h"
HX711 scale;

#define weight_of_standard 50.2  // указываем эталонный вес
float calibration_factor = 19.27;
float units;  // задаём переменную для измерений в граммах
float ounces;

#endif

void initTenzo() {
#if TENZO == 1
  delay(500);
  scale.begin(DOUT_PIN, SCK_PIN);  // инициируем работу с платой HX711, указав номера выводов Arduino, к которым подключена плата
  scale.set_scale();               // не калибруем полученные значения
  scale.tare();
  scale.set_scale(calibration_factor);
#endif
}
float readThrust() {
#if TENZO == 1

  for (int i = 0; i < 10; i++) {  // усредняем показания, считав значения датчика 10 раз
    units += scale.get_units();   // суммируем показания 10 замеров
  }
  units /= 10;                // усредняем показания, разделив сумму значений на 10
  ounces = units * 0.035274;  // переводим вес из унций в граммы
  return ounces;

#else
  return 0;
#endif
}
void calibration() {
#if TENZO == 1
  Serial.println("You have 10 seconds to set your known load");                  // выводим в монитор порта текст о том, что у вас есть 10 секунд для установки эталонного веса на весы
  delay(10000);                                                                  // ждём 10 секунд
  Serial.print("calibration factor: ");                                          // выводим текст в монитор поседовательного порта
  for (int i = 0; i < 10; i++) {                                                 // запускаем цикл, в котором
    calibration_factor += scale.get_units() / (weight_of_standard / 0.035274f);  // считываем значение с тензодатчика и переводим его в граммы
  }
  calibration_factor = calibration_factor / 10;  // делим сумму на количество измерений
  Serial.println(calibration_factor);
#endif
}