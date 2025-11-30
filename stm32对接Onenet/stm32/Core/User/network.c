#include "network.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "buzzer.h"
/*
*************************************
宏定义
*************************************
*/
#define WIFI_SSID        "CHINE_PDCN"
#define WIFI_PASSWD      "xlmqwa1006"

#define MQTT_CLIENT_ID   "device"   
#define MQTT_USER_NAME   "d6LVuVK8r4"
#define MQTT_PASSWD      "version=2018-10-31&res=products%2Fd6LVuVK8r4%2Fdevices%2Fdevice&et=1785139641&method=sha1&sign=9uqrrDWqnE%2F%2BddfmFa7TenmvQRw%3D"
#define BROKER_ASDDRESS  "mqtts.heclouds.com"

#define SUB_TOPIC        "/mqtt_app/user/get"
#define PUB_TOPIC        "$sys/d6LVuVK8r4/device/thing/property/post"

#define JSON_FORMAT "{\\\"id\\\": \\\"123\\\"\\,\\\"version\\\": \\\"1.0\\\"\\,\\\"params\\\": {\\\"t\\\": {\\\"value\\\": %d}\\,\\\"h\\\": {\\\"value\\\": %d}\\,\\\"m1\\\": {\\\"value\\\": %d}\\,\\\"m2\\\": {\\\"value\\\": %d}\\,\\\"m3\\\": {\\\"value\\\": %d}}}"
/*
*************************************
变量定义
*************************************
*/
static unsigned char receive_buf[256];	//串口2接收缓存数组
unsigned char receive_start = 0;	//串口2接收开始标志位
uint16_t receive_count = 0;	      //串口2接收数据计数器
uint16_t receive_finish = 0;	    //串口2接收结束标志位

extern unsigned int  a0_adc_value;
extern unsigned int  a1_adc_value;
extern unsigned int  a2_adc_value;
extern float env_temp;
extern float env_humi;
/*
*************************************
变量声明
*************************************
*/

/*
*************************************
串口2接收handle
*************************************
*/
void uart3_receiver_handle(void)
{
	unsigned char receive_data = 0;   //串口2接收一位数据
	if(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_RXNE) != RESET)
	{
		HAL_UART_Receive(&huart3, &receive_data, 1, 1000);
		receive_buf[receive_count++] = receive_data;
		receive_start = 1;	//串口1接收标志位置1
		receive_finish = 0;	//串口1接收数据完成标志位清零
	}
}
/*
*************************************
清空接收串口1数组程序
*************************************
*/
void network_uart_clear(void)	//清空接收串口1数组程序
{
	memset(receive_buf,0,(unsigned int)strlen((const char *)receive_buf));	//清零串口2数组
	receive_count = 0;
	receive_start = 0;
	receive_finish = 0;
}
/*
*************************************
串口2发送命令
*************************************
*/
unsigned char network_send_cmd(unsigned char *cmd,unsigned char len,char *recdata)	//设置命令
{
	unsigned char retval;
	unsigned int count = 0;
	
	network_uart_clear();	//清空接收串口1数组程序
	HAL_UART_Transmit(&huart3, cmd, len, 1000);	//发送AT指令至NB模组
	while((receive_start == 0)&&(count<1000))	//等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	
	if(count >= 1000)	//超时
	{
		retval = 1;	//未接收到响应
	}
	else	//接收到了响应
	{
		//接收到最后一个字节，再延时5ms
		do{
			receive_finish++;
			HAL_Delay(1);
		}while(receive_finish < 500);	//等待串口1接收完成
		
		receive_count = 0;
		receive_start = 0;
		retval = 2;
		if(strstr((const char*)receive_buf, recdata))	//如果接收到的数组里面有这个字符串
		{
			retval = 0;	//接收到正确响应
		}
	}
	network_uart_clear();
	return retval;
}
/*
*************************************
配置wifi
*************************************
*/
unsigned char network_set_wifi(void)
{
	uint8_t retval;
	uint16_t count = 0;
	
	network_uart_clear();	//清空接收串口1数组程序
	HAL_UART_Transmit(&huart3, (unsigned char *)"AT+CWJAP=\""WIFI_SSID"\",\""WIFI_PASSWD"\"\r\n",strlen("AT+CWJAP=\""WIFI_SSID"\",\""WIFI_PASSWD"\"\r\n"), 1000);	//发送AT指令至NB模组
	
	while((receive_start == 0)&&(count<1000))	//等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	
	if(count >= 1000)	//超时
	{
		retval = 1;	//未接收到响应
	}
	else	//接收到了响应
	{
		//接收到最后一个字节，再延时5ms
		
		HAL_Delay(8000);
		
		receive_count = 0;
		receive_start = 0;
		retval = 2;
		if(strstr((const char*)receive_buf, "OK"))	//如果接收到的数组里面有这个字符串
		{
			retval = 0;	//接收到正确响应
		}
	}
	return retval;
}
/*
*************************************
连接服务器
*************************************
*/
unsigned char network_connect_server(void)
{
	uint8_t retval;
	uint16_t count = 0;
	
	network_uart_clear();	//清空接收串口1数组程序
	HAL_UART_Transmit(&huart3, (unsigned char *)"AT+MQTTCONN=0,\""BROKER_ASDDRESS"\",1883,0\r\n",strlen("AT+MQTTCONN=0,\""BROKER_ASDDRESS"\",1883,0\r\n"), 1000);	
	while((receive_start == 0)&&(count<1000))	//等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	
	if(count >= 1000)	//超时
	{
		retval = 1;	//未接收到响应
	}
	else	//接收到了响应
	{
		//接收到最后一个字节，再延时5ms
		
		HAL_Delay(5000);
		
		receive_count = 0;
		receive_start = 0;
		retval = 2;
		if(strstr((const char*)receive_buf, "OK"))	//如果接收到的数组里面有这个字符串
		{
			retval = 0;	//接收到正确响应
		}
	}
	return retval;
}
/*
*************************************
复位
*************************************
*/
unsigned char network_reset(void)
{
	uint8_t retval;
	uint16_t count = 0;
	
	network_uart_clear();	//清空接收串口1数组程序
	HAL_UART_Transmit(&huart3, (unsigned char *)"AT+RST\r\n",8, 1000);	//发送AT指令至NB模组
	
	while((receive_start == 0)&&(count<2000))	//等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	
	if(count >= 2000)	//超时
	{
		retval = 1;	//未接收到响应
	}
	else	//接收到了响应
	{
		//接收到最后一个字节，再延时5ms
		
		HAL_Delay(5000);
		
		receive_count = 0;
		receive_start = 0;
		retval = 2;
		if(strstr((const char*)receive_buf, "OK"))	//如果接收到的数组里面有这个字符串
		{
			retval = 0;	//接收到正确响应
			printf("RST!!!!!!!!!!!!!!!!!!!!!!!\r\n");
		}
	}
	printf("RST CMD send\r\n");
	return retval;
}

