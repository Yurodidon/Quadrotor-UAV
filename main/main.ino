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
    DataPack dp = receive(false);

    if(dp.angle.ready && millis() - previous >= 500) {
        Serial.println(dp.angle.Pitch);
        for(int i = 0;i < 4;i++) arg.throttle[i] = restrictThrottle(ESC_INITIAL_THROTTLE + (int)(abs(dp.angle.Pitch) / 90.0 * 1000.0));
        previous = millis();
    }

    updateThrottle(arg, micros());
}
