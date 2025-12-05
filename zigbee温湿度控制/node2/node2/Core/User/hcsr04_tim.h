#ifndef _HCSR04_TIM_H
#define _HCSR04_TIM_H

#include "main.h"
#include "tim.h"


#define TRIG_PIN  (GPIO0_Pin)
#define TRIG_PORT (GPIO0_GPIO_Port)


void hcsr04_tim_init(void);

uint8_t hcsr04_read_distance(void);

#endif

