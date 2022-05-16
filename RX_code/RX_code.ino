#include <SoftwareSerial.h>

SoftwareSerial RCSerial(2, 3); // TX, RX pinos digitais do lora e32


void setup() {
  Serial.begin(9600);
  RCSerial.begin(9600); // velocidade da porta serial do mdulo configurada antes
}

void loop() {
  while (RCSerial.available()) {
    Serial.write(RCSerial.read());// mostra no monitor serial a mensagem recebida
  }
}
