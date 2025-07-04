/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-01-28 10:27:35
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:52:18
 */
#include "UI_TX_task.h"
#include "Write_Data.h"


graphic_data_Typdef graphic_data_1;

void UI_TX_Write_graphics_One_Transmit(graphic_data_Typdef *graphic_data_1)
{
	graphic_data_1->color = 0;
	graphic_data_1->details_a = 0;
	graphic_data_1->details_b = 0;
	graphic_data_1->details_c = 0;
	graphic_data_1->graphic_name[0] = (uint8_t)8;
	graphic_data_1->graphic_tpye = 0;
	graphic_data_1->layer = 6;
	graphic_data_1->operate_tpye = 1;
	graphic_data_1->details_d = 1052;
	graphic_data_1->details_e = 1494;
	graphic_data_1->start_x = 652;
	graphic_data_1->start_y = 1094;
	graphic_data_1->width = 6;

}


