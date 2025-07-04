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
#include "RUI_BOTTOM.h"
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //底部总控制函数
 *	@parameter:		    //
 *	@time:				//22-11-25 14:47
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_BOTTOM_CONTRAL(uint8_t DBUS_STATUS)
{

    static uint8_t INIT = RUI_DF_ERROR;
    if (INIT == RUI_DF_ERROR)
    {
        INIT = RUI_F_BOTTOM_INIT();
        return RUI_DF_ERROR;
    }
    if (INIT == RUI_DF_READY)
    {
        RUI_F_CHASSIS_CONTRAL(DBUS_STATUS);
    }

    RUI_F_CAN_SEDN(&hcan1 , 0x200 , RUI_V_MOTOR_BOTTOM_3508_1.PID_C.All_out + 	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_3508_1.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_3508_1.DATA.Aim_last),
	
									RUI_V_MOTOR_BOTTOM_3508_2.PID_C.All_out + 	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_3508_2.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_3508_2.DATA.Aim_last),
	
                                    RUI_V_MOTOR_BOTTOM_3508_3.PID_C.All_out + 	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_3508_3.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_3508_3.DATA.Aim_last),
	
                                    RUI_V_MOTOR_BOTTOM_3508_4.PID_C.All_out + 	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_3508_4.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_3508_4.DATA.Aim_last));
	
	RUI_F_CAN_SEDN(&hcan2 , 0x200 , RUI_V_MOTOR_BOTTOM_2006_1.PID_S.All_out +	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_2006_1.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_2006_1.DATA.Aim_last),
	
									RUI_V_MOTOR_BOTTOM_2006_2.PID_S.All_out +	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_2006_2.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_2006_2.DATA.Aim_last),
									
									RUI_V_MOTOR_BOTTOM_2006_3.PID_S.All_out +	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_2006_3.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_2006_3.DATA.Aim_last),
									
									RUI_V_MOTOR_BOTTOM_2006_4.PID_S.All_out +	//PID
					/*参数待修改*/	1*(RUI_V_MOTOR_BOTTOM_2006_4.DATA.Aim	-	//前馈
									RUI_V_MOTOR_BOTTOM_2006_4.DATA.Aim_last));

    return RUI_DF_READY;
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //底盘总控制函数
 *	@parameter:		    //
 *	@time:				//22-11-25 17:08
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint16_t RUI_V_CURRENT_MAX_1 = 0 , RUI_V_CURRENT_MAX_2 = 0 , RUI_V_CURRENT_MAX_3 = 0 , RUI_V_CURRENT_MAX_4 = 0;
uint8_t RUI_F_CHASSIS_CONTRAL(uint8_t DBUS_STATUS)
{
    static int16_t CHASSIS_VX = 0 , CHASSIS_VY = 0 , CHASSIS_VW = 0;
    static int8_t CHASSIS_VZ = 0 , CHASSIS_VR = 0;
    //2023-05-07 17:04移动速度减小了一点
    CHASSIS_VX = RUI_V_CONTAL.BOTTOM.VX;
    CHASSIS_VY = RUI_V_CONTAL.BOTTOM.VY;
    CHASSIS_VW = RUI_V_CONTAL.BOTTOM.VW;
	CHASSIS_VZ = RUI_V_CONTAL.BOTTOM.VZ;
	CHASSIS_VR = RUI_V_CONTAL.BOTTOM.VR;

    if (!DBUS_STATUS)
    {
        CHASSIS_VX = 0;
        CHASSIS_VY = 0;
        CHASSIS_VW = 0;
		CHASSIS_VZ = 0;
		CHASSIS_VR = 0;
    }
/*                                      底盘部分                                     */
	//麦轮解算，赋目标值
    MecanumResolve(CHASSIS_VX , CHASSIS_VY , CHASSIS_VW);
	//PID计算
    RUI_F_MOTOR_CHSISS_3508RM(&RUI_V_MOTOR_BOTTOM_3508_1);
    RUI_F_MOTOR_CHSISS_3508RM(&RUI_V_MOTOR_BOTTOM_3508_2);
    RUI_F_MOTOR_CHSISS_3508RM(&RUI_V_MOTOR_BOTTOM_3508_3);
    RUI_F_MOTOR_CHSISS_3508RM(&RUI_V_MOTOR_BOTTOM_3508_4);
	//记录输出最大值
    if (RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_1.PID_S.All_out)  > RUI_V_CURRENT_MAX_1)
    {
        RUI_V_CURRENT_MAX_1 = RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_1.PID_S.All_out);
    }
    if (RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_2.PID_S.All_out)  > RUI_V_CURRENT_MAX_2)
    {
        RUI_V_CURRENT_MAX_2 = RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_2.PID_S.All_out);
    }
    if (RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_3.PID_S.All_out)  > RUI_V_CURRENT_MAX_3)
    {
        RUI_V_CURRENT_MAX_3 = RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_3.PID_S.All_out);
    }
    if (RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_4.PID_S.All_out)  > RUI_V_CURRENT_MAX_4)
    {
        RUI_V_CURRENT_MAX_4 = RUI_F_MATH_ABS_int16_t(RUI_V_MOTOR_BOTTOM_3508_4.PID_S.All_out);
    }

