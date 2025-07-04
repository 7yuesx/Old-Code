/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-04-18 10:32:32
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-05 16:41:44
 */
#include "Reset_task.h"
#include "RUI_MOTOR.h"
#include "Silver_ore_task.h"
#include "Goid_ore_task.h"
#include "exchange_task.h"

void One_Reset_task(struct DBUS_Typedef* RUI_V_DBUS_V , struct CONTAL_Typedef *RUI_V_CONTAL_V)
{
	if(RUI_V_DBUS_V->KeyBoard.Z == 1)
	{
		RUI_V_CONTAL_V->MOD = 0;
		//差动关节
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_Left);
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_Right);
		//横移
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_SWAY);
		//前伸
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_HORIZONTAL_L);
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_HORIZONTAL_R);
		//抬升
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_LIFT_L);
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_LIFT_R);
		
		WHW_F_HEAD_MOTOR_SIT(&RUI_V_MOTOR_Camera);
		
		RUI_V_CONTAL_V->HEAD.LIFT = 0;
		RUI_V_CONTAL_V->HEAD.HORIZONTAL = 0;
		RUI_V_CONTAL_V->HEAD.SWAY = 0;
		RUI_V_CONTAL_V->HEAD.Pitch = 0;
		RUI_V_CONTAL_V->HEAD.Roll = 0;
		RUI_V_CONTAL_V->HEAD.Yaw = 0;
		RUI_V_CONTAL_V->HEAD.CUP_PUMP = 0;
		RUI_V_CONTAL_V->HEAD.Camera = 0;
		RUI_V_CONTAL_V->TUCHUAN.pitch = 750;
		RUI_V_CONTAL_V->TUCHUAN.yaw = 1550;
		
		RUI_V_CONTAL_V->User.CUP_PUMP = 0;
		RUI_V_CONTAL_V->User.HORIZONTAL = 0;
		RUI_V_CONTAL_V->User.LIFT = 0;
		RUI_V_CONTAL_V->User.Pitch = 0;
		RUI_V_CONTAL_V->User.Roll = 0;
		RUI_V_CONTAL_V->User.SWAY = 0;
		RUI_V_CONTAL_V->User.Yaw = 0;
		
		One_flag_1 = 0;
		One_flag_2 = 0;
		One_flag_3 = 0;
		One_flag_4 = 0;
	}
}

void One_Back_task(struct DBUS_Typedef* RUI_V_DBUS_V , struct CONTAL_Typedef *RUI_V_CONTAL_V)
{
	if(RUI_V_DBUS_V->KeyBoard.X == 1)
	{
		RUI_V_CONTAL_V->HEAD.LIFT = 0;
		RUI_V_CONTAL_V->HEAD.HORIZONTAL = 0;
		RUI_V_CONTAL_V->HEAD.SWAY = 0;
		RUI_V_CONTAL_V->HEAD.Pitch = 0;
		RUI_V_CONTAL_V->HEAD.Roll = 0;
		RUI_V_CONTAL_V->HEAD.Camera = -294000;
		RUI_V_CONTAL_V->TUCHUAN.pitch = 750;
		RUI_V_CONTAL_V->TUCHUAN.yaw = 1550;
		
		if(RUI_V_CONTAL_V->HEAD.CUP_PUMP == 1)
		{
			RUI_V_CONTAL_V->HEAD.Yaw = 0;			
		}
		else if(RUI_V_CONTAL_V->HEAD.CUP_PUMP == 0)
		{
			RUI_V_CONTAL_V->HEAD.Yaw = 655;
		}
		
		RUI_V_CONTAL_V->User.CUP_PUMP = 0;
		RUI_V_CONTAL_V->User.HORIZONTAL = 0;
		RUI_V_CONTAL_V->User.LIFT = 0;
		RUI_V_CONTAL_V->User.Pitch = 0;
		RUI_V_CONTAL_V->User.Roll = 0;
		RUI_V_CONTAL_V->User.SWAY = 0;
		RUI_V_CONTAL_V->User.Yaw = 0;
		
		One_flag_1 = 0;
		One_flag_2 = 0;
		One_flag_3 = 0;
		One_flag_4 = 0;
		
		RUI_V_DBUS_V->KeyBoard.F_PreeNumber = 0;
		RUI_V_DBUS_V->KeyBoard.G_PreeNumber = 0;
		RUI_V_DBUS_V->KeyBoard.V_PreeNumber = 0;
		RUI_V_DBUS_V->KeyBoard.B_PreeNumber = 0;
		
		RUI_V_CONTAL_V->MOD = 0;
	}
}
