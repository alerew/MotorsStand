void send() {
  if (sendTmr.isReady()) {
    String str = "";
    str += "d ";
    str += data.thrust;
    str += " ";
    str += data.amperage;
    str += data.voltage;
    str += ";";
    Serial.println(str);
  }
}