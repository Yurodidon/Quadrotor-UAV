#include "PID.h"

void Calc_err(float* angles, float* goals);
Throttle_Arg Calc_PID(Throttle_Arg cur_throttle, AltitudeAngle angle, AltitudeAngle goal);

float restrictPID(float a) {
    if(a < MIN_PID) {
        return MIN_PID;
    } else if(a > MAX_PID) {
        return MAX_PID;
    } else {
        return a;
    }
} 



Throttle_Arg Calc_PID(Throttle_Arg cur_throttle, DataPack cur, DataPack goal) {
    // cur_throttle: current throttle
    // cur --> yaw, pitch, roll, z-Acc from IMU
    // goal --> set configuration, depends on flying performance.
    Throttle_Arg throttle;
    // Extract data from DataPack
    AltitudeAngle angle = cur.angle, goalAngle = goal.angle;
    Acceleration acc = cur.acc, goalAcc = goal.acc;
    
    float curs[4] = {angle.Yaw, angle.Pitch, angle.Roll, acc.ACCz};
    float goals[4] = {goalAngle.Yaw, goalAngle.Pitch, goalAngle.Roll, goalAcc.ACCz};
    
    Calc_err(curs, goals);

    // Calc PID. 
    float pid[4] = {0.0, 0.0, 0.0, 0.0};
    for(int i = 0;i < 4;i++) {
        pid[i] = P[i] * err[i] + I[i] * Sum_err[i] + D[i] * Diff_err[i];
        pid[i] = restrictPID(pid[i]);
    }

    // Calc corresponds throttle, for further adjustment
    for(int i = 0;i < 4;i++) {
        throttle.throttle[i] = cur_throttle.throttle[i];
        for(int j = 0;j < 4;j++) {
            throttle.throttle[i] += mappingMat[i][j] * pid[j];
        }
    }

    return throttle;
}

void Calc_err(float* cur, float* goals) {
    for(int i = 0;i < 4;i++) {
        //Calc four errors. for PID
        err[i] = cur[i] - goals[i];
        Sum_err[i] += err[i];
        Diff_err[i] = err[i] - Pre_err[i];
        Pre_err[i] = err[i];
    }
}
