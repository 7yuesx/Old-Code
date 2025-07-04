/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-01-28 09:50:52
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:52:34
 */
/*
 *                                                     __----~~~~~~~~~~~------___
 *                                    .  .   ~~//====......          __--~ ~~
 *                    -.            \_|//     |||\\  ~~~~~~::::... /~
 *                 ___-==_       _-~o~  \/    |||  \\            _/~~-
 *         __---~~~.==~||\=_    -_--~/_-~|-   |\\   \\        _/~
 *     _-~~     .=~    |  \\-_    '-~7  /-   /  ||    \      /
 *   .~       .~       |   \\ -_    /  /-   /   ||      \   /
 *  /  ____  /         |     \\ ~-_/  /|- _/   .||       \ /
 *  |~~    ~~|--~~~~--_ \     ~==-/   | \~--===~~        .\
 *           '         ~-|      /|    |-~\~~       __--~~
 *                       |-~~-_/ |    |   ~\_   _-~            /\
 *                            /  \     \__   \/~                \__
 *                        _--~ _/ | .-~~____--~-/                  ~~==.
 *                       ((->/~   '.|||' -_|    ~~-/ ,              . _||
 *                                  -_     ~\      ~~---l__i__i__i--~~_/
 *                                  _-~-__   ~)  \--______________--~~
 *                                //.-~~~-~_--~- |-------~~~~~~~~
 *                                       //.-~~~--\
 *                       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *                               神兽保佑            永无BUG
 */

#include "Write_Data.h"
#include "stdint.h"
#include "string.h"



/***********************************    ↓    DJI提供的CRC校检函数   ↓  ***********************************/
const unsigned char CRC8_INIT = 0xff;
//crc8 generator polynomial:G(x)=x8+x5+x4+1																						/*帧头*/             /*命令码*/  /*数据段id*/ /*发送id*/  /*接收id*/  /*数据1  数据2    数据3    灯   校验id*/
const unsigned char CRC8_TAB[256] =
{
    0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
    0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
    0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
    0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
    0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
    0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
    0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
    0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
    0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
    0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
    0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
    0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
    0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
    0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
    0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
    0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};


uint8_t Get_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength, uint8_t ucCRC8 )
{
		uint8_t ucIndex;
	
		while (dwLength--)
		{
				ucIndex = ucCRC8^(*pchMessage++);
				ucCRC8 = CRC8_TAB[ucIndex];
		}
		return ucCRC8;
}


/*
** Descriptions: CRC8 Verify function
** Input: Data to Verify,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/
uint32_t Verify_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength)
{
		uint8_t ucExpected = 0;
	
		if (pchMessage == 0 || dwLength <= 2)
		{
			  return 0;
		}
		
		ucExpected = Get_CRC8_Check_Sum( pchMessage, dwLength-1, CRC8_INIT);
		
		return ( ucExpected == pchMessage[dwLength-1] );
}

/*
** Descriptions: append CRC8 to the end of data
** Input: Data to CRC and append,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/
uint8_t ucCRC = 0;
void Append_CRC8_Check_Sum( uint8_t *pchMessage, uint16_t dwLength)
{
		ucCRC=0;
	
		if (pchMessage == 0 || dwLength <= 2)
		{
			  return;
		}
		
		ucCRC = Get_CRC8_Check_Sum( (uint8_t *)pchMessage, dwLength-1, CRC8_INIT);
		
		pchMessage[dwLength-1] = ucCRC;
}

uint16_t CRC_INIT = 0xffff;

const uint16_t wCRC_Table[256] =
{
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


/*
** Descriptions: CRC16 checksum function
** Input: Data to check,Stream length, initialized checksum
** Output: CRC checksum
*/
uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage,uint32_t dwLength,uint16_t wCRC)
{
    uint8_t chData;
    if (pchMessage == 0)
    {
        return 0xFFFF;
    }
    while(dwLength--)
    {
        chData = *pchMessage++;
        (wCRC) = ((uint16_t)(wCRC) >> 8) ^ wCRC_Table[((uint16_t)(wCRC) ^
                                   (uint16_t)(chData)) & 0x00ff];
    }
    return wCRC;
}


/*
** Descriptions: CRC16 Verify function
** Input: Data to Verify,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/

uint32_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength)
{
    uint16_t wExpected = 0;
    if ((pchMessage == 0) || (dwLength <= 2))
    {
        return 0;
    }
    wExpected = Get_CRC16_Check_Sum ( pchMessage, dwLength - 2, CRC_INIT);
    return ((wExpected & 0xff) == pchMessage[dwLength - 2] && ((wExpected >> 8) & 0xff) == pchMessage[dwLength - 1]);
}

 
/*
** Descriptions: append CRC16 to the end of data
** Input: Data to CRC and append,Stream length = Data + checksum
** Output: True or False (CRC Verify Result)
*/
void Append_CRC16_Check_Sum(uint8_t * pchMessage,uint32_t dwLength)
{
    uint16_t wCRC = 0;
    if ((pchMessage == 0) || (dwLength <= 2))
    {
        return;
    }
    wCRC = Get_CRC16_Check_Sum ( (uint8_t *)pchMessage, dwLength-2, CRC_INIT );
    pchMessage[dwLength-2] = (uint8_t)(wCRC & 0x00ff);
    pchMessage[dwLength-1] = (uint8_t)((wCRC >> 8) & 0x00ff);
}

/***********************************        DJI提供的CRC校检函数     ***********************************/



/***********************************        战队主控->裁判系统       ***********************************/

/***********************************     战队主控->裁判系统   UI     ***********************************/
#define test 1

void UI_TX_Write_graphics_Delete_Init(graphic_delete_Typdef *graphic_delete)
{
	graphic_delete->layer = test;
	graphic_delete->operate_tpye = test;
}

/*调用该函数时先写一个UI_TX_Write_graphics_Delete_Init函数，初始化graphic_delete结构体的内容*/
void UI_TX_Write_graphics_Delete(	ALL_TX_Typdef *UI_TX ,
									enum Robot_ID_and_User_ID_Typdef sender_ID ,
									enum Robot_ID_and_User_ID_Typdef receiver_ID ,
									graphic_delete_Typdef *graphic_delete , 
									uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.graphic_delete);
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = erase;
	UI_TX->Data.receiver_ID = receiver_ID;
	UI_TX->Data.sender_ID = sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);
	
	/*********************自定义部分开始***********************/
	UI_TX->Data.User_UI.graphic_delete.layer = graphic_delete->layer;
	UI_TX->Data.User_UI.graphic_delete.operate_tpye = graphic_delete->operate_tpye;
	/*********************自定义部分结束***********************/
	
	memcpy(	&data_au8[13] , 
			&UI_TX->Data.User_UI.graphic_delete , 
			sizeof(UI_TX->Data.User_UI.graphic_delete));
	
	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_delete));

	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_delete)-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_delete)-2]);
			
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_delete));
}

