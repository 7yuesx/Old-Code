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
    return RUI_DF_ERROR;
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
   
    /******************************底盘********************************/
    if (RUI_ROOT.MASTER_LOCATION == RUI_DF_MASTER_LOCATION_JUDGEING || RUI_ROOT.MASTER_LOCATION == RUI_DF_MASTER_LOCATION_BOTTOM)
    {
        RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_1    = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_3508_1);
        RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_2    = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_3508_2);
        RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_3    = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_3508_3);
        RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_4    = RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_3508_4);
		
		RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_1	= RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_2006_1);
		RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_2	= RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_2006_2);
		RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_3	= RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_2006_3);
		RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_4	= RUI_F_MOTOR_STATUS(&RUI_V_MOTOR_BOTTOM_2006_4);
    }
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
	RUI_ROOT.MASTER_LOCATION = RUI_DF_MASTER_LOCATION_BOTTOM;
	return RUI_DF_READY;        
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

        case RUI_DF_MASTER_LOCATION_BOTTOM:
            {
                if (RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_1 ==  RUI_DF_OFFLINE ||
                    RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_2 ==  RUI_DF_OFFLINE ||
                    RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_3 ==  RUI_DF_OFFLINE ||
                    RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_4 ==  RUI_DF_OFFLINE ||
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_1 ==  RUI_DF_OFFLINE ||
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_2 ==  RUI_DF_OFFLINE ||
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_3 ==  RUI_DF_OFFLINE ||
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_4 ==  RUI_DF_OFFLINE 
                  )
                {
                    RUI_F_LED(RUI_DF_LED_CYAN , 50);
                }
                if (RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_1 ==  RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_2 ==  RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_3 ==  RUI_DF_ONLINE &&
                    RUI_ROOT.STATUS.MOTOR_CHASSIS_3508_4 ==  RUI_DF_ONLINE &&
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_1 ==  RUI_DF_ONLINE &&
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_2 ==  RUI_DF_ONLINE &&
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_3 ==  RUI_DF_ONLINE &&
					RUI_ROOT.STATUS.MOTOR_CHASSIS_2006_4 ==  RUI_DF_ONLINE
                  )
                {
                    //2023-05-07 17:02改为闪烁方便观察是不是程序跑死了
                    RUI_F_LED(RUI_DF_LED_GREEN , 400);
                }

            }
            break;
    }
}
