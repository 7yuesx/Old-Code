/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-04-18 10:41:01
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-05 16:42:16
 */
#include "exchange_task.h"
#include "RUI_MOTOR.h"

uint8_t One_flag_3 = 0;

void One_exchange_task(struct DBUS_Typedef* RUI_V_DBUS_V , struct CONTAL_Typedef *RUI_V_CONTAL_V)
{
	if((RUI_V_DBUS_V->KeyBoard.V_PreeNumber == 1)&&(RUI_V_DBUS_V->KeyBoard.B_PreeNumber == 1))
	{	
		if((RUI_V_CONTAL_V->HEAD.CUP_PUMP == 1)&&(One_flag_3 == 0))
		{
			RUI_V_CONTAL_V->HEAD.LIFT = 535776;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 26000;
			RUI_V_CONTAL_V->HEAD.SWAY = -30000;
			RUI_V_CONTAL_V->HEAD.Camera = -608000;
			RUI_V_CONTAL_V->HEAD.Yaw = 5357-6854;
			RUI_V_CONTAL_V->TUCHUAN.pitch = 550;
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			
			RUI_V_DBUS_V->KeyBoard.V_PreeNumber = 0;
			One_flag_3 = 6;
		}
		
		if(One_flag_3 == 0)
		{	//三轴延展目标
			RUI_V_CONTAL_V->HEAD.LIFT = 535776;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 426000;
			RUI_V_CONTAL_V->HEAD.SWAY = -30000;
			RUI_V_CONTAL_V->HEAD.Camera = -608000;
			RUI_V_CONTAL_V->TUCHUAN.pitch = 800;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite >= 528000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite <= -528000)&&
			(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 418000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -418000)&&
			(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite >= 22000))
			{	//三轴延展到位
				One_flag_3 = 1;
			}
		}
		
		if(One_flag_3 == 1)
		{	//2R目标
			RUI_V_CONTAL_V->HEAD.Yaw = 9515-6854;
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 9465)&&(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 9565))
			{	//P轴到位
				One_flag_3 = 2;
			}
		}
		
		if(One_flag_3 == 2)//吸盘吸到矿7
		{
			RUI_V_CONTAL_V->HEAD.Pitch = 608570;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 52000;
			
			if((R_Angle > 595000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 56000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -56000))
			{
				One_flag_3 = 3;
			}
		}
		
		if((One_flag_3 == 3)&&(RUI_V_DBUS_V->KeyBoard.C == 1))
		{
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 450000;
			RUI_V_CONTAL_V->HEAD.Pitch = 0;
			
			if((RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 440000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -440000)&&
				(R_Angle < 10000))
			{
				One_flag_3 = 4;
				RUI_V_CONTAL_V->ORE--;
			}
		}
		
		if(One_flag_3 == 4)
		{
			RUI_V_CONTAL_V->HEAD.Yaw = 5357-6854;
			RUI_V_CONTAL_V->TUCHUAN.pitch = 550;
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 5307)&&(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 5407))
			{	//Y轴到位
				One_flag_3 = 5;
				
			}
		}
		
		if(One_flag_3 == 5)
		{
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 26000;
		
			if((R_Angle > 255000)&&(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 57000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -57000))
			{	//Y轴到位
				One_flag_3 = 6;
				RUI_V_DBUS_V->KeyBoard.V_PreeNumber = 0;
			}
		}
	}
	
}
