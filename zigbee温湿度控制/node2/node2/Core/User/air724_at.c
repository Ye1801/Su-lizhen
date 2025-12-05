#include "air724_at.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "uart_handle.h"

/****************************************功能说明****************************************

void send_json_data(void) {
  uint8_t msg[128]={0};
	
  sprintf((char*)msg,"{\22online\22:%d}",1);
	if(air724_at_send_msg(msg)==TRUE) {
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
串口初始化,设置air724的波特率为115200
**********************************************************************************************************
*/
void air724_uart2_init(void)
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
void air724_uart2_flag_clear(void)	
{
	memset(uart2_buf,0,(unsigned int)strlen((const char *)uart2_buf));	
	uart2_count = 0;
	uart2_start = 0;
	uart2_finish = 0;
}
/*
*************************************
air724_at发送命令
*************************************
*/
unsigned char air724_at_send_cmd(unsigned char *cmd,unsigned char len,char *rec_data)
{
  unsigned char ret_val = FALSE;
  unsigned int count = 0;

  air724_uart2_flag_clear();	                        
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
air724_at配置建立tcp连接
*************************************
*/
unsigned char air724_at_tcp_connect(void)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;
	
	air724_uart2_flag_clear();	
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+MIPSTART=\""AIR_724_MQTT_BROKER_ADDRESS"\",\""AIR_724_MQTT_BROKER_PORT"\"\r\n",
    strlen("AT+MIPSTART=\""AIR_724_MQTT_BROKER_ADDRESS"\",\""AIR_724_MQTT_BROKER_PORT"\"\r\n"), 1000);	
  
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
      if(strstr((const char*)uart2_buf, "CONNECT OK"))
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
air724_at配置连接服务器
*************************************
*/
unsigned char air724_at_connect_server(void)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;
	
	air724_uart2_flag_clear();	
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+MCONNECT=\"1\",\"60\"\r\n",
    strlen("AT+MCONNECT=\"1\",\"60\"\r\n"), 1000);	
  
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
      if(strstr((const char*)uart2_buf, "CONNACK OK"))
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
air724_at复位
*************************************
*/
unsigned char air724_at_reset(void)
{
	uint8_t ret_val =FALSE;
	
	air724_uart2_flag_clear();
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
air724_at发送消息
*************************************
*/
uint8_t air724_at_send_msg(uint8_t* send_msg)
{
	uint8_t ret_val= FALSE;
	uint16_t count = 0;			
  unsigned char msg_buf[256]={0};
	
  sprintf((char *)msg_buf,"AT+MPUB=\""AIR_724_PUB_TOPIC"\",0,1,\"%s\"\r\n",send_msg);
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
*************************************
air724_at发送gsm短信
*************************************
*/
uint8_t air724_at_send_gsm(uint8_t* gsm_msg)
{
	uint8_t ret_val= FALSE;
	uint16_t count = 0;			
  unsigned char msg_buf[256]={0};
	
  sprintf((char *)msg_buf,"AT+CMGS=\"%s\"\r\n",AIR_724_PHONE_NUMBER);
	HAL_UART_Transmit(&huart2, (unsigned char *)msg_buf,strlen((const char *)msg_buf), 1000);	

	while((uart2_start == 0)&&(count<100))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 500)	
	{
		HAL_Delay(50);
		if(strstr((const char*)uart2_buf, ">"))
		{
			uint8_t msg_len = strlen((const char *)gsm_msg);
			HAL_UART_Transmit(&huart2, (unsigned char *)gsm_msg,msg_len, 1000);
			
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
air724_at接收数据处理
*************************************
*/
uint8_t air724_at_receive_msg(uint8_t *rec_msg,uint8_t *rec_len)	
{
  uint8_t ret_val= FALSE;
	int msg_len=0;
	uint8_t msg_body[128] = {0};
	
	if(uart2_start == 1)	                                //指令接收标志位
	{
		//接收到最后一个字节，再延时5ms
		do{
			uart2_finish++;
			HAL_Delay(1);
		}while(uart2_finish < 50);	                          //等待指令接收完成
		
		if(strstr((const char*)uart2_buf,"+MSUB:"))	//如果接收到的指令数组里面有这个字符串
		{
			sscanf((const char *)uart2_buf,"\n+MSUB: \""AIR_724_SUB_TOPIC"\",%d byte,%s\r\n",&msg_len,msg_body);
			if(strlen((const char*)msg_body)== msg_len)
			{
				memcpy(rec_msg,msg_body,msg_len);
				*rec_len = msg_len;
        ret_val= TRUE;
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
  air724_uart2_flag_clear();
  return ret_val;
}
/*
*************************************
air724_at初始化配置
*************************************
*/
void air724_at_init(void)
{
	air724_uart2_init();
	HAL_Delay(1000);
	HAL_UART_Receive_IT(&huart2, &uart2_data, 1);
	printf("1.module reset\r\n");
	while(air724_at_reset() != 0)
	{
		HAL_Delay(5000);
	}
	printf("2.off echo\r\n");
	while(air724_at_send_cmd((uint8_t *)"ATE0\r\n",6,"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("3.net attach\r\n");
	while(air724_at_send_cmd((uint8_t *)"AT+CGATT?\r\n",11,"+CGATT: 1")!=0)
	{
		HAL_Delay(1000);
	}
	printf("4.set apn\r\n");
	while(air724_at_send_cmd((uint8_t *)"AT+CSTT=\"CMNET\",\"\",\"\"\r\n",23,"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("5.activate network\r\n");
	while(air724_at_send_cmd((uint8_t *)"AT+CIICR\r\n",10,"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("6.set text sms \r\n");
	while(air724_at_send_cmd((uint8_t *)"AT+CMGF=1\r\n",11,"OK")!=0)
	{
		HAL_Delay(1000);
	}
	printf("7.connect service config\r\n");
	while(air724_at_send_cmd((uint8_t *)"AT+MCONFIG=\""AIR_724_MQTT_CLIENT_ID"\",\""AIR_724_MQTT_USER_NAME"\",\""AIR_724_MQTT_PASSWD"\"\r\n",
		strlen("AT+MCONFIG=\""AIR_724_MQTT_CLIENT_ID"\",\""AIR_724_MQTT_USER_NAME"\",\""AIR_724_MQTT_PASSWD"\"\r\n"),"OK")!=0)
	{
		HAL_Delay(2000);
	}
	printf("8.setup tcp connect\r\n");
	while(air724_at_tcp_connect() != 0)
	{
		HAL_Delay(5000);
	}
	printf("9.connect service\r\n");
	while(air724_at_connect_server() != 0)
	{
		HAL_Delay(5000);
	}
	printf("10.subscirbe topic\r\n");
	while(air724_at_send_cmd((uint8_t *)"AT+MSUB=\""AIR_724_SUB_TOPIC"\",0\r\n",strlen("AT+MSUB=\""AIR_724_SUB_TOPIC"\",0\r\n"),"OK")!=0)
	{
		HAL_Delay(2000);
	}
	HAL_Delay(1000);
	printf("11.air724_at init sucess!!!\r\n");
}



