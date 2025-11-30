#include "led.h"


/*
**********************************************************************************************************
led1初始化配置
**********************************************************************************************************
*/
void led1_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED1_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);

  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}
/*
**********************************************************************************************************
led2初始化配置
**********************************************************************************************************
*/
void led2_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED2_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET);
	
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI1_IRQn);

}
/*
**********************************************************************************************************
led3初始化配置
**********************************************************************************************************
*/
void led3_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED3_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
**********************************************************************************************************
led4初始化配置
**********************************************************************************************************
*/
void led4_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED4_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_SET);
	
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
**********************************************************************************************************
led5初始化配置
**********************************************************************************************************
*/
void led5_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED5_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED5_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED5_PORT, LED5_PIN, GPIO_PIN_SET);


  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
**********************************************************************************************************
led6初始化配置
**********************************************************************************************************
*/
void led6_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED6_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED6_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED6_PORT, LED6_PIN, GPIO_PIN_SET);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI2_IRQn);
}
/*
**********************************************************************************************************
led1控制，1为亮，0为灭
**********************************************************************************************************
*/
void led1_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
	}
}
/*
**********************************************************************************************************
led2控制，1为亮，0为灭
**********************************************************************************************************
*/
void led2_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);
	}
}
/*
**********************************************************************************************************
led3控制，1为亮，0为灭
**********************************************************************************************************
*/
void led3_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_RESET);
	}
}
/*
**********************************************************************************************************
led4控制，1为亮，0为灭
**********************************************************************************************************
*/
void led4_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_RESET);
	}
}
/*
**********************************************************************************************************
led5控制，1为亮，0为灭
**********************************************************************************************************
*/
void led5_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(LED5_PORT, LED5_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(LED5_PORT, LED5_PIN, GPIO_PIN_RESET);
	}
}
/*
**********************************************************************************************************
led6控制，1为亮，0为灭
**********************************************************************************************************
*/
void led6_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(LED6_PORT, LED6_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(LED6_PORT, LED6_PIN, GPIO_PIN_RESET);
	}
}
/*
**********************************************************************************************************
led1控制，1为亮，0为灭
**********************************************************************************************************
*/
void led1_board_toggle(void) {
  HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
}
/*
**********************************************************************************************************
led2控制，1为亮，0为灭
**********************************************************************************************************
*/
void led2_board_toggle(void) {
  HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
}
/*
**********************************************************************************************************
led3控制，1为亮，0为灭
**********************************************************************************************************
*/
void led3_board_toggle(void) {
  HAL_GPIO_TogglePin(LED3_PORT, LED3_PIN);
}
/*
**********************************************************************************************************
led4控制，1为亮，0为灭
**********************************************************************************************************
*/
void led4_board_toggle(void) {
  HAL_GPIO_TogglePin(LED4_PORT, LED4_PIN);
}
/*
**********************************************************************************************************
led5控制，1为亮，0为灭
**********************************************************************************************************
*/
void led5_board_toggle(void) {
  HAL_GPIO_TogglePin(LED5_PORT, LED5_PIN);
}
/*
**********************************************************************************************************
led6控制，1为亮，0为灭
**********************************************************************************************************
*/
void led6_board_toggle(void) {
  HAL_GPIO_TogglePin(LED6_PORT, LED6_PIN);
}

