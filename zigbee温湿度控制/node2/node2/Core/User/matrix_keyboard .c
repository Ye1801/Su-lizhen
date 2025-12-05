#include "matrix_keyboard .h"

#define KEY_BOARD_PIN_C1  (ADC1_0_Pin)
#define KEY_BOARD_PORT    (GPIOA)

#define KEY_BOARD_PIN_C2  (ADC1_1_Pin)
#define KEY_BOARD_PORT    (GPIOA)

#define KEY_BOARD_PIN_C3  (ADC1_2_Pin)
#define KEY_BOARD_PORT    (GPIOA)

#define KEY_BOARD_PIN_C4  (ADC1_3_Pin)
#define KEY_BOARD_PORT    (GPIOA)

#define KEY_BOARD_PIN_R1  (GPIO_PIN_8)
#define KEY_BOARD_PORT    (GPIOA)

#define KEY_BOARD_PIN_R2  (GPIO_PIN_9)
#define KEY_BOARD_PORT    (GPIOA)

#define KEY_BOARD_PIN_R3  (GPIO_PIN_10)
#define KEY_BOARD_PORT    (GPIOA)

#define KEY_BOARD_PIN_R4  (GPIO_PIN_11)
#define KEY_BOARD_PORT    (GPIOA)


void matrix_key_init(void) {
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY_BOARD_PIN_C1|KEY_BOARD_PIN_C2|KEY_BOARD_PIN_C3|KEY_BOARD_PIN_C4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY_BOARD_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = KEY_BOARD_PIN_R1|KEY_BOARD_PIN_R2|KEY_BOARD_PIN_R3|KEY_BOARD_PIN_R4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY_BOARD_PORT, &GPIO_InitStruct);
}

int matrix_key_scan(void) {
	
		char KeyNumber = 'z'; 
		
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R1, GPIO_PIN_RESET); 

		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0); 
			HAL_Delay(15); 
			KeyNumber = 'A'; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0); 
			HAL_Delay(15); 
			KeyNumber = 3; 
		}	
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0); 
			HAL_Delay(15); 
			KeyNumber = 2; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0); 
			HAL_Delay(15); 
			KeyNumber = 1; 
		}
		
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R1, GPIO_PIN_SET);	
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R2, GPIO_PIN_RESET);

		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0); 
			HAL_Delay(15); 
			KeyNumber = 'B'; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0); 
			HAL_Delay(15); 
			KeyNumber = 6; 
		}	
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0); 
			HAL_Delay(15); 
			KeyNumber = 5; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0); 
			HAL_Delay(15); 
			KeyNumber = 4; 
		}			
			
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R1, GPIO_PIN_SET); 		
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R2, GPIO_PIN_SET); 
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R3, GPIO_PIN_RESET);

		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0) {	
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0); 
			HAL_Delay(15); 
			KeyNumber = 'C'; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0);
			HAL_Delay(15); 
			KeyNumber = 9; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0){		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0); 
			HAL_Delay(15); 
			KeyNumber = 8; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0){		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0);
			HAL_Delay(15); 
			KeyNumber = 7; 
		}
			
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R1, GPIO_PIN_SET); 	
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R2, GPIO_PIN_SET); 
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R3, GPIO_PIN_SET); 
		HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R4, GPIO_PIN_RESET);
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0){		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C1) == 0);
			HAL_Delay(15); 
			KeyNumber = 'D'; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0){		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C2) == 0);
			HAL_Delay(15); 
			KeyNumber = '#'; 
		}	
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C3) == 0);
			HAL_Delay(15); 
			KeyNumber = 0; 
		}
		if (HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0) {		
			HAL_Delay(20); 
			while(HAL_GPIO_ReadPin(KEY_BOARD_PORT, KEY_BOARD_PIN_C4) == 0);
			HAL_Delay(15); 
			KeyNumber = '*'; 
		}
	HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R1, GPIO_PIN_SET); 	
	HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R2, GPIO_PIN_SET); 
	HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KEY_BOARD_PORT, KEY_BOARD_PIN_R4, GPIO_PIN_SET);
			
	return KeyNumber;
}

