void send() {
#if SERIAL == 1
  if (sendTmr.isReady()) {
    String str;
    str.reserve(50);
    str += "d";
    addValue(str, TO_STR(data.thrust));
    addValue(str, TO_STR(data.amperage));
    addValue(str, TO_STR(data.voltage));
    addValue(str, TO_STR(data.vibration));
    addValue(str, TO_STR(data.temp));
    addValue(str, TO_STR(data.rpm));
    addValue(str, TO_STR(settings.value));
    addValue(str, TO_STR(settings.motor));
    addValue(str, TO_STR(settings.mode));
    addValue(str, TO_STR(data.volume), ';');

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


byte parsing() {
  static bool startParse = false;
  static byte count = 0;
  static char buf[12] = { 0 };  // буфер пакета
  static int recData[2];      // принятые данные

  if (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') return 0;
    if (c == 'c') {  // начало пакета
      startParse = true;
      count = 0;
      return 0;
    }
    if (c == ';') {  // конец пакета
      buf[count] = '\0';
      startParse = false;
      parseBytes(buf, recData);
      switch (recData[0]) {
        case 0:
          tare();
          break;
        case 1:
          settings.value = constrain((byte)recData[1], 0, 180);
          break;
        case 2:
          settings.motor = constrain(recData[1], 0, 1);
          break;
        case 3:
          settings.mode = constrain(recData[1], 0, 1);
          break;
        case 4:
          settings.count = constrain(recData[1], 1, 10);
          break;
        case 5:
          sensorsTmr.setInterval(constrain(recData[1], 1, 1000));
          break;
        case 6:
          sendTmr.setInterval(constrain(recData[1], 1, 1000));
          break;
        case 7:
          lcdTmr.setInterval(constrain(recData[1], 1, 1000));
          break;
      }
      return count;
    }
    if (startParse && count < 10) {
      buf[count++] = c;
    }
  }
  return 0;
}
void parseBytes(char* str, int* data) {
  byte count = 0;
  char* offset = str;
  while (true) {
    data[count++] = atoi(offset);
    offset = strchr(offset, ',');
    if (offset) offset++;
    else break;
  }
}
