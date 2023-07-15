#include "ESC.h"

void ESC_initialize() {
    for(int i = 0;i < 4;i++) {
        pinMode(ESC_PINS[i], OUTPUT);
    }
}

void Throttle_set() {
    // maximum throttle 2 sec, minimum throttle 1 sec
    // to initialize ESC
    for(int i = 0;i < 220;i++) {
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], HIGH);
        }
        delayMicroseconds(ESC_MAX_THROTTLE);
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], LOW);
        }
        delayMicroseconds(10000 - ESC_MAX_THROTTLE);
    }

    for(int i = 0;i < 110;i++) {
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], HIGH);
        }
        delayMicroseconds(ESC_MIN_THROTTLE);
        for(int j = 0;j < 4;j++) { 
            setPWM(ESC_PINS[j], LOW);
        }
        delayMicroseconds(10000 - ESC_MIN_THROTTLE);
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
void updateThrottle(Throttle_Arg throttle) {
    
    for(int i = 0;i < 4;i++) {
        unsigned long micro = micros();
        if(previousLev[i] == 0 && micro - previousUpd[i] >= 10000 - throttle.throttle[i]) {
            digitalWrite(ESC_PINS[i], HIGH);
            previousLev[i] = 1; previousUpd[i] = micro;
        } else if(previousLev[i] == 1 && micro - previousUpd[i] >= throttle.throttle[i]) {
            digitalWrite(ESC_PINS[i], LOW);
            previousLev[i] = 0; previousUpd[i] = micro;
        }
    }
}
