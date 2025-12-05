#include "hcsr04_tim.h"

/*
*************************************
获取人体传感器状态,1为有人,0为无人
*************************************
*/
#define SOUND_SPEED      (0.034)

uint32_t distance=0;


void hcsr04_tim_init(void) {
	 
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = TRIG_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TRIG_PORT, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
}


void delay_us(uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	while (__HAL_TIM_GET_COUNTER (&htim3) < time);
}

uint8_t hcsr04_read_distance(void)
{
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_SET);
	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_CC3);
	delay_us(10);
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, GPIO_PIN_RESET);
	HAL_Delay(5);
	return distance;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	static uint32_t start_time=0;
	static uint32_t end_time=0;
	static uint32_t diff_time=0;
	static uint8_t first_captured=0;
	
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)  
	{
		if (first_captured==0)
		{
			start_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			first_captured = 1;  
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (first_captured==1)
		{
			end_time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
			__HAL_TIM_SET_COUNTER(htim, 0);
			if (end_time > start_time)
			{
				diff_time = end_time-start_time;
			}
			else if (start_time > end_time)
			{
				diff_time = (0xffff -start_time) + end_time;
			}
			distance = diff_time * SOUND_SPEED/2;
			first_captured = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim3, TIM_IT_CC3);
		}
	}
}







