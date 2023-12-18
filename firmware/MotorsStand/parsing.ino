String str;
void send() {
  if (sendTmr.isReady()) {
    str = "";
    str += "d";
    addValue(data.thrust);
    addValue(data.amperage);
    addValue(data.voltage);
    addValue(data.vibration);
    addValue(data.temp, ';');
    Serial.println(str);
  }
}

template<typename T>
void addValue(T value){
  str += value;
  str += ',';
}
template<typename T>
void addValue(T value, char end){
  str += value;
  str += end;
}