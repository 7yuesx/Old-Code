/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LIFT_L_H_Pin GPIO_PIN_10
#define LIFT_L_H_GPIO_Port GPIOD
#define LIFT_R_R_Pin GPIO_PIN_11
#define LIFT_R_R_GPIO_Port GPIOD
#define LIFT_L_L_Pin GPIO_PIN_12
#define LIFT_L_L_GPIO_Port GPIOD
#define LIFT_R_H_Pin GPIO_PIN_13
#define LIFT_R_H_GPIO_Port GPIOD
#define LIFT_L_R_Pin GPIO_PIN_14
#define LIFT_L_R_GPIO_Port GPIOD
#define LIFT_R_L_Pin GPIO_PIN_15
#define LIFT_R_L_GPIO_Port GPIOD
#define HORI_SWAY_H_Pin GPIO_PIN_11
#define HORI_SWAY_H_GPIO_Port GPIOC
#define HORI_SWAY_L_Pin GPIO_PIN_2
#define HORI_SWAY_L_GPIO_Port GPIOD
#define HORI_R_Pin GPIO_PIN_4
#define HORI_R_GPIO_Port GPIOD
#define SWAY_Pin GPIO_PIN_6
#define SWAY_GPIO_Port GPIOD
#define LED_G_Pin GPIO_PIN_8
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_9
#define LED_B_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_0
#define LED_R_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
