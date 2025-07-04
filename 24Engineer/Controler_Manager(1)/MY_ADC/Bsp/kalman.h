/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-03 17:05:10
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:54:24
 */
#ifndef __KALMAN_H
#define __KALMAN_H

#include "math.h"//未加
#include "main.h"

#define PI 3.1415927f

#define MYPITCH_ERROR 0.05f
#define MYYAW_ERROR   0.05f

#define PITCH_HARSH 10.0f
#define YAW_HARSH 10.0f

typedef struct {
    float X_last; //上一时刻的最优结果
    float X_mid;  //当前时刻的预测结果
    float X_now;  //当前时刻的最优结果
    float P_mid;  //当前时刻预测结果的协方差
    float P_now;  //当前时刻最优结果的协方差
    float P_last; //上一时刻最优结果的协方差
    float kg;     //kalman增益
    float A;      //系统参数
    float Q;			//误差，外部干扰
    float R;			//误差，测量值和估计值误差
    float H;
}kalman;

extern kalman URy,URz,URx;

void  kalmanInit(void);
void  kalmanUpdate(void);
void  kalmanCreate(kalman *p,float T_Q,float T_R);
float KalmanFilter(kalman* p,double dat);



#endif
