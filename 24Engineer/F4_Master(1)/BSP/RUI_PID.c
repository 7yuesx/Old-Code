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
#include "RUI_PID.h"
#include "MY_define.h"
#include "FFC.h"
#include "bsp_dwt.h"
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //通用PID参数初始化
 *	@parameter:		    //@电机结构体@单环OR双环@速度环数组@角度环数组
 *	@time:				//22-11-25 10:58
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2022-11-25 16:24    by 小瑞
 *  @UpData：           //增加了是否初始化完成的标志位
 *  @LastUpDataTime:    //2022-11-25 16:24    by 小瑞
 *  @UpData：           //受查表法启发，取消了i++
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_MOTOR_PID_COMMON_INIT(struct RUI_MOTOR_Typedef* MOTOR , uint8_t MOD , float* PID_S , float* PID_P)
{
    switch (MOD)
    {
        case RUI_DF_PID_DOUBLE:
        {
            MOTOR->PID_P.P       = PID_P[0];
            MOTOR->PID_P.I       = PID_P[1];
            MOTOR->PID_P.D       = PID_P[2];
            MOTOR->PID_P.I_Lit   = PID_P[3];
            MOTOR->PID_P.All_Lit = PID_P[4];

            MOTOR->PID_S.P       = PID_S[0];
            MOTOR->PID_S.I       = PID_S[1];
            MOTOR->PID_S.D       = PID_S[2];
            MOTOR->PID_S.I_Lit   = PID_S[3];
            MOTOR->PID_S.All_Lit = PID_S[4];

            MOTOR->PID_INIT = RUI_DF_READY;

            return RUI_DF_READY;
        } 
        case RUI_DF_PID_SINGLE:
        {
            MOTOR->PID_S.P       = PID_S[0];
            MOTOR->PID_S.I       = PID_S[1];
            MOTOR->PID_S.D       = PID_S[2];
            MOTOR->PID_S.I_Lit   = PID_S[3];
            MOTOR->PID_S.All_Lit = PID_S[4];

            MOTOR->PID_INIT = RUI_DF_READY;

            return RUI_DF_READY;
        } 
        default:
            return RUI_DF_ERROR;
    }
}


