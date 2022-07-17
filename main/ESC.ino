#include "ESC.h"

void ESC_initialize() {
    for(int i = 0;i < 4;i++) {
        pinMode(ESC_PINS[i], OUTPUT);
    }

    // maximum throttle 2 sec, minimum throttle 1 sec
    // to initialize ESC
    for(int i = 0;i < 220;i++) {
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], HIGH);
        }
        delayMicroseconds(2000);
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], LOW);
        }
        delayMicroseconds(10000 - 2000);
    }

    for(int i = 0;i < 110;i++) {
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], HIGH);
        }
        delayMicroseconds(1000);
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], LOW);
        }
        delayMicroseconds(10000 - 1000);
    }
}

//value range: 1000~2000
void setPWM(int pin, int value) {
    digitalWrite(pin, value);
}

int restrictThrottle(int a) {
    if(a < ESC_MIN_THROTTLE) { return ESC_MIN_THROTTLE; }
    else if(a > ESC_MAX_THROTTLE) { return ESC_MAX_THROTTLE; }
    else return a;
}

//used to record the previous time of updating
unsigned long previousUpd[4] = {0, 0, 0, 0}; 
//used to record the previous electrical level, 1 for high, 0 for low
int previousLev[4] = {0, 0, 0, 0};

// functions implemented by micros(), with problem of overflow after 70mins
void updateThrottle(Throttle_Arg throttle, unsigned long micro) {
    int throttles[4] = {0};
    for(int i = 0;i < 4;i++) { throttles[i] = throttle.throttle[i]; }
    
    for(int i = 0;i < 1;i++) {
        if(previousLev[i] == 0 && micro - previousUpd[i] >= 10000 - throttles[i]) {
            digitalWrite(ESC_PINS[i], HIGH);
            previousLev[i] = 1; previousUpd[i] = micro;
        } else if(previousLev[i] == 1 && micro - previousUpd[i] >= throttles[i]) {
            digitalWrite(ESC_PINS[i], LOW);
            previousLev[i] = 0; previousUpd[i] = micro;
        }
    }
}