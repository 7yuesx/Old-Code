/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2023-12-31 13:49:55
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:49:55
 */
/*
____/\\\\\\\\\_____        __/\\\________/\\\_        __/\\\\\\\\\\\_
 __/\\\///////\\\___        _\/\\\_______\/\\\_        _\/////\\\///__
  _\/\\\_____\/\\\___        _\/\\\_______\/\\\_        _____\/\\\_____
   _\/\\\\\\\\\\\/____        _\/\\\_______\/\\\_        _____\/\\\_____
    _\/\\\//////\\\____        _\/\\\_______\/\\\_        _____\/\\\_____
     _\/\\\____\//\\\___        _\/\\\_______\/\\\_        _____\/\\\_____
      _\/\\\_____\//\\\__        _\//\\\______/\\\__        _____\/\\\_____
       _\/\\\______\//\\\_        __\///\\\\\\\\\/___        __/\\\\\\\\\\\_
        _\///________\///__        ____\/////////_____        _\///////////__
*/
#include "RUI_IRQHANDLER.h"
#include "Write_Data.h"
#include "UI_TX_task.h"

uint8_t data_au8[255];
/************************************************************万能分隔符**************************************************************
 * 	@author:			//小瑞
 *	@performance:	    //定时器回调函数
 *	@parameter:		    //
 *	@time:				//23-04-27 16:55
 *	@ReadMe:			//
 ************************************************************万能分隔符**************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim->Instance == TIM11)
    {
        RUI_F_ROOT();
        UI_TX_Write_graphics_One(&UI_TX , Robot_hero_red , User_hero_red , &graphic_data_1 , data_au8);
    }
    if (htim->Instance == TIM13)
    {
        RUI_F_TOTAL_CONTRAL();
    }

}
