#ifndef _IMU_H_
#define _IMU_H_
  
    #include<NeoSWSerial.h>
    #include "ESC.h"

    #define MAX_LEN 100
    #define IMU_BAUD_RATE 38400
    #define IMU_RX 8
    #define IMU_TX 9
    #define TOLERATE 10
    #define ACC_RANGE 4
    #define GYRO_RANGE 2000


    struct RawData {
        uint8_t ID;
        uint8_t len;
        uint8_t data[MAX_LEN];
        uint8_t sum;
    };

    struct AltitudeAngle {
        float Roll;
        float Pitch;
        float Yaw;
        bool ready;
    };

    struct Quaternion {
        float q0;  
        float q1;
        float q2;
        float q3;
        bool ready;
    };

    // the acceleration is in unit of G=9.8ms-2 
    // so ACC == 1 --> no acceleration
    struct Acceleration {
        float ACCx, ACCy, ACCz;
        float Gyrox, Gyroy, Gyroz;
        bool ready;
    };

    struct Meganetic {
        int16_t Mx, My, Mz;
        float T;
        bool ready;
    };

    struct Altitude {
        int32_t P, A; // NOTE: the unit of A(ltitude) is 
        float T;
        bool ready;
    };

    struct DataPack {
        AltitudeAngle angle;
        Quaternion qua;
        Acceleration acc;
        Meganetic meg;
        Altitude alt;
        bool available;
    };

    DataPack IMU_initialize();
    bool IMU_available();
    uint8_t getData();
    bool receiveRaw(uint8_t cur);
    DataPack receive();
    void decodeData(DataPack* data);
    AltitudeAngle decodeAng();
    Quaternion decodeQua();
    Acceleration decodeAcc();
    Meganetic decodeMeg();
    Altitude decodeAlt();
    DataPack filter(DataPack cur, DataPack past);

#endif
