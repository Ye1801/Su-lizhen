#include "esp8266.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "uart_handle.h"

/*
**********************************************************************************************************
变量声明
**********************************************************************************************************
*/

/*
**********************************************************************************************************
变量定义
**********************************************************************************************************
*/

/*
**********************************************************************************************************
串口初始化,设置esp8266的波特率为115200
**********************************************************************************************************
*/
void esp8266_uart2_init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}
/*
**********************************************************************************************************
清空接收串口数组程序
**********************************************************************************************************
*/
void uart2_flag_clear(void)	
{
	memset(uart2_buf,0,(unsigned int)strlen((const char *)uart2_buf));	
	uart2_count = 0;
	uart2_start = 0;
	uart2_finish = 0;
}
/*
**********************************************************************************************************
esp8266发送命令
**********************************************************************************************************
*/
unsigned char esp8266_send_cmd(unsigned char *cmd,unsigned char len,char *rec_data)
{
  unsigned char ret_val = FALSE;
  unsigned int count = 0;

  uart2_flag_clear();	                        
  HAL_UART_Transmit(&huart2, cmd, len, 1000);	
  while((uart2_start == 0)&&(count<1000))	  
  {
    count++;
    HAL_Delay(1);
  }
  if(count >= 1000)	                       
  {
    ret_val = FALSE;       
  }
  else	                                
  {
    do
    {
      uart2_finish++;
      HAL_Delay(1);
    }
    while(uart2_finish < 100);	                 
    if(strstr((const char*)uart2_buf, rec_data))	
    {
      ret_val = TRUE;            
    }
    else
    {
      ret_val = FALSE;
    }
  }
  return ret_val;
}
/*
**********************************************************************************************************
esp8266配置WIFI连接网络
**********************************************************************************************************
*/
unsigned char esp8266_wifi_config(void)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;
	
	uart2_flag_clear();	
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+CWJAP=\""WIFI_SSID"\",\""WIFI_PASSWD"\"\r\n",
    strlen("AT+CWJAP=\""WIFI_SSID"\",\""WIFI_PASSWD"\"\r\n"), 1000);
	
  while(1)
  {
    while((uart2_start == 0)&&(count<5000))	
    {
      count++;
      HAL_Delay(1);
    }
    if(count<5000)
    {
      HAL_Delay(3000);              //返回数据不长，不需要清空buff
      if(strstr((const char*)uart2_buf, "WIFI CONNECTED"))
      {
        ret_val = TRUE;
        return ret_val;
      }
      else
      {
        ret_val = FALSE;
      }
    }
    else
    {
      ret_val = FALSE;
			return ret_val;
    }
  }
}
/*
**********************************************************************************************************
esp8266配置连接服务器
**********************************************************************************************************
*/
unsigned char esp8266_connect_server(void)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;
	
	uart2_flag_clear();	
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+MQTTCONN=0,\""MQTT_BROKER_ADDRESS"\","MQTT_BROKER_PORT",0\r\n",
    strlen("AT+MQTTCONN=0,\""MQTT_BROKER_ADDRESS"\","MQTT_BROKER_PORT",0\r\n"), 1000);	
  
  while(1)
  {
    while((uart2_start == 0)&&(count<5000))	
    {
      count++;
      HAL_Delay(1);
    }
    if(count<5000)
    {
      HAL_Delay(1000);              //返回数据不长，不需要清空buff
      if(strstr((const char*)uart2_buf, "OK"))
      {
        ret_val = TRUE;
        return ret_val;
      }
      else
      {
        ret_val = FALSE;
      }
    }
    else
    {
      ret_val = FALSE;
			return ret_val;
    }
  }
}
/*
**********************************************************************************************************
esp8266复位
**********************************************************************************************************
*/
unsigned char esp8266_reset(void)
{
	uint8_t ret_val =FALSE;
	uint16_t count = 0;
	
	uart2_flag_clear();
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+RST\r\n",8, 1000);
	
  while(1)
  {
    while((uart2_start == 0)&&(count<1000))	
    {
      count++;
      HAL_Delay(1);
    }
    if(count<1000)
    {
      HAL_Delay(200);
      uart2_flag_clear();         //清除部分杂乱的数据
      HAL_Delay(300);
      if(strstr((const char*)uart2_buf, "ready"))
      {
        ret_val = TRUE;
        return ret_val;
      }
      else
      {
        ret_val = FALSE;
      }
    }
    else
    {
      ret_val = FALSE;
			return ret_val;
    }
  }
}

