/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-09-13 10:32:08
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:45:12
 */
#include "head_task.h"
#include "RUI_PID.h"
#include "MY_define.h"
#include "RUI_CAN.h"
#include "can.h"
#include "RUI_DBUS.h"
#include "RUI_ROOT_INIT.h"
#include "FFC.h"

uint8_t RUI_F_HEAD_AIM_INIT(void)
{
	if (
            RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_L      == RUI_DF_OFFLINE ||
            RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_R      == RUI_DF_OFFLINE ||
            RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_L      		 == RUI_DF_OFFLINE ||
            RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_R            == RUI_DF_OFFLINE ||
			RUI_ROOT.STATUS.MOTOR_HEAD_SWAY           	 == RUI_DF_OFFLINE ||
			RUI_ROOT.STATUS.MOTOR_HEAD_Yaw            	 == RUI_DF_OFFLINE ||
            RUI_ROOT.STATUS.MOTOR_HEAD_Left              == RUI_DF_OFFLINE ||
            RUI_ROOT.STATUS.MOTOR_HEAD_Right             == RUI_DF_OFFLINE ||
			RUI_ROOT.STATUS.MOTER_HEAD_Camera			 == RUI_DF_OFFLINE
        )
		return RUI_DF_ERROR;
        
    
	
	if (HAL_GetTick() < 5000)
    {
        return RUI_DF_ERROR;
    }
    RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_HORIZONTAL_L);
    RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_HORIZONTAL_R);
    RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_LIFT_L);
    RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_LIFT_R);
    RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_SWAY);
	RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_Yaw);
    RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_Left);
    RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_Right);
	RUI_F_HEAD_MOTOR_CLEAR(&RUI_V_MOTOR_Camera);

    return RUI_DF_READY;
}