ALL_TX_Typdef UI_TX;

void UI_TX_Write_graphics_One_Init(graphic_data_Typdef *graphic_data_1)
{
	graphic_data_1->color = test;
	graphic_data_1->details_a = test;
	graphic_data_1->details_b = test;
	graphic_data_1->details_c = test;
	graphic_data_1->graphic_name[0] = test;
	graphic_data_1->graphic_tpye = test;
	graphic_data_1->layer = test;
	graphic_data_1->operate_tpye = test;
	graphic_data_1->details_d = test;
	graphic_data_1->details_e = test;
	graphic_data_1->start_x = test;
	graphic_data_1->start_y = test;
	graphic_data_1->width = test;
}

void UI_TX_Write_graphics_One(	ALL_TX_Typdef *UI_TX ,
								enum Robot_ID_and_User_ID_Typdef sender_ID ,
								enum Robot_ID_and_User_ID_Typdef receiver_ID ,
								graphic_data_Typdef *graphic_data_1 ,
								uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.graphic_data_1);
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = Draw_graphics_1;
	UI_TX->Data.receiver_ID = receiver_ID;
	UI_TX->Data.sender_ID = sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);
	
	/*********************自定义部分开始***********************/
	UI_TX->Data.User_UI.graphic_data_1.color = graphic_data_1->color;
	UI_TX->Data.User_UI.graphic_data_1.details_a = graphic_data_1->details_a;
	UI_TX->Data.User_UI.graphic_data_1.details_b = graphic_data_1->details_b;
	UI_TX->Data.User_UI.graphic_data_1.details_c = graphic_data_1->details_c;
	UI_TX->Data.User_UI.graphic_data_1.graphic_name[0] = graphic_data_1->graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_1.graphic_tpye = graphic_data_1->graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_1.layer = graphic_data_1->layer;
	UI_TX->Data.User_UI.graphic_data_1.operate_tpye = graphic_data_1->operate_tpye;
	UI_TX->Data.User_UI.graphic_data_1.details_d = graphic_data_1->details_d;
	UI_TX->Data.User_UI.graphic_data_1.details_e = graphic_data_1->details_e;
	UI_TX->Data.User_UI.graphic_data_1.start_x = graphic_data_1->start_x;
	UI_TX->Data.User_UI.graphic_data_1.start_y = graphic_data_1->start_y;
	UI_TX->Data.User_UI.graphic_data_1.width = graphic_data_1->width;

	/*********************自定义部分结束***********************/
	
	memcpy(	&data_au8[13] , 
			&UI_TX->Data.User_UI.graphic_data_1 , 
			sizeof(UI_TX->Data.User_UI.graphic_data_1));
	
	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1));
			
	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1));
}

void UI_TX_Write_graphics_Two_Init(graphic_data_Typdef *graphic_data_2)
{
	graphic_data_2[0].color = test;
	graphic_data_2[0].details_a = test;
	graphic_data_2[0].details_b = test;
	graphic_data_2[0].details_c = test;
	graphic_data_2[0].graphic_name[0] = test;
	graphic_data_2[0].graphic_tpye = test;
	graphic_data_2[0].layer = test;
	graphic_data_2[0].operate_tpye = test;
	graphic_data_2[0].details_d = test;
	graphic_data_2[0].details_e = test;
	graphic_data_2[0].start_x = test;
	graphic_data_2[0].start_y = test;
	graphic_data_2[0].width = test;
	
	graphic_data_2[1].color = test;
	graphic_data_2[1].details_a = test;
	graphic_data_2[1].details_b = test;
	graphic_data_2[1].details_c = test;
	graphic_data_2[1].graphic_name[0] = test;
	graphic_data_2[1].graphic_tpye = test;
	graphic_data_2[1].layer = test;
	graphic_data_2[1].operate_tpye = test;
	graphic_data_2[1].details_d = test;
	graphic_data_2[1].details_e = test;
	graphic_data_2[1].start_x = test;
	graphic_data_2[1].start_y = test;
	graphic_data_2[1].width = test;
}

void UI_TX_Write_graphics_Two(	ALL_TX_Typdef *UI_TX ,
								enum Robot_ID_and_User_ID_Typdef sender_ID ,
								enum Robot_ID_and_User_ID_Typdef receiver_ID ,
								graphic_data_Typdef *graphic_data_2 ,
								uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*2;
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = (uint16_t)Draw_graphics_2;
	UI_TX->Data.receiver_ID = (uint16_t)receiver_ID;
	UI_TX->Data.sender_ID = (uint16_t)sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);
	
	/*********************自定义部分开始***********************/
	UI_TX->Data.User_UI.graphic_data_2[0].color = graphic_data_2[0].color;
	UI_TX->Data.User_UI.graphic_data_2[0].details_a = graphic_data_2[0].details_a;
	UI_TX->Data.User_UI.graphic_data_2[0].details_b = graphic_data_2[0].details_b;
	UI_TX->Data.User_UI.graphic_data_2[0].details_c = graphic_data_2[0].details_c;
	UI_TX->Data.User_UI.graphic_data_2[0].graphic_name[0] = graphic_data_2[0].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_2[0].graphic_tpye = graphic_data_2[0].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_2[0].layer = graphic_data_2[0].layer;
	UI_TX->Data.User_UI.graphic_data_2[0].operate_tpye = graphic_data_2[0].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_2[0].details_d = graphic_data_2[0].details_d;
	UI_TX->Data.User_UI.graphic_data_2[0].details_e = graphic_data_2[0].details_e;
	UI_TX->Data.User_UI.graphic_data_2[0].start_x = graphic_data_2[0].start_x;
	UI_TX->Data.User_UI.graphic_data_2[0].start_y = graphic_data_2[0].start_y;
	UI_TX->Data.User_UI.graphic_data_2[0].width = graphic_data_2[0].width;
	
	UI_TX->Data.User_UI.graphic_data_2[1].color = graphic_data_2[1].color;
	UI_TX->Data.User_UI.graphic_data_2[1].details_a = graphic_data_2[1].details_a;
	UI_TX->Data.User_UI.graphic_data_2[1].details_b = graphic_data_2[1].details_b;
	UI_TX->Data.User_UI.graphic_data_2[1].details_c = graphic_data_2[1].details_c;
	UI_TX->Data.User_UI.graphic_data_2[1].graphic_name[0] = graphic_data_2[1].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_2[1].graphic_tpye = graphic_data_2[1].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_2[1].layer = graphic_data_2[1].layer;
	UI_TX->Data.User_UI.graphic_data_2[1].operate_tpye = graphic_data_2[1].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_2[1].details_d = graphic_data_2[1].details_d;
	UI_TX->Data.User_UI.graphic_data_2[1].details_e = graphic_data_2[1].details_e;
	UI_TX->Data.User_UI.graphic_data_2[1].start_x = graphic_data_2[1].start_x;
	UI_TX->Data.User_UI.graphic_data_2[1].start_y = graphic_data_2[1].start_y;
	UI_TX->Data.User_UI.graphic_data_2[1].width = graphic_data_2[1].width;

	/*********************自定义部分结束***********************/
	
	memcpy(	&data_au8[13] , 
			UI_TX->Data.User_UI.graphic_data_2 , 
			sizeof(UI_TX->Data.User_UI.graphic_data_1)*2);
	
	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*2);
	
	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*2-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*2-2]);
			
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*2);
}

