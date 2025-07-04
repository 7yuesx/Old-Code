/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2024-04-09 13:26:42
 * @LastEditors: Andy
 * @LastEditTime: 2024-05-04 14:42:50
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
#ifndef RUI_MATH_H
#define RUI_MATH_H
#include "stdint.h"
int16_t RUI_F_MATH_ABS_int16_t(int16_t DATA);
int32_t RUI_F_MATH_ABS_int32_t(int32_t DATA);
float RUI_F_MATH_ABS_float(float DATA);
float RUI_F_MATH_Limit_float(float MAX , float MIN , float DATA);
int16_t RUI_F_MATH_Limit_int16(int16_t MAX , int16_t MIN , int16_t DATA);
int16_t RUI_F_MATH_Limit_int8(int8_t MAX , int8_t MIN , int8_t DATA);
float RUI_F_MATH_INV_SQRT_float(float DATA);
float uint_to_float(int16_t x_int, float span, int16_t value);
#endif