/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //头部PID+前馈总初始化函数
 *	@parameter:		    //
 *	@time:				//23-04-13 12:42
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_MOTOR_PID_HEAD_INIT(void)
{
	/******************************抬升前馈赋值********************************/
	float C_LIFT_L[3]					= WHW_DF_FFC_DATA_HEAD_LIFT_L;
	float C_LIFT_R[3]					= WHW_DF_FFC_DATA_HEAD_LIFT_R;
	
	Feedforward_Init(&FFC_ALL.LIFT_L,4000,C_LIFT_L,0.5f,2,2);
	Feedforward_Init(&FFC_ALL.LIFT_R,4000,C_LIFT_R,0.5f,2,2);
	
	/******************************抬升PID双环赋值********************************/
	float RUI_HEAD_ANGLE_LIFT[5] 		= RUI_DF_PID_DATA_HEAD_LIFT_P;
    float RUI_HEAD_SPEED_LIFT[5]  		= RUI_DF_PID_DATA_HEAD_LIFT_S;
	
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_LIFT_L,RUI_DF_PID_DOUBLE,RUI_HEAD_SPEED_LIFT,RUI_HEAD_ANGLE_LIFT);
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_LIFT_R,RUI_DF_PID_DOUBLE,RUI_HEAD_SPEED_LIFT,RUI_HEAD_ANGLE_LIFT);

	/******************************前伸前馈赋值********************************/
	float C_HORIZONTAL_L[3]					= WHW_DF_FFC_DATA_HEAD_HORIZONTAL_L;
	float C_HORIZONTAL_R[3]					= WHW_DF_FFC_DATA_HEAD_HORIZONTAL_R;
	
	Feedforward_Init(&FFC_ALL.HORIZONTAL_L,4000,C_HORIZONTAL_L,0.5f,2,2);
	Feedforward_Init(&FFC_ALL.HORIZONTAL_R,4000,C_HORIZONTAL_R,0.5f,2,2);
	
	/******************************前伸PID双环赋值********************************/
	float RUI_HEAD_ANGLE_HORIZONTAL[5]	   		= RUI_DF_PID_DATA_HEAD_HORIZONTAL_P;
	float RUI_HEAD_SPEED_HORIZONTAL[5]	   		= RUI_DF_PID_DATA_HEAD_HORIZONTAL_S;
	
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_HORIZONTAL_L,RUI_DF_PID_DOUBLE,RUI_HEAD_SPEED_HORIZONTAL,RUI_HEAD_ANGLE_HORIZONTAL);
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_HORIZONTAL_R,RUI_DF_PID_DOUBLE,RUI_HEAD_SPEED_HORIZONTAL,RUI_HEAD_ANGLE_HORIZONTAL);
	
	/******************************横移前馈赋值********************************/
	float C_SWAY[3]							= WHW_DF_FFC_DATA_HEAD_SWAY;
	
	Feedforward_Init(&FFC_ALL.SWAY,4000,C_SWAY,0.5f,2,2);
	
	/******************************横移PID双环赋值********************************/
	float WHW_MIDDLE_ANGLE_SWAY[5] 	= RUI_DF_PID_DATA_HEAD_SWAY_P;
	float WHW_MIDDLE_SPEED_SWAY[5] 	= RUI_DF_PID_DATA_HEAD_SWAY_S;
	
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_SWAY,RUI_DF_PID_DOUBLE,WHW_MIDDLE_SPEED_SWAY,WHW_MIDDLE_ANGLE_SWAY);

    /******************************Yaw轴前馈赋值********************************/
    float C_Yaw[3]							= WHW_DF_FFC_DATA_HEAD_Yaw;

    Feedforward_Init(&FFC_ALL.Yaw,4000,C_Yaw,0.5f,2,2);

    /******************************Yaw轴PID赋值********************************/
    float WHW_MIDDLE_ANGLE_Yaw[5] 	= RUI_DF_PID_DATA_HEAD_Yaw_P;
	float WHW_MIDDLE_SPEED_Yaw[5] 	= RUI_DF_PID_DATA_HEAD_Yaw_S;

    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_Yaw,RUI_DF_PID_DOUBLE,WHW_MIDDLE_SPEED_Yaw,WHW_MIDDLE_ANGLE_Yaw);

    /******************************差动关节PID赋值********************************/
    float RUI_HEAD_ANGLE_Pitch[5] 		= RUI_DF_PID_DATA_HEAD_2006_Pitch;
    float RUI_HEAD_ANGLE_Roll[5]  		= RUI_DF_PID_DATA_HEAD_2006_Roll;
	float RUI_HEAD_SPEED_R[5]	   		= RUI_DF_PID_DATA_HEAD_2006_Right;
	float RUI_HEAD_SPEED_L[5]	   		= RUI_DF_PID_DATA_HEAD_2006_Left;
	
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_Pitch  ,RUI_DF_PID_SINGLE,RUI_HEAD_ANGLE_Pitch,0);
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_Roll   ,RUI_DF_PID_SINGLE,RUI_HEAD_ANGLE_Roll ,0);
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_Right  ,RUI_DF_PID_SINGLE,RUI_HEAD_SPEED_R    ,0);
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_Left   ,RUI_DF_PID_SINGLE,RUI_HEAD_SPEED_L    ,0);
	
	/******************************图传抬升PID赋值********************************/
	float RUI_HEAD_ANGLE_Camera[5]		= RUI_DF_PID_DATA_HEAD_2006_Camera_P;
	float RUI_HEAD_SPEED_Camera[5]		= RUI_DF_PID_DATA_HEAD_2006_Camera_S;
	
	RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_Camera,RUI_DF_PID_DOUBLE,RUI_HEAD_SPEED_Camera,RUI_HEAD_ANGLE_Camera);
	
	return RUI_DF_READY;
}


