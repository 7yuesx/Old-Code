/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-31 13:49:55
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:49:09
 */
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
#ifndef RUI_BOTTOM_H
#define RUI_BOTTOM_H
#include "math.h"
#include "main.h"
#include "stdint.h"
#include "RUI_PID.h"
#include "RUI_CAN.h"

// 麦克纳姆轮初始化结构体
struct mecanumInit_typdef
{
    float wheel_perimeter;    /* 轮的周长（mm）*/
    float wheeltrack;         /* 轮距（mm）*/
    float wheelbase;          /* 轴距（mm）*/
    float rotate_x_offset;    /* 相对于底盘中心的x轴旋转偏移量(mm) */
    float rotate_y_offset;    /* 相对于底盘中心的y轴旋转偏移量(mm) */
    float deceleration_ratio; /* 电机减速比 */
    int max_vx_speed;         /* 底盘的x轴的最大速度(mm/s) */
    int max_vy_speed;         /* 底盘的y轴的最大速度(mm/s) */
    int max_vw_speed;         /* 底盘的自转的最大速度(degree/s) */
    int max_wheel_ramp;       /* 3508最大转速 */
                              // 每一个轮子的旋转比率//与旋转中心点相关
    float raid_fr;            // 右前
    float raid_fl;            // 左前
    float raid_bl;            // 左后
    float raid_br;            // 右后
    float wheel_rpm_ratio;    // 用来将速度转化成转每分钟
};

uint8_t RUI_F_BOTTOM_CONTRAL(uint8_t DBUS_STATUS);
uint8_t RUI_F_CHASSIS_CONTRAL(uint8_t DUBS_STATUS);
uint8_t RUI_F_BOTTOM_INIT(void);
uint8_t MecanumInit(void);

void MecanumResolve(int16_t vx_temp , int16_t vy_temp , int16_t vr);

#endif