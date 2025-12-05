#ifndef _MC_H_
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
#define MC20_MQTT_CLIENT_ID              "a16sChhPmeV.stm32_dev|securemode=2,signmethod=hmacsha256,timestamp=1709966610013|"   
#define MC20_MQTT_USER_NAME              "stm32_dev&a16sChhPmeV"
#define MC20_MQTT_PASSWD                 "c39888b678869e33c8d43005e8538a980b817287c0a6230ba030a99f9f568d9e"
#define MC20_MQTT_BROKER_ADDRESS         "a16sChhPmeV.iot-as-mqtt.cn-shanghai.aliyuncs.com"
#define MC20_MQTT_BROKER_PORT            "1883"

#define MC20_SUB_TOPIC                   "/a16sChhPmeV/stm32_dev/user/get"
#define MC20_PUB_TOPIC                   "/a16sChhPmeV/stm32_dev/user/update"

struct MC20_DATA
{
	int32_t longitude;
	int32_t latitude;
	
	uint8_t rec_buff[128];
	uint8_t rec_len;
	
	uint8_t data_type;   
};


/*
***************************************************************************************
函数声明
***************************************************************************************
*/
void    mc20_init(void);
uint8_t mc20_send_msg(uint8_t* send_msg);
uint8_t mc20_send_gsm(uint8_t* phone_num,uint8_t* gsm_msg);
uint8_t mc20_receive_msg(struct MC20_DATA *mc20_data);

#endif

