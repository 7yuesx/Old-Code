#include "Goid_ore_task.h"
#include "RUI_MOTOR.h"

uint8_t One_flag_2 = 0;
uint8_t One_flag_4 = 0;

void One_Goid_ore_task(struct DBUS_Typedef* RUI_V_DBUS_V , struct CONTAL_Typedef *RUI_V_CONTAL_V)
{
	if((RUI_V_DBUS_V->KeyBoard.F_PreeNumber == 1)&&(RUI_V_DBUS_V->KeyBoard.B_PreeNumber == 0))
	{
		if(One_flag_2 == 0)
		{	//三轴延展目标
			RUI_V_CONTAL_V->HEAD.LIFT = 0;
			RUI_V_CONTAL_V->HEAD.SWAY = 150000;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 80000;
			RUI_V_CONTAL_V->HEAD.Camera = -508000;
			
			if((RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 145000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -145000)&&
			(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite >= 75000))
			{	//三轴延展到位
				One_flag_2 = 1;
			}
		}
		
		if(One_flag_2 == 1)
		{	//2R目标
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			RUI_V_CONTAL_V->HEAD.Roll = 300000;
			RUI_V_CONTAL_V->HEAD.Yaw = 7509-6854;
			RUI_V_CONTAL_V->TUCHUAN.pitch = 800;
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 7459)&&(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 7559)&&
				(R_Angle > 245000)&&(P_Angle < -280000))
			{	//P轴到位
				One_flag_2 = 2;
			}
		}
		
		if((One_flag_2 == 2)&&(RUI_V_DBUS_V->KeyBoard.C == 1)&&(RUI_V_CONTAL_V->ORE != 2))//吸盘吸到矿
		{	//抬升目标
			RUI_V_CONTAL_V->HEAD.LIFT = 485000;
			RUI_V_CONTAL_V->HEAD.SWAY = 500000;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite >= 476000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite <= -476000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 495000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -49500))
			{	//抬升就位
				One_flag_2 = 3;
			}
		}
		
		if(One_flag_2 == 3)//吸盘吸到矿
		{	//P轴目标,横移目标
			RUI_V_CONTAL_V->HEAD.Pitch = 0;
			RUI_V_CONTAL_V->HEAD.Yaw = 9515-6854;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 25000;
			
			if((R_Angle < 10000)&&
				(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 9465)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 30000))
			{	//P轴到位,横移到位
				One_flag_2 = 4;
			}
		}
		
		if(One_flag_2 == 4)//吸盘吸到矿7
		{	//Y轴目标
			RUI_V_CONTAL_V->HEAD.LIFT = 330000;	
			RUI_V_CONTAL_V->HEAD.SWAY= 420000;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite <= 340000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite >= -340000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 428000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -428000))
			{	//Y轴到位
				One_flag_2 = 5;
			}
		}
		
		if(One_flag_2 == 5)//吸盘吸到矿
		{	//P轴目标
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			//图传视野改变
			
			if(R_Angle > 255000)
			{	//P轴到位
				One_flag_2 = 6;
			}
		}
		
		if((One_flag_2 == 6)&&(RUI_V_DBUS_V->KeyBoard.R == 1))//收完矿，复位
		{
			//三轴延展目标
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 0;
			
			if(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 12000)
			{	//三轴延展到位
				One_flag_2 = 7;
				RUI_V_CONTAL_V->ORE++;
			}
		}
		
		if(One_flag_2 == 7)
		{	//2R
			RUI_V_CONTAL_V->HEAD.Pitch = 0;
			RUI_V_CONTAL_V->HEAD.Yaw = 7509-6854;
			RUI_V_CONTAL_V->HEAD.Roll = 0;
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 7559)&&
				(R_Angle < 10000)&&(P_Angle > -10000))
			{	//2R到位
				One_flag_2 = 8;
			}
		}
		
		if(One_flag_2 == 8)
		{
			RUI_V_CONTAL_V->HEAD.LIFT = 0;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 0;
			RUI_V_CONTAL_V->HEAD.SWAY = 0;
			RUI_V_CONTAL_V->TUCHUAN.pitch = 550;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite <= 10000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite >= -10000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 10000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -10000)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 10000))
			{	//三轴延展到位
				One_flag_2 = 0;
				RUI_V_DBUS_V->KeyBoard.F_PreeNumber = 0;
			}
		}
	}
}

