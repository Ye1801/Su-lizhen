#ifndef __PWM_LED_H__
#define __PWM_LED_H__

#include "main.h"
#include "tim.h"

void pwm_led1_init(void);
void pwm_led2_init(void);
void pwm_led3_init(void);
void pwm_led4_init(void);

void pwm_led1_set(uint16_t pwm);
void pwm_led2_set(uint16_t pwm);
void pwm_led3_set(uint16_t pwm);
void pwm_led4_set(uint16_t pwm);


#endif

