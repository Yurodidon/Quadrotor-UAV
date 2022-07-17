#include "IMU.h"

AltSoftSerial IMU; // 8 is RX, 9 is TX
uint8_t RecState = 0, index = 0, check = 0;
RawData raw;

void IMU_initialize() {
    pinMode(IMU_RX, INPUT);
    pinMode(IMU_TX, OUTPUT);
    IMU.begin(IMU_BAUD_RATE);
}

bool IMU_available() {
    return IMU.available();
}

uint8_t getData() {
    return (uint8_t)IMU.read();
}

bool receiveRaw(uint8_t cur) {
    if(RecState == 0) {
        if(cur != 0x55) return false;
        RecState += 1, check += cur;
        
        
    } else if(RecState == 1) {
        RecState += 1, check += cur;
        
    } else if(RecState == 2) {
        raw.ID = cur, RecState += 1, check += cur;
        if(cur < 1 || cur > 6) { //Special case for filtering those wrong datas
            RecState = 0;
            check = 0;
            return false;
        }
        
    } else if(RecState == 3) {
        raw.len = cur, RecState += 1, check += cur;
    } else if(RecState == 4) {
        raw.data[index] = cur, check += cur;
        index++;
        if(index == raw.len) {
           RecState += 1, index = 0;
        }
    } else if(RecState == 5) {
        raw.sum = cur, RecState = 0;
        if(cur == check) {
            check = 0;
            return true;
        }
        check = 0;
    }

    return false;
}

DataPack data;
DataPack receive(bool ReciveAll) {
    // Note: for calculate PID effectly, if ReciveAll==False, this function will return
    // immdeately after obtaining complete Attitude Angle data from IMU
    if(IMU_available()) {
        uint8_t cur = getData();
        bool res = receiveRaw(cur);
        if(res) decodeData(&data);
    }
    return data;
}

void decodeData(DataPack* data) {
    switch(raw.ID) {
    case 1: //ID==0x01, Attitude Angle
        AttitudeAngle angle = decodeAng();
        data->angle = angle;
        break;
    
    default:
        break;
    }
}

AttitudeAngle decodeAng() {
    AttitudeAngle angle;
    int data[MAX_LEN] = {0};
    for(int i = 0;i < raw.len;i++) {
        data[i] = raw.data[i];
    }
    angle.Roll = (float)((int16_t)(data[1] << 8) | data[0]) / 32768 * 180;
    angle.Pitch = (float)((int16_t)(data[3] << 8) | data[2]) / 32768 * 180;
    angle.Yaw = (float)((int16_t)(data[5] << 8) | data[4]) / 32768 * 180;
    angle.ready = true;
    return angle;
}


void decodeQua() {
    
}

void decodeAcc() {
    
}

void decodeMeg() {
    
}

void decodeAtt() {
    
}
