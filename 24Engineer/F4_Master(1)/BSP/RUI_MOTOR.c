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
#include "RUI_MOTOR.h"
#include "MY_define.h"
#include "FFC.h"

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //头部部分电机结构体
 *	@parameter:		    //
 *	@time:				//22-11-23 19:14
 *	@ReadMe:			//前伸 HORIZONTAL
                        //升降 LIFT
						//横移 SWAY
 ************************************************************万能分隔符**************************************************************/
//升降
struct RUI_MOTOR_Typedef RUI_V_MOTOR_LIFT_L         ={ 0 };
struct RUI_MOTOR_Typedef RUI_V_MOTOR_LIFT_R         ={ 0 };
//前伸
struct RUI_MOTOR_Typedef RUI_V_MOTOR_HORIZONTAL_L   ={ 0 };
struct RUI_MOTOR_Typedef RUI_V_MOTOR_HORIZONTAL_R   ={ 0 };
//横移
struct RUI_MOTOR_Typedef RUI_V_MOTOR_SWAY           ={ 0 };
//Yaw轴
struct RUI_MOTOR_Typedef RUI_V_MOTOR_Yaw            ={ 0 };
//差动
struct RUI_MOTOR_Typedef RUI_V_MOTOR_Pitch          ={ 0 };
struct RUI_MOTOR_Typedef RUI_V_MOTOR_Roll           ={ 0 };

struct RUI_MOTOR_Typedef RUI_V_MOTOR_Left           ={ 0 };
struct RUI_MOTOR_Typedef RUI_V_MOTOR_Right          ={ 0 };

struct RUI_MOTOR_Typedef RUI_V_MOTOR_Camera         ={ 0 };

