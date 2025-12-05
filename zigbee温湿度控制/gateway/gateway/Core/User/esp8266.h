#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "main.h"

/*
*************************************
宏定义
*************************************
*/
#define TRUE        (0)
#define FALSE       (1)

/*
***************************************************************************************
连接的WIFI热点必须是2.4G WIFI,5GWIFI不可用
***************************************************************************************
*/
#define WIFI_SSID           "PDCN"   
#define WIFI_PASSWD         "1234567890"   
/*
***************************************************************************************
阿里云:
1.MQTT_CLIENT_ID中逗号前面的两个\\不能少

腾讯云:
1.产品名.iotcloud.tencentdevices.com
***************************************************************************************
*/
#define MQTT_CLIENT_ID              "k0hk18LXgsu.stm32_dev|securemode=2\\,signmethod=hmacsha256\\,timestamp=1713010593701|"   
#define MQTT_USER_NAME              "stm32_dev&k0hk18LXgsu"
#define MQTT_PASSWD                 "094c7c6274b7bf6b3c4bfb36a1cf4eb30dc70838a543995123f76ecebf491aae"
#define MQTT_BROKER_ADDRESS         "iot-06z00fsltf5eefe.mqtt.iothub.aliyuncs.com"
#define MQTT_BROKER_PORT            "1883"

#define SUB_TOPIC                   "/k0hk18LXgsu/stm32_dev/user/get"
#define PUB_TOPIC                   "/k0hk18LXgsu/stm32_dev/user/update"

void    esp8266_init(void);
uint8_t esp8266_receive_msg(uint8_t *rec_msg,uint8_t *rec_len);
uint8_t esp8266_send_msg(uint8_t* send_msg);

#endif


/*
*************************************
使用方法：

1.配置波特率115200
2.勾选开启中断使能
3.默认GPIO是TX-PA2,RX-PA3
4.修改连接参数
5.esp8266_init();初始化
6.esp8266_receive_msg();接收数据
7.esp8266_send_msg();   发送数据,timer_init(&timer_detect_receive, esp8266_receive_msg, 100, 1);
8.uart2_receiver_handle();检查是否被调用，写在串口中断回调的靠上面,
*************************************
*/

