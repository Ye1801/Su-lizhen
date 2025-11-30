#ifndef _UART_HANDLE_H_
#define _UART_HANDLE_H_

#include "main.h"

extern uint8_t  uart1_data;		
extern uint8_t  uart1_buf[256];		
extern uint16_t uart1_start;
extern uint16_t uart1_count;     
extern uint16_t uart1_finish;   


extern uint8_t  uart2_data;		
extern uint8_t  uart2_buf[256];		
extern uint16_t uart2_start;
extern uint16_t uart2_count;     
extern uint16_t uart2_finish;   

extern uint8_t  uart3_data;		
extern uint8_t  uart3_buf[256];		
extern uint16_t uart3_start;
extern uint16_t uart3_count;     
extern uint16_t uart3_finish;   


void usb_printf(const char *format, ...);
#endif


