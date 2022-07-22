#include "IMU.h"
#include "ESC.h"
#include "PID.h"

Throttle_Arg arg;
void setup() {  
    ESC_initialize();
    IMU_initialize();
    Serial.begin(115200);
    for(int i = 0;i < 4;i++) arg.throttle[i] = ESC_INITIAL_THROTTLE;
}

unsigned long previous = 0;

void loop() {
    DataPack dp = receive();

    if(dp.angle.ready && millis() - previous >= 100) {
//        Serial.println(dp..ACCz);
        for(int i = 0;i < 4;i++) arg.throttle[i] = restrictThrottle(ESC_INITIAL_THROTTLE + (int)(abs(dp.angle.Pitch) / 90.0 * 1000.0));
        previous = millis();
    }

    updateThrottle(arg, micros());
}
