#include "mc20.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "uart_handle.h"

/****************************************功能说明****************************************

void send_json_data(void) {
  uint8_t msg[128]={0};
	
  sprintf((char*)msg,"{\22online\22:%d}",1);
	if(mc20_send_msg(msg)==TRUE) {
		printf("send msg %s\r\n",msg);
	} else {
		printf("mqtt send error\r\n");
	}
}

注意:发送数据的"全部换为22代替

****************************************功能说明****************************************/

/*
*************************************
宏定义
*************************************
*/

/*
*************************************
变量定义
*************************************
*/

/*
*************************************
变量声明
*************************************
*/
/*
**********************************************************************************************************
串口初始化,设置mc20的波特率为115200
**********************************************************************************************************
*/
void mc20_uart2_init(void)
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
*************************************
清空接收串口2数组程序
*************************************
*/
void mc20_uart2_clear(void)	
{
	memset(uart2_buf,0,(unsigned int)strlen((const char *)uart2_buf));	
	uart2_count = 0;
	uart2_start = 0;
	uart2_finish = 0;
}
/*
*************************************
mc20_at发送命令
*************************************
*/
unsigned char mc20_send_cmd(unsigned char *cmd,unsigned char len,char *rec_data)
{
  unsigned char ret_val = FALSE;
  unsigned int count = 0;

  mc20_uart2_clear();                       
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
*************************************
mc20配置建立tcp连接
*************************************
*/
unsigned char mc20_tcp_connect(void)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;
	
	mc20_uart2_clear();	
	
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+QMTOPEN=0,\""MC20_MQTT_BROKER_ADDRESS"\","MC20_MQTT_BROKER_PORT"\r\n",
		strlen("AT+QMTOPEN=0,\""MC20_MQTT_BROKER_ADDRESS"\","MC20_MQTT_BROKER_PORT"\r\n"), 1000);	
  
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
      if(strstr((const char*)uart2_buf, "+QMTOPEN: 0,0"))
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
*************************************
mc20配置连接服务器
*************************************
*/
unsigned char mc20_connect_server(void)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;
	
	mc20_uart2_clear();	
  
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+QMTCONN=0,\""MC20_MQTT_CLIENT_ID"\",\""MC20_MQTT_USER_NAME"\",\""MC20_MQTT_PASSWD"\"\r\n",
		strlen("AT+QMTCONN=0,\""MC20_MQTT_CLIENT_ID"\",\""MC20_MQTT_USER_NAME"\",\""MC20_MQTT_PASSWD"\"\r\n"), 1000);	
		
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
      if(strstr((const char*)uart2_buf, "+QMTCONN: 0,0,0"))
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
*************************************
mc20复位
*************************************
*/
unsigned char mc20_reset(void)
{
	uint8_t ret_val =FALSE;
	
	mc20_uart2_clear();
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+RESET\r\n",11, 1000);
	
  while(1)
  {
    if(uart2_start != 0)
    {
      if(strstr((const char*)uart2_buf, "SMS READY"))
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
    }
  }
}

