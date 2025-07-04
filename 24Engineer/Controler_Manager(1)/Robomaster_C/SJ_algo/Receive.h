#ifndef __RECEIVE_H
#define __RECEIVE_H

#include "usart.h"

union Receive_Typedef
{
	struct __packed 
	{
		uint8_t begin;		//	A5	
		int16_t URy;		//	
		int16_t URz;		//
		uint8_t Key_begin;	//	F0	
		uint8_t Key_CUP;	//	F0	
		uint8_t nnnn;	
	}channels;
	uint8_t DATA[8];
};


void read_ADC(void);

extern union Receive_Typedef Receive_Data;
extern uint8_t flag_CUP;
extern uint8_t flaag;
#endif
