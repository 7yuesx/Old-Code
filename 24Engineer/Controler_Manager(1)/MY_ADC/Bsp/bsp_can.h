/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-28 12:48:03
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:54:02
 */
#ifndef __BSP_CAN_H
#define __BSP_CAN_H

void CAN_SEND(int16_t stdid , uint8_t* Data);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1);

extern uint8_t Data[8];

#endif
