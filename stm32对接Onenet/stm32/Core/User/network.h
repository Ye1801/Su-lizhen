#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "main.h"
void network_uart_clear(void);
void uart3_receiver_handle(void);
unsigned char network_send_cmd(unsigned char *cmd,unsigned char len,char *recdata);
unsigned char network_reset(void);
uint8_t network_receive_msg(void);
uint8_t network_send_msg(void);
void network_init(void);
#endif

