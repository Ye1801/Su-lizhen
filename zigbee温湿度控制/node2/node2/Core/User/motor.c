#include "motor.h"

void motor1_set(uint16_t pwm);
void motor2_set(uint16_t pwm);
void motor3_set(uint16_t pwm);
void motor4_set(uint16_t pwm);

/*
*************************************
电机初始化,初始占空比为0
*************************************
*/
void motor1_init(void) {
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	motor1_set(0);
}
/*
*************************************
电机初始化,初始占空比为0
*************************************
*/
void motor2_init(void) {
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	motor2_set(0);
}
/*
*************************************
电机初始化,初始占空比为0
*************************************
*/
void motor3_init(void) {
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	motor3_set(0);
}
/*
*************************************
电机初始化,初始占空比为0
*************************************
*/
void motor4_init(void) {
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	motor4_set(0);
}
/*
*************************************
设置占空比0-99
*************************************
*/
void motor1_set(uint16_t pwm) {
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,pwm);
}
/*
*************************************
设置占空比0-99
*************************************
*/
void motor2_set(uint16_t pwm) {
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,pwm);

}
/*
*************************************
设置占空比0-99
*************************************
*/
void motor3_set(uint16_t pwm) {
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,pwm);
}
/*
*************************************
设置占空比0-99
*************************************
*/
void motor4_set(uint16_t pwm) {
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,pwm);
}
