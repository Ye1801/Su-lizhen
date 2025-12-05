#ifndef __ZIGBEE_H
#define __ZIGBEE_H

#include "main.h"


#define TRUE        (0)
#define FALSE       (1)

void zigbee_init(void);
uint8_t zigbee_receive_msg(uint8_t *rec_msg,uint8_t *rec_len);
uint8_t zigbee_send_msg(uint8_t* send_msg,uint8_t msg_len);

#endif