/******************************************转矿部分*********************************************/
	//赋目标值
	RUI_V_MOTOR_BOTTOM_2006_1.DATA.Aim = +CHASSIS_VZ*50;
	RUI_V_MOTOR_BOTTOM_2006_2.DATA.Aim = -CHASSIS_VZ*50-CHASSIS_VR*50;
	RUI_V_MOTOR_BOTTOM_2006_3.DATA.Aim = -CHASSIS_VZ*50;
	RUI_V_MOTOR_BOTTOM_2006_4.DATA.Aim = +CHASSIS_VZ*50-CHASSIS_VR*50;
	//PID计算
	RUI_F_MOTOR_CHSISS_2006RM(&RUI_V_MOTOR_BOTTOM_2006_1);
	RUI_F_MOTOR_CHSISS_2006RM(&RUI_V_MOTOR_BOTTOM_2006_2);
	RUI_F_MOTOR_CHSISS_2006RM(&RUI_V_MOTOR_BOTTOM_2006_3);
	RUI_F_MOTOR_CHSISS_2006RM(&RUI_V_MOTOR_BOTTOM_2006_4);
	
	
    return RUI_DF_READY;
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //底部总初始化函数
 *	@parameter:		    //
 *	@time:				//22-11-25 15:27
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
uint8_t RUI_F_BOTTOM_INIT(void)
{
    /*PID赋值*/
    if (RUI_F_MOTOR_PID_BOTTOM_INIT() != RUI_DF_READY)
    {
        return RUI_DF_ERROR;
    }
    /*麦轮解算赋值*/
    if (MecanumInit() != RUI_DF_READY)
    {
        return RUI_DF_ERROR;
    }

    return RUI_DF_READY;
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞 COPY FORM 澍哥
 *	@performance:	    //带偏移量的
 *	@parameter:		    //
 *	@time:				//22-11-25 14:08
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
struct mecanumInit_typdef mecanumInit_t ={ 0 }; // 初始化使用的机构体
uint8_t MecanumInit(void)
{

    mecanumInit_t.deceleration_ratio = 0.052075f; // 减速比1/19
    mecanumInit_t.max_vw_speed       = 50000;     // r方向上的最大速度单位：毫米/秒
    mecanumInit_t.max_vx_speed       = 50000;     // x方向上的最大速度单位：毫米/秒
    mecanumInit_t.max_vy_speed       = 50000;     // y方向上的最大速度单位：毫米/秒
    mecanumInit_t.max_wheel_ramp     = 8000;      // 3508最大转速不包含限速箱
    mecanumInit_t.rotate_x_offset    = 00.0f;     // 云台在x轴的偏移量  mm
    mecanumInit_t.rotate_y_offset    = 00.0f;     // 云台在y轴的偏移量  mm
    mecanumInit_t.wheelbase          = 300;       // 轮距	mm
    mecanumInit_t.wheeltrack         = 300;       // 轴距	mm
    mecanumInit_t.wheel_perimeter    = 478;       // 轮子的周长(mm)

    /*计算旋转比率*/
    mecanumInit_t.raid_fr = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f -
                             mecanumInit_t.rotate_x_offset + mecanumInit_t.rotate_y_offset) /
        57.3f;
    mecanumInit_t.raid_fl = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f -
                             mecanumInit_t.rotate_x_offset - mecanumInit_t.rotate_y_offset) /
        57.3f;
    mecanumInit_t.raid_bl = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f +
                             mecanumInit_t.rotate_x_offset - mecanumInit_t.rotate_y_offset) /
        57.3f;
    mecanumInit_t.raid_br = ((mecanumInit_t.wheelbase + mecanumInit_t.wheeltrack) / 2.0f +
                             mecanumInit_t.rotate_x_offset + mecanumInit_t.rotate_y_offset) /
        57.3f;
