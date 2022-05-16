#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial RCSerial(2, 3); // TX, RX pinos digitais do lora e32
Servo myServo;

String comStr = "";
int comInt=0;

void setup() {
  Serial.begin(9600);
  RCSerial.begin(9600);
  myServo.attach(9);
  myServo.writeMicroseconds(1000);
}

int a = 0;
char ret;
void loop() {
  while (RCSerial.available()) {
    delay(1);
    comStr = RCSerial.readString();
    comInt = comStr.toInt();
    comInt = constrain(comInt, 1000, 2000);
    Serial.println(comInt);
    myServo.writeMicroseconds(comInt);
  }
}
