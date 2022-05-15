#include <Servo.h>
#include <SoftwareSerial.h>

Servo myServo;
SoftwareSerial loraSerial(2, 3); // TX, RX pinos digitais do lora e32

String comStr = "";
int comInt=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // start serial port
  loraSerial.begin(9600); // velocidade da porta serial do mdulo configurada antes
  while(Serial.read()>=0){} // clear serial port's buffer
  
  myServo.writeMicroseconds(1000); // set initial PWM to minimal
}

void loop() {
  if (Serial.available() > 0){
    comStr = Serial.readString(); // read out the string
    comInt = comStr.toInt(); // convert the string to integer
    comInt = constrain(comInt, 1000, 2000); // limit the integer between to 1000 and 2000
  loraSerial.println(comInt); // show the integer number on Serial Monitor
  Serial.println(comInt);
  myServo.writeMicroseconds(comInt); // write the integer number to Servo in unit of micro-second
  }
}
