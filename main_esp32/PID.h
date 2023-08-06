#ifndef _PID_H_
#define _PID_H_

    #define MAX_PID 400
    #define MIN_PID -400

    // all parameters listed in order of Yaw, Pitch, Roll, z-Acc
    const float P[4] = {0.0, 0.0, 0.0, 0.0}; //Parameters for Proportional
    const float I[4] = {0.0, 0.0, 0.0, 0.0}; // Parameters for Integral
    const float D[4] = {0.0, 0.0, 0.0, 0.0}; // Parameters for Differential

    // global parameters for PID
    float Pre_err[4] = {0.0, 0.0, 0.0, 0.0};
    float Sum_err[4] = {0.0, 0.0, 0.0, 0.0};
    float Diff_err[4] = {0.0, 0.0, 0.0, 0.0};
    float err[4] = {0.0, 0.0, 0.0, 0.0};

    // mapping PID to throttle
    const int mappingMat[4][4] = {{-1, -1, +1, +1},
                                  {-1, +1, -1, +1},
                                  {+1, -1, -1, +1},
                                  {+1, +1, +1, +1}};
                                  /*
                                    
                                  */

    /*
    Assignment of ESCs
                 ^
                 |
                IMU     
     ESC4                  ESC1

                 *
     
     ESC3                  ESC2            
    */

#endif
