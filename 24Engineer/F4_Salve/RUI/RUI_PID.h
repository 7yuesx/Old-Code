/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-31 13:49:55
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:51:39
 */
/*
____/\\\\\\\\\_____        __/\\\________/\\\_        __/\\\\\\\\\\\_
 __/\\\///////\\\___        _\/\\\_______\/\\\_        _\/////\\\///__
  _\/\\\_____\/\\\___        _\/\\\_______\/\\\_        _____\/\\\_____
   _\/\\\\\\\\\\\/____        _\/\\\_______\/\\\_        _____\/\\\_____
    _\/\\\//////\\\____        _\/\\\_______\/\\\_        _____\/\\\_____
     _\/\\\____\//\\\___        _\/\\\_______\/\\\_        _____\/\\\_____
      _\/\\\_____\//\\\__        _\//\\\______/\\\__        _____\/\\\_____
       _\/\\\______\//\\\_        __\///\\\\\\\\\/___        __/\\\\\\\\\\\_
        _\///________\///__        ____\/////////_____        _\///////////__
*/
#ifndef RUI_PID_H
#define RUI_PID_H

#include "stdint.h"
#include "RUI_MOTOR.h"
#include "RUI_MATH.h"
#include "RUI_DEFINE.h"




/*PID通用赋值函数*/
uint8_t RUI_F_MOTOR_PID_COMMON_INIT(struct RUI_MOTOR_Typedef* MOTOR , uint8_t MOD , float* PID_S , float* PID_P);
/*PID电流环赋值*/
void RUI_F_MOTOR_PID_CURRENT_INIT(struct RUI_MOTOR_Typedef* MOTOR , float* PID_C);
/*底盘部分PID赋值*/
uint8_t RUI_F_MOTOR_PID_BOTTOM_INIT(void);
/*头部部分PID赋值*/
uint8_t RUI_F_MOTOR_PID_HEAD_INIT(void);
/*底盘电流速度环PID*/
void RUI_F_MOTOR_CHSISS_3508RM(struct RUI_MOTOR_Typedef* MOTOR);
/*3508单速度环解算*/
void RUI_F_MOTOR_PID_SPEED_3508RM(struct RUI_MOTOR_Typedef* MOTOR);
/*3508双环解算*/
void RUI_F_MOTOR_PID_TWO_3508RM(struct RUI_MOTOR_Typedef* MOTOR);
/*2006双环解算*/
void RUI_F_MOTOR_PID_TWO_2006RM(struct RUI_MOTOR_Typedef* MOTOR);
/*2006单环解算*/
void RUI_F_MOTOR_CHSISS_2006RM(struct RUI_MOTOR_Typedef* MOTOR);
#endif
