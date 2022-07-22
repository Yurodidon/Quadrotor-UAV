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



Throttle_Arg Calc_PID(Throttle_Arg cur_throttle, AltitudeAngle angle, AltitudeAngle goal) {
    // cur_throttle: current throttle
    // angle --> yaw, pitch, roll from IMU
    // goal --> set angle, depends on flying performance, {0, 0, 0} for level flight
    Throttle_Arg throttle; 
    float angles[3] = {angle.Yaw, angle.Pitch, angle.Roll};
    float goals[3] = {goal.Yaw, goal.Pitch, goal.Roll};
    
    Calc_err(angles, goals);

    // Calc PID. 
    float pid[3] = {0.0, 0.0, 0.0};
    for(int i = 0;i < 3;i++) {
        pid[i] = P[i] * err[i] + I[i] * Sum_err[i] + D[i] * Diff_err[i];
        pid[i] = restrictPID(pid[i]);
    }

    // Calc corresponds throttle, for further adjustment
    for(int i = 0;i < 4;i++) {
        throttle.throttle[i] = cur_throttle.throttle[i];
        for(int j = 0;j < 3;j++) {
            throttle.throttle[i] += mappingMat[i][j] * pid[j];
        }
    }

    return throttle;
}

void Calc_err(float* angles, float* goals) {
    for(int i = 0;i < 3;i++) {
        //Calc four errors. for PID
        err[i] = angles[i] - goals[i];
        Sum_err[i] += err[i];
        Diff_err[i] = err[i] - Pre_err[i];
        Pre_err[i] = err[i];
    }
}