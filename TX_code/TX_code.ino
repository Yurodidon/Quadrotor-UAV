#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3); // TX, RX pinos digitais do lora e32


void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600); // velocidade da porta serial do mdulo configurada antes

}

void loop() {
   loraSerial.println("Hello RX");
   Serial.println("Sending");
   delay(1000);
}
