#include <SoftwareSerial.h>

SoftwareSerial RCSerial(2, 3);

uint16_t temp;

void setup() {
  Serial.begin(115200);
  RCSerial.begin(115200);
}


int16_t readInt() {
  char rec = '0';
  int16_t num = -1;
  while (true) {
    if (RCSerial.available()) {
      rec = RCSerial.read();
      if (rec < '0' || rec > '9') {
        return num;
      } else if (num == -1) {
        num = 0;
      }
      num = num * 10 + (rec - '0');
    }
  }
}

void loop() {
  if (RCSerial.available()) {
    temp = readInt();
    if (temp != -1) {
      if (temp < 1000 || temp > 2000) {
        temp = 1000;
      }
      Serial.println(temp);
    }
  }
}
