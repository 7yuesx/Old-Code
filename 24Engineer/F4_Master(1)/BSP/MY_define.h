#ifndef __MY_DEFINE
#define __MY_DEFINE

//INIT成功
#define RUI_DF_READY 1
//INIT错误
#define RUI_DF_ERROR 0

#define RUI_DF_NOW  1
#define RUI_DF_LAST 0

//PID双环
#define RUI_DF_PID_DOUBLE 1
//PID单环
#define RUI_DF_PID_SINGLE 0
//正在判断主控位置
#define RUI_DF_MASTER_LOCATION_JUDGEING 0
//主控位置判断完成，在头部
#define RUI_DF_MASTER_LOCATION_HEAD 1
//主控位置判断完成，在底盘
#define RUI_DF_MASTER_LOCATION_BOTTOM 2

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	//LED
 *	@parameter:		//
 *	@time:				//23-04-13 15:57
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
#define RUI_DF_LED_RED    0
#define RUI_DF_LED_GREEN  1
#define RUI_DF_LED_BLUE   2
#define RUI_DF_LED_YELLOW 3
#define RUI_DF_LED_PURPLE 4
#define RUI_DF_LED_CYAN   5

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	//遥控拨杆上中下的值
 *	@parameter:		//
 *	@time:				//23-05-10 18:16
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
#define RUI_DF_DBUS_R_UP     1
#define RUI_DF_DBUS_R_MIDDLE 3
#define RUI_DF_DBUS_R_DOWN   2

#define RUI_DF_DBUS_L_UP     1
#define RUI_DF_DBUS_L_MIDDLE 3
#define RUI_DF_DBUS_L_DOWN   2

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //离线检测宏定义
 *	@parameter:		    //
 *	@time:				//23-03-28 20:13
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
//设备离线
#define RUI_DF_OFFLINE 0
//设备在线
#define RUI_DF_ONLINE  1 
//遥控器离线检测时间
#define RUI_DF_DBUS_OFFLINE_TIME 30  
//电机离线检测时间
#define RUI_DF_MOTOR_OFFLINE_TIME 15
//自定义控制器离线检测时间
#define RUI_DF_Crotral_OFFLINE_TIME 60
/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //抬升、前伸电机ID宏定义
 *	@parameter:		    //
 *	@time:				//23-04-14 15:55
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
//主机CAN1
//前伸
#define RUI_DF_MOTOR_HEAD_3508_1_ID 0x201
#define RUI_DF_MOTOR_HEAD_3508_2_ID 0x202
//抬升
#define RUI_DF_MOTOR_HEAD_3508_3_ID 0x203
#define RUI_DF_MOTOR_HEAD_3508_4_ID 0x204

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //横移、达妙电机、机械臂、从机ID宏定义
 *	@parameter:		    //
 *	@time:				//23-04-14 15:55
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
//主机CAN2
//横移
#define RUI_DF_MOTOR_HEAD_3508_5_ID 0x205
//差动
#define RUI_DF_MOTOR_HEAD_2006_L_ID 0x206
#define RUI_DF_MOTOR_HEAD_2006_R_ID 0x207
//Yaw轴
#define RUI_DF_MOTOR_HEAD_6020_YAW_ID 0x208

#define RUI_DF_MOTOR_HEAD_2006_Camera_ID 0x201

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //电机堵转相关宏定义
 *	@parameter:		    //
 *	@time:				//23-04-14 15:55
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
//前伸（待修改）
#define RUI_DF_MOTOR_HEAD_HORIZONTAL_STUCK_ANGLE 200
#define RUI_DF_MOTOR_HEAD_HORIZONTAL_STUCK_SPEED 20
#define RUI_DF_MOTOR_HEAD_HORIZONTAL_STUCK_TIME  1000
//升降（待修改）
#define RUI_DF_MOTOR_HEAD_LIFT_STUCK_ANGLE       700
#define RUI_DF_MOTOR_HEAD_LIFT_STUCK_SPEED       20
#define RUI_DF_MOTOR_HEAD_LIFT_STUCK_TIME        500
//横移（待修改）
#define RUI_DF_MOTOR_HEAD_SWAY_STUCK_ANGLE       700
#define RUI_DF_MOTOR_HEAD_SWAY_STUCK_SPEED       20
#define RUI_DF_MOTOR_HEAD_SWAY_STUCK_TIME        500

