#ifndef __SERVO_H
#define __SERVO_H 
    
#include "main.h"
#include "tim.h"

void servo1_init(void);
void servo2_init(void);

void servo1_set(uint8_t angle);
void servo2_set(uint8_t angle);

#endif
