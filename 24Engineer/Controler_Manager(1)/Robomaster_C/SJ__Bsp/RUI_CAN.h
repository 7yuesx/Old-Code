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
#ifndef RUI_CAN_H
#define RUI_CAN_H

#include "can.h"
#include "string.h"

union COMMUNICATION_UNION_Typdef // 使用共用体整合数据
{
    struct
    {
        //遥控数据
        int16_t VX;
        int16_t VY;
        int16_t VW;
        uint8_t PUMP : 2;
        uint8_t AID : 2;
        uint8_t DBUS_STATUS : 2;
		uint8_t CAMERR:2;
		uint8_t CAMERRPUMP:2;
    } DataNeaten;
    // 接收到的数组
    uint8_t  Data[8];
};


void CAN_Filter_Init(void);
//电机can发送
void RUI_F_CAN_SEDN(CAN_HandleTypeDef* _hcan , int16_t stdid , int16_t num1 , int16_t num2 , int16_t num3 , int16_t num4);

//共用体发送
void RUI_F_CAN_SEDN_UNION(CAN_HandleTypeDef* _hcan , int16_t stdid , uint8_t* Data);

#endif
