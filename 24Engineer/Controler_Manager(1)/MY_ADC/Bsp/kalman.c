#include "kalman.h"
#include "gpio.h"
#include "math.h"
#include "tim.h"
#include "stdlib.h"

/** *****************************************************************************************
  * @file    kalman.c                                                                                                                                      *
  * @author  Liu heng                                                                                                                                    *
  * @version V1.0.0                                                                                                                                      *
  * @date    27-August-2013                                                                                                                         *
  * @brief   一维卡尔曼滤波器的具体实现。实现过程完全与硬件无关，   *
  *   可直接调用，任意移植。                                                                                               *
  *   使用时先定义一个kalman指针，然后调用kalmanCreate()创建一个滤波器?*
  *   每次读取到传感器数据后即可调用KalmanFilter()来对数据进行滤波。               *
  *****************************************************************************************
  *                          使用示例                                                     *
  *          kalman p;                                                                   *
  *          float SersorData;                                                            *
  *          kalmanCreate(&p,20,200);                                                  *
  *          while(1)                                                                     *
  *          {                                                                            *
  *             SersorData = sersor();                                                    *
  *             SersorData = KalmanFilter(&p,SersorData);                                  *
  *             printf("%2.2f",SersorData);                                               *
  *          }                                                                            *
  *****************************************************************************************
  *          MPU6050的卡尔曼滤波器参考参数 Q：10 R：400                                   *
  *****************************************************************************************/

#include "kalman.h"
#include "main.h"
/**
  * @name   kalmanCreate
  * @brief  创建一个卡尔曼滤波器
  * @param  p:  滤波器
  *         T_Q:系统噪声协方差
  *         T_R:测量噪声协方差
  *         
  * @retval none
  */
kalman URy,URz;
	
//void kalmanInit(void)		//创建六个轴对应的卡尔曼结构体
//{
//	kalmanCreate(&Kgx,10,3);
//	kalmanCreate(&Kgy,10,3);
//	kalmanCreate(&Kgz,10,1);
//	kalmanCreate(&Kax,10,22);
//	kalmanCreate(&Kay,10,31);
//	kalmanCreate(&Kaz,10,37);
//}	

void kalmanInit(void)		//创建六个轴对应的卡尔曼结构体
{
	kalmanCreate(&URy,400,10);
	kalmanCreate(&URz,400,10);
}

//void kalmanUpdate(void)	
//{
//	ICM_Data.ACCL[0] = KalmanFilter(&Kax,ICM_Data.ACCL[0]);
//	ICM_Data.ACCL[1] = KalmanFilter(&Kay,ICM_Data.ACCL[1]);
//	ICM_Data.ACCL[2] = KalmanFilter(&Kaz,ICM_Data.ACCL[2]);
//	ICM_Data.GYRO[0] = KalmanFilter(&Kgx,ICM_Data.GYRO[0]);
//	ICM_Data.GYRO[1] = KalmanFilter(&Kgy,ICM_Data.GYRO[1]);  //Pitch轴角速度
//	ICM_Data.GYRO[2] = KalmanFilter(&Kgz,ICM_Data.GYRO[2]);  //Yaw轴角速度
//}
	
void kalmanCreate(kalman *p,float T_Q,float T_R)
{
    p->X_last = (float)0;
    p->P_last = 0;
    p->Q = T_Q;
    p->R = T_R;
    p->A = 1;
    p->H = 1;
    p->X_mid = p->X_last;
    //return p;
}

/**
  * @name   KalmanFilter
  * @brief  卡尔曼滤波器
  * @param  p:  滤波器
  *         dat:待滤波数据
  * @retval 滤波后的数据
  */

float KalmanFilter(kalman* p,double dat)
{
    p->X_mid =p->A*p->X_last;                     //x(k|k-1) = AX(k-1|k-1)+BU(k)
    p->P_mid = p->A*p->P_last+p->Q;               //p(k|k-1) = Ap(k-1|k-1)A'+Q
    p->kg = p->P_mid/(p->P_mid+p->R);             //kg(k) = p(k|k-1)H'/(Hp(k|k-1)'+R)
    p->X_now = p->X_mid+p->kg*(dat-p->X_mid);     //x(k|k) = X(k|k-1)+kg(k)(Z(k)-HX(k|k-1))
    p->P_now = (1-p->kg)*p->P_mid;                //p(k|k) = (I-kg(k)H)P(k|k-1)
    p->P_last = p->P_now;                         //状态更新
    p->X_last = p->X_now;
    return p->X_now;
}


