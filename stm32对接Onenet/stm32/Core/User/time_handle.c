#include "time_handle.h"
#include "main.h"
#include "tim.h"
#include <stdio.h>


uint16_t index_10ms = 0;
uint16_t index_send_msg=0;
uint8_t index_adc = 0;
uint8_t index_oled = 0;
uint8_t index_ir = 0;
uint8_t index_buzzer = 0;

//定时器回调函数程序
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)	//定时器回调函数程序
{
	if (htim->Instance == htim2.Instance) //判断是否定时器2
	{	//10ms进入一次
		index_10ms++;	//10ms计时
		if(index_10ms % 10 == 0)	//100ms计时
		{
      index_ir=1;
      index_buzzer=1;
		}
		if(index_10ms ==100)	//1000ms计时
		{
      index_adc=1;
		}
    if(index_10ms ==200)	//1000ms计时
		{
			index_oled=1;
		}
    if(index_10ms ==300)	//1000ms计时
		{
      index_ir=1;
		}
		if(index_10ms >= 400)	//4000ms计时
		{
			index_send_msg=1;
			index_10ms = 0;
		}
	}
}

void init_tiner2(void)
{
	HAL_TIM_Base_Start_IT(&htim2);	//打开定时器2中断
}

