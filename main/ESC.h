#ifndef _ESC_H_
#define _ESC_H_

    #include "PID.h"
    #include "IMU.h"
    #include<Servo.h>
    #include<Arduino.h>

    #define ESC_MAX_THROTTLE 2000
    #define ESC_MIN_THROTTLE 1000
    #define ESC_INITIAL_THROTTLE 1300

    struct Throttle_Arg {
        int throttle[4];  
    };
    /*
    Assignment of ESCs
                 ^
                 |
                IMU     
     ESC3                  ESC0

                 *
     
     ESC2                  ESC1            
    */

    // ESC 0 --> 5, ESC 1 --> 4, ESC 2 --> 2, ESC 3 --> 3
    int ESC_PINS[4] = {5, 4, 2, 3};
    Servo servos[4];
    Throttle_Arg arg;

    void ESC_initialize();
    void setPWM(int pin, int value);
    int restrictThrottle(int a);
    void updateThrottle(Throttle_Arg throttle);

#endif
