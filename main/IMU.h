#ifndef _IMU_H_
#define _IMU_H_
  
    #include<AltSoftSerial.h>

    #define MAX_LEN 100
    #define IMU_BAUD_RATE 19200
    #define IMU_RX 8
    #define IMU_TX 9


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
        bool ready; //Refer to recieve function to see why a bool value is placed here
    };

    struct Quaternion {
        float q0;  
        float q1;
        float q2;
        float q3;
    };

    struct Acceleration {
        int16_t Ax, Gx;
        float ACCx, gyro;
    };

    struct Meganetic {
        int16_t Mx;
        float T;
    };

    struct Attitude {
        int32_t P, A;
        float T;
    };

    struct DataPack {
        AttitudeAngle angle;
        Quaternion qua;
        Acceleration acc;
        Meganetic meg;
        Attitude att;
        bool avaliable;
    };

    void IMU_initialize();
    bool IMU_available();
    uint8_t getData();
    bool receiveRaw(uint8_t cur);
    DataPack receive(bool ReciveAll);
    void decodeData(DataPack* data);
    AttitudeAngle decodeAng();
    void decodeQua();
    void decodeAcc();
    void decodeMeg();
    void decodeAtt();

#endif
