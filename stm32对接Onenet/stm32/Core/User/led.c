#include "led.h"

static uint8_t led_status=0;
/*
*************************************
设置led灯的状态,为1 1ed亮起,为0 led熄灭
*************************************
*/
void set_led(uint8_t status)
{
	if(status==1)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);//响
		led_status=1;
	}
	else
  {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);//不响
		led_status=0;
	}
}
void toggle_led(void)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);//响
}

/*
*************************************
获取led灯的状态,为1 1ed亮起,为0 led熄灭
*************************************
*/
uint8_t get_led(void)
{
	return led_status;
}