#ifndef __HALL_H
#define __HALL_H 
    
#include "main.h"
#include "gpio.h"


#define HALL1_PIN  (GPIO_IN1_Pin)
#define HALL1_PORT (GPIO_IN1_GPIO_Port)

#define HALL2_PIN  (GPIO_IN2_Pin)
#define HALL2_PORT (GPIO_IN2_GPIO_Port)

#define HALL3_PIN  (GPIO_IN3_Pin)
#define HALL3_PORT (GPIO_IN3_GPIO_Port)

#define HALL4_PIN  (GPIO_IN4_Pin)
#define HALL4_PORT (GPIO_IN4_GPIO_Port)

#define HALL5_PIN  (GPIO_IN5_Pin)
#define HALL5_PORT (GPIO_IN5_GPIO_Port)

void hall1_init(void);
void hall2_init(void);
void hall3_init(void);
void hall4_init(void);
void hall5_init(void);

uint8_t hall1_get(void);
uint8_t hall2_get(void);
uint8_t hall3_get(void);
uint8_t hall4_get(void);
uint8_t hall5_get(void);

	
#endif

