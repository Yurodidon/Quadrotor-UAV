#ifndef _PID_H_
#define _PID_H_

    #define MAX_PID 400
    #define MIN_PID -400

    // all parameters listed in order of Yaw, Pitch, Roll
    const float P[3] = {0.0, 0.0, 0.0}; //Parameters for Proportional
    const float I[3] = {0.0, 0.0, 0.0}; // Parameters for Integral
    const float D[3] = {0.0, 0.0, 0.0}; // Parameters for Differential

    // global parameters for PID
    float Pre_err[3] = {0.0, 0.0, 0.0};
    float Sum_err[3] = {0.0, 0.0, 0.0};
    float Diff_err[3] = {0.0, 0.0, 0.0};
    float err[3] = {0.0, 0.0, 0.0};

    // mapping PID to throttle
    const int mappingMat[4][3] = {{-1, -1, +1},
                                {-1, +1, -1},
                                {+1, -1, -1},
                                {+1, +1, +1}};

    struct Throttle_Arg {
        int throttle[4];
    };

#endif