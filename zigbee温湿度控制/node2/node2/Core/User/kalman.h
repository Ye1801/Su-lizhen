#ifndef HARDWARE_KALMAN_H_
#define HARDWARE_KALMAN_H_

#include "main.h"

#include <math.h>

// Kalman structure
typedef struct
{
    double Q_angle;   //角度数据置信度，角度噪声的协方差
    double Q_gyro;    //角速度数据置信度，角速度噪声的协方差
    double R_measure; //加速度计噪声协方差
    double angle;     //角度
    double bias;      //陀螺仪偏差
    double P[2][2];   //过程协方差矩阵P
} Kalman_t;

void KalmanAHRSupdateIMU(short ax_raw, short ay_raw, short az_raw, short gx_raw, short gy_raw, short gz_raw, double *roll, double *pitch);
double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);

#endif /* HARDWARE_KALMAN_H_ */

