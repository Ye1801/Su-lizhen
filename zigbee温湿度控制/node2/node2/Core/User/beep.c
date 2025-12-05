#include "beep.h"

/****************************************功能说明****************************************
1.低电平触发的有源蜂鸣器

*****************************************功能说明****************************************/

/**************************************************************************************
* 函数名称：beep1_init
* 功能描述：蜂鸣器初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：蜂鸣器初始化
***************************************************************************************/
void beep1_init(void) {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP1_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP1_PORT, BEEP1_PIN, GPIO_PIN_SET);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/**************************************************************************************
* 函数名称：beep2_init
* 功能描述：蜂鸣器初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：蜂鸣器初始化
***************************************************************************************/
void beep2_init(void) {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP2_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP2_PORT, BEEP2_PIN, GPIO_PIN_SET);
	
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}
/**************************************************************************************
* 函数名称：beep3_init
* 功能描述：蜂鸣器初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：蜂鸣器初始化
***************************************************************************************/
void beep3_init(void) {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP3_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP3_PORT, BEEP3_PIN, GPIO_PIN_SET);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/**************************************************************************************
* 函数名称：beep4_init
* 功能描述：蜂鸣器初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：蜂鸣器初始化
***************************************************************************************/
void beep4_init(void) {
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP4_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP4_PORT, BEEP4_PIN, GPIO_PIN_SET);
	
	HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI3_IRQn);
}
/**************************************************************************************
* 函数名称：beep5_init
* 功能描述：蜂鸣器初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：蜂鸣器初始化
***************************************************************************************/
void beep5_init(void) {
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP5_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP5_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP5_PORT, BEEP5_PIN, GPIO_PIN_SET);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI4_IRQn);
}
/**************************************************************************************
* 函数名称：beep6_init
* 功能描述：蜂鸣器初始化
* 入口参数：无
* 出口参数：无
* 返 回 值：无
* 说    明：蜂鸣器初始化
***************************************************************************************/
void beep6_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BEEP6_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BEEP6_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP6_PORT, BEEP6_PIN, GPIO_PIN_SET);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}
/**************************************************************************************
* 函数名称：beep1_set
* 功能描述：控制蜂鸣器
* 入口参数：1响0不响
* 出口参数：无
* 返 回 值：无
* 说    明：控制蜂鸣器
***************************************************************************************/
void beep1_set(uint8_t level) {
	if(level == 1) {
		HAL_GPIO_WritePin(BEEP1_PORT, BEEP1_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BEEP1_PORT, BEEP1_PIN, GPIO_PIN_SET);
	}
}
/**************************************************************************************
* 函数名称：beep2_set
* 功能描述：控制蜂鸣器
* 入口参数：1响0不响
* 出口参数：无
* 返 回 值：无
* 说    明：控制蜂鸣器
***************************************************************************************/
void beep2_set(uint8_t level) {
	if(level == 1) {
		HAL_GPIO_WritePin(BEEP2_PORT, BEEP2_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BEEP2_PORT, BEEP2_PIN, GPIO_PIN_SET);
	}
}
/**************************************************************************************
* 函数名称：beep3_set
* 功能描述：控制蜂鸣器
* 入口参数：1响0不响
* 出口参数：无
* 返 回 值：无
* 说    明：控制蜂鸣器
***************************************************************************************/
void beep3_set(uint8_t level) {
	if(level == 1) {
		HAL_GPIO_WritePin(BEEP3_PORT, BEEP3_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BEEP3_PORT, BEEP3_PIN, GPIO_PIN_SET);
	}
}
/**************************************************************************************
* 函数名称：beep4_set
* 功能描述：控制蜂鸣器
* 入口参数：1响0不响
* 出口参数：无
* 返 回 值：无
* 说    明：控制蜂鸣器
***************************************************************************************/
void beep4_set(uint8_t level) {
	if(level == 1) {
		HAL_GPIO_WritePin(BEEP4_PORT, BEEP4_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BEEP4_PORT, BEEP4_PIN, GPIO_PIN_SET);
	}
}
/**************************************************************************************
* 函数名称：beep5_set
* 功能描述：控制蜂鸣器
* 入口参数：1响0不响
* 出口参数：无
* 返 回 值：无
* 说    明：控制蜂鸣器
***************************************************************************************/
void beep5_set(uint8_t level) {
	if(level == 1) {
		HAL_GPIO_WritePin(BEEP5_PORT, BEEP5_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BEEP5_PORT, BEEP5_PIN, GPIO_PIN_SET);
	}
}
/**************************************************************************************
* 函数名称：beep6_set
* 功能描述：控制蜂鸣器
* 入口参数：1响0不响
* 出口参数：无
* 返 回 值：无
* 说    明：控制蜂鸣器
***************************************************************************************/
void beep6_set(uint8_t level) {
	if(level == 1) {
		HAL_GPIO_WritePin(BEEP6_PORT, BEEP6_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(BEEP6_PORT, BEEP6_PIN, GPIO_PIN_SET);
	}
}