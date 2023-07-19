#include "ESC.h"

void ESC_initialize() {
    for(int i = 0;i < 4;i++) {
        servos[i].attach(ESC_PINS[i]);
        servos[i].writeMicroseconds(ESC_MAX_THROTTLE);
    }
}

//value range: 1000~2000
void setPWM(int pin, int value) {
    servos[pin].writeMicroseconds(restrictThrottle(value));
}

int restrictThrottle(int a) {
    if(a < ESC_MIN_THROTTLE) { return ESC_MIN_THROTTLE; }
    else if(a > ESC_MAX_THROTTLE) { return ESC_MAX_THROTTLE; }
    else return a;
}

void updateThrottle(Throttle_Arg throttle) {
    for(int i = 0;i < 4;i++) {
        setPWM(i, throttle.throttle[i]);
    }
}
