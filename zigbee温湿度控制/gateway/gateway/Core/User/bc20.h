#ifndef __BC20_H
#define __BC20_H

#include "main.h"


#define TRUE        (0)
#define FALSE       (1)

#define BC20_MQTT_CLIENT_ID        "k0y2gGDV19T.stm32_dev|securemode=2,signmethod=hmacsha256,timestamp=1710751118008|"   
#define BC20_MQTT_USER_NAME        "stm32_dev&k0y2gGDV19T"
#define BC20_MQTT_PASSWD           "cea3c85f602483d9e3f0d968fe72fa24011e8f6a837caf2a6f1a09fe03942d88"
#define BC20_MQTT_BROKER_ADDRESS   "iot-06z00csfbcula9r.mqtt.iothub.aliyuncs.com"
#define BC20_MQTT_BROKER_PORT      "1883"

#define BC20_SUB_TOPIC             "/k0y2gGDV19T/stm32_dev/user/get"
#define BC20_PUB_TOPIC             "/k0y2gGDV19T/stm32_dev/user/update"

struct BC20_DATA
{
	int32_t longitude;
	int32_t latitude;
	
	uint8_t rec_buff[UART2_REC_MAX];
	uint8_t rec_len;
	
	uint8_t data_type;   
};

void bc20_init(void);

uint8_t bc20_send_msg(uint8_t* send_msg);
uint8_t bc20_receive_msg(struct BC20_DATA *bc20_data);
#endif


/*
*************************************
stm32cubemx配置
1.开启串口2
2.开启串口2中断
3.串口2波特率为115200


*************************************
*/

