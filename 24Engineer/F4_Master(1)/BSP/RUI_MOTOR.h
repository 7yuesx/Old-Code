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
#include "RUI_MATH.h"
#include "string.h"

struct RUI_MOTOR_DATA_Typedef
{
    int8_t ONLINE_JUDGE_TIME;
    int16_t Angle_last; // 上一个角度值
    int16_t Angle_now;  // 现在的角度值
    int16_t Speed_last; // 上一个速度值
    int16_t Speed_now;  // 现在的速度值
    int16_t current;
    int8_t temperature;
    int32_t Angle_Infinite;
    uint16_t Stuck_Time;
	uint16_t Stuck_Flag[2];
    int16_t Laps;
    float Error;
    float Aim;
    float Aim_last;
    float dt;
    uint32_t DWT_CNT;
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
 *	@performance:	    //头部部分电机结构体
 *	@parameter:		    //
 *	@time:				//22-11-23 19:14
 *	@ReadMe:			//二级前伸  HORIZONTAL
                        //爪子旋转  REVOLVE
                        //升降    VERTICAL
                        //爪子ROW轴 ROW
                        //摄像头    CAMERA
 ************************************************************万能分隔符**************************************************************/
//升降
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_LIFT_L;
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_LIFT_R;
//前伸
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_HORIZONTAL_L;
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_HORIZONTAL_R;
//横移
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_SWAY;
//Yaw轴
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_Yaw;
//差动
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_Pitch;
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_Roll;

extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_Left;
extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_Right;

extern struct RUI_MOTOR_Typedef RUI_V_MOTOR_Camera;

extern float P_Angle;
extern float R_Angle;


//电机解算函数
void RUI_F_MOTOR_CAN_RX_3508RM_WITHOUT_ANGLE(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data);
void WHW_F_MOTOR_CAN_RX_6020RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data);
void RUI_F_MOTOR_CAN_RX_3508RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data);
void RUI_F_MOTOR_CAN_RX_2006RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data);

//头部电机清空函数
void RUI_F_HEAD_MOTOR_CLEAR(struct RUI_MOTOR_Typedef* MOTOR);
//头部电机重置函数
void WHW_F_HEAD_MOTOR_SIT(struct RUI_MOTOR_Typedef* MOTOR);

//电机堵转检测函数
void RUI_F_HEAD_MOTOR2006_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_ANGLE , uint16_t ERROR_SPEED , uint16_t ERROR_TIME);
void RUI_F_HEAD_MOTOR6020_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_ANGLE , uint16_t ERROR_SPEED , uint16_t ERROR_TIME);
void RUI_F_HEAD_MOTOR3508_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_CURRENT , uint16_t ERROR_SPEED);



#endif
