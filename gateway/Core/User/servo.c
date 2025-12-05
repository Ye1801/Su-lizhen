/****************************************功能说明****************************************
1.舵机控制 接线:舵机1->PA0  舵机2->PA1  

2.舵机接线 红色->3.3V  橙色->PWM  棕色->GND
****************************************功能说明****************************************/

#include "servo.h"

void servo1_set(uint8_t angle);
void servo2_set(uint8_t angle);

/*
*************************************
舵机控制初始化
*************************************
*/
void servo1_init(void) {
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	servo1_set(0);
}
/*
*************************************
舵机控制初始化
*************************************
*/
void servo2_init(void) {
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	servo2_set(0);
}
/*
*************************************
舵机控制PWM:500-2500->0-180
*************************************
*/
void servo1_set(uint8_t angle) {
	uint16_t pwm = (angle * 2000) / 180 + 500;
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,pwm);
}
/*
*************************************
舵机控制PWM:500-2500->0-180
*************************************
*/
void servo2_set(uint8_t angle) {
	uint16_t pwm = (angle * 2000) / 180 + 500;
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,pwm);
}