float R_Angle;
float P_Angle;

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //3508电机解算函数
 *	@parameter:		    //@电机结构体  @can接收到的数组
 *	@time:				//22-11-23 20:31
 *	@ReadMe:			//底盘运动只要单速度环，所以写了一个没有角度环解算的函数
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_CAN_RX_3508RM_WITHOUT_ANGLE(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data)
{
    MOTOR->DATA.Speed_last = MOTOR->DATA.Angle_now;
    MOTOR->DATA.Speed_now  = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);
    MOTOR->DATA.ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //3508电机解算函数
 *	@parameter:		    //@电机结构体  @can接收到的数组
 *	@time:				//22-11-23 18:50
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_CAN_RX_3508RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data)
{
    MOTOR->DATA.Angle_last = MOTOR->DATA.Angle_now;

    MOTOR->DATA.Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    MOTOR->DATA.Speed_last = MOTOR->DATA.Speed_now;

    MOTOR->DATA.Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    MOTOR->DATA.current   = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    MOTOR->DATA.temperature = can_data[6];

    if (MOTOR->DATA.Angle_now - MOTOR->DATA.Angle_last < -4000)
    {
        MOTOR->DATA.Laps++;
    }
    else if (MOTOR->DATA.Angle_now - MOTOR->DATA.Angle_last > 4000)
    {
        MOTOR->DATA.Laps--;
    }

    if ((MOTOR->DATA.Laps > 32500) | (MOTOR->DATA.Laps < -32500))
    {
        MOTOR->DATA.Laps = 0;
        MOTOR->DATA.Aim  = MOTOR->DATA.Angle_now;
    }

    MOTOR->DATA.ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;

    MOTOR->DATA.Angle_Infinite = (int32_t) ((MOTOR->DATA.Laps << 13)+ MOTOR->DATA.Angle_now);

}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //2006电机解算函数
 *	@parameter:		    //@电机结构体  @can接收到的数组
 *	@time:				//22-11-23 18:49
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_CAN_RX_2006RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data)
{
    MOTOR->DATA.Angle_last = MOTOR->DATA.Angle_now;

    MOTOR->DATA.Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    MOTOR->DATA.Speed_last = MOTOR->DATA.Speed_now;

    MOTOR->DATA.Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    MOTOR->DATA.current = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    if (MOTOR->DATA.Angle_now - MOTOR->DATA.Angle_last < -4000)
    {
        MOTOR->DATA.Laps++;
    }
    else if (MOTOR->DATA.Angle_now - MOTOR->DATA.Angle_last > 4000)
    {
        MOTOR->DATA.Laps--;
    }

    if ((MOTOR->DATA.Laps > 32500) | (MOTOR->DATA.Laps < -32500))
    {
        MOTOR->DATA.Laps = 0;
        MOTOR->DATA.Aim  = MOTOR->DATA.Angle_now;
    }

    MOTOR->DATA.Angle_Infinite = (int32_t) ((MOTOR->DATA.Laps << 13) + MOTOR->DATA.Angle_now);
    MOTOR->DATA.ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //6020电机解算函数
 *	@parameter:		    //@电机结构体  @can接收到的数组
 *	@time:				//22-11-23 18:50
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void WHW_F_MOTOR_CAN_RX_6020RM(struct RUI_MOTOR_Typedef* MOTOR , uint8_t* can_data)
{
    MOTOR->DATA.Angle_last = MOTOR->DATA.Angle_now;

    MOTOR->DATA.Angle_now = (int16_t) (((can_data[0] << 8) | can_data[1]) & 0xFFFF);

    MOTOR->DATA.Speed_last = MOTOR->DATA.Speed_now;

    MOTOR->DATA.Speed_now = (int16_t) (((can_data[2] << 8) | can_data[3]) & 0xFFFF);

    MOTOR->DATA.current   = (int16_t) (((can_data[4] << 8) | can_data[5]) & 0xFFFF);

    MOTOR->DATA.temperature = can_data[6];
	
	if(MOTOR->DATA.Angle_now < 2900)	MOTOR->DATA.Laps = 1;
	if(MOTOR->DATA.Angle_now > 4000)	MOTOR->DATA.Laps = 0;

//    if (MOTOR->DATA.Angle_now - MOTOR->DATA.Angle_last < -4000)
//    {
//        MOTOR->DATA.Laps++;
//    }
//    else if (MOTOR->DATA.Angle_now - MOTOR->DATA.Angle_last > 4000)
//    {
//        MOTOR->DATA.Laps--;
//    }

    if ((MOTOR->DATA.Laps > 32500) | (MOTOR->DATA.Laps < -32500))
    {
        MOTOR->DATA.Laps = 0;
        MOTOR->DATA.Aim  = MOTOR->DATA.Angle_now;
    }

    MOTOR->DATA.ONLINE_JUDGE_TIME = RUI_DF_MOTOR_OFFLINE_TIME;

    MOTOR->DATA.Angle_Infinite = (int32_t) ((MOTOR->DATA.Laps << 13)+ MOTOR->DATA.Angle_now);

}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //电机清空函数
 *	@parameter:		    //
 *	@time:				//23-04-13 19:23
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-05-07 17:06    bestrui
 *  @UpData：           //不太好描述
 ************************************************************万能分隔符**************************************************************/
void RUI_F_HEAD_MOTOR_CLEAR(struct RUI_MOTOR_Typedef* MOTOR)
{
    MOTOR->PID_P.I_out  = 0.0f;
    MOTOR->PID_S.I_out  = 0.0f;
    MOTOR->DATA.Aim     = MOTOR->DATA.Angle_Infinite;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //电机清空函数
 *	@parameter:		    //
 *	@time:				//23-04-13 19:23
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-05-07 17:06    bestrui
 *  @UpData：           //将本时刻的电机刻度作为初始刻度
 ************************************************************万能分隔符**************************************************************/
void WHW_F_HEAD_MOTOR_SIT(struct RUI_MOTOR_Typedef* MOTOR)
{
    MOTOR->PID_P.I_out  = 0.0f;
    MOTOR->PID_S.I_out  = 0.0f;
	MOTOR->DATA.Laps 	= 0;
    MOTOR->DATA.Aim     = MOTOR->DATA.Angle_now;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //2006电机堵转检测函数
 *	@parameter:		    //
 *	@time:				//23-04-13 20:31
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-04-14 15:34    bestrui
 *  @UpData：           //给电机结构体增加堵转时间
 ************************************************************万能分隔符**************************************************************/
void RUI_F_HEAD_MOTOR2006_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_ANGLE , uint16_t ERROR_SPEED , uint16_t ERROR_TIME)
{
    //一定误差  速度小于某个值初步判断电机卡住，接下来去判断卡住的时间
    if (RUI_F_MATH_ABS_float(MOTOR->PID_P.Error[RUI_DF_NOW]) > ERROR_ANGLE && RUI_F_MATH_ABS_float(MOTOR->DATA.Speed_now) < ERROR_SPEED)
    {
        MOTOR->DATA.Stuck_Time++;
        if (MOTOR->DATA.Stuck_Time > ERROR_TIME)
        {
            RUI_F_HEAD_MOTOR_CLEAR(MOTOR);
            MOTOR->DATA.Stuck_Time = 0;
			MOTOR->DATA.Stuck_Flag[0]++;
        }
    }
    else
    {
        MOTOR->DATA.Stuck_Time = 0;
    }
    MOTOR->DATA.Aim_last = MOTOR->DATA.Aim;

}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //3508堵转检测
 *	@parameter:		    //
 *	@time:				//23-05-25 18:14
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_HEAD_MOTOR3508_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_CURRENT , uint16_t ERROR_SPEED)
{
    if (RUI_F_MATH_ABS_float(MOTOR->DATA.Speed_now) < ERROR_SPEED)
    {
        if (RUI_F_MATH_ABS_float(MOTOR->DATA.current) > ERROR_CURRENT)
        {
            RUI_F_HEAD_MOTOR_CLEAR(MOTOR);
			MOTOR->DATA.Stuck_Flag[0]++;
        }
    }
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //6020电机堵转检测函数
 *	@parameter:		    //
 *	@time:				//23-04-13 20:31
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-04-14 15:34    bestrui
 *  @UpData：           //给电机结构体增加堵转时间
 ************************************************************万能分隔符**************************************************************/
void RUI_F_HEAD_MOTOR6020_STUCK(struct RUI_MOTOR_Typedef* MOTOR , uint16_t ERROR_ANGLE , uint16_t ERROR_SPEED , uint16_t ERROR_TIME)
{
    //一定误差  速度小于某个值初步判断电机卡住，接下来去判断卡住的时间
    if (RUI_F_MATH_ABS_float(MOTOR->PID_P.Error[RUI_DF_NOW]) > ERROR_ANGLE && RUI_F_MATH_ABS_float(MOTOR->DATA.Speed_now) < ERROR_SPEED)
    {
        MOTOR->DATA.Stuck_Time++;
        if (MOTOR->DATA.Stuck_Time > ERROR_TIME)
        {
            RUI_F_HEAD_MOTOR_CLEAR(MOTOR);
            MOTOR->DATA.Stuck_Time = 0;
			MOTOR->DATA.Stuck_Flag[0]++;
        }
    }
    else
    {
        MOTOR->DATA.Stuck_Time = 0;
    }
    MOTOR->DATA.Aim_last = MOTOR->DATA.Aim;

}