/*
*************************************
发送消息
*************************************
*/
uint8_t network_send_msg(void)	//接收处理函数
{
	uint8_t retval=0;
	static uint8_t error_count=0;
	uint16_t count = 0;			
	static unsigned char msg_buf[512];
 
//	sprintf((char *)msg_buf,"AT+MQTTPUB=0,\""PUB_TOPIC"\",\""JSON_FORMAT"\",0,0\r\n",(int)env_temp,(int)env_humi,a1_adc_value,a0_adc_value,a2_adc_value);
  sprintf((char *)msg_buf,"AT+MQTTPUB=0,\""PUB_TOPIC"\",\""JSON_FORMAT"\",0,0\r\n",(int)env_temp,(int)env_humi,a1_adc_value,a0_adc_value,a2_adc_value);
	HAL_UART_Transmit(&huart3, (unsigned char *)msg_buf,strlen((const char *)msg_buf), 1000);	
  HAL_UART_Transmit(&huart1, (unsigned char *)msg_buf,strlen((const char *)msg_buf), 1000);	
  
	while((receive_start == 0)&&(count<500))	//等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	if(count >= 500)	//超时
	{
		retval = 1;	//未接收到响应
	}
	else	//接收到了响应
	{
		//接收到最后一个字节，再延时5ms
		HAL_Delay(50);
		
		receive_count = 0;
		receive_start = 0;
		retval = 1;
		if(strstr((const char*)receive_buf, "OK"))	//如果接收到的数组里面有这个字符串
		{
			retval = 0;	//接收到正确响应
			error_count=0;
		}
		else 
		{
			error_count++;
			if(error_count==5)
			{
				error_count=0;
				while(network_connect_server() != 0)
				{
					HAL_Delay(8000);
					printf("connect again!!!!!!!!!!!!!!!!\r\n");
				}
			}
		}
	}
	return retval;
}
/*
*************************************
接收数据处理
*************************************
*/
uint8_t network_receive_msg(void)	//接收处理函数
{
	int msg_len=0;
	uint8_t msg_body[128] = {0};
	
	if(receive_start == 1)	//指令接收标志位
	{
		//接收到最后一个字节，再延时5ms
		do{
			receive_finish++;
			HAL_Delay(1);
		}while(receive_finish < 5);	//等待指令接收完成
		
		if(strstr((const char*)receive_buf,"+MQTTSUBRECV:"))	//如果接收到的指令数组里面有这个字符串
		{
			sscanf((const char *)receive_buf,"+MQTTSUBRECV:0,\"/mqtt_app/user/get\",%d,%s",&msg_len,msg_body);
			
			printf("msg:%s\r\n",receive_buf);
			if(strlen((const char*)msg_body)== msg_len)
			{

			}
		}
		network_uart_clear();	//清空接收串口1数组程序
	}
}
/*
*************************************
初始化配置
*************************************
*/
void network_init(void)
{
	__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);           											//打开串口2接收中断
	
	printf("1.AT+CWMODE=1\r\n");
	while(network_send_cmd((uint8_t *)"AT+CWMODE=1\r\n",strlen("AT+CWMODE=1\r\n"),"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("2.ATE0\r\n");
	while(network_send_cmd((uint8_t *)"ATE0\r\n",strlen("ATE0\r\n"),"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("3.NO auto connect wifi\r\n");
	while(network_send_cmd((uint8_t *)"AT+CWAUTOCONN=0\r\n",strlen("AT+CWAUTOCONN=0\r\n"),"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("4.AT+RST\r\n");
	while(network_reset() != 0)
	{
		HAL_Delay(5000);
	}
	printf("5.WIFI SETTING\r\n");
	while(network_set_wifi() != 0)
	{
		HAL_Delay(8000);
	}
	printf("6.USER CONFIG\r\n");
	while(network_send_cmd((uint8_t *)"AT+MQTTUSERCFG=0,1,\""MQTT_CLIENT_ID"\",\""MQTT_USER_NAME"\",\""MQTT_PASSWD"\",0,0,\"\"\r\n",strlen("AT+MQTTUSERCFG=0,1,\""MQTT_CLIENT_ID"\",\""MQTT_USER_NAME"\",\""MQTT_PASSWD"\",0,0,\"\"\r\n"),"OK")!=0)
	{
		HAL_Delay(2000);
	}
	printf("7.CONNECT SERVER\r\n");
	while(network_connect_server() != 0)
	{
		HAL_Delay(8000);
	}
	printf("8.NETWORK OK!!!\r\n");
}





























