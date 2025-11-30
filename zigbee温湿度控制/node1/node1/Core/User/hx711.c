#include "hx711.h"
#include "stdio.h"
#include "stdint.h"
#include "gpio.h"
 
uint8_t ReceiveBuff[BUFFERSIZE]; //接收缓冲区
uint8_t recv_end_flag = 0,Rx_len;//接收完成中断标志，接收到字符长度

uint32_t weight_first = 0;//首次质量
uint32_t weight_real = 0;//每次读取的实际值


/***********************************************************************************************
*Name :          
*Function : 
*Parameter :   
                
***********************************************************************************************/
void hx711_init(void)
{
	  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = SCK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SCK_GPIO_Port, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Pin = DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DT_GPIO_Port, &GPIO_InitStruct);
}

/***********************************************************************************************
*Name : ReadCount
*Function : 读取传感器数值，通道A，增益128
*Parameter :    count 计数值
                i    24位数据计数，改变i的值可选择不同通道和增益24~26
***********************************************************************************************/
uint32_t ReadCount(void)
{
	uint32_t Count = 0;
	uint8_t i = 0;
	HAL_Delay(10);
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
	
	while(HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin));//判断AD转换器是否准备好（DOUT应为低电平）
	for(i = 0; i <24; i++)//24
	{
	  HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
		Count = Count << 1;		
		if(HAL_GPIO_ReadPin(DT_GPIO_Port, DT_Pin))
		{
		    Count ++;
		}
		HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);			
	}
	
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
	Count = Count ^ 0x800000;
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
	return Count;
}
/***********************************************************************************************
*Name :        weighing_peeling
*Function :    实现去皮
*Parameter :   无
               无
***********************************************************************************************/
void weighing_peeling(void)
{
	weight_first = ReadCount();//首次读取重量进行去皮操作
}
/***********************************************************************************************
*Name : ReadWeight
*Function : 读取拉力值
*Parameter :   weight_real          实际拉力值
               weight_first         传感器首次数据
***********************************************************************************************/
uint32_t WeightReal(void)
{
   weight_real = ReadCount();//实际质量计算
		if(weight_first>=weight_real)
		{
			weight_real = weight_first-weight_real;
			weight_real = weight_real/100;
		}
		else
		{
			weight_real = weight_real-weight_first;
			weight_real = weight_real/100;
		}
		
		float weight = (weight_real/1000)*9.8;
		weight_real = (uint32_t)weight;
		return weight_real;
}
