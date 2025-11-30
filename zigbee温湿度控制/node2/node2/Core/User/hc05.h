#ifndef __HC05_H
#define __HC05_H

#include "main.h"


#define TRUE        (0)
#define FALSE       (1)

void hc05_init(void);
uint8_t hc05_receive_msg(uint8_t *rec_msg,uint8_t *rec_len);
uint8_t hc05_send_msg(uint8_t* send_msg);
#endif


/*
*************************************
stm32cubemx配置
1.开启串口2
2.开启串口2中断
3.串口2波特率为115200


*************************************
*/
