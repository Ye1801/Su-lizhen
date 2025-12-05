#ifndef _ESP32CAM_H
#define _ESP32CAM_H

#include "main.h"

/*
*************************************
???
*************************************
*/
#define TRUE        (0)
#define FALSE       (1)

uint8_t esp32_receive_msg(uint8_t *rec_msg);
void esp32cam_init(void);

#endif

