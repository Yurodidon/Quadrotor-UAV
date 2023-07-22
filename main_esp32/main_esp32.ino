#include "IMU.h"
#include "ESC.h"
#include "PID.h"

// Stable configuration: we ask the UAV to be placed horizontally before starting up.
DataPack stable_conf, goal;


unsigned long previous = 0;
bool IfGo = true;
char cur_command = 'h';
DataPack past;

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


void setup() {
  Serial.begin(115200);

  ESC_initialize();
  stable_conf = IMU_initialize();
  past = stable_conf;

  goal = stable_conf;


  // NOTE: After initialization, throttles need to be set to minimum at every starting up
  for (int i = 0; i < 4; i++) arg.throttle[i] = ESC_MIN_THROTTLE;
}

void loop() {
  // Codes used to initialize ESCs
  if (Serial.available() > 0) {
    int cur_thro = readInt();
    if (cur_thro < 1000 || cur_thro > 2000) {

    } else {
      for (int i = 0; i < 4; i++) {
        arg.throttle[i] = cur_thro;
      }
    }
    Serial.println(cur_thro);
  }

  // for(int i = 0;i < 4;i++) {
  //   setPWM(i, cur_thro);
  // }


  if (millis() - previous >= 100) {
    DataPack dp = receive();

    past = filter(dp, past);

    float Yaw_cur = dp.angle.Yaw;

    // Serial.println(Yaw_cur, 2);
    previous = millis();
  }



  updateThrottle(arg);
}
