#include <SoftwareSerial.h>

SoftwareSerial RCSerial(2, 3);    //3 to RX,2 to TX

uint16_t temp;

void setup() {
  Serial.begin(115200);
  RCSerial.begin(115200);
}

int16_t readInt() {
  char rec = '0';
  int16_t num = 0;
  while (true) {
    if (Serial.available()) {
      rec = Serial.read();
      if (rec < '0' || rec > '9') {
        if (num < 1000 || num > 2000) {
          num = 1000;
          return num;
        }
        return num;
      }
      num = num * 10 + (rec - '0');
    }
  }
}

void loop() {
  if (Serial.available()) {
    Serial.println("Received");  
    temp = readInt();
    RCSerial.println(temp);
    Serial.println(temp);
  }
}
