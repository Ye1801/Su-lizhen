#include "buzzer.h"

static uint8_t buzzer_status=0;
/*
*************************************
设置buzzer的状态,为1 蜂鸣器响,为0 蜂鸣器不响
*************************************
*/
void set_buzzer(uint8_t status)
{
	if(status==1)
	{
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin, GPIO_PIN_RESET);//响
		buzzer_status=1;
	}
	else
  {
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin, GPIO_PIN_SET);//不响
		buzzer_status=0;
	}
}
void toggle_buzzer(void)
{
	HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);//响
}
/*
*************************************
获取蜂鸣器的状态,为1 蜂鸣器响,为0 蜂鸣器不响
*************************************
*/
uint8_t get_buzzer(void)
{
	return buzzer_status;
}
