#ifndef __JDY_24M_H
#define __JDY_24M_H

#include "main.h"


#define TRUE        (0)
#define FALSE       (1)

void jdy_24m_init(void);
uint8_t jdy_24m_receive_msg(uint8_t *rec_msg,uint8_t *rec_len);
uint8_t jdy_24m_send_msg(uint8_t* send_msg);
#endif


/*
*************************************
stm32cubemx配置
1.开启串口3
2.开启串口3中断
3.串口2波特率为9600
*************************************
*/
