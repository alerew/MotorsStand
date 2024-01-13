#include <EncButton.h>
EncButtonT<S1_PIN, S2_PIN, BTN_PIN> enc;

void readEnc() {
  if (enc.tick()) {
    switch (enc.action()) {
      case EB_TURN:
        if (enc.pressing()) {
          page += enc.dir();
          arrowPos = 0;
        } else {
          arrowPos += enc.dir();
        }
        break;
      case EB_CLICK:
        break;
      case EB_CLICKS:
        break;
    }
  }
}