#ifndef _HCSR04_UART_H
#define _HCSR04_UART_H

#include "main.h"

/*
*************************************

*************************************
*/
#define TRUE        (0)
#define FALSE       (1)

uint8_t hcsr04_receive_msg(uint16_t *rec_msg);
void hcsr04_uart_init(void);

#endif

