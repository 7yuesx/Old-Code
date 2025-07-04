#ifndef __RUI_ALLUI_H
#define __RUI_ALLUI_H


#include "stdint.h"
#include "usart.h"

extern uint8_t sit[11];
extern uint8_t data_au8[255] ;
extern union receive_Typdef receive;
void sending(void);

#define X_CENTER 960
#define Y_CENTER 540




/*__packed  c语言关键字，有了它结构体中的数据就不会首地址对齐
进而说有了它数据会被压缩
1.通常编译器在生成代码的时候都会进行结构体的填充，保证（结构体内部成员）最高性能的对齐方式
2.编译器自动分配出来结构体的内存（比如定义为全局变量或局部变量）肯定是对齐的
*/





//必要的函数声明
uint8_t Get_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength, uint8_t ucCRC8 );
uint32_t Verify_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength);
void Append_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength);
void judgeCalculate(uint8_t * JudgeDataBuffer);
void determine_ID(void);
_Bool is_red_or_blue(void);







/*********************************裁判系统发送begin*****************************/

//帧头
typedef  struct  __packed
{
  uint8_t   SOF;				//0xA5
  uint16_t  DataLenth;	//数据位长度
	uint8_t   Seq;				//包序号
  uint8_t   CRC8;				//crc8位校验
}tFrameHeader;

//相关变量的结构体
typedef struct __packed
{
	float Pitch;
	float Roll;
	float Yaw;
	float Y_length;
	float Z_length;
	uint8_t CUP;
	uint8_t aaaa[9];
	
} ext_client_map_command_t;


typedef  struct __packed
{
	ext_client_map_command_t		graphic_data_struct_t;
}ext_uiradar; 




//////////裁判系统发送整体数据//////////
typedef struct __packed
{
  tFrameHeader          frameHeader;//帧头
  uint16_t              CmdId;//命令码
	ext_uiradar				uiradar;
	uint16_t              CRC16;		
}hypTypedef;

extern hypTypedef hyp;//线的绘制







/*****end********/
     
//必要的函数声明
uint8_t Get_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength, uint8_t ucCRC8 );
uint32_t Verify_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength);
void Append_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength);
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC);
uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength);
void judgeCalculate(uint8_t * JudgeDataBuffer);
void int_into_char(char *Data, int16_t i);
void determine_ID(void);
_Bool is_red_or_blue(void);
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
void sending(void);


void Usart1_TX_staticUI(void);		//辅助线
#endif

/***********************************命令码ID*************************************/
/*

ID: 0x0001          Byte: 11      比赛状态数据                   发送频率 1Hz
ID: 0x0002          Byte: 1       比赛结果数据                   比赛结束后发送
ID: 0x0003          Byte: 32      比赛机器人血量数据             发送频率 1Hz
ID: 0x0004          Byte: 3       飞镖发射状态                   飞镖发射后发送
ID: 0x0005          Byte: 11      人工智能挑战赛加成与惩罚       发送频率 1Hz
ID: 0x0101          Byte: 4       场地事件数据                   事件改变后发送
ID: 0x0102          Byte: 4       场地补给站动作标识数据         动作改变后发送
//ID: 0X0103          Byte: 2       场地补给站预约子弹数据         参赛队发送，上限10Hz（RM对抗赛未开放） 
ID: 0X0104          Byte: 2       裁判警告数据                   警告发生后发送
ID: 0x0105          Byte: 1       飞镖发射口倒计时               发送频率 1Hz
ID: 0X0201          Byte: 27      机器人状态数据                 发送频率 10Hz
ID: 0X0202          Byte: 16      实时功率热量数据               发送频率 50Hz
ID: 0X0203          Byte: 16      机器人位置数据                 发送频率 10Hz
ID: 0X0204          Byte: 1       机器人增益数据                 增益状态改变后发送
ID: 0X0205          Byte: 2       空中机器人能量状态数据         发送频率 10Hz，只有空中机器人主控发送
ID: 0X0206          Byte: 1       伤害状态数据                   伤害发生后发送
ID: 0X0207          Byte: 7       实时射击数据                   子弹发射后发送
ID: 0X0208          Byte: 6       子弹剩余发送数                 无人机与哨兵发送  发送频率 1Hz
ID: 0X0209          Byte: 4       机器人RFID状态                 发送频率 1Hz
ID: 0x020A          Byte: 12      飞镖机器人客户端指令书         发送频率 10Hz
ID: 0X0301          Byte: n       机器人间交互数据               发送方触发发送    上限频率 10Hz
ID: 0x0302          Byte: n       自定义控制器交互数据接口       客户端触发发送    上限频率 30Hz
ID: 0x0303          Byte: 15      客户端小地图交互数据           触发发送
ID: 0x0304          Byte: 12      键盘、鼠标信息                 通过图传串口发送 */

/*******************************************************************************
/    内容ID          长度（头结构+内容数据段）            功能说明
/ 0x0200~0x02FF             6+n                         己方机器人间通信           
/    0x0100                 6+2                         客户端删除图形
/    0x0101                 6+15                        客户端绘制一个图形
/    0x0102                 6+30                        客户端绘制二个图形
/    0x0103                 6+75                        客户端绘制五个图形
/    0x0104                 6+105                       客户端绘制七个图形
/    0x0110                 6+45                        客户端绘制字符图形
********************************************************************************/
/*
	uint8_t graphic_name[3]; //图形名,在删除，修改等操作中，作为客户端的索引。
	uint32_t operate_tpye:3; //图形操作：0：空操作；1：增加；2：修改；3：删除；
	uint32_t graphic_tpye:3; //图形类型：0：直线；1：矩形；2：整圆；3：椭圆；4：圆弧；5:浮点数 6：整型数 7：字符
	uint32_t layer:4; //图层数，0~9
	uint32_t color:4; //颜色：0：红蓝主色；1：黄色；2：绿色；3：橙色；4：紫红色；5：粉色；6：青色；7：黑色；8：白色；
	uint32_t start_angle:9; //：起始角度，单位：°，范围[0,360]；
	uint32_t end_angle:9; //终止角度，单位：°，范围[0,360]。
	uint32_t width:10; //线宽；0-9
	uint32_t start_x:11; //起点x坐标；
	uint32_t start_y:11; //起点y坐标。
	uint32_t radius:10; //字体大小或者半径；
	uint32_t end_x:11; //终点x坐标；
	uint32_t end_y:11; //终点y坐标。
*/



