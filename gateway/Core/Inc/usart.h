/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define UART_DMA_REC_SIZE 128
#define UART_REC_SIZE     128

typedef struct 
{
  uint8_t  UART_RecFlag;
  uint16_t UART_DMA_RecLen;
  uint16_t UART_RecLen;
  uint8_t  UART_DMARecBuffer[UART_DMA_REC_SIZE];
  uint8_t  UART_RecBuffer[UART_REC_SIZE];
}UART_TypeDef;
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
extern UART_TypeDef UART_Type;
extern uint8_t UART_ReceiveString(uint8_t *Rx_Buffer);
void QK_SZ1(void);	//清空接收串口1数组程序
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

