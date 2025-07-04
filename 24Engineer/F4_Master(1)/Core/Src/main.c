/* USER CODE BEGIN Header */

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "crc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "RUI_CAN.h"
#include "stdio.h"
#include "RUI_ROOT_INIT.h"
#include "FFC.h"
#include "bsp_dwt.h"
#include "RUI_DBUS.h"
#include "RUI_MOTOR.h"
#include "RUI_ANONYMITY.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_TIM11_Init();
  MX_TIM9_Init();
  MX_TIM10_Init();
  MX_UART4_Init();
  MX_TIM12_Init();
  MX_UART7_Init();
  /* USER CODE BEGIN 2 */
  //DTW初始化
  DWT_Init(168);
  
  //CAN初始化
  CAN_Filter_Init();
  
  //发送任务定时器
  HAL_TIM_Base_Start_IT(&htim9);
  HAL_TIM_Base_Start_IT(&htim10);
  HAL_TIM_Base_Start_IT(&htim11);
  
  //图传舵机
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
  
  //抬升复位，读PD11、PD14
  HAL_GPIO_WritePin(GPIOD , GPIO_PIN_10 , GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD , GPIO_PIN_12 , GPIO_PIN_RESET);
  
  HAL_GPIO_WritePin(GPIOD , GPIO_PIN_13 , GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD , GPIO_PIN_15 , GPIO_PIN_RESET);
  
  //前伸、横移复位，读PD4、PD6
  HAL_GPIO_WritePin(GPIOC , GPIO_PIN_11 , GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD , GPIO_PIN_2 , GPIO_PIN_RESET);
  
  RUI_V_CONTAL.TUCHUAN.pitch = WHW_DF_MG995_Pitch_up;
  RUI_V_CONTAL.TUCHUAN.yaw = WHW_DF_MG995_Yaw_up;
  
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  if (__HAL_UART_GET_FLAG(&huart4 , UART_FLAG_IDLE) == 1)
//	  HAL_UART_DMAStop(&huart4);
//    HAL_UART_Receive_DMA(&huart4 , receive.Data , 13);
//	RUI_V_Crotral_ONLINE_JUDGE_TIME = RUI_DF_Crotral_OFFLINE_TIME;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint8_t flag;
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM11){
	RUI_F_ROOT();
	HAL_UART_Transmit_DMA(&huart2,RUI_V_COMMUNICATION.Data,sizeof(RUI_V_COMMUNICATION.Data));
  }
  
  if (htim->Instance == TIM10){
	
    //CAN2发送（抬升、前伸）
    RUI_F_CAN_SEDN(&hcan2,0x200,					
				RUI_V_MOTOR_HORIZONTAL_L.PID_S.All_out	+ FFC_ALL.HORIZONTAL_L.Output,
				RUI_V_MOTOR_HORIZONTAL_R.PID_S.All_out 	+ FFC_ALL.HORIZONTAL_R.Output,
				RUI_V_MOTOR_LIFT_L.PID_S.All_out 		+ FFC_ALL.LIFT_L.Output,
				RUI_V_MOTOR_LIFT_R.PID_S.All_out		+ FFC_ALL.LIFT_R.Output);
	
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_3 , RUI_V_CONTAL.HEAD.CUP_PUMP);

    //CAN1发送（横移,差动,Yaw）
	RUI_F_CAN_SEDN(&hcan1,0x1ff,
				RUI_V_MOTOR_SWAY.PID_S.All_out+FFC_ALL.SWAY.Output,
				RUI_V_MOTOR_Left.PID_S.All_out,
				RUI_V_MOTOR_Right.PID_S.All_out,
				RUI_V_MOTOR_Yaw.PID_S.All_out);
	  
	Micro.LIFT_L = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_11);//set:1
	Micro.LIFT_R = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_14);//set:0
	Micro.SWAY_B   = HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6);//set:1
	Micro.SWAY_E = 1;//set:0
	
	__HAL_TIM_SET_COMPARE(&htim12 , TIM_CHANNEL_1 , RUI_V_CONTAL.TUCHUAN.yaw);//Yaw:向前，左加右减
	__HAL_TIM_SET_COMPARE(&htim12 , TIM_CHANNEL_2 , RUI_V_CONTAL.TUCHUAN.pitch);//Pitch:平视，下减上加
	
//	RUI_F_ANONYMITY_TX(RUI_V_CONTAL.User.Pitch , RUI_V_CONTAL.User.Roll , RUI_V_CONTAL.User.Yaw ,0,0,0,0,0,0);
	
  }
  if (htim->Instance == TIM9){
	flag++;
    if(flag > 5)
    {
	   RUI_F_CAN_SEDN(&hcan1,0x200,
				RUI_V_MOTOR_Camera.PID_S.All_out,
				0,
				0,
				0);
	   flag = 0;
    }
	  
	}

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
