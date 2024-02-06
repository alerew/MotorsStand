#include <EncButton.h>
EncButtonT<S1_PIN, S2_PIN, BTN_PIN> enc;

void readEnc() {
  static uint32_t tmr = 0;
  static bool start = false;
  if (enc.tick()) {
    switch (enc.action()) {
      case EB_TURN:
        if (enc.pressing()) {
          page += enc.dir();
          arrowPos = 0;
          controlState = 0;
        } else {
          if (page == 0 || controlState == 0) {
            arrowPos += enc.dir();
          } else {
            setSettings(enc.fast() ? (enc.dir() * 10) : enc.dir());
          }
        }
        start = false;
        break;
      case EB_CLICK:
        controlState = controlState == 0 ? 1 : 0;
        break;
      case EB_CLICKS:
        if (enc.clicks == 2) {
          page = 0;
          arrowPos = 0;
          controlState = 0;
        }
        if (enc.clicks == 3) tare();
        break;
      case EB_STEP:
        if (!start) {
          start = true;
          tmr = millis();
        } else if (millis() - tmr >= 2000) {
          settings.value = 0;
          settings.motor = 0;
          start = false;
        }
        break;
      case EB_REL_HOLD:
        start = false;
        break;
    }
  }
}
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