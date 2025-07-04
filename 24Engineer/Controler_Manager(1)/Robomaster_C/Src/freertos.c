/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "QuaternionEKF.h"
#include "ins_task.h"
#include "RUI_ALLUI.h"
#include "RUI_ANONYMITY.h"
#include "handle.h"
#include "hand_two.h"
#include "Receive.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId INSTaskHandle;
osThreadId classis_taskHandle;
osThreadId to_gimbal_taskHandle;
osThreadId juc_sys_taskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartINSTask(void const * argument);
void classis_(void const * argument);
void to_gimbal(void const * argument);
void juc_sys(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer = &xTimerStack[0];
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
    /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of INSTask */
  osThreadDef(INSTask, StartINSTask, osPriorityNormal, 0, 1024);
  INSTaskHandle = osThreadCreate(osThread(INSTask), NULL);

  /* definition and creation of classis_task */
  osThreadDef(classis_task, classis_, osPriorityIdle, 0, 512);
  classis_taskHandle = osThreadCreate(osThread(classis_task), NULL);

  /* definition and creation of to_gimbal_task */
  osThreadDef(to_gimbal_task, to_gimbal, osPriorityIdle, 0, 256);
  to_gimbal_taskHandle = osThreadCreate(osThread(to_gimbal_task), NULL);

  /* definition and creation of juc_sys_task */
  osThreadDef(juc_sys_task, juc_sys, osPriorityIdle, 0, 256);
  juc_sys_taskHandle = osThreadCreate(osThread(juc_sys_task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartINSTask */
/**
 * @brief Function implementing the INSTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartINSTask */
void StartINSTask(void const * argument)
{
  /* USER CODE BEGIN StartINSTask */
    INS_Init();
    /* Infinite loop */
    for (;;)
    {
        INS_Task();
        osDelay(1);
    }
  /* USER CODE END StartINSTask */
}

/* USER CODE BEGIN Header_classis_ */
/**
* @brief Function implementing the classis_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_classis_ */
__weak void classis_(void const * argument)
{
  /* USER CODE BEGIN classis_ */
//	Calibrate();
  /* Infinite loop */
  for(;;)
  {
//	hand();
//	bei_yong();
    osDelay(1);
  }
  /* USER CODE END classis_ */
}

/* USER CODE BEGIN Header_to_gimbal */
/**
* @brief Function implementing the to_gimbal_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_to_gimbal */
__weak void to_gimbal(void const * argument)
{
  /* USER CODE BEGIN to_gimbal */
  /* Infinite loop */
  for(;;)
  {
//	Usart1_TX_staticUI();
//	RUI_F_AN_REVOLVE();
    osDelay(1);
  }
  /* USER CODE END to_gimbal */
}

/* USER CODE BEGIN Header_juc_sys */
/**
* @brief Function implementing the juc_sys_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_juc_sys */
__weak void juc_sys(void const * argument)
{
  /* USER CODE BEGIN juc_sys */
  /* Infinite loop */
  for(;;)
  {
	
    osDelay(1);
  }
  /* USER CODE END juc_sys */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
