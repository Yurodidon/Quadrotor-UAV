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
DataPack receive() {

    if(IMU_available()) {
        uint8_t cur = getData();
        bool res = receiveRaw(cur);
        if(res) decodeData(&data);
    }
    return data;
}

void decodeData(DataPack* data) {
    // Note: it seems that switch does not work
    if(raw.ID == 1) { //ID==0x01, Altitude Angle
        AltitudeAngle angle = decodeAng();
        data->angle = angle;
    }
    if(raw.ID == 2) { //ID==0x02, Quaternion
        Quaternion qua = decodeQua();
        data->qua = qua;
    }
    if(raw.ID == 3) { //ID==0x03, Acceleration & Gyro
        Acceleration acc = decodeAcc();
        data->acc = acc;
    }
    if(raw.ID == 4) { //ID==0x04, Meganetic & temp
        Meganetic meg = decodeMeg();
        data->meg = meg;
    }
    if(raw.ID == 5) { //ID==0x05, Altitude & pressure & temp
        Altitude alt = decodeAlt();
        data->alt = alt;
    }
}


// Angles
AltitudeAngle decodeAng() {
    AltitudeAngle angle;
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

// Quaternion
Quaternion decodeQua() {
    Quaternion qua;
    int data[MAX_LEN] = {0};
    for(int i = 0;i < raw.len;i++) {
        data[i] = raw.data[i];
    }
    qua.q0 = (float)((int16_t)(data[1] << 8) | data[0]) / 32768;
    qua.q1 = (float)((int16_t)(data[3] << 8) | data[2]) / 32768;
    qua.q2 = (float)((int16_t)(data[5] << 8) | data[4]) / 32768;
    qua.q3 = (float)((int16_t)(data[7] << 8) | data[6]) / 32768;
    return qua;
}

// Acceleration
Acceleration decodeAcc() {
    Acceleration acc;
    int data[MAX_LEN] = {0};
    for(int i = 0;i < raw.len;i++) {
        data[i] = raw.data[i];
    }
    // note: the unit of acc is g, 
    acc.ACCx = (float)((int16_t)(data[1] << 8) | data[0]) / 32768 * ACC_RANGE;
    acc.ACCy = (float)((int16_t)(data[3] << 8) | data[2]) / 32768 * ACC_RANGE;
    acc.ACCz = (float)((int16_t)(data[5] << 8) | data[4]) / 32768 * ACC_RANGE;
    acc.Gyrox = (float)((int16_t)(data[7] << 8) | data[6]) / 32768 * GYRO_RANGE;
    acc.Gyroy = (float)((int16_t)(data[9] << 8) | data[8]) / 32768 * GYRO_RANGE;
    acc.Gyroz = (float)((int16_t)(data[11] << 8) | data[10]) / 32768 * GYRO_RANGE;
    return acc;
}

// Megnetic
Meganetic decodeMeg() {
    Meganetic meg;
    int data[MAX_LEN] = {0};
    for(int i = 0;i < raw.len;i++) {
        data[i] = raw.data[i];
    }
    meg.Mx = (int16_t)(data[1] << 8) | data[0];
    meg.My = (int16_t)(data[3] << 8) | data[2];
    meg.Mz = (int16_t)(data[5] << 8) | data[4];
    meg.T = (float)((int16_t)(data[7] << 8) | data[6]) / 100;
    return meg;
}

// Altitude
Altitude decodeAlt() {
    Altitude alt;
    int data[MAX_LEN] = {0};
    for(int i = 0;i < raw.len;i++) {
        data[i] = raw.data[i];
    }
    alt.P = (int32_t)(data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
    alt.A = (int32_t)(data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4];
    alt.T = (float)((int16_t)(data[9] << 8) | data[8]) / 100;
    return alt;
}