/*
**********************************************************************************************************
esp8266发送消息
**********************************************************************************************************
*/
uint8_t esp8266_send_msg(uint8_t* send_msg)
{
	uint8_t ret_val= FALSE;
	uint16_t count = 0;			
  unsigned char msg_buf[256]={0};
	
  	sprintf((char *)msg_buf,"AT+MQTTPUB=0,\""PUB_TOPIC"\",\"%s\",0,0\r\n",send_msg);
	HAL_UART_Transmit(&huart2, (unsigned char *)msg_buf,strlen((const char *)msg_buf), 1000);	
    
	while((uart2_start == 0)&&(count<100))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 500)	
	{
		HAL_Delay(50);
		if(strstr((const char*)uart2_buf, "OK"))
		{
      ret_val = TRUE;
      return ret_val;  
		}
		else 
		{
      ret_val = FALSE;
      return ret_val; 
		}
	}
	return ret_val;
}
/*
**********************************************************************************************************
esp8266接收数据处理
**********************************************************************************************************
*/
uint8_t esp8266_receive_msg(uint8_t *rec_msg,uint8_t *rec_len)
{
  uint8_t ret_val= FALSE;
	int msg_len=0;
	uint8_t msg_body[256] = {0};
	
	if(uart2_start == 1)	                                //指令接收标志位
	{
		//接收到最后一个字节，再延时5ms
		do{
			uart2_finish++;
			HAL_Delay(1);
		}while(uart2_finish < 5);	                          //等待指令接收完成
		
		if(strstr((const char*)uart2_buf,"+MQTTSUBRECV:"))	//如果接收到的指令数组里面有这个字符串
		{
			sscanf((const char *)uart2_buf,"+MQTTSUBRECV:0,\""SUB_TOPIC"\",%d,%s",&msg_len,msg_body);
			if(strlen((const char*)msg_body)== msg_len)
			{
				memcpy(rec_msg,msg_body,msg_len);
				*rec_len = msg_len;
        ret_val= TRUE;
			}
      else {
        ret_val= FALSE;
      }
		}
    else
    {
      ret_val= FALSE;
    }
	}
  else
  {
    ret_val= FALSE;
  }
  uart2_flag_clear();
  return ret_val;
}
/*
**********************************************************************************************************
esp8266初始化配置
**********************************************************************************************************
*/
void esp8266_init(void)
{
	esp8266_uart2_init();
	HAL_UART_Receive_IT(&huart2, &uart2_data, 1);
	
	printf("1.Setting Mode\r\n");
	while(esp8266_send_cmd((uint8_t *)"AT+CWMODE=1\r\n",13,"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("2.Close Echo\r\n");
	while(esp8266_send_cmd((uint8_t *)"ATE0\r\n",6,"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("3.Setting No AUTO Connect WIFI\r\n");
	while(esp8266_send_cmd((uint8_t *)"AT+CWAUTOCONN=0\r\n",17,"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("4.Reset module\r\n");
	while(esp8266_reset() != 0)
	{
		HAL_Delay(5000);
	}
	HAL_Delay(2000);
	printf("5.Connect WIFI Config\r\n");
	while(esp8266_wifi_config() != 0)
	{
		HAL_Delay(5000);
	}
	printf("6.Connect Service Config\r\n");
	while(esp8266_send_cmd((uint8_t *)"AT+MQTTUSERCFG=0,1,\""MQTT_CLIENT_ID"\",\""MQTT_USER_NAME"\",\""MQTT_PASSWD"\",0,0,\"\"\r\n",strlen("AT+MQTTUSERCFG=0,1,\""MQTT_CLIENT_ID"\",\""MQTT_USER_NAME"\",\""MQTT_PASSWD"\",0,0,\"\"\r\n"),"OK")!=0)
	{
		HAL_Delay(2000);
	}
	printf("7.Connect Service\r\n");
	while(esp8266_connect_server() != 0)
	{
		HAL_Delay(8000);
	}
	printf("8.Subscribe Topic\r\n");
	while(esp8266_send_cmd((uint8_t *)"AT+MQTTSUB=0,\""SUB_TOPIC"\",0\r\n",strlen("AT+MQTTSUB=0,\""SUB_TOPIC"\",0\r\n"),"OK")!=0)
	{
		HAL_Delay(2000);
	}
	printf("9.esp8266 Init success !!!\r\n");
}



