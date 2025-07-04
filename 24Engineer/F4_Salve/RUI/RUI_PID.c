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
            } break;

        case RUI_DF_PID_SINGLE:
            {
                MOTOR->PID_S.P       = PID_S[0];
                MOTOR->PID_S.I       = PID_S[1];
                MOTOR->PID_S.D       = PID_S[2];
                MOTOR->PID_S.I_Lit   = PID_S[3];
                MOTOR->PID_S.All_Lit = PID_S[4];

                MOTOR->PID_INIT = RUI_DF_READY;

                return RUI_DF_READY;

            } break;

        default:
            return RUI_DF_ERROR;
            break;
    }
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //电流环赋值
 *	@parameter:		    //
 *	@time:				//23-05-27 17:45
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_PID_CURRENT_INIT(struct RUI_MOTOR_Typedef* MOTOR , float* PID_C)
{
    MOTOR->PID_C.P       = PID_C[0];
    MOTOR->PID_C.I       = PID_C[1];
    MOTOR->PID_C.D       = PID_C[2];
    MOTOR->PID_C.I_Lit   = PID_C[3];
    MOTOR->PID_C.All_Lit = PID_C[4];
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //底盘PID总初始化函数
 *	@parameter:		    //
 *	@time:				//23-03-28 20:24
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_MOTOR_PID_BOTTOM_INIT(void)
{
    /******************************底盘电机PID单速度环赋值********************************/
    float RUI_MOTOR_BOTTOM_3508_PID_SPEED[5]   = RUI_DF_PID_DATA_BOTTOM_3508_SPEED;
    float RUI_MOTOR_BOTTOM_3508_PID_CURRENT[5] = RUI_DF_PID_DATA_BOTTOM_3508_CURENT;

    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_3508_1 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_3508_PID_SPEED , 0);
    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_3508_2 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_3508_PID_SPEED , 0);
    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_3508_3 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_3508_PID_SPEED , 0);
    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_3508_4 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_3508_PID_SPEED , 0);

    RUI_F_MOTOR_PID_CURRENT_INIT(&RUI_V_MOTOR_BOTTOM_3508_1 , RUI_MOTOR_BOTTOM_3508_PID_CURRENT);
    RUI_F_MOTOR_PID_CURRENT_INIT(&RUI_V_MOTOR_BOTTOM_3508_2 , RUI_MOTOR_BOTTOM_3508_PID_CURRENT);
    RUI_F_MOTOR_PID_CURRENT_INIT(&RUI_V_MOTOR_BOTTOM_3508_3 , RUI_MOTOR_BOTTOM_3508_PID_CURRENT);
    RUI_F_MOTOR_PID_CURRENT_INIT(&RUI_V_MOTOR_BOTTOM_3508_4 , RUI_MOTOR_BOTTOM_3508_PID_CURRENT);

    float RUI_MOTOR_BOTTOM_2006_PID_SPEED[5]   = RUI_DF_PID_DATA_BOTTOM_2006_SPEED;

    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_2006_1 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_2006_PID_SPEED , 0);
    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_2006_2 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_2006_PID_SPEED , 0);
    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_2006_3 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_2006_PID_SPEED , 0);
    RUI_F_MOTOR_PID_COMMON_INIT(&RUI_V_MOTOR_BOTTOM_2006_4 , RUI_DF_PID_SINGLE , RUI_MOTOR_BOTTOM_2006_PID_SPEED , 0);

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

    MOTOR->PID_S.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Speed_now;
    /*比例输出*/
    MOTOR->PID_S.P_out = (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.P);
    /*微分输出*/
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) * MOTOR->PID_S.D;
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
    MOTOR->PID_C.D_out = (MOTOR->PID_C.Error[RUI_DF_NOW] - MOTOR->PID_C.Error[RUI_DF_LAST]) * MOTOR->PID_C.D;
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
    MOTOR->PID_P.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Angle_Infinite;

    /*比例输出*/
    MOTOR->PID_P.P_out = (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.P);
    /*微分输出*/
    MOTOR->PID_P.D_out = (MOTOR->PID_P.Error[RUI_DF_NOW] - MOTOR->PID_P.Error[RUI_DF_LAST]) * MOTOR->PID_P.D;
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
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) * MOTOR->PID_S.D;
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
    MOTOR->PID_P.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Angle_Infinite;

    /*比例输出*/
    MOTOR->PID_P.P_out = (MOTOR->PID_P.Error[RUI_DF_NOW] * MOTOR->PID_P.P);
    /*微分输出*/
    MOTOR->PID_P.D_out = (MOTOR->PID_P.Error[RUI_DF_NOW] - MOTOR->PID_P.Error[RUI_DF_LAST]) * MOTOR->PID_P.D;
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
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) * MOTOR->PID_S.D;
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
 *	@performance:	    //2006单环PID
 *	@parameter:		    //
 *	@time:				//22-11-23 20:05
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_MOTOR_CHSISS_2006RM(struct RUI_MOTOR_Typedef* MOTOR)
{
	MOTOR->PID_S.Error[RUI_DF_NOW] = MOTOR->DATA.Aim - MOTOR->DATA.Speed_now;

    /*比例输出*/
    MOTOR->PID_S.P_out = (MOTOR->PID_S.Error[RUI_DF_NOW] * MOTOR->PID_S.P);
    /*微分输出*/
    MOTOR->PID_S.D_out = (MOTOR->PID_S.Error[RUI_DF_NOW] - MOTOR->PID_S.Error[RUI_DF_LAST]) * MOTOR->PID_S.D;
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
