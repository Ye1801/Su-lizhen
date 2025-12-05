/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define GPIO5_Pin GPIO_PIN_13
#define GPIO5_GPIO_Port GPIOC
#define ADC1_Pin GPIO_PIN_0
#define ADC1_GPIO_Port GPIOA
#define ADC2_Pin GPIO_PIN_1
#define ADC2_GPIO_Port GPIOA
#define ADC3_Pin GPIO_PIN_4
#define ADC3_GPIO_Port GPIOA
#define ADC4_Pin GPIO_PIN_5
#define ADC4_GPIO_Port GPIOA
#define MOTOR1_Pin GPIO_PIN_6
#define MOTOR1_GPIO_Port GPIOA
#define MOTOR2_Pin GPIO_PIN_7
#define MOTOR2_GPIO_Port GPIOA
#define MOTOR3_Pin GPIO_PIN_0
#define MOTOR3_GPIO_Port GPIOB
#define MOTOR4_Pin GPIO_PIN_1
#define MOTOR4_GPIO_Port GPIOB
#define GPIO6_Pin GPIO_PIN_2
#define GPIO6_GPIO_Port GPIOB
#define GPIO1_Pin GPIO_PIN_12
#define GPIO1_GPIO_Port GPIOB
#define GPIO1_EXTI_IRQn EXTI15_10_IRQn
#define CAPTURE1_Pin GPIO_PIN_8
#define CAPTURE1_GPIO_Port GPIOA
#define CAPTURE2_Pin GPIO_PIN_9
#define CAPTURE2_GPIO_Port GPIOA
#define GPIO2_Pin GPIO_PIN_10
#define GPIO2_GPIO_Port GPIOA
#define GPIO2_EXTI_IRQn EXTI15_10_IRQn
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SERVO1_Pin GPIO_PIN_15
#define SERVO1_GPIO_Port GPIOA
#define SERVO2_Pin GPIO_PIN_3
#define SERVO2_GPIO_Port GPIOB
#define GPIO3_Pin GPIO_PIN_4
#define GPIO3_GPIO_Port GPIOB
#define GPIO4_Pin GPIO_PIN_5
#define GPIO4_GPIO_Port GPIOB
#define LOG_TX_Pin GPIO_PIN_6
#define LOG_TX_GPIO_Port GPIOB
#define LOG_RX_Pin GPIO_PIN_7
#define LOG_RX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define UART1_REC_MAX (256)
#define UART2_REC_MAX (256)
#define UART3_REC_MAX (256)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
