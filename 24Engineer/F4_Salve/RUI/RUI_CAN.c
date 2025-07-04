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
#include "RUI_CAN.h"
CAN_FilterTypeDef CAN_FilterInitStrt;
struct CONTAL_Typedef RUI_V_CONTAL;
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //CAN ID过滤
 *	@parameter:		    //
 *	@time:				//22-11-23 20:39
 *	@ReadMe:			//放在主函数里初始化一次
 ************************************************************万能分隔符**************************************************************/
void CAN_Filter_Init(void)
{
    CAN_FilterInitStrt.SlaveStartFilterBank = 14;
    CAN_FilterInitStrt.FilterBank           = 14;
    CAN_FilterInitStrt.FilterActivation     = ENABLE;
    CAN_FilterInitStrt.FilterMode           = CAN_FILTERMODE_IDMASK;
    CAN_FilterInitStrt.FilterScale          = CAN_FILTERSCALE_32BIT;
    CAN_FilterInitStrt.FilterIdHigh         = 0x0000;
    CAN_FilterInitStrt.FilterIdLow          = 0x0000;
    CAN_FilterInitStrt.FilterMaskIdHigh     = 0x0000;
    CAN_FilterInitStrt.FilterMaskIdLow      = 0x0000;
    CAN_FilterInitStrt.FilterBank           = 0;
    CAN_FilterInitStrt.FilterFIFOAssignment = CAN_RX_FIFO0;

    HAL_CAN_ConfigFilter(&hcan1 , &CAN_FilterInitStrt);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1 , CAN_IT_RX_FIFO0_MSG_PENDING);

    CAN_FilterInitStrt.SlaveStartFilterBank = 14;
    CAN_FilterInitStrt.FilterBank           = 14;

    HAL_CAN_ConfigFilter(&hcan2 , &CAN_FilterInitStrt);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2 , CAN_IT_RX_FIFO0_MSG_PENDING);

    return;
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //CAN发送函数
 *	@parameter:		    //@CAN1 or CAN2 @stdid:ID @num1:要发送的int16数据
 *	@time:				//22-11-23 20:41
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_CAN_SEDN(CAN_HandleTypeDef* _hcan , int16_t stdid , int16_t num1 , int16_t num2 , int16_t num3 , int16_t num4)
{
    CAN_TxHeaderTypeDef TXMessage;
    uint8_t Data[8];
    uint32_t send_mail_box;

    TXMessage.DLC   = 0x08;
    TXMessage.IDE   = CAN_ID_STD;
    TXMessage.RTR   = CAN_RTR_DATA;
    TXMessage.StdId = stdid;

    Data[0] = ((num1) >> 8);
    Data[1] = (num1);
    Data[2] = ((num2) >> 8);
    Data[3] = (num2);
    Data[4] = ((num3) >> 8);
    Data[5] = (num3);
    Data[6] = ((num4) >> 8);
    Data[7] = (num4);

    if ((_hcan) == &hcan1)
    {
        HAL_CAN_AddTxMessage(&hcan1 , &TXMessage , Data , &send_mail_box);

    }
    else if ((_hcan) == &hcan2)
    {
        HAL_CAN_AddTxMessage(&hcan2 , &TXMessage , Data , &send_mail_box);
    }
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //共用体can发送
 *	@parameter:		    //
 *	@time:				//23-05-06 19:07
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_CAN_SEDN_UNION(CAN_HandleTypeDef* _hcan , int16_t stdid , uint8_t* Data)
{
    CAN_TxHeaderTypeDef TXMessage;

    uint32_t send_mail_box;

    TXMessage.DLC   = 0x08;
    TXMessage.IDE   = CAN_ID_STD;
    TXMessage.RTR   = CAN_RTR_DATA;
    TXMessage.StdId = stdid;


    if ((_hcan) == &hcan1)
    {
        HAL_CAN_AddTxMessage(&hcan1 , &TXMessage , Data , &send_mail_box);

    }
    else if ((_hcan) == &hcan2)
    {
        HAL_CAN_AddTxMessage(&hcan2 , &TXMessage , Data , &send_mail_box);
    }
}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //CAN接收函数
 *	@parameter:		    //
 *	@time:				//22-11-23 20:42
 *	@ReadMe:			//
 *  @LastUpDataTime:    //2023-04-20 02:52    bestrui
 *  @UpData：           //更新成共用体
 *  @LastUpDataTime:    //2023-05-06 20:23    bestrui
 *  @UpData：           //更新判断逻辑
 ************************************************************万能分隔符**************************************************************/
CAN_RxHeaderTypeDef can_rx;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
    static union COMMUNICATION_UNION_Typdef  RUI_V_COMMUNICATION ={ 0 };

    uint8_t rx_data[8];

    HAL_CAN_GetRxMessage(hcan , CAN_RX_FIFO0 , &can_rx , rx_data);
    //2023-05-06 20:24    更新判断逻辑   
    if (RUI_ROOT.MASTER_LOCATION == RUI_DF_MASTER_LOCATION_BOTTOM || RUI_ROOT.MASTER_LOCATION == RUI_DF_MASTER_LOCATION_JUDGEING)
    {
        if (hcan == &hcan2)
        {
            switch (can_rx.StdId)
            {
//                //底盘CAN1接受从云台发送的遥控数据
//                case 0x151:
//				{
//					memcpy(RUI_V_COMMUNICATION.Data , rx_data , 8);

//					RUI_V_CONTAL.BOTTOM.VX = RUI_V_COMMUNICATION.DataNeaten.VX;
//					RUI_V_CONTAL.BOTTOM.VY = RUI_V_COMMUNICATION.DataNeaten.VY;
//					RUI_V_CONTAL.BOTTOM.VW = RUI_V_COMMUNICATION.DataNeaten.VW;
//					RUI_V_CONTAL.BOTTOM.VZ = RUI_V_COMMUNICATION.DataNeaten.VZ;
//					RUI_ROOT.STATUS.RM_DBUS  = RUI_V_COMMUNICATION.DataNeaten.DBUS_STATUS;
//					

//				}break;
				
				case RUI_DF_MOTOR_BOTTOM_2006_1_ID:
					RUI_F_MOTOR_CAN_RX_2006RM(&RUI_V_MOTOR_BOTTOM_2006_1 , rx_data);
					break;
				
				case RUI_DF_MOTOR_BOTTOM_2006_2_ID:
					RUI_F_MOTOR_CAN_RX_2006RM(&RUI_V_MOTOR_BOTTOM_2006_2 , rx_data);
					break;
				
				case RUI_DF_MOTOR_BOTTOM_2006_3_ID:
					RUI_F_MOTOR_CAN_RX_2006RM(&RUI_V_MOTOR_BOTTOM_2006_3 , rx_data);
					break;
				
				case RUI_DF_MOTOR_BOTTOM_2006_4_ID:
					RUI_F_MOTOR_CAN_RX_2006RM(&RUI_V_MOTOR_BOTTOM_2006_4 , rx_data);
					break;

            }
        }
        if (hcan == &hcan1)
        {
            //底盘CAN2底盘四个3508电机接收数据
            switch (can_rx.StdId)
            {

                case RUI_DF_MOTOR_BOTTOM_3508_1_ID:
                    RUI_F_MOTOR_CAN_RX_3508RM(&RUI_V_MOTOR_BOTTOM_3508_1 , rx_data);
                    break;

                case RUI_DF_MOTOR_BOTTOM_3508_2_ID:
                    RUI_F_MOTOR_CAN_RX_3508RM(&RUI_V_MOTOR_BOTTOM_3508_2 , rx_data);
                    break;

                case RUI_DF_MOTOR_BOTTOM_3508_3_ID:
                    RUI_F_MOTOR_CAN_RX_3508RM(&RUI_V_MOTOR_BOTTOM_3508_3 , rx_data);
                    break;

                case RUI_DF_MOTOR_BOTTOM_3508_4_ID:
                    RUI_F_MOTOR_CAN_RX_3508RM(&RUI_V_MOTOR_BOTTOM_3508_4 , rx_data);
                    break;
            }
        }
    }   
}