/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //3508单速度环PID(用在底盘)
 *	@parameter:		    //
 *	@time:				//22-11-23 20:03
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_CHSISS_3508RM(struct RUI_MOTOR_Typedef* MOTOR)
{
    MOTOR->DATA.dt = DWT_GetDeltaT((void *)&MOTOR->DATA.DWT_CNT);

    MOTOR->PID_S.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Speed_now;
    /*比例输出*/
    MOTOR->PID_S.P_out = (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.P);
    /*微分输出*/
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_S.D;
    /*积分输出*/
    MOTOR->PID_S.I_out += (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.I);
    MOTOR->PID_S.I_out += MOTOR->PID_S.D_out;
    /*积分限幅*/
    MOTOR->PID_S.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.I_Lit , -MOTOR->PID_S.I_Lit , MOTOR->PID_S.I_out);
    /*数据迭代*/
    MOTOR->PID_S.Error[RUI_DF_LAST] = MOTOR->PID_S.Error[RUI_DF_NOW];
    /*速度环总输出*/
    MOTOR->PID_S.All_out = (MOTOR->PID_S.P_out + MOTOR->PID_S.I_out);
    /*总输出限幅*/
    MOTOR->PID_S.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.All_Lit , -MOTOR->PID_S.All_Lit , MOTOR->PID_S.All_out);

    /*电流环*/
    MOTOR->PID_C.Error[RUI_DF_NOW] = MOTOR->PID_S.All_out - MOTOR->DATA.current;
    /*比例输出*/
    MOTOR->PID_C.P_out = (MOTOR->PID_C.Error[RUI_DF_NOW] * MOTOR->PID_C.P);
    /*微分输出*/
    MOTOR->PID_C.D_out = (MOTOR->PID_C.Error[RUI_DF_NOW] - MOTOR->PID_C.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_C.D;
    /*积分输出*/
    MOTOR->PID_C.I_out += (MOTOR->PID_C.Error[RUI_DF_NOW] * MOTOR->PID_C.I);
    /*积分限幅*/
    MOTOR->PID_C.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_C.I_Lit , -MOTOR->PID_C.I_Lit , MOTOR->PID_C.I_out);
    /*数据迭代*/
    MOTOR->PID_C.Error[RUI_DF_LAST] = MOTOR->PID_C.Error[RUI_DF_NOW];
    /*速度环总输出*/
    MOTOR->PID_C.All_out = (MOTOR->PID_C.P_out + MOTOR->PID_C.I_out);
    /*总输出限幅*/
    MOTOR->PID_C.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_C.All_Lit , -MOTOR->PID_C.All_Lit , MOTOR->PID_C.All_out);

}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //3508双环PID(预计用在精细控制移动部分)
 *	@parameter:		    //
 *	@time:				//22-11-23 20:03
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_PID_TWO_3508RM(struct RUI_MOTOR_Typedef* MOTOR)
{
    MOTOR->DATA.dt = DWT_GetDeltaT((void *)&MOTOR->DATA.DWT_CNT);

    MOTOR->PID_P.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Angle_Infinite;
    /*比例输出*/
    MOTOR->PID_P.P_out = (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.P);
    /*微分输出*/
    MOTOR->PID_P.D_out = (MOTOR->PID_P.Error[RUI_DF_NOW] - MOTOR->PID_P.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_P.D;
    /*积分输出*/
    MOTOR->PID_P.I_out += (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.I);
    MOTOR->PID_P.I_out += MOTOR->PID_P.D_out;
    /*积分限幅*/
    MOTOR->PID_P.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_P.I_Lit , -MOTOR->PID_P.I_Lit , MOTOR->PID_P.I_out);
    /*数据迭代*/
    MOTOR->PID_P.Error[RUI_DF_LAST] = MOTOR->PID_P.Error[RUI_DF_NOW];
    /*角度环总输出*/
    MOTOR->PID_P.All_out = (MOTOR->PID_P.P_out + MOTOR->PID_P.I_out);
    /*总输出限幅*/
    MOTOR->PID_P.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_P.All_Lit , -MOTOR->PID_P.All_Lit , MOTOR->PID_P.All_out);

    MOTOR->PID_S.Error[RUI_DF_NOW] = MOTOR->PID_P.All_out - MOTOR->DATA.Speed_now;

    /*比例输出*/
    MOTOR->PID_S.P_out = (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.P);
    /*微分输出*/
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_S.D;
    /*积分输出*/
    MOTOR->PID_S.I_out += (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.I);
    MOTOR->PID_S.I_out += MOTOR->PID_S.D_out;
    /*积分限幅*/
    MOTOR->PID_S.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.I_Lit , -MOTOR->PID_S.I_Lit , MOTOR->PID_S.I_out);
    /*数据迭代*/
    MOTOR->PID_S.Error[RUI_DF_LAST] = MOTOR->PID_S.Error[RUI_DF_NOW];
    /*速度环总输出*/
    MOTOR->PID_S.All_out = (MOTOR->PID_S.P_out + MOTOR->PID_S.I_out);
    /*总输出限幅*/
    MOTOR->PID_S.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.All_Lit , -MOTOR->PID_S.All_Lit , MOTOR->PID_S.All_out);
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //2006双环PID
 *	@parameter:		    //
 *	@time:				//22-11-23 20:05
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_PID_TWO_2006RM(struct RUI_MOTOR_Typedef* MOTOR)
{
    MOTOR->DATA.dt = DWT_GetDeltaT((void *)&MOTOR->DATA.DWT_CNT);

    MOTOR->PID_P.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Angle_Infinite;
    /*比例输出*/
    MOTOR->PID_P.P_out = (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.P);
    /*微分输出*/
    MOTOR->PID_P.D_out = (MOTOR->PID_P.Error[RUI_DF_NOW] - MOTOR->PID_P.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_P.D;
    /*积分输出*/
    MOTOR->PID_P.I_out += (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.I);
    MOTOR->PID_P.I_out += MOTOR->PID_P.D_out;
    /*积分限幅*/
    MOTOR->PID_P.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_P.I_Lit , -MOTOR->PID_P.I_Lit , MOTOR->PID_P.I_out);
    /*数据迭代*/
    MOTOR->PID_P.Error[RUI_DF_LAST] = MOTOR->PID_P.Error[RUI_DF_NOW];
    /*角度环总输出*/
    MOTOR->PID_P.All_out = (MOTOR->PID_P.P_out + MOTOR->PID_P.I_out);
    /*总输出限幅*/
    MOTOR->PID_P.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_P.All_Lit , -MOTOR->PID_P.All_Lit , MOTOR->PID_P.All_out);

    MOTOR->PID_S.Error[RUI_DF_NOW] = MOTOR->PID_P.All_out - MOTOR->DATA.Speed_now;

    /*比例输出*/
    MOTOR->PID_S.P_out = (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.P);
    /*微分输出*/
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_S.D;
    /*积分输出*/
    MOTOR->PID_S.I_out += (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.I);
    MOTOR->PID_S.I_out += MOTOR->PID_S.D_out;
    /*积分限幅*/
    MOTOR->PID_S.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.I_Lit , -MOTOR->PID_S.I_Lit , MOTOR->PID_S.I_out);
    /*数据迭代*/
    MOTOR->PID_S.Error[RUI_DF_LAST] = MOTOR->PID_S.Error[RUI_DF_NOW];
    /*速度环总输出*/
    MOTOR->PID_S.All_out = (MOTOR->PID_S.P_out + MOTOR->PID_S.I_out);
    /*总输出限幅*/
    MOTOR->PID_S.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.All_Lit , -MOTOR->PID_S.All_Lit , MOTOR->PID_S.All_out);
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //2006单环PID,陀螺仪角度
 *	@parameter:		    //
 *	@time:				//22-11-23 20:05
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void MPU_MOTOR_PID_ONE_2006RM(struct RUI_MOTOR_Typedef* MOTOR,float Aim_Angle,float Date_MPU_Angle)
{
    MOTOR->DATA.dt = DWT_GetDeltaT((void *)&MOTOR->DATA.DWT_CNT);

    MOTOR->PID_S.Error[RUI_DF_NOW] = Aim_Angle - Date_MPU_Angle;
    /*比例输出*/
    MOTOR->PID_S.P_out = (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.P);
    /*微分输出*/
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_S.D;
    /*积分输出*/
    MOTOR->PID_S.I_out += (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.I);
    MOTOR->PID_S.I_out += MOTOR->PID_S.D_out;
    /*积分限幅*/
    MOTOR->PID_S.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.I_Lit , -MOTOR->PID_S.I_Lit , MOTOR->PID_S.I_out);
    /*数据迭代*/
    MOTOR->PID_S.Error[RUI_DF_LAST] = MOTOR->PID_S.Error[RUI_DF_NOW];
    /*角度环总输出*/
    MOTOR->PID_S.All_out = (MOTOR->PID_S.P_out + MOTOR->PID_S.I_out);
    /*总输出限幅*/
    MOTOR->PID_S.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.All_Lit , -MOTOR->PID_S.All_Lit , MOTOR->PID_S.All_out);
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //6020双环PID
 *	@parameter:		    //
 *	@time:				//22-11-23 20:05
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_PID_TWO_6020RM(struct RUI_MOTOR_Typedef* MOTOR)
{
    MOTOR->DATA.dt = DWT_GetDeltaT((void *)&MOTOR->DATA.DWT_CNT);

    MOTOR->PID_P.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Angle_Infinite;
    /*比例输出*/
    MOTOR->PID_P.P_out = (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.P);
    /*微分输出*/
    MOTOR->PID_P.D_out = (MOTOR->PID_P.Error[RUI_DF_NOW] - MOTOR->PID_P.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_P.D;
    /*积分输出*/
    MOTOR->PID_P.I_out += (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.I);
    MOTOR->PID_P.I_out += MOTOR->PID_P.D_out;
    /*积分限幅*/
    MOTOR->PID_P.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_P.I_Lit , -MOTOR->PID_P.I_Lit , MOTOR->PID_P.I_out);
    /*数据迭代*/
    MOTOR->PID_P.Error[RUI_DF_LAST] = MOTOR->PID_P.Error[RUI_DF_NOW];
    /*角度环总输出*/
    MOTOR->PID_P.All_out = (MOTOR->PID_P.P_out + MOTOR->PID_P.I_out);
    /*总输出限幅*/
    MOTOR->PID_P.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_P.All_Lit , -MOTOR->PID_P.All_Lit , MOTOR->PID_P.All_out);

    MOTOR->PID_S.Error[RUI_DF_NOW] = MOTOR->PID_P.All_out - MOTOR->DATA.Speed_now;

    /*比例输出*/
    MOTOR->PID_S.P_out = (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.P);
    /*微分输出*/
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) / MOTOR->DATA.dt * MOTOR->PID_S.D;
    /*积分输出*/
    MOTOR->PID_S.I_out += (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.I);
    MOTOR->PID_S.I_out += MOTOR->PID_S.D_out;
    /*积分限幅*/
    MOTOR->PID_S.I_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.I_Lit , -MOTOR->PID_S.I_Lit , MOTOR->PID_S.I_out);
    /*数据迭代*/
    MOTOR->PID_S.Error[RUI_DF_LAST] = MOTOR->PID_S.Error[RUI_DF_NOW];
    /*速度环总输出*/
    MOTOR->PID_S.All_out = (MOTOR->PID_S.P_out + MOTOR->PID_S.I_out);
    /*总输出限幅*/
    MOTOR->PID_S.All_out = RUI_F_MATH_Limit_float(MOTOR->PID_S.All_Lit , -MOTOR->PID_S.All_Lit , MOTOR->PID_S.All_out);
}

