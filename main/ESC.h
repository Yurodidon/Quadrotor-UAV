#ifndef _ESC_H_
#define _ESC_H_

    #include "PID.h"
    #include "IMU.h"
    #include<Arduino.h>

    #define ESC_MAX_THROTTLE 2000
    #define ESC_MIN_THROTTLE 1100
    #define ESC_INITIAL_THROTTLE 1100

    int ESC_PINS[4] = {2, 3, 4, 5};

    void ESC_initialize();
    void setPWM(int pin, int value);
    int restrictThrottle(int a);
    void updateThrottle(Throttle_Arg throttle, unsigned long micro);

#endif