void One_Goid_ore_task_Other(struct DBUS_Typedef* RUI_V_DBUS_V , struct CONTAL_Typedef *RUI_V_CONTAL_V)
{
	if((RUI_V_DBUS_V->KeyBoard.F_PreeNumber == 1)&&(RUI_V_DBUS_V->KeyBoard.B_PreeNumber == 1))
	{
		if(One_flag_4 == 0)
		{	//三轴延展目标
			RUI_V_CONTAL_V->HEAD.LIFT = 0;
			RUI_V_CONTAL_V->HEAD.SWAY = -50618;
			RUI_V_CONTAL_V->HEAD.Camera = -508000;
			
			if((RUI_V_MOTOR_SWAY.DATA.Angle_Infinite >= 45000))
			{	//三轴延展到位
				One_flag_4 = 1;
			}
		}
		
		if(One_flag_4 == 1)
		{	//2R目标
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			RUI_V_CONTAL_V->HEAD.Roll = 300000;
			RUI_V_CONTAL_V->HEAD.Yaw = 5357-6854;
			RUI_V_CONTAL_V->TUCHUAN.pitch = 800;
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 5307)&&(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 5407)&&
				(R_Angle > 255000)&&(P_Angle < -280000))
			{	//P轴到位
				One_flag_4 = 2;
			}
		}
		
		if((One_flag_4 == 2)&&(RUI_V_DBUS_V->KeyBoard.C == 1)&&(RUI_V_CONTAL_V->ORE != 2))//吸盘吸到矿
		{	//抬升目标
				
			RUI_V_CONTAL_V->HEAD.Camera = -590000;
//			if()
			{	//抬升就位
				One_flag_4 = 3;
			}
		}
		
		if(One_flag_4 == 3)//吸盘吸到矿
		{	//P轴目标,横移目标
			RUI_V_CONTAL_V->HEAD.Pitch = 0;
			RUI_V_CONTAL_V->HEAD.LIFT = 456000;		
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 500000;
			RUI_V_CONTAL_V->HEAD.SWAY = -25000;
			
			if((R_Angle < 10000)&&
				(RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite >= 435000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite <= -435000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 495000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -495000)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 30000))	
			{	//P轴到位,横移到位
				One_flag_4 = 4;
			}
		}
		
		if(One_flag_4 == 4)//吸盘吸到矿7
		{	//Y轴目标
			RUI_V_CONTAL_V->HEAD.Yaw = 9515-6854;
			if(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 9465)
			{	//Y轴到位
				One_flag_4 = 5;
			}
		}
		
		if(One_flag_4 == 5)//吸盘吸到矿
		{	//P轴目标
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			RUI_V_CONTAL_V->HEAD.LIFT = 330000;	
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 420000;
			//图传视野改变
			RUI_V_CONTAL_V->TUCHUAN.pitch = 800;
			
			if((R_Angle > 255000)&&
				(RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite <= 340000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite >= -340000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 428000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -428000))
			{	//P轴到位
				One_flag_4 = 6;
			}
		}
		
		if((One_flag_4 == 6)&&(RUI_V_DBUS_V->KeyBoard.R == 1))//收完矿，复位
		{
			//三轴延展目标
			RUI_V_CONTAL_V->HEAD.LIFT = 460000;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 500000;
			RUI_V_CONTAL_V->HEAD.SWAY = 0;
			
			RUI_V_CONTAL_V->TUCHUAN.pitch = 550;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite >= 450000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite <= -450000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 490000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -490000)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 10000))
			{	//三轴延展到位
				One_flag_4 = 7;
				RUI_V_CONTAL_V->ORE++;
			}
		}
		
		if(One_flag_4 == 7)
		{	//2R
			RUI_V_CONTAL_V->HEAD.Pitch = 0;
			RUI_V_CONTAL_V->HEAD.Yaw = 7509-6854;
			RUI_V_CONTAL_V->HEAD.Roll = 0;			
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 7559)&&
				(R_Angle < 10000)&&(P_Angle > -10000))
			{	//2R到位
				One_flag_4 = 8;
			}
		}
		
		if(One_flag_4 == 8)
		{
			RUI_V_CONTAL_V->HEAD.LIFT = 0;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 0;
			RUI_V_CONTAL_V->HEAD.SWAY = 0;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite <= 10000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite >= -10000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 10000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -10000)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 10000))
			{	//三轴延展到位
				One_flag_4 = 0;
				RUI_V_DBUS_V->KeyBoard.F_PreeNumber = 0;
			}
		}
		
	}
}
void One_Goid_ore_task_Other2(struct DBUS_Typedef* RUI_V_DBUS_V , struct CONTAL_Typedef *RUI_V_CONTAL_V)
{
	if((RUI_V_DBUS_V->KeyBoard.F_PreeNumber == 1)&&(RUI_V_DBUS_V->KeyBoard.B_PreeNumber == 1))
	{
		if(One_flag_4 == 0)
		{	//三轴延展目标
			RUI_V_CONTAL_V->HEAD.LIFT = 0;
			RUI_V_CONTAL_V->HEAD.SWAY = -50618;
			RUI_V_CONTAL_V->HEAD.Camera = -508000;
			
			if((RUI_V_MOTOR_SWAY.DATA.Angle_Infinite >= 45000))
			{	//三轴延展到位
				One_flag_4 = 1;
			}
		}
		
		if(One_flag_4 == 1)
		{	//2R目标
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			RUI_V_CONTAL_V->HEAD.Roll = 300000;
			RUI_V_CONTAL_V->HEAD.Yaw = 5357-6854;
			RUI_V_CONTAL_V->TUCHUAN.pitch = 800;
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 5307)&&(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 5407)&&
				(R_Angle > 255000)&&(P_Angle < -280000))
			{	//P轴到位
				One_flag_4 = 2;
			}
		}
		
		if((One_flag_4 == 2)&&(RUI_V_DBUS_V->KeyBoard.C == 1)&&(RUI_V_CONTAL_V->ORE != 2))//吸盘吸到矿
		{	//抬升目标
				
			RUI_V_CONTAL_V->HEAD.Camera = -590000;
//			if()
			{	//抬升就位
				One_flag_4 = 3;
			}
		}
		
		if(One_flag_4 == 3)//吸盘吸到矿
		{	//P轴目标,横移目标
			RUI_V_CONTAL_V->HEAD.Pitch = 0;
			RUI_V_CONTAL_V->HEAD.LIFT = 456000;		
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 500000;
			RUI_V_CONTAL_V->HEAD.SWAY = -25000;
			
			if((R_Angle < 10000)&&
				(RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite >= 435000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite <= -435000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 495000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -495000)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 30000))	
			{	//P轴到位,横移到位
				One_flag_4 = 4;
			}
		}
		
		if(One_flag_4 == 4)//吸盘吸到矿7
		{	//Y轴目标
			RUI_V_CONTAL_V->HEAD.Yaw = 9515-6854;
			if(RUI_V_MOTOR_Yaw.DATA.Angle_Infinite >= 9465)
			{	//Y轴到位
				One_flag_4 = 5;
			}
		}
		
		if(One_flag_4 == 5)//吸盘吸到矿
		{	//P轴目标
			RUI_V_CONTAL_V->HEAD.Pitch = 265000;
			RUI_V_CONTAL_V->HEAD.LIFT = 330000;	
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 420000;
			//图传视野改变
			RUI_V_CONTAL_V->TUCHUAN.pitch = 800;
			
			if((R_Angle > 255000)&&
				(RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite <= 340000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite >= -340000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 428000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -428000))
			{	//P轴到位
				One_flag_4 = 6;
			}
		}
		
		if((One_flag_4 == 6)&&(RUI_V_DBUS_V->KeyBoard.R == 1))//收完矿，复位
		{
			//三轴延展目标
			RUI_V_CONTAL_V->HEAD.LIFT = 460000;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 500000;
			RUI_V_CONTAL_V->HEAD.SWAY = 0;
			
			RUI_V_CONTAL_V->TUCHUAN.pitch = 550;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite >= 450000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite <= -450000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite >= 490000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite <= -490000)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 10000))
			{	//三轴延展到位
				One_flag_4 = 7;
				RUI_V_CONTAL_V->ORE++;
			}
		}
		
		if(One_flag_4 == 7)
		{	//2R
			RUI_V_CONTAL_V->HEAD.Pitch = 0;
			RUI_V_CONTAL_V->HEAD.Yaw = 7509-6854;
			RUI_V_CONTAL_V->HEAD.Roll = 0;			
			
			if((RUI_V_MOTOR_Yaw.DATA.Angle_Infinite <= 7559)&&
				(R_Angle < 10000)&&(P_Angle > -10000))
			{	//2R到位
				One_flag_4 = 8;
			}
		}
		
		if(One_flag_4 == 8)
		{
			RUI_V_CONTAL_V->HEAD.LIFT = 0;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL = 0;
			RUI_V_CONTAL_V->HEAD.SWAY = 0;
			
			if((RUI_V_MOTOR_LIFT_R.DATA.Angle_Infinite <= 10000)&&(RUI_V_MOTOR_LIFT_L.DATA.Angle_Infinite >= -10000)&&
				(RUI_V_MOTOR_HORIZONTAL_L.DATA.Angle_Infinite <= 10000)&&(RUI_V_MOTOR_HORIZONTAL_R.DATA.Angle_Infinite >= -10000)&&
				(RUI_V_MOTOR_SWAY.DATA.Angle_Infinite <= 10000))
			{	//三轴延展到位
				One_flag_4 = 0;
				RUI_V_DBUS_V->KeyBoard.F_PreeNumber = 0;
			}
		}
		
	}
}

