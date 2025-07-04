/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-31 11:56:13
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:39:37
 */
#ifndef __FFC_H
#define __FFC_H

#include "user_lib.h"

/*************************** FEEDFORWARD CONTROL *****************************/
typedef struct __attribute__((packed)) 
{
    float c[3]; // G(s) = 1/(c2s^2 + c1s + c0)

    float Ref;
    float Last_Ref;

    float DeadBand;

    uint32_t DWT_CNT;
    float dt;

    float LPF_RC; // RC = 1/omegac	一阶低通滤波参数

    float Ref_dot;
    float Ref_ddot;
    float Last_Ref_dot;

    uint16_t Ref_dot_OLS_Order;//样本数？
    Ordinary_Least_Squares_t Ref_dot_OLS;
    uint16_t Ref_ddot_OLS_Order;//样本数？
    Ordinary_Least_Squares_t Ref_ddot_OLS;

    float Output;
    float MaxOut;

} Feedforward_t;

void Feedforward_Init(
    Feedforward_t *ffc,
    float max_out,
    float *c,
    float lpf_rc,
    uint16_t ref_dot_ols_order,
    uint16_t ref_ddot_ols_order);


struct FFC_ALL_Typdef
{
	Feedforward_t LIFT_L;
	Feedforward_t LIFT_R;
	Feedforward_t HORIZONTAL_L;
	Feedforward_t HORIZONTAL_R;
	Feedforward_t SWAY;
    Feedforward_t Yaw;
};

extern struct FFC_ALL_Typdef FFC_ALL;
float Feedforward_Calculate(Feedforward_t *ffc, float ref);

#endif
