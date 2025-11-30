#include "vibration_sensor.h"
#include "gpio_handle.h"

void vibration1_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = VIBRATION1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VIBRATION1_PORT, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void vibration2_init(void) {
	  
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = VIBRATION2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VIBRATION2_PORT, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void vibration3_init(void) {
	  
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = VIBRATION3_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VIBRATION3_PORT, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void vibration4_init(void) {
	 
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = VIBRATION4_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VIBRATION4_PORT, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

uint8_t vibration1_get_data() {
  return !gpio_in1;
}

uint8_t vibration2_get_data() {
  return !gpio_in2;
}

uint8_t vibration3_get_data() {
  return !gpio_in3;
}

uint8_t vibration4_get_data() {
  return !gpio_in4;
}



uint8_t vibration1_set_clear() {
	
	gpio_in1=1;
  return gpio_in1;
}

uint8_t vibration2_set_clear() {
  	
	gpio_in2=1;
  return gpio_in2;
}

uint8_t vibration3_set_clear() {
  	
	gpio_in3=1;
  return gpio_in3;
}

uint8_t vibration4_set_clear() {
  
	gpio_in4=1;
  return gpio_in4;
}

