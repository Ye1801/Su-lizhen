#ifndef __MOTOR_H
#define __MOTOR_H 
    
#include "main.h"
#include "tim.h"

void motor1_init(void);
void motor2_init(void);
void motor3_init(void);
void motor4_init(void);

void motor1_set(uint16_t pwm);
void motor2_set(uint16_t pwm);
void motor3_set(uint16_t pwm);
void motor4_set(uint16_t pwm);
#endif