// 将算出来的数据转化到转每分钟上去 raid = 60/(电机减速比*轮的周长)
    mecanumInit_t.wheel_rpm_ratio = 60.0f / (mecanumInit_t.wheel_perimeter * mecanumInit_t.deceleration_ratio);

    return RUI_DF_READY;
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞 CPOY  FORM 澍哥
*	@performance:	    //带中心点的麦轮解算。可以让车辆绕着一个中心点转动,在移动时保证以操作手为正方向
*	@parameter:		    //@平移速度@前进速度@旋转速度
*	@time:				//22-11-25 13:44
*	@ReadMe:			//左负右正//前正后负//顺正逆负
                        //带有中心偏移量，可以调节旋转中心
                        //要在初始化函数结束之后才能调用
                             矢量表     	//箭头代表每一个麦轮的分力方向，数字带表ID
                              车头
                            ↑  ||  ↑
                            2→ || ←1
                            —————————   Y轴  左正右负，上正下负
                            3→ || ←4
                            ↓  ||  ↓
                              车尾
                        //目前仅仅支持到速度环
************************************************************万能分隔符**************************************************************/

void MecanumResolve(int16_t vx_temp , int16_t vy_temp , int16_t vr)
{
    //float max          = 0;
    float wheel_rpm[4] ={ 0 };

    wheel_rpm[0] = (-vx_temp + vy_temp + vr * mecanumInit_t.raid_fr) * mecanumInit_t.wheel_rpm_ratio;
    wheel_rpm[1] = (vx_temp + vy_temp + vr * mecanumInit_t.raid_fl) * mecanumInit_t.wheel_rpm_ratio;
    wheel_rpm[2] = (vx_temp - vy_temp + vr * mecanumInit_t.raid_bl) * mecanumInit_t.wheel_rpm_ratio;
    wheel_rpm[3] = (-vx_temp - vy_temp + vr * mecanumInit_t.raid_br) * mecanumInit_t.wheel_rpm_ratio;
    // // 寻找四个轮子里面的最大值
    // for (uint8_t i = 0; i < 4; i++)
    // {
    //     if (RUI_F_MATH_ABS_float(wheel_rpm[i]) > max)
    //     {
    //         max = RUI_F_MATH_ABS_float(wheel_rpm[i]);
    //     }

    // }
    // // 如果超出了最大值，则进行等比例降速
    // if (max > mecanumInit_t.max_wheel_ramp)
    // {
    //     float rate = mecanumInit_t.max_wheel_ramp / max;
    //     for (uint8_t i = 0; i < 4; i++)
    //         wheel_rpm[i] *= rate;
    // }
    RUI_V_MOTOR_BOTTOM_3508_1.DATA.Aim = wheel_rpm[1];
    RUI_V_MOTOR_BOTTOM_3508_2.DATA.Aim = wheel_rpm[0];
    RUI_V_MOTOR_BOTTOM_3508_3.DATA.Aim = wheel_rpm[3];
    RUI_V_MOTOR_BOTTOM_3508_4.DATA.Aim = wheel_rpm[2];
}