void UI_TX_Write_graphics_Five_Init(graphic_data_Typdef *graphic_data_5)
{
	graphic_data_5[0].color = test;
	graphic_data_5[0].details_a = test;
	graphic_data_5[0].details_b = test;
	graphic_data_5[0].details_c = test;
	graphic_data_5[0].graphic_name[0] = test;
	graphic_data_5[0].graphic_tpye = test;
	graphic_data_5[0].layer = test;
	graphic_data_5[0].operate_tpye = test;
	graphic_data_5[0].details_d = test;
	graphic_data_5[0].details_e = test;
	graphic_data_5[0].start_x = test;
	graphic_data_5[0].start_y = test;
	graphic_data_5[0].width = test;
	
	graphic_data_5[1].color = test;
	graphic_data_5[1].details_a = test;
	graphic_data_5[1].details_b = test;
	graphic_data_5[1].details_c = test;
	graphic_data_5[1].graphic_name[0] = test;
	graphic_data_5[1].graphic_tpye = test;
	graphic_data_5[1].layer = test;
	graphic_data_5[1].operate_tpye = test;
	graphic_data_5[1].details_d = test;
	graphic_data_5[1].details_e = test;
	graphic_data_5[1].start_x = test;
	graphic_data_5[1].start_y = test;
	graphic_data_5[1].width = test;
	
	graphic_data_5[2].color = test;
	graphic_data_5[2].details_a = test;
	graphic_data_5[2].details_b = test;
	graphic_data_5[2].details_c = test;
	graphic_data_5[2].graphic_name[0] = test;
	graphic_data_5[2].graphic_tpye = test;
	graphic_data_5[2].layer = test;
	graphic_data_5[2].operate_tpye = test;
	graphic_data_5[2].details_d = test;
	graphic_data_5[2].details_e = test;
	graphic_data_5[2].start_x = test;
	graphic_data_5[2].start_y = test;
	graphic_data_5[2].width = test;
	
	graphic_data_5[3].color = test;
	graphic_data_5[3].details_a = test;
	graphic_data_5[3].details_b = test;
	graphic_data_5[3].details_c = test;
	graphic_data_5[3].graphic_name[0] = test;
	graphic_data_5[3].graphic_tpye = test;
	graphic_data_5[3].layer = test;
	graphic_data_5[3].operate_tpye = test;
	graphic_data_5[3].details_d = test;
	graphic_data_5[3].details_e = test;
	graphic_data_5[3].start_x = test;
	graphic_data_5[3].start_y = test;
	graphic_data_5[3].width = test;
	
	graphic_data_5[4].color = test;
	graphic_data_5[4].details_a = test;
	graphic_data_5[4].details_b = test;
	graphic_data_5[4].details_c = test;
	graphic_data_5[4].graphic_name[0] = test;
	graphic_data_5[4].graphic_tpye = test;
	graphic_data_5[4].layer = test;
	graphic_data_5[4].operate_tpye = test;
	graphic_data_5[4].details_d = test;
	graphic_data_5[4].details_e = test;
	graphic_data_5[4].start_x = test;
	graphic_data_5[4].start_y = test;
	graphic_data_5[4].width = test;
}

