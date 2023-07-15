#include "IMU.h"
#include "ESC.h"
#include "PID.h"

Throttle_Arg arg;
// Stable configuration: we ask the UAV to be placed horizontally before starting up.
DataPack stable_conf, goal; 

void setup() {  
    ESC_initialize();
    stable_conf = IMU_initialize();

    goal = stable_conf;
    // Set throttle for the first time.
    // DO NOT OPEN THIS WHEN ALL PROPELLERS ARE ON
    // DANGEROUS! DANGEROUS!!
    Throttle_set(); 


    Serial.begin(115200);
    // NOTE: After initialization, throttles need to be set to minimum at every starting up
    for(int i = 0;i < 4;i++) arg.throttle[i] = ESC_MIN_THROTTLE;
}

unsigned long previous = 0;
bool IfGo = true;
char cur_command = 'h';

void loop() {
//    DataPack dp = receive();
//    
//    // NOTE: The reason to pick interval as 7 millionsecond is because one pulse of PWM is 10000microseconds
//    // That is 10 milliseconds, and the time for high electrical level is 2000 micro at maximum (2 millionsecond)
//    // And therefore a 7 millionsecond interval between calculation of PID will always fall in the time that the PWM 
//    // is at low electrical level, and therefore will not disturb the updatingThrottle function.
//    if(dp.available && millis() - previous >= 7 && IfGo) {
//        if(Serial.available()) {
//            char cmd = Serial.read();
//            if(cmd == 'v') { // Stop
//                for(int i = 0;i < 4;i++) arg.throttle[i] = ESC_MIN_THROTTLE;
//                IfGo = false;
//            }
//            if(cmd == 'g') { // Go
//                for(int i = 0;i < 4;i++) arg.throttle[i] = ESC_INITIAL_THROTTLE;
//                IfGo = true;
//            }
//        }
//        // Calculate PID.
//        
//        
//        previous = millis();
//    }

    updateThrottle(arg);
}
