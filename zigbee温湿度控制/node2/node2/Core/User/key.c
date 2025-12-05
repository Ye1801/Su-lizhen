#include "key.h"


/*
**********************************************************************************************************
按键1初始化
**********************************************************************************************************
*/
void key1_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY1_PORT, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
**********************************************************************************************************
按键2初始化
**********************************************************************************************************
*/
void key2_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY2_PORT, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
**********************************************************************************************************
按键3初始化
**********************************************************************************************************
*/
void key3_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY3_PORT, &GPIO_InitStruct);
	
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI4_IRQn);
}
/*
**********************************************************************************************************
按键4初始化
**********************************************************************************************************
*/
void key4_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY4_PORT, &GPIO_InitStruct);
	
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}
/*
**********************************************************************************************************
按键5初始化
**********************************************************************************************************
*/
void key5_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY5_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY5_PORT, &GPIO_InitStruct);
	
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
**********************************************************************************************************
按键6初始化
**********************************************************************************************************
*/
void key6_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY6_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY6_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI2_IRQn);
}
/*
**********************************************************************************************************
按键1键值
**********************************************************************************************************
*/
int key1_get(void) {
	
	uint8_t key_value =0;
	
	if (HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN) == 0) {
		HAL_Delay(5); 
		if(HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN) == 0){
		  key_value =1;
		}
	}
	return key_value;
}
/*
**********************************************************************************************************
按键2键值
**********************************************************************************************************
*/
int key2_get(void) {
	
	uint8_t key_value =0;
	
	if (HAL_GPIO_ReadPin(KEY2_PORT, KEY2_PIN) == 0) {
		HAL_Delay(20); 
		while(HAL_GPIO_ReadPin(KEY2_PORT, KEY2_PIN) == 0); 
		HAL_Delay(15); 
		key_value =1;
	}
	return key_value;
}
/*
**********************************************************************************************************
按键3键值
**********************************************************************************************************
*/
int key3_get(void) {
	
	uint8_t key_value =0;
	
	if (HAL_GPIO_ReadPin(KEY3_PORT, KEY3_PIN) == 0) {
		HAL_Delay(20); 
		while(HAL_GPIO_ReadPin(KEY3_PORT, KEY3_PIN) == 0); 
		HAL_Delay(15); 
		key_value =1;
	}
	return key_value;
}
/*
**********************************************************************************************************
按键4键值
**********************************************************************************************************
*/
int key4_get(void) {
	
	uint8_t key_value =0;
	
	if (HAL_GPIO_ReadPin(KEY4_PORT, KEY4_PIN) == 0) {
		HAL_Delay(20); 
		while(HAL_GPIO_ReadPin(KEY4_PORT, KEY4_PIN) == 0); 
		HAL_Delay(15); 
		key_value =1;
	}
	return key_value;
}
/*
**********************************************************************************************************
按键5键值
**********************************************************************************************************
*/
int key5_get(void) {
	
	uint8_t key_value =0;
	
	if (HAL_GPIO_ReadPin(KEY5_PORT, KEY5_PIN) == 0) {
		HAL_Delay(20); 
		while(HAL_GPIO_ReadPin(KEY5_PORT, KEY5_PIN) == 0); 
		HAL_Delay(15); 
		key_value =1;
	}
	return key_value;
}
/*
**********************************************************************************************************
按键6键值
**********************************************************************************************************
*/
int key6_get(void) {
	
	uint8_t key_value =0;
	
	if (HAL_GPIO_ReadPin(KEY6_PORT, KEY6_PIN) == 0) {
		HAL_Delay(20); 
		while(HAL_GPIO_ReadPin(KEY6_PORT, KEY6_PIN) == 0); 
		HAL_Delay(15); 
		key_value =1;
	}
	return key_value;
}