void UI_TX_Write_graphics_Five(	ALL_TX_Typdef *UI_TX ,
								enum Robot_ID_and_User_ID_Typdef sender_ID ,
								enum Robot_ID_and_User_ID_Typdef receiver_ID ,
								graphic_data_Typdef *graphic_data_5 ,
								uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*5;
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = (uint16_t)Draw_graphics_5;
	UI_TX->Data.receiver_ID = (uint16_t)receiver_ID;
	UI_TX->Data.sender_ID = (uint16_t)sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);
	
	/*********************自定义部分开始***********************/
	UI_TX->Data.User_UI.graphic_data_5[0].color = graphic_data_5[0].color;
	UI_TX->Data.User_UI.graphic_data_5[0].details_a = graphic_data_5[0].details_a;
	UI_TX->Data.User_UI.graphic_data_5[0].details_b = graphic_data_5[0].details_b;
	UI_TX->Data.User_UI.graphic_data_5[0].details_c = graphic_data_5[0].details_c;
	UI_TX->Data.User_UI.graphic_data_5[0].graphic_name[0] = graphic_data_5[0].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_5[0].graphic_tpye = graphic_data_5[0].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_5[0].layer = graphic_data_5[0].layer;
	UI_TX->Data.User_UI.graphic_data_5[0].operate_tpye = graphic_data_5[0].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_5[0].details_d = graphic_data_5[0].details_d;
	UI_TX->Data.User_UI.graphic_data_5[0].details_e = graphic_data_5[0].details_e;
	UI_TX->Data.User_UI.graphic_data_5[0].start_x = graphic_data_5[0].start_x;
	UI_TX->Data.User_UI.graphic_data_5[0].start_y = graphic_data_5[0].start_y;
	UI_TX->Data.User_UI.graphic_data_5[0].width = graphic_data_5[0].width;
	
	UI_TX->Data.User_UI.graphic_data_5[1].color = graphic_data_5[1].color;
	UI_TX->Data.User_UI.graphic_data_5[1].details_a = graphic_data_5[1].details_a;
	UI_TX->Data.User_UI.graphic_data_5[1].details_b = graphic_data_5[1].details_b;
	UI_TX->Data.User_UI.graphic_data_5[1].details_c = graphic_data_5[1].details_c;
	UI_TX->Data.User_UI.graphic_data_5[1].graphic_name[0] = graphic_data_5[1].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_5[1].graphic_tpye = graphic_data_5[1].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_5[1].layer = graphic_data_5[1].layer;
	UI_TX->Data.User_UI.graphic_data_5[1].operate_tpye = graphic_data_5[1].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_5[1].details_d = graphic_data_5[1].details_d;
	UI_TX->Data.User_UI.graphic_data_5[1].details_e = graphic_data_5[1].details_e;
	UI_TX->Data.User_UI.graphic_data_5[1].start_x = graphic_data_5[1].start_x;
	UI_TX->Data.User_UI.graphic_data_5[1].start_y = graphic_data_5[1].start_y;
	UI_TX->Data.User_UI.graphic_data_5[1].width = graphic_data_5[1].width;
	
	UI_TX->Data.User_UI.graphic_data_5[2].color = graphic_data_5[2].color;
	UI_TX->Data.User_UI.graphic_data_5[2].details_a = graphic_data_5[2].details_a;
	UI_TX->Data.User_UI.graphic_data_5[2].details_b = graphic_data_5[2].details_b;
	UI_TX->Data.User_UI.graphic_data_5[2].details_c = graphic_data_5[2].details_c;
	UI_TX->Data.User_UI.graphic_data_5[2].graphic_name[0] = graphic_data_5[2].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_5[2].graphic_tpye = graphic_data_5[2].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_5[2].layer = graphic_data_5[2].layer;
	UI_TX->Data.User_UI.graphic_data_5[2].operate_tpye = graphic_data_5[2].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_5[2].details_d = graphic_data_5[2].details_d;
	UI_TX->Data.User_UI.graphic_data_5[2].details_e = graphic_data_5[2].details_e;
	UI_TX->Data.User_UI.graphic_data_5[2].start_x = graphic_data_5[2].start_x;
	UI_TX->Data.User_UI.graphic_data_5[2].start_y = graphic_data_5[2].start_y;
	UI_TX->Data.User_UI.graphic_data_5[2].width = graphic_data_5[2].width;
	
	UI_TX->Data.User_UI.graphic_data_5[3].color = graphic_data_5[3].color;
	UI_TX->Data.User_UI.graphic_data_5[3].details_a = graphic_data_5[3].details_a;
	UI_TX->Data.User_UI.graphic_data_5[3].details_b = graphic_data_5[3].details_b;
	UI_TX->Data.User_UI.graphic_data_5[3].details_c = graphic_data_5[3].details_c;
	UI_TX->Data.User_UI.graphic_data_5[3].graphic_name[0] = graphic_data_5[3].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_5[3].graphic_tpye = graphic_data_5[3].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_5[3].layer = graphic_data_5[3].layer;
	UI_TX->Data.User_UI.graphic_data_5[3].operate_tpye = graphic_data_5[3].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_5[3].details_d = graphic_data_5[3].details_d;
	UI_TX->Data.User_UI.graphic_data_5[3].details_e = graphic_data_5[3].details_e;
	UI_TX->Data.User_UI.graphic_data_5[3].start_x = graphic_data_5[3].start_x;
	UI_TX->Data.User_UI.graphic_data_5[3].start_y = graphic_data_5[3].start_y;
	UI_TX->Data.User_UI.graphic_data_5[3].width = graphic_data_5[3].width;
	
	UI_TX->Data.User_UI.graphic_data_5[4].color = graphic_data_5[4].color;
	UI_TX->Data.User_UI.graphic_data_5[4].details_a = graphic_data_5[4].details_a;
	UI_TX->Data.User_UI.graphic_data_5[4].details_b = graphic_data_5[4].details_b;
	UI_TX->Data.User_UI.graphic_data_5[4].details_c = graphic_data_5[4].details_c;
	UI_TX->Data.User_UI.graphic_data_5[4].graphic_name[0] = graphic_data_5[4].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_5[4].graphic_tpye = graphic_data_5[4].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_5[4].layer = graphic_data_5[4].layer;
	UI_TX->Data.User_UI.graphic_data_5[4].operate_tpye = graphic_data_5[4].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_5[4].details_d = graphic_data_5[4].details_d;
	UI_TX->Data.User_UI.graphic_data_5[4].details_e = graphic_data_5[4].details_e;
	UI_TX->Data.User_UI.graphic_data_5[4].start_x = graphic_data_5[4].start_x;
	UI_TX->Data.User_UI.graphic_data_5[4].start_y = graphic_data_5[4].start_y;
	UI_TX->Data.User_UI.graphic_data_5[4].width = graphic_data_5[4].width;

	/*********************自定义部分结束***********************/
	
	memcpy(	&data_au8[13] , 
			UI_TX->Data.User_UI.graphic_data_5 , 
			sizeof(UI_TX->Data.User_UI.graphic_data_1)*5);
	
	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*5);
	
	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*5-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*5-2]);
			
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*5);
}

