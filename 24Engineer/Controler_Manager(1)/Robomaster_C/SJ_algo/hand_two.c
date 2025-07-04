#include "hand_two.h"
#include "ins_task.h"
#include "math.h"

#define PAI 3.1415926f

float XYZ[3];
int8_t flag;

void readX()
{
	//决定flag的值，0、1、-1。
}

void bei_yong()
{
	/*横移*/XYZ[0] = sinf((-INS.Yaw)*(PAI/180.0f));// + sinf(INS.Roll*(PAI/180.0f)) * sinf(INS.Pitch*(PAI/180.0f));//决定左右方向
	/*升降*/XYZ[1] = sinf(INS.Pitch*(PAI/180.0f));// * cosf(INS.Roll*(PAI/180.0f));//决定上下方向
	/*前伸*/XYZ[2] = cosf(INS.Pitch*(PAI/180.0f)) * cosf(INS.Yaw*(PAI/180.0f));// + sinf(INS.Roll*(PAI/180.0f)) * sinf(INS.Pitch*(PAI/180.0f));//决定前后方向
}

