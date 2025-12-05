#ifndef _IR_PAIR_H
#define _IR_PAIR_H 
    
#include "main.h"
#include "gpio.h"


#define IR_PAIR1_PIN  (GPIO1_Pin)
#define IR_PAIR1_PORT (GPIO1_GPIO_Port)

#define IR_PAIR2_PIN  (GPIO2_Pin)
#define IR_PAIR2_PORT (GPIO2_GPIO_Port)

#define IR_PAIR3_PIN  (GPIO3_Pin)
#define IR_PAIR3_PORT (GPIO3_GPIO_Port)

#define IR_PAIR4_PIN  (GPIO4_Pin)
#define IR_PAIR4_PORT (GPIO4_GPIO_Port)

#define IR_PAIR5_PIN  (GPIO5_Pin)
#define IR_PAIR5_PORT (GPIO5_GPIO_Port)

#define IR_PAIR6_PIN  (GPIO6_Pin)
#define IR_PAIR6_PORT (GPIO6_GPIO_Port)

void ir_pair1_init(void);
void ir_pair2_init(void);
void ir_pair3_init(void);
void ir_pair4_init(void);

uint8_t ir_pair1_get_data(void);
uint8_t ir_pair2_get_data(void);
uint8_t ir_pair3_get_data(void);
uint8_t ir_pair4_get_data(void);

#endif