/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //电机PID参数宏定义
 *	@parameter:		    //
 *	@time:				//23-03-29 18:18
 *	@ReadMe:			//
 *************************************************************万能分隔符**************************************************************/
//头部前馈C矩阵参数
#define WHW_DF_FFC_DATA_HEAD_LIFT_L			{	0,	0,	0	}
#define WHW_DF_FFC_DATA_HEAD_LIFT_R			{	0,	0,	0	}
#define WHW_DF_FFC_DATA_HEAD_HORIZONTAL_L	{	0,	0,	0	}
#define WHW_DF_FFC_DATA_HEAD_HORIZONTAL_R	{	0,	0,	0	}
#define WHW_DF_FFC_DATA_HEAD_SWAY			{	0,	0,	0	}
#define WHW_DF_FFC_DATA_HEAD_Yaw			{	0,	0,	0	}

//头部双环PID参数                               	  P       I       D   maxI    maxOut
//头部前伸PID参数（待修改）
#define RUI_DF_PID_DATA_HEAD_HORIZONTAL_S  {    10,  0.0f, 0, 0,   9000           }
#define RUI_DF_PID_DATA_HEAD_HORIZONTAL_P  {   0.25, 0.0f, 0, 0,   5500           }
//头部升降PID参数（待修改）
#define RUI_DF_PID_DATA_HEAD_LIFT_S        {    5.5 , 0.32f, 0, 3000, 16000         }
#define RUI_DF_PID_DATA_HEAD_LIFT_P        {   0.15, 0.01f, 0, 80, 5500           }
//头部横移PID参数（待修改）
#define RUI_DF_PID_DATA_HEAD_SWAY_S        {    11, 0.005f, 0, 3000, 16000         }
#define RUI_DF_PID_DATA_HEAD_SWAY_P        {   0.065, 0.0f, 0, 80, 8500           }
//头部Yaw轴PID参数（待修改）
#define RUI_DF_PID_DATA_HEAD_Yaw_S        {    350 , 0.002f, 0, 4500, 20000         }
#define RUI_DF_PID_DATA_HEAD_Yaw_P        {   0.7f, 0.0f, 0.0003, 15, 45           }

//差动关节PID参数（待修改）
//角度
#define RUI_DF_PID_DATA_HEAD_2006_Pitch  	{     0.1,     0.0f,   0.0f,   0,   4000   }
#define RUI_DF_PID_DATA_HEAD_2006_Roll   	{     0.1,     0.0f,   0.0f,   0,   4000   }
//速度
#define RUI_DF_PID_DATA_HEAD_2006_Right     {	  1.5,   0.0f,   0,      0,   16400  }
#define RUI_DF_PID_DATA_HEAD_2006_Left      {	  1.5,   0.0f,   0,      0,   16400  }

#define RUI_DF_PID_DATA_HEAD_2006_Camera_S	{	  1.5,   0.0f,   0,      0,   16400  }
#define RUI_DF_PID_DATA_HEAD_2006_Camera_P	{     0.1,     0.0f,   0.0f,   0,   4000 }

/************************************************************万能分隔符**************************************************************
 * 	@author:			//王涵炜
 *	@performance:	    //绝对刻度宏定义
 *	@parameter:		    //
 *	@time:				//23-03-29 18:18
 *	@ReadMe:			//
 *************************************************************万能分隔符**************************************************************/
//Yaw轴位置
#define WHW_DF_Yaw_RESET 6854
#define WHW_DF_Yaw_back 7509

//舵机角度
#define WHW_DF_MG995_Pitch_up 750
#define WHW_DF_MG995_Yaw_up 1550

#endif
