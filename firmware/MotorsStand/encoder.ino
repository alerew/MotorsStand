#if LCD
#include <EncButton.h>
EncButtonT<S1_PIN, S2_PIN, BTN_PIN> enc;
#endif

void readEnc() {
#if LCD
  static Timer timer(1000, false);      // таймер для экстренного выключения мотора
  if (enc.tick()) {
    switch (enc.action()) {
      case EB_TURN:
        if (enc.pressing()) {  // поврот с нажатием
          page += enc.dir();
          arrowPos = 0;
          controlState = 0;
        } else {
          if (page == 0 || controlState == 0) {
            arrowPos += enc.dir();  // перелистываем меню
          } else {
            setSettings(enc.fast() ? (enc.dir() * 10) : enc.dir());  // меняем значение в меню
          }
        }
        timer.stop();
        break;
      case EB_CLICK:
        controlState = controlState == 0 ? 1 : 0;
        break;
      case EB_CLICKS:
        if (enc.clicks == 2) {
          page = 0;
          arrowPos = 0;
          controlState = 0;
        } else if (enc.clicks == 3) tare();
        break;
      case EB_STEP:
        if (!timer.running()) {
          timer.restart();
        } else if (timer.isReady()) {  // экстренное выключение мотора
          settings.value = 0;
          settings.motor = 0;
          timer.stop();
        }
        break;
      case EB_REL_HOLD:
        timer.stop();
        break;
    }
  }
#endif
}

#if LCD
void setSettings(int8_t increment) {
  switch (arrowPos) {
    case 0:
      settings.motor = constrain(settings.motor + increment, 0, 1);
      if (settings.motor == 1) tare();
      break;
    case 1:
      settings.value = constrain(settings.value + increment, 0, 180);
      break;
  }
}
#endif