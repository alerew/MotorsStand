void send() {
  String str = "";
  str += "d ";
  str += data.thrust;
  str += " ";
  str += data.amperage;
  str += data.voltage;
  str += ";";
  Serial.print(str);
}