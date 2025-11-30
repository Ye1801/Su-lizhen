#ifndef __HUMAN_BODY_H
#define __HUMAN_BODY_H 
    
#include "main.h"
#include "gpio.h"


#define HUMAN_BODY1_PIN  (GPIO_IN1_Pin)
#define HUMAN_BODY1_PORT (GPIO_IN1_GPIO_Port)

#define HUMAN_BODY2_PIN  (GPIO_IN2_Pin)
#define HUMAN_BODY2_PORT (GPIO_IN2_GPIO_Port)

#define HUMAN_BODY3_PIN  (GPIO_IN3_Pin)
#define HUMAN_BODY3_PORT (GPIO_IN3_GPIO_Port)

#define HUMAN_BODY4_PIN  (GPIO_IN4_Pin)
#define HUMAN_BODY4_PORT (GPIO_IN4_GPIO_Port)

#define HUMAN_BODY5_PIN  (GPIO_IN5_Pin)
#define HUMAN_BODY5_PORT (GPIO_IN5_GPIO_Port)

void human_body1_init(void);
void human_body2_init(void);
void human_body3_init(void);
void human_body4_init(void);
void human_body5_init(void);

uint8_t human_body1_get(void);
uint8_t human_body2_get(void);
uint8_t human_body3_get(void);
uint8_t human_body4_get(void);
uint8_t human_body5_get(void);

	
#endif

