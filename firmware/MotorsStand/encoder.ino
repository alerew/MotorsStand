#include <EncButton.h>
EncButtonT<S1_PIN, S2_PIN, BTN_PIN> enc;

void readEnc() {
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
        break;
      //case EB_HOLD:
        //tare();
        //break;
    }
  }
}
void setSettings(int8_t increment){
  switch(arrowPos){
    case 0:
      settings.motor = constrain(settings.motor + increment, 0, 1); 
      break;
    case 1:
      settings.value = constrain(settings.value + increment, 0, 180); 
      break;
  }
}