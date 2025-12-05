#include "fire_sensor.h"

/****************************************功能说明****************************************

*****************************************功能说明****************************************/

void fire1_init(void) {
	  
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FIRE1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FIRE1_PORT, &GPIO_InitStruct);
}

void fire2_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FIRE2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FIRE2_PORT, &GPIO_InitStruct);
}

void fire3_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FIRE3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FIRE3_PORT, &GPIO_InitStruct);
}

void fire4_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = FIRE4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FIRE4_PORT, &GPIO_InitStruct);
}

uint8_t fire1_get_data() {
	uint8_t value = HAL_GPIO_ReadPin(FIRE1_PORT, FIRE1_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

uint8_t fire2_get_data() {
	uint8_t value = HAL_GPIO_ReadPin(FIRE2_PORT, FIRE2_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

uint8_t fire3_get_data() {
	uint8_t value = HAL_GPIO_ReadPin(FIRE3_PORT, FIRE3_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

uint8_t fire4_get_data() {
	uint8_t value = HAL_GPIO_ReadPin(FIRE4_PORT, FIRE4_PIN);
	if(value==1) {
		value=0;
	} else {
		value=1;
	}
  return value;
}