void UI_TX_Write_graphics_Seven_Init(graphic_data_Typdef *graphic_data_7)
{
	graphic_data_7[0].color = test;
	graphic_data_7[0].details_a = test;
	graphic_data_7[0].details_b = test;
	graphic_data_7[0].details_c = test;
	graphic_data_7[0].graphic_name[0] = test;
	graphic_data_7[0].graphic_tpye = test;
	graphic_data_7[0].layer = test;
	graphic_data_7[0].operate_tpye = test;
	graphic_data_7[0].details_d = test;
	graphic_data_7[0].details_e = test;
	graphic_data_7[0].start_x = test;
	graphic_data_7[0].start_y = test;
	graphic_data_7[0].width = test;
	
	graphic_data_7[1].color = test;
	graphic_data_7[1].details_a = test;
	graphic_data_7[1].details_b = test;
	graphic_data_7[1].details_c = test;
	graphic_data_7[1].graphic_name[0] = test;
	graphic_data_7[1].graphic_tpye = test;
	graphic_data_7[1].layer = test;
	graphic_data_7[1].operate_tpye = test;
	graphic_data_7[1].details_d = test;
	graphic_data_7[1].details_e = test;
	graphic_data_7[1].start_x = test;
	graphic_data_7[1].start_y = test;
	graphic_data_7[1].width = test;
	
	graphic_data_7[2].color = test;
	graphic_data_7[2].details_a = test;
	graphic_data_7[2].details_b = test;
	graphic_data_7[2].details_c = test;
	graphic_data_7[2].graphic_name[0] = test;
	graphic_data_7[2].graphic_tpye = test;
	graphic_data_7[2].layer = test;
	graphic_data_7[2].operate_tpye = test;
	graphic_data_7[2].details_d = test;
	graphic_data_7[2].details_e = test;
	graphic_data_7[2].start_x = test;
	graphic_data_7[2].start_y = test;
	graphic_data_7[2].width = test;
	
	graphic_data_7[3].color = test;
	graphic_data_7[3].details_a = test;
	graphic_data_7[3].details_b = test;
	graphic_data_7[3].details_c = test;
	graphic_data_7[3].graphic_name[0] = test;
	graphic_data_7[3].graphic_tpye = test;
	graphic_data_7[3].layer = test;
	graphic_data_7[3].operate_tpye = test;
	graphic_data_7[3].details_d = test;
	graphic_data_7[3].details_e = test;
	graphic_data_7[3].start_x = test;
	graphic_data_7[3].start_y = test;
	graphic_data_7[3].width = test;
	
	graphic_data_7[4].color = test;
	graphic_data_7[4].details_a = test;
	graphic_data_7[4].details_b = test;
	graphic_data_7[4].details_c = test;
	graphic_data_7[4].graphic_name[0] = test;
	graphic_data_7[4].graphic_tpye = test;
	graphic_data_7[4].layer = test;
	graphic_data_7[4].operate_tpye = test;
	graphic_data_7[4].details_d = test;
	graphic_data_7[4].details_e = test;
	graphic_data_7[4].start_x = test;
	graphic_data_7[4].start_y = test;
	graphic_data_7[4].width = test;
	
	graphic_data_7[5].color = test;
	graphic_data_7[5].details_a = test;
	graphic_data_7[5].details_b = test;
	graphic_data_7[5].details_c = test;
	graphic_data_7[5].graphic_name[0] = test;
	graphic_data_7[5].graphic_tpye = test;
	graphic_data_7[5].layer = test;
	graphic_data_7[5].operate_tpye = test;
	graphic_data_7[5].details_d = test;
	graphic_data_7[5].details_e = test;
	graphic_data_7[5].start_x = test;
	graphic_data_7[5].start_y = test;
	graphic_data_7[5].width = test;
	
	graphic_data_7[6].color = test;
	graphic_data_7[6].details_a = test;
	graphic_data_7[6].details_b = test;
	graphic_data_7[6].details_c = test;
	graphic_data_7[6].graphic_name[0] = test;
	graphic_data_7[6].graphic_tpye = test;
	graphic_data_7[6].layer = test;
	graphic_data_7[6].operate_tpye = test;
	graphic_data_7[6].details_d = test;
	graphic_data_7[6].details_e = test;
	graphic_data_7[6].start_x = test;
	graphic_data_7[6].start_y = test;
	graphic_data_7[6].width = test;
}

