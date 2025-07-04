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
#include "RUI_ROOT_INIT.h"
#include "MY_define.h"
#include "RUI_DBUS.h"
#include "usart.h"

struct RUI_ROOT_Typedef RUI_ROOT ={ 0 };
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //ROOT函数
 *	@parameter:		    //
 *	@time:				//23-04-13 17:38
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_ROOT(void)
{
    RUI_F_ROOT_ALL_STATUS();
    RUI_F_MASTER_LOCATION_JUDGE();
    RUI_F_LED_SHOW_STATUS();
	RUI_F_MASTER_COMMUNICATION();
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //电机离线检测
 *	@parameter:		    //
 *	@time:				//23-04-13 15:01
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_MOTOR_STATUS(struct RUI_MOTOR_Typedef* MOTOR)
{
    MOTOR->DATA.ONLINE_JUDGE_TIME--;

    if (MOTOR->DATA.ONLINE_JUDGE_TIME < 5)
    {
        MOTOR->DATA.ONLINE_JUDGE_TIME = 0;
        return RUI_DF_OFFLINE;
    }
    else
    {
        return RUI_DF_ONLINE;
    }
}


/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //总的离线检测
 *	@parameter:		    //
 *	@time:				//23-03-29 19:34
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-04-13 15:22    bestrui
 *  @UpData：           //电机检测封装成函数
 ************************************************************万能分隔符**************************************************************/
void RUI_F_ROOT_ALL_STATUS(void)
{
	//遥控在线监测
	if (RUI_V_DBUS_ONLINE_JUDGE_TIME < 5)
	{
		RUI_V_DBUS_ONLINE_JUDGE_TIME = 3;
		RUI_ROOT.STATUS.RM_DBUS = RUI_DF_OFFLINE;
	}
	else
	{
		RUI_ROOT.STATUS.RM_DBUS = RUI_DF_ONLINE;
	}
	RUI_V_DBUS_ONLINE_JUDGE_TIME--;
	
	//自定义控制器在线监测
	if (RUI_V_Crotral_ONLINE_JUDGE_TIME < 5)
	{
		RUI_V_Crotral_ONLINE_JUDGE_TIME = 3;
		RUI_ROOT.STATUS.User_Crotral = RUI_DF_OFFLINE;
	}
	else
	{
		RUI_ROOT.STATUS.User_Crotral = RUI_DF_ONLINE;
	}
	RUI_V_Crotral_ONLINE_JUDGE_TIME--;

	//电机在线检测
	RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_L = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_HORIZONTAL_L);
	RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_R = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_HORIZONTAL_R);
	RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_L       = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_LIFT_L);
	RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_R       = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_LIFT_R);
	RUI_ROOT.STATUS.MOTOR_HEAD_SWAY         = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_SWAY);
	RUI_ROOT.STATUS.MOTOR_HEAD_Yaw          = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_Yaw);
    RUI_ROOT.STATUS.MOTOR_HEAD_Left         = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_Left);
    RUI_ROOT.STATUS.MOTOR_HEAD_Right        = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_Right);
	RUI_ROOT.STATUS.MOTER_HEAD_Camera		= RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_Camera);
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //主控位置判断
 *	@parameter:		    //
 *	@time:				//23-03-29 19:34
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_MASTER_LOCATION_JUDGE(void)
{
	RUI_ROOT.MASTER_LOCATION = RUI_DF_MASTER_LOCATION_HEAD;
	return RUI_DF_READY;        
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //主控之间通信
 *	@parameter:		    //
 *	@time:				//23-03-30 12:34
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
union COMMUNICATION_UNION_Typdef  RUI_V_COMMUNICATION ={ 0 };
uint8_t RUI_F_MASTER_COMMUNICATION(void)
{
	switch (RUI_ROOT.MASTER_LOCATION)
    {
        case RUI_DF_MASTER_LOCATION_JUDGEING:
		{
			return RUI_DF_ERROR;
		};
       
        case RUI_DF_MASTER_LOCATION_HEAD:
		{
			if(RUI_V_CONTAL.MOD == 1)
			{
				RUI_V_COMMUNICATION.DataNeaten.VX  = RUI_V_CONTAL.BOTTOM.VX;
				RUI_V_COMMUNICATION.DataNeaten.VY  = RUI_V_CONTAL.BOTTOM.VY;
				
			}
			if(RUI_V_CONTAL.MOD == 0)
			{
				RUI_V_COMMUNICATION.DataNeaten.VX  = RUI_V_CONTAL.BOTTOM.VY;
				RUI_V_COMMUNICATION.DataNeaten.VY  = -RUI_V_CONTAL.BOTTOM.VX;
			}
			RUI_V_COMMUNICATION.DataNeaten.VW  = RUI_V_CONTAL.BOTTOM.VW;
			RUI_V_COMMUNICATION.DataNeaten.VZ  = RUI_V_CONTAL.BOTTOM.VZ;
			RUI_V_COMMUNICATION.DataNeaten.VR  = RUI_V_CONTAL.BOTTOM.VR;
			RUI_V_COMMUNICATION.DataNeaten.DBUS_STATUS = RUI_ROOT.STATUS.RM_DBUS;
		}break;
        default:	return RUI_DF_ERROR;
    }
    return RUI_DF_ERROR;
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //LED
 *	@parameter:		    //
 *	@time:				//23-04-13 16:05
 *	@ReadMe:			//颜色参考RUI_DEFINE.h文件中的颜色 TIME小于10时视觉效果为长亮
 ************************************************************万能分隔符**************************************************************/
void RUI_F_LED(uint8_t COLOR , int TIME)
{
    uint32_t TIME_NOW = HAL_GetTick();

    static uint32_t TIME_LAST = 0;

    static int8_t BIT = 0 , status_LAST = 9;

    static GPIO_TypeDef* LED_PORT[3] ={ LED_R_GPIO_Port, LED_G_GPIO_Port, LED_B_GPIO_Port };

    static uint16_t LED_PIN[3] ={ LED_R_Pin, LED_G_Pin, LED_B_Pin };

    static uint8_t LED_CONFIG[6][3] ={
        {1, 0, 0},    // RED
        {0, 1, 0},    // GREEN
        {0, 0, 1},    // BLUE
        {1, 1, 0},    // YELLOW
        {1, 0, 1},    // PURPLE
        {0, 1, 1},    // CYAN
    };

    if (COLOR != status_LAST)
    {
        for (int i = 0; i < 3; i++)
        {
            HAL_GPIO_WritePin(LED_PORT[i] , LED_PIN[i] , GPIO_PIN_SET);
        }
        status_LAST = COLOR;
    }



    if ((TIME_NOW - TIME_LAST) > TIME)
    {
        BIT = !BIT;
        TIME_LAST = TIME_NOW;
    }

    for (int i = 0; i < 3; i++)
    {
        if (LED_CONFIG[COLOR][i])
        {
            HAL_GPIO_WritePin(LED_PORT[i] , LED_PIN[i] , BIT);
        }
    }
}

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //用LED灯显示状态
 *	@parameter:		    //
 *	@time:				//23-04-13 17:36
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-05-07 17:03    bestrui
 *  @UpData：           //底盘正常改为绿灯闪烁
 ************************************************************万能分隔符**************************************************************/
void RUI_F_LED_SHOW_STATUS(void)
{
    switch (RUI_ROOT.MASTER_LOCATION)
    {
		case RUI_DF_MASTER_LOCATION_JUDGEING:
            RUI_F_LED(RUI_DF_LED_YELLOW , 100);
            break;


        case RUI_DF_MASTER_LOCATION_HEAD:
            {
                if (RUI_ROOT.STATUS.RM_DBUS                 == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_L == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_L       == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_R == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_R       == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_SWAY         == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_Yaw          == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_Left         == RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_HEAD_Right        == RUI_DF_ONLINE && 
					RUI_ROOT.STATUS.MOTER_HEAD_Camera		== RUI_DF_ONLINE
                   )
                {
                    RUI_F_LED(RUI_DF_LED_CYAN , 200);
                }
                if (RUI_ROOT.STATUS.RM_DBUS                  == RUI_DF_OFFLINE &&
                    (RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_L == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_L       == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_R == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_R       == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_SWAY         == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_Yaw          == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_Left         == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_Right        == RUI_DF_OFFLINE ||
					 RUI_ROOT.STATUS.MOTER_HEAD_Camera		 == RUI_DF_OFFLINE)
                  )
                {
                    RUI_F_LED(RUI_DF_LED_PURPLE , 50);
                }
                if (RUI_ROOT.STATUS.RM_DBUS                  == RUI_DF_ONLINE &&
                    (RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_L == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_L       == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_HORIZONTAL_R == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_LIFT_R       == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_SWAY         == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_Yaw          == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_Left         == RUI_DF_OFFLINE ||
                     RUI_ROOT.STATUS.MOTOR_HEAD_Right        == RUI_DF_OFFLINE ||
					 RUI_ROOT.STATUS.MOTER_HEAD_Camera		 == RUI_DF_OFFLINE) 
                  )
                {
                    RUI_F_LED(RUI_DF_LED_CYAN , 50);
                }
            }
            break;
        
    }
}
