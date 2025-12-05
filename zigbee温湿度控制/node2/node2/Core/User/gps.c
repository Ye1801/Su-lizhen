#include "gps.h"
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
extern UART_HandleTypeDef huart1;
/*
*************************************
变量定义
*************************************
*/


/*
**********************************************************************************************************
串口初始化,设置gps的波特率为9600
**********************************************************************************************************
*/
void gps_uart1_init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}
/*
*************************************
清空接收串口数组程序
*************************************
*/
void gps_uart1_clear(void)	//清空接收串口1数组程序
{
	memset(uart1_buf,0,(unsigned int)strlen((const char *)uart1_buf));	//清零串口数组
	uart1_count = 0;
	uart1_start = 0;
	uart1_finish = 0;
}



int startsWith(const char *str, const char *prefix) {
    return strstr(str, prefix) == str;
}

/*
*************************************
gps接收数据处理
*************************************
*/
uint8_t gps_receive_msg(struct GPS_DATA *gps_data)	//接收处理函数
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;		
	
	uint32_t temp_int = 0;
	float temp_float = 0;
	uint32_t weidu_int = 0;   // 获取纬度的dd
	float weidu_float = 0;    // 获取纬度的mm
	uint32_t jingdu_int = 0;  // 获取经度的dd
	float jingdu_float = 0;   // 获取经度的mm

	while((uart1_start == 0)&&(count<1000))	                    //等待命令发送完成
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
		HAL_Delay(70);
		if(startsWith((char *)uart1_buf, "$GNGGA,"))
		{      
			// +QGNSSRD: $GNRMC,032956.42,A,3748.7157,N,11238.7823,E,0.260,,100520,,,A,V*10
			//$GNGGA,172550.000,3218.78642,N,11600.68863,E,1,18,0.7,50.6,M,-9.9,M,,*64
			// 获取纬度
			temp_int=(uart1_buf[20]-0x30)*100000+(uart1_buf[21]-0x30)*10000+(uart1_buf[23]-0x30)*1000+(uart1_buf[24]-0x30)*100+(uart1_buf[25]-0x30)*10+(uart1_buf[26]-0x30); // 487157
						
			temp_float = (float)temp_int/600000;                      // 487157/600000=0.811928
			weidu_int = (uart1_buf[18]-0x30)*10+(uart1_buf[19]-0x30); // 37
			weidu_float = temp_float+(float)weidu_int;                // 37.811928
			weidu_float = weidu_float * 1000000;                      // 37811928.0
			weidu_int = weidu_float;                                  // 37811928
			gps_data->latitude = weidu_int;
			
			// 获取经度
			temp_int=(uart1_buf[34]-0x30)*100000+(uart1_buf[35]-0x30)*10000+(uart1_buf[37]-0x30)*1000+(uart1_buf[38]-0x30)*100+(uart1_buf[39]-0x30)*10+(uart1_buf[40]-0x30); // 387823
			temp_float = (float)temp_int/600000;                                                // 387823/600000=0.646372
			jingdu_int = (uart1_buf[31]-0x30)*100+(uart1_buf[32]-0x30)*10+(uart1_buf[33]-0x30); // 112
			jingdu_float = temp_float+(float)jingdu_int;                                        // 112.646372
			jingdu_float = jingdu_float * 1000000;                                              // 112646372.0
			jingdu_int = jingdu_float;                                                          // 112646372
			gps_data->longitude=jingdu_int;

			ret_val = TRUE;
      
		} else {
			ret_val = FALSE;
		}
	}
	gps_uart1_clear();
	return ret_val;
}
/*
*************************************
gps初始化
*************************************
*/
void gps_init(void)
{
  gps_uart1_init();
	HAL_UART_Receive_IT(&huart1, &uart1_data, 1);
}