void UI_TX_Write_graphics_Seven(	ALL_TX_Typdef *UI_TX ,
									enum Robot_ID_and_User_ID_Typdef sender_ID ,
									enum Robot_ID_and_User_ID_Typdef receiver_ID ,
									graphic_data_Typdef *graphic_data_7 ,
									uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*7;
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = (uint16_t)Draw_graphics_7;
	UI_TX->Data.receiver_ID = (uint16_t)receiver_ID;
	UI_TX->Data.sender_ID = (uint16_t)sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);
	
	/*********************自定义部分开始***********************/
	UI_TX->Data.User_UI.graphic_data_7[0].color = graphic_data_7[0].color;
	UI_TX->Data.User_UI.graphic_data_7[0].details_a = graphic_data_7[0].details_a;
	UI_TX->Data.User_UI.graphic_data_7[0].details_b = graphic_data_7[0].details_b;
	UI_TX->Data.User_UI.graphic_data_7[0].details_c = graphic_data_7[0].details_c;
	UI_TX->Data.User_UI.graphic_data_7[0].graphic_name[0] = graphic_data_7[0].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_7[0].graphic_tpye = graphic_data_7[0].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_7[0].layer = graphic_data_7[0].layer;
	UI_TX->Data.User_UI.graphic_data_7[0].operate_tpye = graphic_data_7[0].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_7[0].details_d = graphic_data_7[0].details_d;
	UI_TX->Data.User_UI.graphic_data_7[0].details_e = graphic_data_7[0].details_e;
	UI_TX->Data.User_UI.graphic_data_7[0].start_x = graphic_data_7[0].start_x;
	UI_TX->Data.User_UI.graphic_data_7[0].start_y = graphic_data_7[0].start_y;
	UI_TX->Data.User_UI.graphic_data_7[0].width = graphic_data_7[0].width;
	
	UI_TX->Data.User_UI.graphic_data_7[1].color = graphic_data_7[1].color;
	UI_TX->Data.User_UI.graphic_data_7[1].details_a = graphic_data_7[1].details_a;
	UI_TX->Data.User_UI.graphic_data_7[1].details_b = graphic_data_7[1].details_b;
	UI_TX->Data.User_UI.graphic_data_7[1].details_c = graphic_data_7[1].details_c;
	UI_TX->Data.User_UI.graphic_data_7[1].graphic_name[0] = graphic_data_7[1].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_7[1].graphic_tpye = graphic_data_7[1].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_7[1].layer = graphic_data_7[1].layer;
	UI_TX->Data.User_UI.graphic_data_7[1].operate_tpye = graphic_data_7[1].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_7[1].details_d = graphic_data_7[1].details_d;
	UI_TX->Data.User_UI.graphic_data_7[1].details_e = graphic_data_7[1].details_e;
	UI_TX->Data.User_UI.graphic_data_7[1].start_x = graphic_data_7[1].start_x;
	UI_TX->Data.User_UI.graphic_data_7[1].start_y = graphic_data_7[1].start_y;
	UI_TX->Data.User_UI.graphic_data_7[1].width = graphic_data_7[1].width;
	
	UI_TX->Data.User_UI.graphic_data_7[2].color = graphic_data_7[2].color;
	UI_TX->Data.User_UI.graphic_data_7[2].details_a = graphic_data_7[2].details_a;
	UI_TX->Data.User_UI.graphic_data_7[2].details_b = graphic_data_7[2].details_b;
	UI_TX->Data.User_UI.graphic_data_7[2].details_c = graphic_data_7[2].details_c;
	UI_TX->Data.User_UI.graphic_data_7[2].graphic_name[0] = graphic_data_7[2].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_7[2].graphic_tpye = graphic_data_7[2].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_7[2].layer = graphic_data_7[2].layer;
	UI_TX->Data.User_UI.graphic_data_7[2].operate_tpye = graphic_data_7[2].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_7[2].details_d = graphic_data_7[2].details_d;
	UI_TX->Data.User_UI.graphic_data_7[2].details_e = graphic_data_7[2].details_e;
	UI_TX->Data.User_UI.graphic_data_7[2].start_x = graphic_data_7[2].start_x;
	UI_TX->Data.User_UI.graphic_data_7[2].start_y = graphic_data_7[2].start_y;
	UI_TX->Data.User_UI.graphic_data_7[2].width = graphic_data_7[2].width;
	
	UI_TX->Data.User_UI.graphic_data_7[3].color = graphic_data_7[3].color;
	UI_TX->Data.User_UI.graphic_data_7[3].details_a = graphic_data_7[3].details_a;
	UI_TX->Data.User_UI.graphic_data_7[3].details_b = graphic_data_7[3].details_b;
	UI_TX->Data.User_UI.graphic_data_7[3].details_c = graphic_data_7[3].details_c;
	UI_TX->Data.User_UI.graphic_data_7[3].graphic_name[0] = graphic_data_7[3].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_7[3].graphic_tpye = graphic_data_7[3].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_7[3].layer = graphic_data_7[3].layer;
	UI_TX->Data.User_UI.graphic_data_7[3].operate_tpye = graphic_data_7[3].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_7[3].details_d = graphic_data_7[3].details_d;
	UI_TX->Data.User_UI.graphic_data_7[3].details_e = graphic_data_7[3].details_e;
	UI_TX->Data.User_UI.graphic_data_7[3].start_x = graphic_data_7[3].start_x;
	UI_TX->Data.User_UI.graphic_data_7[3].start_y = graphic_data_7[3].start_y;
	UI_TX->Data.User_UI.graphic_data_7[3].width = graphic_data_7[3].width;
	
	UI_TX->Data.User_UI.graphic_data_7[4].color = graphic_data_7[4].color;
	UI_TX->Data.User_UI.graphic_data_7[4].details_a = graphic_data_7[4].details_a;
	UI_TX->Data.User_UI.graphic_data_7[4].details_b = graphic_data_7[4].details_b;
	UI_TX->Data.User_UI.graphic_data_7[4].details_c = graphic_data_7[4].details_c;
	UI_TX->Data.User_UI.graphic_data_7[4].graphic_name[0] = graphic_data_7[4].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_7[4].graphic_tpye = graphic_data_7[4].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_7[4].layer = graphic_data_7[4].layer;
	UI_TX->Data.User_UI.graphic_data_7[4].operate_tpye = graphic_data_7[4].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_7[4].details_d = graphic_data_7[4].details_d;
	UI_TX->Data.User_UI.graphic_data_7[4].details_e = graphic_data_7[4].details_e;
	UI_TX->Data.User_UI.graphic_data_7[4].start_x = graphic_data_7[4].start_x;
	UI_TX->Data.User_UI.graphic_data_7[4].start_y = graphic_data_7[4].start_y;
	UI_TX->Data.User_UI.graphic_data_7[4].width = graphic_data_7[4].width;

	UI_TX->Data.User_UI.graphic_data_7[5].color = graphic_data_7[5].color;
	UI_TX->Data.User_UI.graphic_data_7[5].details_a = graphic_data_7[5].details_a;
	UI_TX->Data.User_UI.graphic_data_7[5].details_b = graphic_data_7[5].details_b;
	UI_TX->Data.User_UI.graphic_data_7[5].details_c = graphic_data_7[5].details_c;
	UI_TX->Data.User_UI.graphic_data_7[5].graphic_name[0] = graphic_data_7[5].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_7[5].graphic_tpye = graphic_data_7[5].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_7[5].layer = graphic_data_7[5].layer;
	UI_TX->Data.User_UI.graphic_data_7[5].operate_tpye = graphic_data_7[5].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_7[5].details_d = graphic_data_7[5].details_d;
	UI_TX->Data.User_UI.graphic_data_7[5].details_e = graphic_data_7[5].details_e;
	UI_TX->Data.User_UI.graphic_data_7[5].start_x = graphic_data_7[5].start_x;
	UI_TX->Data.User_UI.graphic_data_7[5].start_y = graphic_data_7[5].start_y;
	UI_TX->Data.User_UI.graphic_data_7[5].width = graphic_data_7[5].width;
	
	UI_TX->Data.User_UI.graphic_data_7[6].color = graphic_data_7[6].color;
	UI_TX->Data.User_UI.graphic_data_7[6].details_a = graphic_data_7[6].details_a;
	UI_TX->Data.User_UI.graphic_data_7[6].details_b = graphic_data_7[6].details_b;
	UI_TX->Data.User_UI.graphic_data_7[6].details_c = graphic_data_7[6].details_c;
	UI_TX->Data.User_UI.graphic_data_7[6].graphic_name[0] = graphic_data_7[6].graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_7[6].graphic_tpye = graphic_data_7[6].graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_7[6].layer = graphic_data_7[6].layer;
	UI_TX->Data.User_UI.graphic_data_7[6].operate_tpye = graphic_data_7[6].operate_tpye;
	UI_TX->Data.User_UI.graphic_data_7[6].details_d = graphic_data_7[6].details_d;
	UI_TX->Data.User_UI.graphic_data_7[6].details_e = graphic_data_7[6].details_e;
	UI_TX->Data.User_UI.graphic_data_7[6].start_x = graphic_data_7[6].start_x;
	UI_TX->Data.User_UI.graphic_data_7[6].start_y = graphic_data_7[6].start_y;
	UI_TX->Data.User_UI.graphic_data_7[6].width = graphic_data_7[6].width;
	/*********************自定义部分结束***********************/
	
	memcpy(	&data_au8[13] , 
			UI_TX->Data.User_UI.graphic_data_7 , 
			sizeof(UI_TX->Data.User_UI.graphic_data_1)*7);
	
	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*7);
	
	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*7-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*7-2]);
			
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_1)*7);
}

void UI_TX_Write_char_Init(graphic_data_Typdef *graphic_data_char)
{
	graphic_data_char->color = test;
	graphic_data_char->details_a = test;
	graphic_data_char->details_b = test;
	graphic_data_char->details_c = test;
	graphic_data_char->graphic_name[0] = test;
	graphic_data_char->graphic_tpye = test;
	graphic_data_char->layer = test;
	graphic_data_char->operate_tpye = test;
	graphic_data_char->details_d = test;
	graphic_data_char->details_e = test;
	graphic_data_char->start_x = test;
	graphic_data_char->start_y = test;
	graphic_data_char->width = test;
}

