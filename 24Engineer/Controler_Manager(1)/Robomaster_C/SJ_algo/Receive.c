/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-02-15 08:21:19
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:59:12
 */
#include "Receive.h"
#include "string.h"
#include "handle.h"

union Receive_Typedef Receive_Data;
uint8_t flag_CUP = 0xf0;
uint8_t flaag = 0;

void read_ADC(void)
{
	if(Receive_Data.channels.begin == 0xA5)
	{
		//高贵的锁
		if(Receive_Data.channels.Key_CUP == 1)
			flaag = 0;
		if(Receive_Data.channels.Key_CUP == 0)
			flaag = 1;
//		if((Receive_Data.channels.Key_CUP == 1)&&(flaag == 0))
//		{
//			flag_CUP = !flag_CUP;
//			flaag = 1;
//		}else if((Receive_Data.channels.Key_CUP == 0)&&(flaag == 1))
//		{
//			flaag = 0;
//		}
		
	}
}
