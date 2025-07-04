/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-31 13:49:55
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:52:05
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
#ifndef RUI_ROOT_INIT_H
#define RUI_ROOT_INIT_H
#include "main.h"
#include "can.h"
#include "stdint.h"
#include "RUI_CAN.h"
#include "RUI_MATH.h"
#include "RUI_MOTOR.h"
#include "RUI_DEFINE.h"

//是否在线的标志
struct RUI_ROOT_STATUS_Typedef
{
    /******************************遥控********************************/
    uint8_t RM_DBUS;
    /******************************底盘电机********************************/
    uint8_t MOTOR_CHASSIS_3508_1;
    uint8_t MOTOR_CHASSIS_3508_2;
    uint8_t MOTOR_CHASSIS_3508_3;
    uint8_t MOTOR_CHASSIS_3508_4;
	/******************************转矿电机********************************/
	uint8_t MOTOR_CHASSIS_2006_1;
    uint8_t MOTOR_CHASSIS_2006_2;
    uint8_t MOTOR_CHASSIS_2006_3;
    uint8_t MOTOR_CHASSIS_2006_4;
};



struct RUI_ROOT_Typedef
{
    //主控位置
    uint8_t MASTER_LOCATION;
    //2023-05-09 19:13 | 工程需要控制的太多，增加一个模式选项
    uint8_t MOD;
    //是否在线的标志
    struct RUI_ROOT_STATUS_Typedef STATUS;
};


extern struct RUI_ROOT_Typedef RUI_ROOT;
//在定时器调用这一个函数即可
void RUI_F_ROOT(void);
//电机在线监测
uint8_t RUI_F_MOTOR_STATUS(struct RUI_MOTOR_Typedef* MOTOR);
//总的状态监测
void RUI_F_ROOT_ALL_STATUS(void);
//主控位置判断
uint8_t RUI_F_MASTER_LOCATION_JUDGE(void);
//LED
void RUI_F_LED(uint8_t COLOR , int TIME);
void RUI_F_LED_SHOW_STATUS(void);
#endif

