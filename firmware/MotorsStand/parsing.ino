void send() {
#if SERIAL == 1
  if (sendTmr.isReady()) {
    String str;
    //str += "d";
    addValue(str, data.thrust);
    addValue(str, data.amperage);
    addValue(str, data.voltage);
    addValue(str, data.vibration);
    addValue(str, data.temp);
    addValue(str, data.rpm, ';');
    Serial.println(str);
  }
#endif
}

template<typename T>
void addValue(String& str, T& value) {
  addValue(str, value, ',');
}

template<typename T>
void addValue(String& str, T& value, char end) {
  str += value;
  str += end;
}