uint8_t heading(uint8_t DBUS_STATUS)
{
	static uint8_t PID_INIT=RUI_DF_ERROR;
	static uint8_t AIM_INIT = RUI_DF_ERROR;
	
	//电机PID赋值
	if (PID_INIT != RUI_DF_READY)
    {
        PID_INIT = RUI_F_MOTOR_PID_HEAD_INIT();
        return RUI_DF_ERROR;
    }
	//电机在线检测
	if (AIM_INIT != RUI_DF_READY)
    {
        AIM_INIT = RUI_F_HEAD_AIM_INIT();
        return RUI_DF_ERROR;
    }
	
	/******************************微动开关控制*********************************/
	if(RUI_V_CONTAL.MOD == 1)
	{
		if((Micro.LIFT_L == 1)&&(Micro.LIFT_R == 0))//抬升降到底
		{
			if(RUI_V_CONTAL.HEAD.LIFT < RUI_V_CONTAL_Last.HEAD.LIFT)//还继续下降
			{
				RUI_V_CONTAL.HEAD.LIFT = RUI_V_CONTAL_Last.HEAD.LIFT;//用上一次的值
				RUI_V_CONTAL.User.LIFT = RUI_V_CONTAL_Last.User.LIFT;//用上一次的值
				WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_LIFT_L);//自动复位
				WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_LIFT_R);//自动复位
			}
		}
		
		if(Micro.SWAY_E == 0)//横移到头
		{
			if(RUI_V_CONTAL.HEAD.SWAY < RUI_V_CONTAL_Last.HEAD.SWAY)//还继续横移进
			{
				RUI_V_CONTAL.HEAD.SWAY = RUI_V_CONTAL_Last.HEAD.SWAY;//用上一次的值
			}
		}
		
		if(Micro.SWAY_B == 1)//横移到初始
		{
			if(RUI_V_CONTAL.HEAD.SWAY > RUI_V_CONTAL_Last.HEAD.SWAY)//还继续横移退
			{
				RUI_V_CONTAL.HEAD.SWAY = RUI_V_CONTAL_Last.HEAD.SWAY;//用上一次的值
				WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_SWAY);//自动复位
			}
		}
		
		if((Micro.LIFT_L == 0)&&(Micro.LIFT_R == 1))//抬升没降到底
		{
			RUI_V_CONTAL_Last.HEAD.LIFT = RUI_V_CONTAL.HEAD.LIFT;//正常同步数据
			RUI_V_CONTAL_Last.User.LIFT = RUI_V_CONTAL.User.LIFT;//正常同步数据
		}
		
		if((Micro.SWAY_E == 1)&&(Micro.SWAY_B == 0))//横移没到两端
		{
			RUI_V_CONTAL_Last.HEAD.SWAY = RUI_V_CONTAL.HEAD.SWAY;//正常同步数据
			RUI_V_CONTAL_Last.User.SWAY = RUI_V_CONTAL.User.SWAY;//正常同步数据
		}
	}
	if(RUI_V_CONTAL.MOD == 0)
	{
		if((Micro.LIFT_L == 1)&&(Micro.LIFT_R == 0))//抬升降到底
		{
			if(RUI_V_CONTAL.HEAD.LIFT < RUI_V_CONTAL_Last.HEAD.LIFT)//还继续下降
			{
				RUI_V_CONTAL.HEAD.LIFT = RUI_V_CONTAL_Last.HEAD.LIFT;//用上一次的值
				RUI_V_CONTAL.User.LIFT = RUI_V_CONTAL_Last.User.LIFT;//用上一次的值
				WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_LIFT_L);//自动复位
				WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_LIFT_R);//自动复位
			}
		}
		
		if(Micro.SWAY_E == 0)//横移到头
		{
			if(RUI_V_CONTAL.HEAD.HORIZONTAL > RUI_V_CONTAL_Last.HEAD.HORIZONTAL)//还继续横移进
			{
				RUI_V_CONTAL.HEAD.HORIZONTAL = RUI_V_CONTAL_Last.HEAD.HORIZONTAL;//用上一次的值
			}
		}
		
		if(Micro.SWAY_B == 1)//横移到初始
		{
			if(RUI_V_CONTAL.HEAD.HORIZONTAL < RUI_V_CONTAL_Last.HEAD.HORIZONTAL)//还继续横移退
			{
				RUI_V_CONTAL.HEAD.HORIZONTAL = RUI_V_CONTAL_Last.HEAD.HORIZONTAL;//用上一次的值
				WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_SWAY);//自动复位
			}
		}
		
		if((Micro.LIFT_L == 0)&&(Micro.LIFT_R == 1))//抬升没降到底
		{
			RUI_V_CONTAL_Last.HEAD.LIFT = RUI_V_CONTAL.HEAD.LIFT;//正常同步数据
			RUI_V_CONTAL_Last.User.LIFT = RUI_V_CONTAL.User.LIFT;//正常同步数据
		}
		
		if((Micro.SWAY_E == 1)&&(Micro.SWAY_B == 0))//横移没到两端
		{
			RUI_V_CONTAL_Last.HEAD.HORIZONTAL = RUI_V_CONTAL.HEAD.HORIZONTAL;//正常同步数据
			RUI_V_CONTAL_Last.User.HORIZONTAL = RUI_V_CONTAL.User.HORIZONTAL;//正常同步数据
		}
	}
	/****************************************************************************/
	
	//头部赋值
	if(RUI_V_CONTAL.MOD == 1)
	{
		RUI_V_MOTOR_HORIZONTAL_L.DATA.Aim		= +RUI_V_CONTAL.HEAD.HORIZONTAL+RUI_V_CONTAL.User.HORIZONTAL;
		RUI_V_MOTOR_HORIZONTAL_R.DATA.Aim		= -RUI_V_CONTAL.HEAD.HORIZONTAL-RUI_V_CONTAL.User.HORIZONTAL;
		RUI_V_MOTOR_SWAY.DATA.Aim				= -RUI_V_CONTAL.HEAD.SWAY -RUI_V_CONTAL.User.SWAY;
	}
	if(RUI_V_CONTAL.MOD == 0)
	{
		RUI_V_MOTOR_HORIZONTAL_L.DATA.Aim		= +RUI_V_CONTAL.HEAD.SWAY+RUI_V_CONTAL.User.SWAY;
		RUI_V_MOTOR_HORIZONTAL_R.DATA.Aim		= -RUI_V_CONTAL.HEAD.SWAY-RUI_V_CONTAL.User.SWAY;
		RUI_V_MOTOR_SWAY.DATA.Aim				= +RUI_V_CONTAL.HEAD.HORIZONTAL +RUI_V_CONTAL.User.HORIZONTAL;
	}
	RUI_V_MOTOR_LIFT_L.DATA.Aim				= -RUI_V_CONTAL.HEAD.LIFT;
	RUI_V_MOTOR_LIFT_R.DATA.Aim				= +RUI_V_CONTAL.HEAD.LIFT;
	RUI_V_MOTOR_Yaw.DATA.Aim	            = RUI_V_CONTAL.HEAD.Yaw + RUI_V_CONTAL.User.Yaw*46 + WHW_DF_Yaw_RESET;
    RUI_V_MOTOR_Pitch.DATA.Aim              = -RUI_V_CONTAL.HEAD.Pitch + RUI_V_CONTAL.User.Pitch*6666;
    RUI_V_MOTOR_Roll.DATA.Aim               = RUI_V_CONTAL.HEAD.Roll + RUI_V_CONTAL.User.Roll*6666;
    RUI_V_MOTOR_Camera.DATA.Aim				= RUI_V_CONTAL.HEAD.Camera*0.8;//需要增大
	
	//遥控离线保护
	if(!DBUS_STATUS)
    {	/*限幅归零*/
		//前伸
		RUI_V_MOTOR_HORIZONTAL_L.PID_P.I_Lit = 0;
        RUI_V_MOTOR_HORIZONTAL_L.PID_S.I_Lit = 0;

        RUI_V_MOTOR_HORIZONTAL_R.PID_P.I_Lit = 0;
        RUI_V_MOTOR_HORIZONTAL_R.PID_S.I_Lit = 0;

		//升降限幅归零
        RUI_V_MOTOR_LIFT_L.PID_P.I_Lit = 0;
        RUI_V_MOTOR_LIFT_L.PID_S.I_Lit = 0;

        RUI_V_MOTOR_LIFT_R.PID_P.I_Lit = 0;
        RUI_V_MOTOR_LIFT_R.PID_S.I_Lit = 0;
		
		//横移限幅归零
		RUI_V_MOTOR_SWAY.PID_P.I_Lit = 0;
		RUI_V_MOTOR_SWAY.PID_S.I_Lit = 0;

        //Yaw轴限幅归零
		RUI_V_MOTOR_Yaw.PID_P.I_Lit = 0;
		RUI_V_MOTOR_Yaw.PID_S.I_Lit = 0;

        //差动限幅归零
		RUI_V_MOTOR_Pitch.PID_S.I_Lit = 0;
		RUI_V_MOTOR_Roll.PID_S.I_Lit = 0;

        //差动限幅归零
		RUI_V_MOTOR_Left.PID_S.I_Lit = 0;
		RUI_V_MOTOR_Right.PID_S.I_Lit = 0;
		
		//图传相机
		RUI_V_MOTOR_Camera.PID_P.I_Lit = 0;
		RUI_V_MOTOR_Camera.PID_S.I_Lit = 0;
		
		/*误差值归零*/
		//前伸
        RUI_V_MOTOR_HORIZONTAL_L.DATA.Aim   = RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite;
        RUI_V_MOTOR_HORIZONTAL_R.DATA.Aim   = RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite;
		
        //升降误差值归零
        RUI_V_MOTOR_LIFT_L.DATA.Aim         = RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite;
        RUI_V_MOTOR_LIFT_R.DATA.Aim         = RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite;
		
		//横移误差值归零
		RUI_V_MOTOR_SWAY.DATA.Aim		    = RUI_V_MOTOR_SWAY.DATA.Angle_Infinite;
		
		//Yaw轴误差值归零
        RUI_V_MOTOR_Yaw.DATA.Aim	        = RUI_V_MOTOR_Yaw.DATA.Angle_Infinite;

        //差动误差值归零
        RUI_V_MOTOR_Left.DATA.Aim	        = RUI_V_MOTOR_Left.DATA.Angle_Infinite;
        RUI_V_MOTOR_Right.DATA.Aim	        = RUI_V_MOTOR_Right.DATA.Angle_Infinite;

        RUI_V_MOTOR_Pitch.DATA.Aim          = RUI_V_MOTOR_Left.DATA.Angle_Infinite + RUI_V_MOTOR_Right.DATA.Angle_Infinite;
        RUI_V_MOTOR_Roll.DATA.Aim           = RUI_V_MOTOR_Left.DATA.Angle_Infinite - RUI_V_MOTOR_Right.DATA.Angle_Infinite;

		RUI_V_MOTOR_Camera.DATA.Aim			= RUI_V_MOTOR_Camera.DATA.Angle_Infinite;
	}
	
	//电机堵转检测	
	RUI_F_HEAD_MOTOR3508_STUCK(&RUI_V_MOTOR_LIFT_L , 8000 , 10);
    RUI_F_HEAD_MOTOR3508_STUCK(&RUI_V_MOTOR_LIFT_R , 8000 , 10);
    RUI_F_HEAD_MOTOR3508_STUCK(&RUI_V_MOTOR_HORIZONTAL_L,2500,10);
	RUI_F_HEAD_MOTOR3508_STUCK(&RUI_V_MOTOR_HORIZONTAL_R,2500,10);
	RUI_F_HEAD_MOTOR3508_STUCK(&RUI_V_MOTOR_SWAY,4000,10);
    RUI_F_HEAD_MOTOR3508_STUCK(&RUI_V_MOTOR_Yaw,25000,10);
	RUI_F_HEAD_MOTOR3508_STUCK(&RUI_V_MOTOR_Camera,2500,10);
	
	//电机前馈计算
	Feedforward_Calculate(&FFC_ALL.LIFT_L , RUI_V_MOTOR_LIFT_L.DATA.Aim);
	Feedforward_Calculate(&FFC_ALL.LIFT_R , RUI_V_MOTOR_LIFT_R.DATA.Aim);
	Feedforward_Calculate(&FFC_ALL.HORIZONTAL_L , RUI_V_MOTOR_HORIZONTAL_L.DATA.Aim);
	Feedforward_Calculate(&FFC_ALL.HORIZONTAL_R , RUI_V_MOTOR_HORIZONTAL_R.DATA.Aim);
	Feedforward_Calculate(&FFC_ALL.SWAY , RUI_V_MOTOR_SWAY.DATA.Aim);
    Feedforward_Calculate(&FFC_ALL.Yaw , RUI_V_MOTOR_Yaw.DATA.Aim);

	//电机PID计算
	RUI_F_MOTOR_PID_TWO_3508RM(&RUI_V_MOTOR_LIFT_L);
	RUI_F_MOTOR_PID_TWO_3508RM(&RUI_V_MOTOR_LIFT_R);
    RUI_F_MOTOR_PID_TWO_3508RM(&RUI_V_MOTOR_HORIZONTAL_L);
    RUI_F_MOTOR_PID_TWO_3508RM(&RUI_V_MOTOR_HORIZONTAL_R);
	RUI_F_MOTOR_PID_TWO_3508RM(&RUI_V_MOTOR_SWAY);
    RUI_F_MOTOR_PID_TWO_3508RM(&RUI_V_MOTOR_Yaw);
	RUI_F_MOTOR_PID_TWO_3508RM(&RUI_V_MOTOR_Camera);

	//差动关节角度计算
	P_Angle = RUI_V_MOTOR_Left.DATA.Angle_Infinite + RUI_V_MOTOR_Right.DATA.Angle_Infinite;
    R_Angle = RUI_V_MOTOR_Left.DATA.Angle_Infinite - RUI_V_MOTOR_Right.DATA.Angle_Infinite;
	
	if (RUI_F_MATH_ABS_float(RUI_V_MOTOR_Left.DATA.Speed_now) < 10)
    {
        if (RUI_F_MATH_ABS_float(RUI_V_MOTOR_Left.DATA.current) > 3000)
        {
            RUI_V_MOTOR_Pitch.DATA.Aim     = P_Angle;
			RUI_V_MOTOR_Roll.DATA.Aim	   = R_Angle;
        }
    }
	if (RUI_F_MATH_ABS_float(RUI_V_MOTOR_Right.DATA.Speed_now) < 10)
    {
        if (RUI_F_MATH_ABS_float(RUI_V_MOTOR_Right.DATA.current) > 3000)
        {
            RUI_V_MOTOR_Pitch.DATA.Aim     = P_Angle;
			RUI_V_MOTOR_Roll.DATA.Aim	   = R_Angle;
        }
    }
	
    MPU_MOTOR_PID_ONE_2006RM(&RUI_V_MOTOR_Pitch , RUI_V_MOTOR_Pitch.DATA.Aim , P_Angle);
    MPU_MOTOR_PID_ONE_2006RM(&RUI_V_MOTOR_Roll  , RUI_V_MOTOR_Roll.DATA.Aim , R_Angle);
	
    MPU_MOTOR_PID_ONE_2006RM(&RUI_V_MOTOR_Left , 
                              RUI_V_MOTOR_Pitch.PID_S.All_out + RUI_V_MOTOR_Roll.PID_S.All_out , 
                              RUI_V_MOTOR_Left.DATA.Speed_now);
    MPU_MOTOR_PID_ONE_2006RM(&RUI_V_MOTOR_Right , 
                              RUI_V_MOTOR_Pitch.PID_S.All_out - RUI_V_MOTOR_Roll.PID_S.All_out , 
                              RUI_V_MOTOR_Right.DATA.Speed_now);

	return RUI_DF_READY;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //主机从机总的控制函数
 *	@parameter:		    //
 *	@time:				//23-05-27 17:58
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_TOTAL_CONTRAL(void)
{
    uint8_t RUI_V_DBUS_STATUS = RUI_ROOT.STATUS.RM_DBUS;
    switch (RUI_ROOT.MASTER_LOCATION)
    {
        case RUI_DF_MASTER_LOCATION_HEAD:
            {
                heading(RUI_V_DBUS_STATUS);
                return RUI_DF_READY;
            };
    }
    return RUI_DF_ERROR;
}

