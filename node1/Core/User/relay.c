#include "relay.h"


/*
***********************************************************************
默认设置为低电平0，适用于高电平触发继电器
***********************************************************************
*/
void relay1_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RELAY1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RELAY1_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RELAY1_PORT, RELAY1_PIN, GPIO_PIN_RESET);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
***********************************************************************
默认设置为低电平0，适用于高电平触发继电器
***********************************************************************
*/
void relay2_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RELAY2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RELAY2_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RELAY2_PORT, RELAY2_PIN, GPIO_PIN_RESET);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
***********************************************************************
默认设置为低电平0，适用于高电平触发继电器
***********************************************************************
*/
void relay3_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RELAY3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RELAY3_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RELAY3_PORT, RELAY3_PIN, GPIO_PIN_RESET);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI4_IRQn);
}
/*
***********************************************************************
默认设置为低电平0，适用于高电平触发继电器
***********************************************************************
*/
void relay4_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RELAY4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RELAY4_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RELAY4_PORT, RELAY4_PIN, GPIO_PIN_RESET);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}
/*
***********************************************************************
默认设置为低电平0，适用于高电平触发继电器
***********************************************************************
*/
void relay5_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RELAY5_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RELAY5_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RELAY5_PORT, RELAY5_PIN, GPIO_PIN_RESET);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}
/*
***********************************************************************
默认设置为低电平0，适用于高电平触发继电器
***********************************************************************
*/
void relay6_init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = RELAY6_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RELAY6_PORT, &GPIO_InitStruct);
	
	  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RELAY6_PORT, RELAY6_PIN, GPIO_PIN_RESET);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI2_IRQn);
}
/*
***********************************************************************
1为高电平，0为低电平，高电平吸合导通
***********************************************************************
*/
void relay1_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(RELAY1_PORT, RELAY1_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RELAY1_PORT, RELAY1_PIN, GPIO_PIN_SET);
	}
}
/*
***********************************************************************
1为高电平，0为低电平，高电平吸合导通
***********************************************************************
*/
void relay2_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(RELAY2_PORT, RELAY2_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RELAY2_PORT, RELAY2_PIN, GPIO_PIN_SET);
	}
}
/*
***********************************************************************
1为高电平，0为低电平，高电平吸合导通
***********************************************************************
*/
void relay3_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(RELAY3_PORT, RELAY3_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RELAY3_PORT, RELAY3_PIN, GPIO_PIN_SET);
	}
}
/*
***********************************************************************
1为高电平，0为低电平，高电平吸合导通
***********************************************************************
*/
void relay4_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(RELAY4_PORT, RELAY4_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RELAY4_PORT, RELAY4_PIN, GPIO_PIN_SET);
	}
}

/*
***********************************************************************
1为高电平，0为低电平，高电平吸合导通
***********************************************************************
*/
void relay5_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(RELAY5_PORT, RELAY5_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RELAY5_PORT, RELAY5_PIN, GPIO_PIN_SET);
	}
}

/*
***********************************************************************
1为高电平，0为低电平，高电平吸合导通
***********************************************************************
*/
void relay6_set(uint8_t level) {
	if(level == 0) {
		HAL_GPIO_WritePin(RELAY6_PORT, RELAY6_PIN, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(RELAY6_PORT, RELAY6_PIN, GPIO_PIN_SET);
	}
}

