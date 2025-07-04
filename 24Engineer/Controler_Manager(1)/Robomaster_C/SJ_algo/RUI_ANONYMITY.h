#ifndef RUI_ANONYMITY_H
#define RUI_ANONYMITY_H
#include "stdint.h"

union ANONYMITY_UNION_Typdef // 使用共用体整合数据
{
    struct
    {
        uint8_t HEAD;
        uint8_t D_ADDR;
        uint8_t ID;
        uint8_t LEN;

        int16_t NUM1;
        int16_t NUM2;
        int16_t NUM3;
        int16_t NUM4;
        int16_t NUM5;
        int16_t NUM6;
        int16_t NUM7;
        int16_t NUM8;
        int16_t NUM9;

        uint8_t SUMCHECK;
        uint8_t ADDCHECK;
    }TX;
    uint8_t DATA[24];
};

void RUI_F_ANONYMITY_TX(int16_t NUM1 , int16_t NUM2 , int16_t NUM3 , int16_t NUM4 , int16_t NUM5 , int16_t NUM6 , int16_t NUM7 , int16_t NUM8 , int16_t NUM9);
//升降电机PID匿名
void RUI_F_AN_REVOLVE(void);
#endif
