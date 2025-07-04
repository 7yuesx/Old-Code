/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-04-10 17:31:24
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:41:19
 */
#include "RUI_ANONYMITY.h"
#include "usart.h"



/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //匿名发送函数
 *	@parameter:		    //
 *	@time:				//23-04-26 22:20
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
union ANONYMITY_UNION_Typdef RUI_V_ANONYMITY_UNION ={ 0 };

void RUI_F_ANONYMITY_TX(int16_t NUM1 , int16_t NUM2 , int16_t NUM3 , int16_t NUM4 , int16_t NUM5 , int16_t NUM6 , int16_t NUM7 , int16_t NUM8 , int16_t NUM9)
{
    RUI_V_ANONYMITY_UNION.TX.HEAD   = 0xAA;
    RUI_V_ANONYMITY_UNION.TX.D_ADDR = 0xFF;
    RUI_V_ANONYMITY_UNION.TX.ID     = 0xF1;
    RUI_V_ANONYMITY_UNION.TX.LEN    = 18;

    RUI_V_ANONYMITY_UNION.TX.NUM1 = NUM1;
    RUI_V_ANONYMITY_UNION.TX.NUM2 = NUM2;
    RUI_V_ANONYMITY_UNION.TX.NUM3 = NUM3;
    RUI_V_ANONYMITY_UNION.TX.NUM4 = NUM4;
    RUI_V_ANONYMITY_UNION.TX.NUM5 = NUM5;
    RUI_V_ANONYMITY_UNION.TX.NUM6 = NUM6;
    RUI_V_ANONYMITY_UNION.TX.NUM7 = NUM7;
    RUI_V_ANONYMITY_UNION.TX.NUM8 = NUM8;
    RUI_V_ANONYMITY_UNION.TX.NUM9 = NUM9;

    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;

    for (uint8_t i = 0; i < (RUI_V_ANONYMITY_UNION.DATA[3]+4); i++)
    {
        sumcheck += RUI_V_ANONYMITY_UNION.DATA[i];
        addcheck += sumcheck;
    }

    RUI_V_ANONYMITY_UNION.TX.SUMCHECK = sumcheck;
    RUI_V_ANONYMITY_UNION.TX.ADDCHECK = addcheck;

    HAL_UART_Transmit_IT(&huart7 , RUI_V_ANONYMITY_UNION.DATA , 24);

}
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //升降电机
 *	@parameter:		    //
 *	@time:				//23-05-07 15:36
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void RUI_F_AN_REVOLVE(void)
{
    RUI_F_ANONYMITY_TX((int16_t) 0 ,
                       (int16_t) 0 ,
                       (int16_t) 0 ,
					   (int16_t) 0 ,
                       (int16_t) 0 ,
                       (int16_t) 0 ,
                       (int16_t) 0 ,
                       (int16_t) 0 ,
                       (int16_t) 0
    );

}
