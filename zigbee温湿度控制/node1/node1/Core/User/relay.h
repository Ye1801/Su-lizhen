#ifndef __RELAY_H
#define __RELAY_H 
    
#include "main.h"
#include "gpio.h"


#define RELAY1_PIN  (GPIO1_Pin)
#define RELAY1_PORT (GPIO1_GPIO_Port)

#define RELAY2_PIN  (GPIO2_Pin)
#define RELAY2_PORT (GPIO2_GPIO_Port)

#define RELAY3_PIN  (GPIO3_Pin)
#define RELAY3_PORT (GPIO3_GPIO_Port)

#define RELAY4_PIN  (GPIO4_Pin)
#define RELAY4_PORT (GPIO4_GPIO_Port)

#define RELAY5_PIN  (GPIO5_Pin)
#define RELAY5_PORT (GPIO5_GPIO_Port)

#define RELAY6_PIN  (GPIO6_Pin)
#define RELAY6_PORT (GPIO6_GPIO_Port)

void relay1_init(void);
void relay2_init(void);
void relay3_init(void);
void relay4_init(void);
void relay5_init(void);
void relay6_init(void);

void relay1_set(uint8_t level);
void relay2_set(uint8_t level);
void relay3_set(uint8_t level);
void relay4_set(uint8_t level);
void relay5_set(uint8_t level);
void relay6_set(uint8_t level);

	
#endif

