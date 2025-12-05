#ifndef _AIR724_AT_H_
#define _AIR724_AT_H_

#include "main.h"

/*
***************************************************************************************
连接状态标志
***************************************************************************************
*/
#define TRUE        (0)
#define FALSE       (1)
/*
***************************************************************************************
连接参数
***************************************************************************************
*/
#define AIR_724_MQTT_CLIENT_ID              "5LY2E0QVYTstm32_dev"   
#define AIR_724_MQTT_USER_NAME              "5LY2E0QVYTstm32_dev;12010126;13c2c;1715443200"
#define AIR_724_MQTT_PASSWD                 "f937dd5e6b6b98dae68ea181ad18e361ec19b8ab6db1de7959f6c5848882fd2e;hmacsha256"
#define AIR_724_MQTT_BROKER_ADDRESS         "5LY2E0QVYT.iotcloud.tencentdevices.com"
#define AIR_724_MQTT_BROKER_PORT            "1883"

#define AIR_724_SUB_TOPIC                   "5LY2E0QVYT/stm32_dev/control"
#define AIR_724_PUB_TOPIC                   "5LY2E0QVYT/stm32_dev/data"

#define AIR_724_PHONE_NUMBER                "12345678901"

/*
***************************************************************************************
函数声明
***************************************************************************************
*/
void    air724_at_init(void);
void    uart2_receiver_handle(void);
uint8_t air724_at_receive_msg(uint8_t *rec_msg,uint8_t *rec_len);
uint8_t air724_at_send_msg(uint8_t* send_msg);
uint8_t air724_at_send_gsm(uint8_t* gsm_msg);

#endif

