void send() {
#if SERIAL == 1
  if (sendTmr.isReady()) {
    String str;
    //str += "d";
    addValue(str, TO_STR(data.thrust));
    addValue(str, TO_STR(data.amperage));
    addValue(str, TO_STR(data.voltage));
    addValue(str, TO_STR(data.vibration));
    addValue(str, TO_STR(data.temp));
    addValue(str, TO_STR(data.rpm), ';');
    Serial.println(str);
  }
#endif
}

void addValue(String& str, const String& value) {
  addValue(str, value, ',');
}

void addValue(String& str, const String& value, char end) {
  str += value;
  str += end;
}
