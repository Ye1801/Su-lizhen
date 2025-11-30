#ifndef __AIR724_DTU_H
#define __AIR724_DTU_H

#include "main.h"


#define TRUE        (0)
#define FALSE       (1)

void air724_dtu_init(void);
uint8_t air724_dtu_receive(uint8_t *beep, uint16_t *fan,uint16_t *servo,uint8_t *relay1,uint8_t *relay2);
uint8_t air724_dtu_send(uint8_t* send_msg);
#endif


/*
*************************************
stm32cubemx配置
1.开启串口2
2.开启串口2中断
3.串口2波特率为115200


*************************************
*/