/*
*************************************
mc20发送消息
*************************************
*/
uint8_t mc20_send_msg(uint8_t* send_msg)
{
	uint8_t ret_val= FALSE;
	uint16_t count = 0;		
  unsigned char ctrol_z[1]={0x1a};	
  unsigned char msg_buf[256]={0};
  
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+QMTPUB=0,0,0,0,\""MC20_PUB_TOPIC"\"\r\n",strlen((const char *)"AT+QMTPUB=0,0,0,0,\""MC20_PUB_TOPIC"\"\r\n"), 1000);	

	
	while((uart2_start == 0)&&(count<1000))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 1000)	
	{
		HAL_Delay(100);
		if(strstr((const char*)uart2_buf, ">"))
		{
			HAL_UART_Transmit(&huart2, (unsigned char *)send_msg,strlen((const char *)send_msg), 1000);	
			HAL_UART_Transmit(&huart2,ctrol_z,1, 1000);	
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
*************************************
mc20发送gsm短信
*************************************
*/
uint8_t mc20_send_gsm(uint8_t* phone_num,uint8_t* gsm_msg)
{
	uint8_t ret_val= FALSE;
	uint16_t count = 0;		
  unsigned char ctrol_z[1]={0x1a};	
  unsigned char msg_buf[256]={0};
	
  sprintf((char *)msg_buf,"AT+CMGS=\"%s\"\r\n",phone_num);
	HAL_UART_Transmit(&huart2, (unsigned char *)msg_buf,strlen((const char *)msg_buf), 1000);	

	while((uart2_start == 0)&&(count<100))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 1000)	
	{
		HAL_Delay(10);
		if(strstr((const char*)uart2_buf, ">"))
		{
			HAL_UART_Transmit(&huart2, (unsigned char *)gsm_msg,strlen((char*)gsm_msg), 1000);
			HAL_UART_Transmit(&huart2,ctrol_z,1, 1000);	
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
*************************************
mc20接收数据处理
*************************************
*/
uint8_t mc20_receive_msg(struct MC20_DATA *mc20_data)	
{
	static int count =2;
  uint8_t ret_val= FALSE;
	uint8_t msg_body[128] = {0};
	
	uint32_t temp_int = 0;
	uint32_t jingdu_int = 0;  
  uint32_t weidu_int = 0;   

  float temp_float = 0;
  float weidu_float = 0;    
  float jingdu_float = 0;   
	
	if(count==20) {
	  HAL_UART_Transmit(&huart2, (unsigned char *)"AT+QGNSSRD=\"NMEA/RMC\"\r\n",strlen((const char *)"AT+QGNSSRD=\"NMEA/RMC\"\r\n"), 1000);	
		count=0;
	}
	count++;
	
	if(uart2_start == 1)	                                //指令接收标志位
	{
		//接收到最后一个字节，再延时5ms
		do{
			uart2_finish++;
			HAL_Delay(1);
		}while(uart2_finish < 100);	                          //等待指令接收完成
		
		if(strstr((const char*)uart2_buf,"+QMTRECV:"))	//如果接收到的指令数组里面有这个字符串
		{
			sscanf((const char *)uart2_buf,"\r\n+QMTRECV: 0,0,"MC20_SUB_TOPIC",%s\r\n",msg_body);
			
			mc20_data->latitude=0;
			mc20_data->longitude=0;
			mc20_data->rec_len = strlen((char *)msg_body);
			memcpy(mc20_data->rec_buff,msg_body,mc20_data->rec_len);
			
			mc20_data->data_type =1;
			
      ret_val= TRUE;
		} else if(strstr((const char*)uart2_buf,"+QGNSSRD:")) {
			if(uart2_buf[29+23]=='A')    
      {
        // +QGNSSRD: $GNRMC,032956.42,A,3748.7157,N,11238.7823,E,0.260,,100520,,,A,V*10
        temp_int=(uart2_buf[56]-0x30)*100000+(uart2_buf[57]-0x30)*10000+(uart2_buf[59]-0x30)*1000+(uart2_buf[60]-0x30)*100+(uart2_buf[61]-0x30)*10+(uart2_buf[62]-0x30); // 487157
        temp_float = (float)temp_int/600000;                      // 487157/600000=0.811928
        weidu_int = (uart2_buf[54]-0x30)*10+(uart2_buf[55]-0x30); // 37
        weidu_float = temp_float+(float)weidu_int;                // 37.811928
        weidu_float = weidu_float * 1000000;                      // 37811928.0
        weidu_int = weidu_float;                                  // 37811928
        mc20_data->latitude = weidu_int;
  
        temp_int=(uart2_buf[69]-0x30)*100000+(uart2_buf[70]-0x30)*10000+(uart2_buf[72]-0x30)*1000+(uart2_buf[73]-0x30)*100+(uart2_buf[74]-0x30)*10+(uart2_buf[75]-0x30); // 387823
        temp_float = (float)temp_int/600000;                                                // 387823/600000=0.646372
        jingdu_int = (uart2_buf[66]-0x30)*100+(uart2_buf[67]-0x30)*10+(uart2_buf[68]-0x30); // 112
        jingdu_float = temp_float+(float)jingdu_int;                                        // 112.646372
        jingdu_float = jingdu_float * 1000000;                                              // 112646372.0
        jingdu_int = jingdu_float;                                                          // 112646372
        mc20_data->longitude=jingdu_int;
				
			  mc20_data->rec_len = strlen((char *)msg_body);
			  memcpy(mc20_data->rec_buff,msg_body,mc20_data->rec_len);
				mc20_data->data_type =2;
        ret_val = TRUE;
      }
      else
      {
        ret_val = FALSE;
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
  mc20_uart2_clear();
  return ret_val;
}
/*
*************************************
mc20初始化配置
*************************************
*/
void mc20_init(void)
{
	mc20_uart2_init();
	HAL_Delay(1000);
	HAL_UART_Receive_IT(&huart2, &uart2_data, 1);
	

	printf("1.setting mqtt version\r\n");
	while(mc20_send_cmd((uint8_t *)"AT+QMTCFG=\"VERSION\",0,1\r\n",strlen("AT+QMTCFG=\"VERSION\",0,1\r\n"),"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("2.net attach\r\n");
	while(mc20_send_cmd((uint8_t *)"AT+CGATT=1\r\n",strlen("AT+CGATT=1\r\n"),"OK")!=0)
	{
		HAL_Delay(1000);
	}
  printf("3.mqtt connect service\r\n");
	while(mc20_tcp_connect()!=0)
	{
		HAL_Delay(5000);
	}
	printf("4.mqtt connect \r\n");
	while(mc20_connect_server()!=0)
	{
		HAL_Delay(10000);
	}
	printf("5.AT+QMTSUB\r\n");
	while(mc20_send_cmd((uint8_t *)"AT+QMTSUB=0,1,\""MC20_SUB_TOPIC"\",0\r\n",strlen("AT+QMTSUB=0,0,\""MC20_SUB_TOPIC"\",0\r\n"),"+QMTSUB")!=0)
	{
		HAL_Delay(5000);
	}
	printf("6.AT+CMGF=1\r\n");
	while(mc20_send_cmd((uint8_t *)"AT+CMGF=1\r\n",strlen("AT+CMGF=1\r\n"),"OK")!=0)
	{
		HAL_Delay(5000);
	}
	HAL_Delay(1000);
	printf("7.AT+CSCS=\"GSM\"\r\n");
	while(mc20_send_cmd((uint8_t *)"AT+CSCS=\"GSM\"\r\n",strlen("AT+CSCS=\"GSM\"\r\n"),"OK")!=0)
	{
		HAL_Delay(5000);
	}
	HAL_Delay(1000);
	printf("8.AT+QGNSSC=1\r\n");
	while(mc20_send_cmd((uint8_t *)"AT+QGNSSC=1\r\n",strlen("AT+QGNSSC=1\r\n"),"OK")!=0)
	{
		HAL_Delay(5000);
	}
	printf("9.mc20 init ok\r\n");
	HAL_Delay(2000);
}