void UI_TX_Write_char(	ALL_TX_Typdef *UI_TX ,
						enum Robot_ID_and_User_ID_Typdef sender_ID ,
						enum Robot_ID_and_User_ID_Typdef receiver_ID ,
						graphic_data_Typdef *graphic_data_char ,
						uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.graphic_data_char);
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = Draw_character;
	UI_TX->Data.receiver_ID = receiver_ID;
	UI_TX->Data.sender_ID = sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);
	
	/*********************自定义部分开始***********************/
	UI_TX->Data.User_UI.graphic_data_char.color = graphic_data_char->color;
	UI_TX->Data.User_UI.graphic_data_char.details_a = graphic_data_char->details_a;
	UI_TX->Data.User_UI.graphic_data_char.details_b = graphic_data_char->details_b;
	UI_TX->Data.User_UI.graphic_data_char.details_c = graphic_data_char->details_c;
	UI_TX->Data.User_UI.graphic_data_char.graphic_name[0] = graphic_data_char->graphic_name[0];
	UI_TX->Data.User_UI.graphic_data_char.graphic_tpye = graphic_data_char->graphic_tpye;
	UI_TX->Data.User_UI.graphic_data_char.layer = graphic_data_char->layer;
	UI_TX->Data.User_UI.graphic_data_char.operate_tpye = graphic_data_char->operate_tpye;
	UI_TX->Data.User_UI.graphic_data_char.details_d = graphic_data_char->details_d;
	UI_TX->Data.User_UI.graphic_data_char.details_e = graphic_data_char->details_e;
	UI_TX->Data.User_UI.graphic_data_char.start_x = graphic_data_char->start_x;
	UI_TX->Data.User_UI.graphic_data_char.start_y = graphic_data_char->start_y;
	UI_TX->Data.User_UI.graphic_data_char.width = graphic_data_char->width;
	/*********************自定义部分结束***********************/
	
	memcpy(	&data_au8[13] , 
			&UI_TX->Data.User_UI.graphic_data_char , 
			sizeof(UI_TX->Data.User_UI.graphic_data_char));
	
	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_char));
			
	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_char)-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.graphic_data_char)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.graphic_data_char));
}

void Route_decisions_Init(sentry_cmd_t *Data)
{
	Data->Ranged_exchange_shots = test;
	Data->Read_strip_resurrection = test;
	Data->Redeem_amount = test;
	Data->Redeem_resurrection = test;
	Data->Remotely_exchange_HP = test;
	Data->retain = test;
}

void Route_decisions(	ALL_TX_Typdef *UI_TX ,
						enum Robot_ID_and_User_ID_Typdef sender_ID ,
						enum Robot_ID_and_User_ID_Typdef receiver_ID ,
						sentry_cmd_t *Data ,
						uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.sentry_cmd);
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = Sentinels_decisions;
	UI_TX->Data.receiver_ID = receiver_ID;
	UI_TX->Data.sender_ID = sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);

	UI_TX->Data.User_UI.sentry_cmd.Ranged_exchange_shots = Data->Ranged_exchange_shots;
	UI_TX->Data.User_UI.sentry_cmd.Read_strip_resurrection = Data->Read_strip_resurrection;
	UI_TX->Data.User_UI.sentry_cmd.Redeem_amount = Data->Redeem_amount;
	UI_TX->Data.User_UI.sentry_cmd.Redeem_resurrection = Data->Redeem_resurrection;
	UI_TX->Data.User_UI.sentry_cmd.Remotely_exchange_HP = Data->Remotely_exchange_HP;
	UI_TX->Data.User_UI.sentry_cmd.retain = Data->retain;
	memcpy(	&data_au8[13] , 
			&UI_TX->Data.User_UI.sentry_cmd , 
			sizeof(UI_TX->Data.User_UI.sentry_cmd));
	
	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.sentry_cmd));
			
	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.sentry_cmd)-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.sentry_cmd)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.sentry_cmd));
}

void Radar_decisions_Init(radar_cmd_t *Data)
{
	Data->radar_decisions = test;
}

