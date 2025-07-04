#include "kernel.h"
#include "RUI_DBUS.h"
#include "RUI_ROOT_INIT.h"
#include "exchange_task.h"
#include "Goid_ore_task.h"
#include "Reset_task.h"
#include "Silver_ore_task.h"

float temp_hand = 0;
float temp_a = 0;

void kernel_run(struct DBUS_Typedef* RUI_V_DBUS_V , struct CONTAL_Typedef *RUI_V_CONTAL_V)
{
	//底盘基础速度
	static uint16_t RUI_V_BOTTOM_SPEED_X = 1230;
	static uint16_t RUI_V_BOTTOM_SPEED_Y = 830;
	static uint8_t  RUI_V_BOTTOM_SPEED_W = 120;//需要减小
	//底盘键鼠
	int8_t RUI_V_BOTTOM_VX = RUI_V_DBUS_V->KeyBoard.W  - RUI_V_DBUS_V->KeyBoard.S;
	int8_t RUI_V_BOTTOM_VY = RUI_V_DBUS_V->KeyBoard.D  - RUI_V_DBUS_V->KeyBoard.A;
	int16_t RUI_V_BOTTOM_VW = RUI_V_DBUS_V->Mouse.X_Flt;
	
	//转矿基础速度
	static uint16_t RUI_V_BOTTOM_SPEED_R   = 50;//待修改
	static uint16_t RUI_V_BOTTOM_SPEED_Z   = 50;//待修改
	//转矿键鼠
	int8_t RUI_V_BOTTOM_VR = RUI_V_DBUS_V->KeyBoard.Q - RUI_V_DBUS_V->KeyBoard.E;
	int8_t RUI_V_BOTTOM_VZ = RUI_V_DBUS_V->KeyBoard.Z - RUI_V_DBUS_V->KeyBoard.X;
	
	//云台基础速度
	static uint16_t RUI_V_HEAD_SPEED_LIFT   = 200;//待修改
	static uint16_t RUI_V_HEAD_SPEED_HORI   = 260;//待修改
	static uint16_t RUI_V_HEAD_SPEED_HORI_One   = 600;//待修改
	static uint16_t RUI_V_HEAD_SPEED_SWAY   = 260;//待修改
	//云台键鼠
	int8_t RUI_V_HEAD_LIFT = RUI_V_DBUS_V->KeyBoard.Q  - RUI_V_DBUS_V->KeyBoard.E;
	int8_t RUI_V_HEAD_HORI = RUI_V_DBUS_V->KeyBoard.W  - RUI_V_DBUS_V->KeyBoard.S;
	int8_t RUI_V_HEAD_SWAY = RUI_V_DBUS_V->KeyBoard.D  - RUI_V_DBUS_V->KeyBoard.A;
	
	//机械臂基础速度
	static uint16_t RUI_V_HEAD_SPEED_P   = 300;//待修改
	static uint16_t RUI_V_HEAD_SPEED_R   = 300;//待修改
	static float RUI_V_HEAD_SPEED_Y   = 1.1f;//待修改+
	//机械臂键鼠
	int8_t RUI_V_HEAD_P = RUI_V_DBUS_V->Mouse.Z_Flt;
	int8_t RUI_V_HEAD_R = RUI_V_DBUS_V->KeyBoard.Z - RUI_V_DBUS_V->KeyBoard.X;
	int8_t RUI_V_HEAD_Y = RUI_V_DBUS_V->Mouse.X_Flt;
	
	static uint16_t RUI_V_HEAD_SPEED_C	  = 500;
	int8_t Camera = RUI_V_DBUS_V->Mouse.Z_Flt;

	if(RUI_V_DBUS_V->KeyBoard.B_PreeNumber)
	{
		RUI_V_CONTAL_V->TUCHUAN.yaw = 800;
		RUI_V_CONTAL_V->MOD = 1;
	}
	else
	{
		RUI_V_CONTAL_V->TUCHUAN.yaw = 1550;
		RUI_V_CONTAL_V->MOD = 0;
		if(One_flag_2 > 0)
		{
			RUI_V_CONTAL_V->TUCHUAN.yaw = 1300;
		}
	}
	
	if((One_flag_1 > 0)||(One_flag_2 > 0)||(One_flag_3 > 0)||(One_flag_4 > 0))
	{
		RUI_V_BOTTOM_SPEED_X = 830;
		RUI_V_BOTTOM_SPEED_Y = 100;
		RUI_V_BOTTOM_SPEED_W = 50;
	}
	else
	{
		RUI_V_BOTTOM_SPEED_X = 3030;
		RUI_V_BOTTOM_SPEED_Y = 830;
		RUI_V_BOTTOM_SPEED_W = 200;
	}

    if(RUI_V_DBUS_V->KeyBoard.Ctrl == 0)//底盘、转矿
	{
		if(RUI_V_DBUS_V->KeyBoard.Shift == 1)
		{
			
		}
		else
		{
			RUI_V_CONTAL_V->BOTTOM.VX = RUI_V_BOTTOM_SPEED_X * RUI_V_BOTTOM_VX;
			RUI_V_CONTAL_V->BOTTOM.VY = RUI_V_BOTTOM_SPEED_Y * RUI_V_BOTTOM_VY;
			RUI_V_CONTAL_V->BOTTOM.VW = RUI_V_BOTTOM_SPEED_W * RUI_V_BOTTOM_VW;
			
			RUI_V_CONTAL_V->BOTTOM.VR = RUI_V_BOTTOM_SPEED_R * RUI_V_BOTTOM_VR;
			RUI_V_CONTAL_V->BOTTOM.VZ = RUI_V_BOTTOM_SPEED_Z * RUI_V_BOTTOM_VZ;
		}
	}
	
	if((RUI_V_DBUS_V->KeyBoard.Ctrl == 1)&&(RUI_V_DBUS_V->KeyBoard.Shift == 1))
	{
		One_Reset_task(RUI_V_DBUS_V , RUI_V_CONTAL_V);
		One_Back_task(RUI_V_DBUS_V , RUI_V_CONTAL_V);
	}
	
	if(RUI_V_DBUS_V->KeyBoard.Ctrl == 1)//云台、机械臂
	{
		if(RUI_V_DBUS_V->KeyBoard.Shift == 1)
		{
			
		}
		else
		{
			RUI_V_CONTAL_V->HEAD.LIFT += RUI_V_HEAD_SPEED_LIFT * RUI_V_HEAD_LIFT;
			RUI_V_CONTAL_V->HEAD.HORIZONTAL += RUI_V_HEAD_SPEED_HORI * RUI_V_HEAD_HORI;
			if(One_flag_2 == 2)
			{
				RUI_V_CONTAL_V->HEAD.HORIZONTAL += RUI_V_HEAD_SPEED_HORI_One * RUI_V_HEAD_HORI;//抢金矿
			}
			RUI_V_CONTAL_V->HEAD.SWAY += RUI_V_HEAD_SPEED_SWAY * RUI_V_HEAD_SWAY;
			RUI_V_CONTAL_V->HEAD.Pitch += RUI_V_HEAD_SPEED_P * RUI_V_HEAD_P;
			RUI_V_CONTAL_V->HEAD.Roll += RUI_V_HEAD_SPEED_R * RUI_V_HEAD_R;
			RUI_V_CONTAL_V->HEAD.Yaw -= RUI_V_HEAD_SPEED_Y * RUI_V_HEAD_Y;
		}
		
		//互锁
		RUI_V_CONTAL_V->BOTTOM.VX = 0;
		RUI_V_CONTAL_V->BOTTOM.VY = 0;
		RUI_V_CONTAL_V->BOTTOM.VW = 0;
		RUI_V_CONTAL_V->BOTTOM.VR = 0;
		RUI_V_CONTAL_V->BOTTOM.VZ = 0;

	}
	
	if((RUI_ROOT.STATUS.User_Crotral == RUI_DF_ONLINE)&&(receive.channels.cmd_id = 0x0302))//自定义控制器
	{
		RUI_V_CONTAL_V->User.Yaw = 0;//receive.channels.User_data.Yaw;
		RUI_V_CONTAL_V->User.Pitch = 0;//receive.channels.User_data.Roll;
		RUI_V_CONTAL_V->User.Roll = 0;//receive.channels.User_data.Pitch;
		temp_a = receive.channels.User_data.Z_length - temp_hand;
		
		RUI_V_CONTAL_V->User.HORIZONTAL += (-temp_a)*100;
		RUI_V_CONTAL_V->User.SWAY += 0;//receive.channels.User_data.Y_length;
		RUI_V_CONTAL_V->User.LIFT =0; //receive.channels.User_data.Z_length;
		
		temp_hand = receive.channels.User_data.Z_length;
		
		if(receive.channels.User_data.CUP == 1)
		{
			RUI_V_DBUS_V->Mouse.R_PressTime = 0;
		}
	}
	if(RUI_ROOT.STATUS.User_Crotral == RUI_DF_OFFLINE)
	{
		receive.channels.User_data.Pitch = 0;
		receive.channels.User_data.Roll = 0;
		receive.channels.User_data.Yaw = 0;
		receive.channels.User_data.Y_length = 0;
		receive.channels.User_data.Z_length = 0;
		
		RUI_V_CONTAL_V->User.Yaw = receive.channels.User_data.Yaw;
		RUI_V_CONTAL_V->User.Pitch = -receive.channels.User_data.Pitch;
		RUI_V_CONTAL_V->User.Roll = receive.channels.User_data.Roll;
		RUI_V_CONTAL_V->User.HORIZONTAL += receive.channels.User_data.Z_length;
		RUI_V_CONTAL_V->User.SWAY += receive.channels.User_data.Y_length;
	}
	
	if(RUI_V_DBUS_V->KeyBoard.Shift == 1)//一键
	{
		if(RUI_V_DBUS_V->KeyBoard.Ctrl == 1)
		{
			
		}
		else
		{
			One_exchange_task(RUI_V_DBUS_V , RUI_V_CONTAL_V);
			One_Goid_ore_task(RUI_V_DBUS_V , RUI_V_CONTAL_V);
			One_Goid_ore_task_Other(RUI_V_DBUS_V , RUI_V_CONTAL_V);
			One_Silver_ore_task(RUI_V_DBUS_V , RUI_V_CONTAL_V);
		}
	}
	
	
	//气泵
	RUI_V_CONTAL_V->HEAD.CUP_PUMP = RUI_V_DBUS_V->Mouse.R_PressTime;
	
	//图传
	if(RUI_V_DBUS_V->Mouse.L_State)
	{
		RUI_V_CONTAL_V->HEAD.Camera  += Camera*RUI_V_HEAD_SPEED_C;
	}
	
	
}



