/**
 * @brief          前馈控制初始化
 * @param[in]      前馈控制结构体
 * @param[in]      略
 * @retval         返回空
 */
 #include "main.h"
 #include "user_lib.h"
 #include "FFC.h"
 #include "bsp_dwt.h"
 
struct FFC_ALL_Typdef FFC_ALL;
 
void Feedforward_Init(
    Feedforward_t *ffc,
    float max_out,
    float *c,
    float lpf_rc,
    uint16_t ref_dot_ols_order,
    uint16_t ref_ddot_ols_order)
{
    ffc->MaxOut = max_out;

    // 设置前馈控制器参数 详见前馈控制结构体定义
    // set parameters of feed-forward controller (see struct definition)
    if (c != NULL && ffc != NULL)
    {
        ffc->c[0] = c[0];
        ffc->c[1] = c[1];
        ffc->c[2] = c[2];
    }
    else
    {
        ffc->c[0] = 0;
        ffc->c[1] = 0;
        ffc->c[2] = 0;
        ffc->MaxOut = 0;
    }

    ffc->LPF_RC = lpf_rc;

    // 最小二乘提取信号微分初始化
    // differential signal is distilled by OLS
    ffc->Ref_dot_OLS_Order = ref_dot_ols_order;
    ffc->Ref_ddot_OLS_Order = ref_ddot_ols_order;
    if (ref_dot_ols_order > 2)
        OLS_Init(&ffc->Ref_dot_OLS, ref_dot_ols_order);
    if (ref_ddot_ols_order > 2)
        OLS_Init(&ffc->Ref_ddot_OLS, ref_ddot_ols_order);

    ffc->DWT_CNT = 0;

    ffc->Output = 0;
}

	/**
 * @brief          PID计算
 * @param[in]      PID结构体
 * @param[in]      测量值
 * @param[in]      期望值
 * @retval         返回空
 */
float Feedforward_Calculate(Feedforward_t *ffc, float ref)
{
	//求离散后的单位时间
    ffc->dt = DWT_GetDeltaT((void *)&ffc->DWT_CNT);
	//将设定值进行一阶低通滤波
    ffc->Ref = ref * ffc->dt / (ffc->LPF_RC + ffc->dt) +
               ffc->Ref * ffc->LPF_RC / (ffc->LPF_RC + ffc->dt);
    /*公式解析
    ffc->Ref = ref * ffc->dt / (ffc->LPF_RC + ffc->dt) + ffc->Ref * ffc->LPF_RC / (ffc->LPF_RC + ffc->dt);
             = ref * (1/(LPF_RC/ffc->dt + 1)) + ffc->Ref * (1/(ffc->dt/LPF_RC + 1))
             = ref * A + ffc->Ref * (1-A)
    A   = 1/(LPF_RC/ffc->dt + 1)
    1-A = 1/(ffc->dt/LPF_RC + 1)
    注：https://blog.csdn.net/qq_37662088/article/details/125075600
    */

    // 计算一阶导数
    // calculate first derivative
    if (ffc->Ref_dot_OLS_Order > 2)//如果样本数量大于两个，则采用最小二乘法估计，这里不采用
        ffc->Ref_dot = OLS_Derivative(&ffc->Ref_dot_OLS, ffc->dt, ffc->Ref);
    else
        ffc->Ref_dot = (ffc->Ref - ffc->Last_Ref) / ffc->dt;
    // 计算二阶导数
    // calculate second derivative
    if (ffc->Ref_ddot_OLS_Order > 2)//如果样本数量大于两个，则采用最小二乘法估计，这里不采用
        ffc->Ref_ddot = OLS_Derivative(&ffc->Ref_ddot_OLS, ffc->dt, ffc->Ref_dot);
    else
        ffc->Ref_ddot = (ffc->Ref_dot - ffc->Last_Ref_dot) / ffc->dt;
    // 计算前馈控制输出
    // calculate feed-forward controller output
    ffc->Output = ffc->c[0] * ffc->Ref + ffc->c[1] * ffc->Ref_dot + ffc->c[2] * ffc->Ref_ddot;

    ffc->Output = float_constrain(ffc->Output, -ffc->MaxOut, ffc->MaxOut);

    ffc->Last_Ref = ffc->Ref;
	
    ffc->Last_Ref_dot = ffc->Ref_dot;

    return ffc->Output;
}


