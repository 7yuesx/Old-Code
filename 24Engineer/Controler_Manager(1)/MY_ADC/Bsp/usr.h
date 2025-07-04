/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-01 12:36:45
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:55:06
 */
#ifndef __USR_H
#define __USR_H

#include "usart.h"

union MYADC_Typdef
{
	struct __packed
	{
		uint16_t URy;
		uint16_t URz;
	}ADC_name;
	uint16_t ADC_Value[2];
};

union Transmit_Typedef
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

void task(void);

extern union MYADC_Typdef MYADC;
extern union Transmit_Typedef Transmit_Data;

#endif