void Radar_decisions(	ALL_TX_Typdef *UI_TX ,
						enum Robot_ID_and_User_ID_Typdef sender_ID ,
						enum Robot_ID_and_User_ID_Typdef receiver_ID ,
						radar_cmd_t *Data ,
						uint8_t *data_au8)
{
	UI_TX->frame_header.SOF = 0xA5;
	UI_TX->frame_header.DataLenth = 6 + sizeof(UI_TX->Data.User_UI.radar_cmd);
	UI_TX->frame_header.Seq = 1;
	memcpy(data_au8 , &UI_TX->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	
	UI_TX->cmd_id = (uint16_t)Robot_interaction_data;
	memcpy(&data_au8[5] , &UI_TX->cmd_id , 2);
	
	UI_TX->Data.data_cmd_id = Radars_decisions;
	UI_TX->Data.receiver_ID = receiver_ID;
	UI_TX->Data.sender_ID = sender_ID;
	memcpy(&data_au8[7] , &UI_TX->Data , 6);

	UI_TX->Data.User_UI.radar_cmd.radar_decisions = Data->radar_decisions;
	data_au8[13] = UI_TX->Data.User_UI.radar_cmd.radar_decisions;

	Append_CRC16_Check_Sum(data_au8 , 13 + sizeof(UI_TX->Data.User_UI.radar_cmd));
			
	UI_TX->frame_tail = (((uint16_t)data_au8[13 + sizeof(UI_TX->Data.User_UI.radar_cmd)-1])<<8) | 
						(data_au8[13 + sizeof(UI_TX->Data.User_UI.radar_cmd)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 13 + sizeof(UI_TX->Data.User_UI.radar_cmd));
}

/***********************************    战队主控->裁判系统    雷达    **********************************/
void Radar_UART_Transmit_Init(map_robot_data_t *Data)
{
	Data->target_robot_id = test;
	Data->target_position_x = test;
	Data->target_position_y = test;
}

void Radar_UART_Transmit(Radar_Typdef *Radar , map_robot_data_t *Data , uint8_t *data_au8)
{
	Radar->frame_header.SOF = 0xA5;
	Radar->frame_header.DataLenth = sizeof(Radar->Data);
	Radar->frame_header.Seq = 1;
	memcpy(data_au8 , &Radar->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	Radar->frame_header.CRC8 = data_au8[4];
	
	Radar->cmd_id = (uint16_t)minimap_RX;
	memcpy(&data_au8[5] , &Radar->cmd_id , 2);

	Radar->Data.target_robot_id = Data->target_robot_id;
	Radar->Data.target_position_x = Data->target_position_x;
	Radar->Data.target_position_y = Data->target_position_y;
	memcpy(&data_au8[7] , &Radar->Data , sizeof(Radar->Data));

	Append_CRC16_Check_Sum(data_au8 , 7 + sizeof(Radar->Data));
	Radar->frame_tail = (((uint16_t)data_au8[7 + sizeof(Radar->Data)-1])<<8) | 
						(data_au8[7 + sizeof(Radar->Data)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 7 + sizeof(Radar->Data));
}

/*******************************    战队主控->裁判系统    自定义控制器    *******************************/
void controller_UART_Transmit_Init(custom_robot_data_t *Data)
{
	memset(Data->data , 0 , 30);
}

void controller_UART_Transmit(controller_Typdef *controller , custom_robot_data_t *Data , uint8_t *data_au8)
{
	controller->frame_header.SOF = 0xA5;
	controller->frame_header.DataLenth = sizeof(controller->Data);
	controller->frame_header.Seq = 1;
	memcpy(data_au8 , &controller->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	controller->frame_header.CRC8 = data_au8[4];
	
	controller->cmd_id = (uint16_t)Customer_controller;
	memcpy(&data_au8[5] , &controller->cmd_id , 2);

	memcpy(controller->Data.data , Data->data , 30);
	memcpy(&data_au8[7] , &controller->Data , sizeof(controller->Data));

	Append_CRC16_Check_Sum(data_au8 , 7 + sizeof(controller->Data));
	controller->frame_tail = (((uint16_t)data_au8[7 + sizeof(controller->Data)-1])<<8) | 
								(data_au8[7 + sizeof(controller->Data)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 7 + sizeof(controller->Data));
}

/*********************************    战队主控->裁判系统    模拟键鼠    *********************************/
void Non_link_data_UART_Transmit_Init(custom_client_data_t *Data)
{
	Data->key_value 	= test;
	Data->mouse_left 	= test;
	Data->mouse_right 	= test;
	Data->reserved 		= test;
	Data->x_position 	= test;
	Data->y_position 	= test;
}

void Non_link_data_UART_Transmit(Non_link_data_Typdef *Non_link_data , custom_client_data_t *Data , uint8_t *data_au8)
{
	Non_link_data->frame_header.SOF = 0xA5;
	Non_link_data->frame_header.DataLenth = sizeof(Non_link_data->Data);
	Non_link_data->frame_header.Seq = 1;
	memcpy(data_au8 , &Non_link_data->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	Non_link_data->frame_header.CRC8 = data_au8[4];

	Non_link_data->cmd_id = (uint16_t)Non_link;
	memcpy(&data_au8[5] , &Non_link_data->cmd_id , 2);

	Non_link_data->Data.key_value 	= Data->key_value;
	Non_link_data->Data.mouse_left 	= Data->mouse_left;
	Non_link_data->Data.mouse_right = Data->mouse_right;
	Non_link_data->Data.reserved 	= Data->reserved;
	Non_link_data->Data.x_position 	= Data->x_position;
	Non_link_data->Data.y_position 	= Data->y_position;
	memcpy(&data_au8[7] , &Non_link_data->Data , sizeof(Non_link_data->Data));

	Append_CRC16_Check_Sum(data_au8 , 7 + sizeof(Non_link_data->Data));
	Non_link_data->frame_tail = (((uint16_t)data_au8[7 + sizeof(Non_link_data->Data)-1])<<8) | 
								(data_au8[7 + sizeof(Non_link_data->Data)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 7 + sizeof(Non_link_data->Data));
}

/*********************************    战队主控->裁判系统    哨兵回传    *********************************/
void Route_data_UART_Transmit_Init(map_data_t *Data , uint8_t frequency)
{
	Data->delta_x[frequency] = test;
	Data->delta_y[frequency] = test;
	Data->intention = test;
	Data->sender_id = test;
	Data->start_position_x = test;
	Data->start_position_y = test;
}

void Route_data_UART_Transmit(Route_data_Typdef *Route_data , map_data_t *Data , uint8_t *data_au8)
{
	Route_data->frame_header.SOF = 0xA5;
	Route_data->frame_header.DataLenth = sizeof(Route_data->Data);
	Route_data->frame_header.Seq = 1;
	memcpy(data_au8 , &Route_data->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	Route_data->frame_header.CRC8 = data_au8[4];

	Route_data->cmd_id = (uint16_t)Route_coordinates;
	memcpy(&data_au8[5] , &Route_data->cmd_id , 2);

	Route_data->Data.intention = Data->intention;
	Route_data->Data.sender_id = Data->sender_id;
	Route_data->Data.start_position_x = Data->start_position_x;
	Route_data->Data.start_position_y = Data->start_position_y;
	memcpy(Route_data->Data.delta_x , Data->delta_x , 49);
	memcpy(Route_data->Data.delta_y , Data->delta_y , 49);
	memcpy(&data_au8[7] , &Route_data->Data , sizeof(Route_data->Data));

	Append_CRC16_Check_Sum(data_au8 , 7 + sizeof(Route_data->Data));
	Route_data->frame_tail = (((uint16_t)data_au8[7 + sizeof(Route_data->Data)-1])<<8) | 
								(data_au8[7 + sizeof(Route_data->Data)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 7 + sizeof(Route_data->Data));
}

/*********************************    战队主控->裁判系统    任意车回传    *******************************/
void Customized_UART_Transmit_Init(custom_info_t *Data)
{
	Data->sender_id = test;
	Data->receiver_id = test;
	memset(Data->user_data , 0 , 30);
}

void Customized_UART_Transmit(Customized_Typdef *Customized , custom_info_t *Data , uint8_t *data_au8)
{
	Customized->frame_header.SOF = 0xA5;
	Customized->frame_header.DataLenth = sizeof(Customized->Data);
	Customized->frame_header.Seq = 1;
	memcpy(data_au8 , &Customized->frame_header , 5);
	Append_CRC8_Check_Sum(data_au8 , 5);
	Customized->frame_header.CRC8 = data_au8[4];

	Customized->cmd_id = (uint16_t)Customized_messages;
	memcpy(&data_au8[5] , &Customized->cmd_id , 2);

	Customized->Data.sender_id = Data->sender_id;
	Customized->Data.receiver_id = Data->receiver_id;
	memcpy(Customized->Data.user_data , Data->user_data , 30);
	memcpy(&data_au8[7] , &Customized->Data , sizeof(Customized->Data));

	Append_CRC16_Check_Sum(data_au8 , 7 + sizeof(Customized->Data));
	Customized->frame_tail = (((uint16_t)data_au8[7 + sizeof(Customized->Data)-1])<<8) | 
								(data_au8[7 + sizeof(Customized->Data)-2]);
	
	HAL_UART_Transmit_DMA(&huart4 , data_au8 , 7 + sizeof(Customized->Data));
}

/***********************************    战队主控->裁判系统   end    ***********************************/
