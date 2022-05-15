#include <AltSoftSerial.h>

#define MAX_LEN 100

AltSoftSerial altSerial;


struct RawData {
    uint8_t ID;
    uint8_t len;
    uint8_t data[MAX_LEN];
    uint8_t sum;
};

struct AttitudeAngle {
    float Roll;
    float Pitch;
    float Yaw;
};

void setup() {
    Serial.begin(115200);
    altSerial.begin(38400);
}

int getData() {
    return (uint8_t)altSerial.read();
}

uint8_t RecState = 0, index = 0, check = 0;
bool receiveData(RawData* raw, uint8_t cur) {
    if(RecState == 0) {
        if(cur != 0x55) return false;
        RecState += 1, check += cur;
        
    } else if(RecState == 1) {
        if(cur != 0x55) {
            RecState = 0;
            check = 0;
            return false;
        }
        RecState += 1, check += cur;
    } else if(RecState == 2) {
        raw->ID = cur, RecState += 1, check += cur;
    } else if(RecState == 3) {
        raw->len = cur, RecState += 1, check += cur;
        
    } else if(RecState == 4) {
        raw->data[index] = cur, check += cur;
        index++;
        if(index == raw->len) {
           RecState += 1, index = 0;
        }
    } else if(RecState == 5) {
        raw->sum = cur, RecState = 0;
        if(cur == check) {
            return true;
        }
        check = 0;
    }

    return false;
}


void DecodeAttAngle(RawData raw, AttitudeAngle *atta) {
    if(raw.ID != 0x01) return;
    int data[MAX_LEN] = {0};
    for(int i = 0;i < raw.len;i++) {
        data[i] = raw.data[i];
    }
    atta->Roll = (float)((int16_t)(data[1] << 8) | data[0]) / 32768 * 180;
    atta->Pitch = (float)((int16_t)(data[3] << 8) | data[2]) / 32768 * 180;
    atta->Yaw = (float)((int16_t)(data[5] << 8) | data[4]) / 32768 * 180;
    Serial.println(atta->Roll);
    Serial.println(atta->Pitch);
    Serial.println(atta->Yaw);
}

int ti = 0;
RawData raw;
AttitudeAngle atta;

void loop() {
    ti++;
    if(altSerial.available()) {
        uint8_t cur = getData();
        if(cur != 0) {
            bool state = receiveData(&raw, cur);
            if(state) DecodeAttAngle(raw, &atta);   
        }
        
    }
    
}
