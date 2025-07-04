/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-31 13:49:55
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:46:31
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
#include "MY_define.h"

//是否在线的标志
struct RUI_ROOT_STATUS_Typedef
{
    /******************************遥控********************************/
    uint8_t RM_DBUS;
     /******************************头部电机********************************/
    uint8_t MOTOR_HEAD_HORIZONTAL_L;
    uint8_t MOTOR_HEAD_HORIZONTAL_R;
    uint8_t MOTOR_HEAD_LIFT_L;
    uint8_t MOTOR_HEAD_LIFT_R;
    uint8_t MOTOR_HEAD_SWAY;
    uint8_t MOTOR_HEAD_Yaw;
    uint8_t MOTOR_HEAD_Left;
    uint8_t MOTOR_HEAD_Right;
	uint8_t User_Crotral;
	uint8_t MOTER_HEAD_Camera;
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
extern union COMMUNICATION_UNION_Typdef  RUI_V_COMMUNICATION;

//在定时器调用这一个函数即可
void RUI_F_ROOT(void);
//电机在线监测
uint8_t RUI_F_MOTOR_STATUS(struct RUI_MOTOR_Typedef* MOTOR);

//总的状态监测
void RUI_F_ROOT_ALL_STATUS(void);
//主控位置判断
uint8_t RUI_F_MASTER_LOCATION_JUDGE(void);
//主控通信
uint8_t RUI_F_MASTER_COMMUNICATION(void);
//LED
void RUI_F_LED(uint8_t COLOR , int TIME);
void RUI_F_LED_SHOW_STATUS(void);
#endif

