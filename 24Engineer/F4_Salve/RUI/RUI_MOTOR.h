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
#ifndef RUI_MOTOR_H
#define RUI_MOTOR_H

#include "stdint.h"
#include "RUI_DEFINE.h"
#include "RUI_MATH.h"

struct RUI_MOTOR_DATA_Typedef
{
    int8_t ONLINE_JUDGE_TIME;
    int16_t Angle_last; // 上一个角度值
    int16_t Angle_now;  // 现在的角度值
    int16_t Speed_last; // 上一个速度值
    int16_t Speed_now;  // 现在的速度值
    int16_t current;
    int32_t Angle_Infinite;
    uint16_t Stuck_Time;
    int16_t Laps;
    float Error;
    float Aim;
    float Aim_last;
};

struct RUI_MOTOR_PID_Typedef
{
    float P;
    float I;
    float D;
    int32_t I_Lit;
    int32_t All_Lit;

    float Error[2];
    float P_out;
    float I_out;
    int32_t D_out;
    float All_out;
};

struct RUI_MOTOR_Typedef
{
    uint8_t PID_INIT;
    struct RUI_MOTOR_DATA_Typedef DATA;
    struct RUI_MOTOR_PID_Typedef PID_P;
    struct RUI_MOTOR_PID_Typedef PID_S;
    struct RUI_MOTOR_PID_Typedef PID_C;  //电流环

};

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //底部电机结构体
 *	@parameter:		    //
 *	@time:				//22-11-23 19:10
 *	@ReadMe:			//电机分布图
                              车头
                            ↑  ||  ↑
                            2→ || ←1
                            ————————
                            3→ || ←4
                            ↓  ||  ↓
                              车尾
 ************************************************************万能分隔符**************************************************************/

extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_3508_1;      // 底盘0x201
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_3508_2;      // 底盘0x202
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_3508_3;      // 底盘0x203
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_3508_4;      // 底盘0x204


extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_2006_1;		//  转矿0x205
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_2006_2;		//  转矿0x206
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_2006_3;		//  转矿0x207
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_BOTTOM_2006_4;		//  转矿0x208
	


void RUI_F_MOTOR_CAN_RX_3508RM_WITHOUT_ANGLE(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data);
void RUI_F_MOTOR_CAN_RX_3508RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data);
void RUI_F_MOTOR_CAN_RX_2006RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data);
//头部电机清空函数
void RUI_F_HEAD_MOTOR_CLEAR(struct RUI_MOTOR_Typedef* MOTOR);
void RUI_F_HEAD_MOTOR2006_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_ANGLE , uint16_t ERROR_SPEED , uint16_t ERROR_TIME);
void RUI_F_HEAD_MOTOR3508_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_CURRENT , uint16_t ERROR_SPEED);
//电机堵转检测函数
void RUI_F_HEAD_MOTOR_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_ANGLE , uint16_t ERROR_SPEED , uint16_t ERROR_TIME);

#endif