//陀螺仪零漂，上电后静止一段时间，进行数据采集，好后期减去零漂。全程只进行了一次零点采集
//uint8_t ICM20602_GyroOffSet()
//{
//	IMU_OffSet.Gyro[0] = 0;
//	IMU_OffSet.Gyro[1] = 0;
//	IMU_OffSet.Gyro[2] = 0;
//	uint16_t i;
//	for(i=0;i<250;i++)
//	{
//		icm20602_get_gyro_adc(&ICM_Data.GYRO_ADC[0],&ICM_Data.GYRO_ADC[1],&ICM_Data.GYRO_ADC[2]);
//		IMU_OffSet.Gyro[0] += ICM_Data.GYRO_ADC[0];
//		IMU_OffSet.Gyro[1] += ICM_Data.GYRO_ADC[1];
//		IMU_OffSet.Gyro[2] += ICM_Data.GYRO_ADC[2];
//		my_delay_ms(2);
//	}
//	//进行了250次加和，此处进行取平均值，即乘0.004
//	IMU_OffSet.Gyro[0] *= 0.004f;
//	IMU_OffSet.Gyro[1] *= 0.004f;
//	IMU_OffSet.Gyro[2] *= 0.004f;
//	
//	return 0;
//} 

//uint32_t Get_Time_Micros(void)//读取陀螺仪积分时间
//{
//	return TIM4->CNT;
//}

//uint32_t lastUpdate, now; // 采样周期计数 单位 us 
//float halfT;
//void ICM20602_GetValue()
//{
//	icm20602_get_accel_adc(&ICM_Data.ACCL_ADC[ax],&ICM_Data.ACCL_ADC[ay],&ICM_Data.ACCL_ADC[az]);
//	icm20602_get_gyro_adc(&ICM_Data.GYRO_ADC[gx],&ICM_Data.GYRO_ADC[gy],&ICM_Data.GYRO_ADC[gz]);
////	ICM_Data.Temp = icm20602_get_temp();
//	float alpha = 0.3;
//	//一阶低通滤波，加速度值，加速度计进行了低通滤波，没有进行卡方检验
//	ICM_Data.ACCL[ax] = (((float)ICM_Data.ACCL_ADC[ax]) * alpha) / 16348.0f * 9.8f + ICM_Data.ACCL[ax] * (1 - alpha);
//	ICM_Data.ACCL[ay] = (((float)ICM_Data.ACCL_ADC[ay]) * alpha) / 16348.0f * 9.8f + ICM_Data.ACCL[ay] * (1 - alpha);
//	ICM_Data.ACCL[az] = (((float)ICM_Data.ACCL_ADC[az]) * alpha) / 16348.0f * 9.8f + ICM_Data.ACCL[az] * (1 - alpha);
//	
//	//陀螺仪角速度转换为弧度制角速度;deg/s->rad/s，并且角速度减去了零漂
//	ICM_Data.GYRO[gx] = ((float)ICM_Data.GYRO_ADC[gx] - IMU_OffSet.Gyro[gx]) * PI / 180.0f / 16.4f;
//	ICM_Data.GYRO[gy] = ((float)ICM_Data.GYRO_ADC[gy] - IMU_OffSet.Gyro[gy]) * PI / 180.0f / 16.4f;
//	ICM_Data.GYRO[gz] = ((float)ICM_Data.GYRO_ADC[gz] - IMU_OffSet.Gyro[gz]) * PI / 180.0f / 16.4f;
//	
//		now = Get_Time_Micros();  //读取时间 单位是us   
//	if(now>=lastUpdate)	
//    {
//        halfT =  ((float)(now - lastUpdate) / 2000000.0f);
//    }
//    lastUpdate = now;	//更新时间
//	
//	
//	ICM_Data.GetData_Status = 1;
//}

