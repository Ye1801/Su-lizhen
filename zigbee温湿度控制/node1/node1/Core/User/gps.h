#ifndef __GPS_H
#define __GPS_H

#include "main.h"

#define TRUE        (0)
#define FALSE       (1)

struct GPS_DATA
{
	int32_t longitude;
	int32_t latitude;
};

void gps_init(void);
uint8_t gps_receive_msg(struct GPS_DATA *gps_data);

#endif

/*
*************************************
stm32cubemx配置
1.开启串口2
2.开启串口2中断
3.串口2波特率为115200


*************************************
*/

