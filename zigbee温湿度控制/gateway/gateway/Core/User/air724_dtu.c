#include "air724_dtu.h"
#include "stdio.h"
#include "string.h"
#include "cJSON.h"
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
uint8_t  uart2_data;					    //串口接收缓存数组
uint8_t  uart2_buf[128];					//串口接收缓存数组
uint16_t uart2_start = 0;				  //串口接收开始标志位
uint16_t uart2_count = 0;	        //串口接收数据计数器
uint16_t uart2_finish = 0;	      //串口接收结束标志位
/*
*************************************
串口接收handle
*************************************
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART2) {
    uart2_buf[uart2_count++] = uart2_data;
    HAL_UART_Receive_IT(&huart2, &uart2_data, 1);		
		uart2_start = 1;																//串口1接收标志位置1
		uart2_finish = 0;																//串口1接收数据完成标志位清零
  }
}
/*
*************************************
清空接收串口数组程序
*************************************
*/
void uart2_flag_clear(void)	//清空接收串口1数组程序
{
	memset(uart2_buf,0,(unsigned int)strlen((const char *)uart2_buf));	//清零串口数组
	uart2_count = 0;
	uart2_start = 0;
	uart2_finish = 0;
}
/*
*************************************
air724发送数据
*************************************
*/
uint8_t air724_dtu_send(uint8_t* send_msg)
{
	uint8_t ret_val= FALSE;
	
	HAL_UART_Transmit(&huart2, (unsigned char *)send_msg,strlen((const char *)send_msg), 1000);	
	
	return ret_val;
}
/*
*************************************
bc20接收gps数据处理,TRUE返回经纬度数据,输出的坐标系是wgs84，百度地图的坐标系BD09LL
*************************************
*/
uint8_t air724_dtu_receive(uint8_t *beep, uint16_t *fan,uint16_t *servo,uint8_t *relay1,uint8_t *relay2)	//接收处理函数
{
	uint8_t ret_val = FALSE;
	uint16_t count = 0;		
  
	while((uart2_start == 0)&&(count<100))	                    //等待命令发送完成
	{
		count++;
		HAL_Delay(1);
	}
	if(count >= 100)	                                          //超时
	{
		ret_val = FALSE;	                                          //未接收到响应
	}
	else
	{
		HAL_Delay(60);
		
		cJSON *json, *json_beep, *json_fan, *json_servo, *json_relay1, *json_relay2;
		json = cJSON_Parse((const char*)uart2_buf);
		if(NULL == json)
		{
			printf("Error before: [%s]\n", cJSON_GetErrorPtr());
		}

		json_beep = cJSON_GetObjectItem(json, "beep");
		if(json_beep->type == cJSON_Number)
		{
			*beep = json_beep->valueint;
		}

		json_fan = cJSON_GetObjectItem(json, "fan");
		if(json_fan->type == cJSON_Number)
		{
			*fan = json_fan->valueint;
		}
		
		json_servo = cJSON_GetObjectItem(json, "servo");
		if(json_servo->type == cJSON_Number)
		{
			*servo = json_servo->valueint;
		}
		
		json_relay1 = cJSON_GetObjectItem(json, "relay1");
		if(json_relay1->type == cJSON_Number)
		{
			*relay1 = json_relay1->valueint;
		}
		
		json_relay2 = cJSON_GetObjectItem(json, "relay2");
		if(json_relay2->type == cJSON_Number)
		{
			*relay2 = json_relay2->valueint;
		}

		cJSON_Delete(json);
		ret_val = TRUE;
	}
  uart2_flag_clear();
	return ret_val;
}
/*
*************************************
bc20初始化
*************************************
*/
void air724_dtu_init(void)
{
  HAL_UART_Receive_IT(&huart2, &uart2_data, 1);
}

