/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-28 12:48:03
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:53:52
 */
#include "can.h"
#include "bsp_can.h"



void CAN_SEND(int16_t stdid , uint8_t* Data)
{
 
	CAN_TxHeaderTypeDef CAN_TX;

	uint32_t TX_MAILBOX;
	
  
	CAN_TX.DLC = 0x08;
	CAN_TX.IDE = CAN_ID_STD;//标准帧
	CAN_TX.RTR = CAN_RTR_DATA;//数据帧
	CAN_TX.StdId = stdid;//标准帧ID
	
	HAL_CAN_AddTxMessage(&hcan,&CAN_TX,Data,&TX_MAILBOX);
}


CAN_RxHeaderTypeDef  RxMessage;
uint8_t Data[8];
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{	
   
   HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, Data);
 
}
