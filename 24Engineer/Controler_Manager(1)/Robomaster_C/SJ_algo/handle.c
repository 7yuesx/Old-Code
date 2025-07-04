#include "handle.h"
#include "math.h"
#include "QuaternionEKF.h"
#include "ins_task.h"

#define PAI 3.1415926f

float Accel_now[3];
float Accel_last[3];
float Accel_static[3];

float speed_now[3];
float speed_last[3];

float siting_now[3];
float siting_last[3];

float gg;
uint8_t count1 = 0,count2 = 0,count3 = 0;


void Calibrate(void)
{
	uint8_t i;
	uint16_t count;
	count = 0;
	//测量重力加速度
	do{
		gg += INS.Accel[2];
		count++;
	}while(count != 0xffff);
	gg = gg/64551;
	//测量稳定偏移量
	do{
		Accel_static[1] = INS.Accel[1] - sinf(INS.Pitch*(PAI/180.0f))*gg;
		Accel_static[0] = INS.Accel[0] + sinf(INS.Roll*(PAI/180.0f))*gg;
		Accel_static[2] = INS.Accel[2] - cosf(INS.Roll*(PAI/180.0f))*cosf(INS.Pitch*(PAI/180.0f))*gg;
		count++;
	}while(count != 0x0800);
	
	for(i=0;i<3;i++)
		Accel_static[i] = Accel_static[i]/2048;
	
	
}

void hand(void)
{
	uint8_t i;

	/***********去除重力加速度和稳定误差的影响*************/
	for(i=0;i<3;i++)
		Accel_last[i] = Accel_now[i];
		
	Accel_now[0] = INS.Accel[1] - sinf(INS.Pitch*(PAI/180.0f))*gg - Accel_static[1];
	Accel_now[1] = INS.Accel[0] + sinf(INS.Roll*(PAI/180.0f))*gg - Accel_static[0];
	Accel_now[2] = INS.Accel[2] - cosf(INS.Roll*(PAI/180.0f))*cosf(INS.Pitch*(PAI/180.0f))*gg - Accel_static[2];
	
	/***********对加速度积分得到速度************/
	
	for(i=0;i<3;i++)
	{
		speed_last[i] = speed_now[i];
		if(Accel_now[i] - Accel_last[i] > 0.1f)   //设置死区
			speed_now[i] = speed_last[i] + Accel_last[i] + ((Accel_now[i] - Accel_last[i])/2.0f);
		if(Accel_now[i] - Accel_last[i] < -0.1f)  //设置死区
			speed_now[i] = speed_last[i] + Accel_last[i] + ((Accel_now[i] - Accel_last[i])/2.0f);	
	}
	//速度清零
	if((int16_t)Accel_now[1] == 0)
		count2++;
	else
		count2 = 0;
	if(count2 >= 24)
	{
		count2 = 0;
		speed_now[1] = 0;
		speed_last[1] = 0;
	}
	
	if((int16_t)Accel_now[0] == 0)
		count1++;
	else
		count1 = 0;
	if(count1 >= 24)
	{
		count1 = 0;
		speed_now[0] = 0;
		speed_last[0] = 0;
	}
	
	if((int16_t)Accel_now[2] == 0)
		count3++;
	else
		count3 = 0;
	if(count3 >= 24)
	{
		count3 = 0;
		speed_now[2] = 0;
		speed_last[2] = 0;
	}
	
	/***********对速度积分得到位移************/
	
	for(i=0;i<3;i++)
	{
		siting_last[i] = siting_now[i];
		if(speed_now[i] - speed_last[i] > 0.1f)
			siting_now[i] = siting_last[i] + speed_last[i] + ((speed_now[i] - speed_last[i])/2.0f);
		if(speed_now[i] - speed_last[i] < -0.1f)
			siting_now[i] = siting_last[i] + speed_last[i] + ((speed_now[i] - speed_last[i])/2.0f);
	}
	
}


