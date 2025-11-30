#include "bc20.h"
#include "stdio.h"
#include "string.h"
#include "uart_handle.h"

/*
*************************************
宏定义
*************************************
*/

/*
*************************************
变量声明
*************************************
*/
extern UART_HandleTypeDef huart2;
/*
*************************************
变量定义
*************************************
*/


/*
**********************************************************************************************************
串口初始化,设置esp8266的波特率为115200
**********************************************************************************************************
*/
void bc20_uart2_init(void)
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
清空接收串口数组程序
*************************************
*/
void bc20_uart2_clear(void)	//清空接收串口1数组程序
{
	memset(uart2_buf,0,(unsigned int)strlen((const char *)uart2_buf));	//清零串口数组
	uart2_count = 0;
	uart2_start = 0;
	uart2_finish = 0;
}
/*
*************************************
bc20发送命令
*************************************
*/
unsigned char bc20_send_cmd(unsigned char *cmd,unsigned char len,char *rec_data)
{
  unsigned char ret_val = FALSE;
  unsigned int count = 0;

  bc20_uart2_clear();	                        //清空接收串口数组程序
  HAL_UART_Transmit(&huart2, cmd, len, 1000);	//发送AT指令至NB模组
  while((uart2_start == 0)&&(count<1000))	    //等待命令发送完成
  {
    count++;
    HAL_Delay(1);
  }
  if(count >= 1000)	                          //超时
  {
    ret_val = FALSE;	                          //未接收到响应
  }
  else	                                      //接收到了响应
  {
    do
    {
      uart2_finish++;
      HAL_Delay(1);
    }
    while(uart2_finish < 100);	                  //接收到最后一个字节，再延时100ms,等待串口接收完成
    if(strstr((const char*)uart2_buf, rec_data))	//如果接收到的数组里面有这个字符串
    {
      ret_val = TRUE;	                            //接收到正确响应
    }
    else
    {
      ret_val = FALSE;	                            //未接收到正确响应
    }
  }
  return ret_val;
}
/*
*************************************
bc20连接服务器
*************************************
*/
unsigned char bc20_connect_server(void)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;
  
  bc20_uart2_clear();
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+QMTOPEN=0,\""BC20_MQTT_BROKER_ADDRESS"\","BC20_MQTT_BROKER_PORT"\r\n",
    strlen("AT+QMTOPEN=0,\""BC20_MQTT_BROKER_ADDRESS"\","BC20_MQTT_BROKER_PORT"\r\n"), 1000);	
	
	while(1)
	{
		while((uart2_start == 0)&&(count<10000))	
		{
			count++;
			HAL_Delay(1);
		}
		if(count < 10000)		                  //"OK"和"+QMTOPEN: 0,0"各进入一次
		{
			HAL_Delay(50);
			if(strstr((const char*)uart2_buf, "+QMTOPEN: 0,0"))
			{
		    ret_val = TRUE;
			  return ret_val;
			}
      else
      {
        ;                                 
      }
      bc20_uart2_clear();                 //清除"OK"等返回命令，先收到"OK",再收到"+QMTOPEN: 0,0"
		}
    else                                  //处理超时没收到任何命令
    {
      ret_val = FALSE;
			return ret_val;
    }
	}
}
/*
*************************************
bc20登录服务器
*************************************
*/
unsigned char bc20_logon_server(void)
{
	uint8_t ret_val;
	uint16_t count = 0;
	
  bc20_uart2_clear();
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+QMTCONN=0,\""BC20_MQTT_CLIENT_ID"\",\""BC20_MQTT_USER_NAME"\",\""BC20_MQTT_PASSWD"\"\r\n",
		strlen("AT+QMTCONN=0,\""BC20_MQTT_CLIENT_ID"\",\""BC20_MQTT_USER_NAME"\",\""BC20_MQTT_PASSWD"\"\r\n"), 1000);	
	
  while(1)
	{
		while((uart2_start == 0)&&(count<10000))	
		{
			count++;
			HAL_Delay(1);
		}
		if(count < 10000)		                  //"OK"和"+QMTCONN: 0,0,0"各进入一次
		{
			HAL_Delay(50);
			if(strstr((const char*)uart2_buf, "+QMTCONN: 0,0,0"))
			{
		    ret_val = TRUE;
			  return ret_val;
			}
      else
      {
        ;                                 
      }
      bc20_uart2_clear();                 //清除"OK"等返回命令，先收到"OK",再收到"+QMTCONN: 0,0,0"   
		}
    else                                  //处理超时没收到任何命令
    {
      ret_val = FALSE;
			return ret_val;
    }
	}
}
/*
*************************************
bc20发送消息
*************************************
*/
uint8_t bc20_send_msg(uint8_t* send_msg)
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;		
	unsigned char ctrol_z[1]={0x1a};	
	
	bc20_uart2_clear();
	HAL_UART_Transmit(&huart2, (unsigned char *)"AT+QMTPUB=0,0,0,0,\""BC20_PUB_TOPIC"\"\r\n",
    strlen((const char *)"AT+QMTPUB=0,0,0,0,\""BC20_PUB_TOPIC"\"\r\n"), 1000);	
  
  while(1)
  {
    while((uart2_start == 0)&&(count<10000))	
    {
      count++;
      HAL_Delay(1);
    }
    if(count < 10000)
    {
      HAL_Delay(20);
      if(strstr((const char*)uart2_buf, ">"))
      {
        HAL_UART_Transmit(&huart2, (unsigned char *)send_msg,strlen((const char*)send_msg), 1000);
				HAL_Delay(2);
				HAL_UART_Transmit(&huart2,ctrol_z,1, 1000);	
      }
      else if(strstr((const char*)uart2_buf, "+QMTPUB: 0,0,0"))
      {
        ret_val = TRUE;
        return ret_val;  
      }
      else
      {
        ;
      }
      bc20_uart2_clear();
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
bc20接收数据处理
*************************************
*/
uint8_t bc20_receive_msg(struct BC20_DATA *bc20_data)	//接收处理函数
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;		
  uint8_t msg_body[UART2_REC_MAX] = {0};
	static uint8_t gps_count =0;
	
  uint32_t temp_int = 0;
  float temp_float = 0;
  uint32_t weidu_int = 0;   // 获取纬度的dd
  float weidu_float = 0;    // 获取纬度的mm
  uint32_t jingdu_int = 0;  // 获取经度的dd
  float jingdu_float = 0;   // 获取经度的mm
  
	bc20_uart2_clear();
	
	if(gps_count==20) {
	  HAL_UART_Transmit(&huart2, (uint8_t *)"AT+QGNSSRD=\"NMEA/RMC\"\r\n", 23, 1000);
		gps_count=0;
	}
	gps_count++;
	
	while((uart2_start == 0)&&(count<1000))	                    //等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	if(count >= 1000)	                                          //超时
	{
		ret_val = FALSE;	                                          //未接收到响应
	}
	else
	{
		HAL_Delay(60);
		if(strstr((const char*)uart2_buf,"+QGNSSRD: "))	          //如果接收到的指令数组里面有这个字符串
		{
      if(uart2_buf[29]=='A')                                  // 如果获取到了经纬度信息
      {
        // +QGNSSRD: $GNRMC,032956.42,A,3748.7157,N,11238.7823,E,0.260,,100520,,,A,V*10
        // 获取纬度
        temp_int=(uart2_buf[33]-0x30)*100000+(uart2_buf[34]-0x30)*10000+(uart2_buf[36]-0x30)*1000+(uart2_buf[37]-0x30)*100+(uart2_buf[38]-0x30)*10+(uart2_buf[39]-0x30); // 487157
        temp_float = (float)temp_int/600000;                      // 487157/600000=0.811928
        weidu_int = (uart2_buf[31]-0x30)*10+(uart2_buf[32]-0x30); // 37
        weidu_float = temp_float+(float)weidu_int;                // 37.811928
        weidu_float = weidu_float * 1000000;                      // 37811928.0
        weidu_int = weidu_float;                                  // 37811928
        bc20_data->latitude = weidu_int;
        // 获取经度
        temp_int=(uart2_buf[46]-0x30)*100000+(uart2_buf[47]-0x30)*10000+(uart2_buf[49]-0x30)*1000+(uart2_buf[50]-0x30)*100+(uart2_buf[51]-0x30)*10+(uart2_buf[52]-0x30); // 387823
        temp_float = (float)temp_int/600000;                                                // 387823/600000=0.646372
        jingdu_int = (uart2_buf[43]-0x30)*100+(uart2_buf[44]-0x30)*10+(uart2_buf[45]-0x30); // 112
        jingdu_float = temp_float+(float)jingdu_int;                                        // 112.646372
        jingdu_float = jingdu_float * 1000000;                                              // 112646372.0
        jingdu_int = jingdu_float;                                                          // 112646372
        bc20_data->longitude=jingdu_int;

				bc20_data->rec_len = strlen((char *)msg_body);
			  memcpy(bc20_data->rec_buff,msg_body,bc20_data->rec_len);
				bc20_data->data_type =2;
        ret_val = TRUE;
      }
      else
      {
        ret_val = FALSE;
      }
		}
		else if(strstr((const char*)uart2_buf,"\r\n+QMTRECV:"))
		{
			//+QMTRECV: 0,0,"/k0y2gGDV19T/stm32_dev/user/get","{"beep":1}"
			sscanf((const char *)uart2_buf,"\r\n+QMTRECV: 0,0,\""BC20_SUB_TOPIC"\",\"%s",msg_body);
      bc20_data->latitude=0;
			bc20_data->longitude=0;
			bc20_data->rec_len = strlen((char *)msg_body)-1;
			memcpy(bc20_data->rec_buff,msg_body,bc20_data->rec_len);
			//printf(">>>>>>>>>>>>>>>msg:%s,len:%d\r\n",bc20_data->rec_buff,bc20_data->rec_len);
			bc20_data->data_type =1;
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
bc20初始化
*************************************
*/
void bc20_init(void)
{
  bc20_uart2_init();
	HAL_UART_Receive_IT(&huart2, &uart2_data, 1);
	  
//	printf("1.AT测试命令\r\n");
//	while(bc20_send_cmd((uint8_t *)"AT\r\n",4,"OK")!=0)
//	{
//		HAL_Delay(1000);
//	}
//	printf("2.关闭回显\r\n");
//	while(bc20_send_cmd((uint8_t *)"ATE0\r\n",6,"OK")!=0)
//	{
//		HAL_Delay(1000);
//	}
//	printf("3.是否注网\r\n");
//	while(bc20_send_cmd((uint8_t *)"AT+CEREG?\r\n",11,"+CEREG: 0,1")!=0)
//	{
//		HAL_Delay(5000);
//	}
//	printf("4.网络是否附着\r\n");
//	while(bc20_send_cmd((uint8_t *)"AT+CGATT?\r\n",11,"+CGATT: 1")!=0)
//	{
//		HAL_Delay(5000);
//	}
//	printf("5.AT+mqtt3.1.1版本\r\n");
//	while(bc20_send_cmd((uint8_t *)"AT+QMTCFG=\"VERSION\",0,4\r\n",25,"OK")!=0)
//	{
//		HAL_Delay(5000);
//	}
//	printf("6.打开服务\r\n");
//	while(bc20_connect_server()!=0)
//	{
//		HAL_Delay(5000);
//	}
//	printf("7.连接服务器\r\n");
//	while(bc20_logon_server()!=0)
//	{
//		HAL_Delay(5000);
//	}
//	printf("8.订阅服务\r\n");
//	while(bc20_send_cmd((uint8_t *)"AT+QMTSUB=0,1,\""BC20_SUB_TOPIC"\",0\r\n",strlen("AT+MQTTSUB=0,\""BC20_SUB_TOPIC"\",0\r\n"),"OK")!=0)
//	{
//		HAL_Delay(5000);
//	}
//	printf("9.打开GPS\r\n");
//	while(bc20_send_cmd((uint8_t *)"AT+QGNSSC=1\r\n",strlen("AT+QGNSSC=1\r\n"),"OK")!=0)
//	{
//		HAL_Delay(5000);
//	}
//	printf("10.检查GPS是否已经打开\r\n");
//	while(bc20_send_cmd((uint8_t *)"AT+QGNSSC?\r\n",strlen("AT+QGNSSC?\r\n"),"+QGNSSC: 1")!=0)
//	{
//		HAL_Delay(5000);
//	}
//	HAL_Delay(1000);
//  printf(">>>BC20初始化完成\r\n");
}

