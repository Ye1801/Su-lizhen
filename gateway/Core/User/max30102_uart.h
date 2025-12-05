#ifndef _MAX30102_UART_H
#define _MAX30102_UART_H

#include "main.h"

#define TRUE        (0)
#define FALSE       (1)

struct max30102_data_t{
	uint8_t heart_flag;
  int heart;
	uint8_t spo2_flag;
  int spo2;
} ;

void max30102_uart_init(void);
uint8_t max30102_uart_receive_msg(struct max30102_data_t *data);

#endif

