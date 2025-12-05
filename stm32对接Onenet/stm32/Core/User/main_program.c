#include "main_program.h"
#include <stdio.h>
#include "usart.h"
#include "network.h"
#include "time_handle.h"
#include "buzzer.h"
#include "ir.h"
#include "oled.h"
#include "led.h"
#include "dht11.h"
#include "adc.h"
/*
*************************************
变量声明
*************************************
*/
extern uint8_t index_send_msg;
extern uint8_t index_adc;
extern uint8_t index_ir;
extern uint8_t index_oled;
extern uint8_t index_buzzer;
/*
*************************************
变量定义
*************************************
*/
long adcBuf[3] = {0,0,0};
unsigned int  a0_adc_value = 0;
unsigned int  a1_adc_value = 0;
unsigned int  a2_adc_value = 0;
uint8_t ir=0;
float env_temp=0;
float env_humi=0;
/*
*************************************
初始化程序,开机只执行一次
*************************************
*/
void user_init_program(void)
{
  OLED_init(); 
	OLED_printf(0,0,"temp:%5d,humi:%4d",0,0);
	OLED_printf(1,0,"mq-2:%5d,mq-7:%4d",0,0);
	OLED_printf(2,0,"mq-135:%4d,fire:%4d",0,0);
	OLED_refresh_gram();
  
  set_led(0);
  set_buzzer(0);
	network_init();          		
	init_tiner2();
	printf("success\r\n");
}
/*
*************************************
主程序,一直执行
*************************************
*/
void user_main_program(void)
{
	network_receive_msg();

  if(index_ir==1)
  {
    index_ir=0;
    ir = get_ir_status();
//    printf("ir=%d\r\n",ir);
    
  }
	if(index_adc==1)
	{
		index_adc=0;
    
    for(uint8_t j=0;j<100;j++)	//读取100次求平均值
		{
			for(uint8_t i=0;i<3;i++)	//读取3组ADC
			{
				HAL_ADC_Start(&hadc1);
        if(HAL_OK == HAL_ADC_PollForConversion(&hadc1,100))
				adcBuf[i] += HAL_ADC_GetValue(&hadc1);
			}
      HAL_ADC_Stop(&hadc1);
		}
		
		a0_adc_value = adcBuf[0]/100;
		a1_adc_value = adcBuf[1]/100;
    a2_adc_value = adcBuf[2]/100;
    adcBuf[0] = 0;
		adcBuf[1] = 0;
		adcBuf[2] = 0;
    
    printf("mq-2:%d,mq-7:%d,mq-135:%d\r\n",a1_adc_value,a0_adc_value,a2_adc_value);
	}
  if(index_oled==1)
  {
    index_oled=0;
    DHT11_SampleData(&env_temp, &env_humi);    
    
    
    OLED_printf(0,0,"temp:%5d,humi:%4d",(int)env_temp,(int)env_humi,ir);
	  OLED_printf(1,0,"mq-2:%5d,mq-7:%4d",a1_adc_value,a0_adc_value);
	  OLED_printf(2,0,"mq-135:%4d,fire:%4d",a2_adc_value,ir);
    
    OLED_refresh_gram();
    printf("temp:%.2f,humi:%.2f\r\n",env_temp,env_humi);
  }
  
  if(index_buzzer==1)
  {
    index_buzzer=0;
    if((a0_adc_value>2000)||(a1_adc_value>2000)||(a2_adc_value>2000)||(env_temp>40)||(env_humi<20)||(ir==1))
    {
      toggle_led();
      toggle_buzzer();
      
      if(a0_adc_value>2000)
      {
        OLED_printf(3,0,"CO Warning");
      }
      else if(a1_adc_value>2000)
      {
        OLED_printf(3,0,"Smoke Warning");
      }
      else if(a2_adc_value>2000)
      {
        OLED_printf(3,0,"Air Warning");
      }
      else if(env_temp>40)
      {
        OLED_printf(3,0,"Temp Warning");
      }
      else if(env_humi<20)
      {
        OLED_printf(3,0,"Humi Warning");
      }
      else if(ir==1)
      {
        OLED_printf(3,0,"Fire Warning");
      }
      OLED_refresh_gram();
    }
    else
    {
      set_led(0);
      set_buzzer(0);
      OLED_printf(3,0,"                  ");
      OLED_printf(4,0,"                  ");
      OLED_printf(5,0,"                  ");
      OLED_refresh_gram();
    }
  }

	if(index_send_msg==1)
	{
		index_send_msg=0;
		if(network_send_msg()==0)
		{
		}
		else
		{
			printf("msg send error\r\n");
		}
	}
}

