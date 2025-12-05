#include "jsymk163.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "uart_handle.h"
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
float temp =0;
const uint16_t crctalbeabs[]= {
    0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401, 
    0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400 
};

/*
**********************************************************************************************************
清空接收串口数组程序
**********************************************************************************************************
*/
void jsymk163_uart3_clear(void)	
{
	memset(uart3_buf,0,(unsigned int)strlen((const char *)uart3_buf));	
	uart3_count = 0;
	uart3_start = 0;
	uart3_finish = 0;
}
\
/*
*************************************
计算crc16(modbus)
*************************************
*/
uint16_t crc16tablefast(uint8_t *ptr, uint16_t len) 
{
    uint16_t crc = 0xffff; 
    uint16_t i;
    uint8_t ch;
    for (i = 0; i < len; i++) {
        ch = *ptr++;
        crc = crctalbeabs[(ch ^ crc) & 15] ^ (crc >> 4);
        crc = crctalbeabs[((ch >> 4) ^ crc) & 15] ^ (crc >> 4);
    } 
    crc = ((crc & 0x00FF) << 8) | ((crc & 0xFF00) >> 8); //??????  
    return crc;
}
/*
**********************************************************************************************************
jsymk163接收数据处理
**********************************************************************************************************
*/
uint8_t jsymk163_receive_msg(struct jsymk163_data_t *data)
{
  uint8_t ret_val= FALSE;
	uint16_t count = 0;
	
	uint8_t send_masg[8]={0x01,0x03,0x00,0x48,0x00,0x0A,0x45,0xDB};
	HAL_UART_Transmit(&huart3, send_masg, 8, 1000);	
	
	while((uart3_start == 0)&&(count<100))	
	{
		count++;
		HAL_Delay(1);
	}
	if(count < 100)	
	{
		HAL_Delay(50);

		uint16_t crc16_value = (uart3_buf[23]<<8) | uart3_buf[24];
		
		if(crc16tablefast(uart3_buf, 23)==crc16_value)
		{
			data->voltage = ((uart3_buf[3]<<8)|uart3_buf[4])/100;
			data->power = ((uart3_buf[7]<<8)|uart3_buf[8]);
			data->current = data->power/data->voltage;
			
			temp = ((uart3_buf[9]<<24)|(uart3_buf[10]<<16)|(uart3_buf[11]<<8)|uart3_buf[12]);
			data->power_consumption = (float)temp/3200.0;

  		//printf("voltage:%d,current:%d,power:%d\r\n",data->voltage,data->current,data->power);
			ret_val = TRUE;
		}
	}

  jsymk163_uart3_clear();
  return ret_val;
}
/*
**********************************************************************************************************
串口初始化,设置jsymk163的波特率为4800
**********************************************************************************************************
*/
void jsymk163_uart3_init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 4800;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}
/*
*************************************
max30102串口初始化配置
*************************************
*/
void jsymk163_init(void)
{
	jsymk163_uart3_init();
	HAL_UART_Receive_IT(&huart3, &uart3_data, 1);
}

