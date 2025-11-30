#include "ir_pair.h"

/****************************************功能说明****************************************

*****************************************功能说明****************************************/

void ir_pair1_init(void) {
	  
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IR_PAIR1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IR_PAIR1_PORT, &GPIO_InitStruct);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}

void ir_pair2_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IR_PAIR2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IR_PAIR2_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

void ir_pair3_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IR_PAIR3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IR_PAIR3_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void ir_pair4_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IR_PAIR4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IR_PAIR4_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void ir_pair5_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IR_PAIR5_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IR_PAIR5_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void ir_pair6_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = IR_PAIR6_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IR_PAIR6_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}

uint8_t ir_pair1_get_data() {
	uint8_t ir_pair_value =0;
	
	if (HAL_GPIO_ReadPin(IR_PAIR1_PORT, IR_PAIR1_PIN) == 0) {
		ir_pair_value =1;
	}
	return ir_pair_value;
}

uint8_t ir_pair2_get_data() {
	uint8_t ir_pair_value =0;
	
	if (HAL_GPIO_ReadPin(IR_PAIR2_PORT, IR_PAIR2_PIN) == 0) {
		ir_pair_value =1;
	}
	return ir_pair_value;
}

uint8_t ir_pair3_get_data() {
	uint8_t ir_pair_value =0;
	
	if (HAL_GPIO_ReadPin(IR_PAIR3_PORT, IR_PAIR3_PIN) == 0) {
		ir_pair_value =1;
	}
	return ir_pair_value;
}

uint8_t ir_pair4_get_data() {
	uint8_t ir_pair_value =0;
	
	if (HAL_GPIO_ReadPin(IR_PAIR4_PORT, IR_PAIR4_PIN) == 0) {
		ir_pair_value =1;
	}
	return ir_pair_value;
}

uint8_t ir_pair5_get_data() {
	uint8_t ir_pair_value =0;
	
	if (HAL_GPIO_ReadPin(IR_PAIR5_PORT, IR_PAIR5_PIN) == 0) {
		ir_pair_value =1;
	}
	return ir_pair_value;
}

uint8_t ir_pair6_get_data() {
	uint8_t ir_pair_value =0;
	
	if (HAL_GPIO_ReadPin(IR_PAIR6_PORT, IR_PAIR6_PIN) == 0) {
		ir_pair_value =1;
	}
	return ir_pair_value;
}

