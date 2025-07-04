#include "usr.h"
#include "RUI_ANONYMITY.h"
#include "kalman.h"
#include "bsp_can.h"

union MYADC_Typdef MYADC;
union Transmit_Typedef Transmit_Data;

void task(void)
{	
	Transmit_Data.channels.begin = 0xA5;
	Transmit_Data.channels.URy = (int16_t)MYADC.ADC_name.URy;
	Transmit_Data.channels.URz = (int16_t)MYADC.ADC_name.URz;
	Transmit_Data.channels.Key_begin = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
	Transmit_Data.channels.Key_CUP = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);

	CAN_SEND(0x101,Transmit_Data.DATA);
//	RUI_F_AN_REVOLVE();
}

