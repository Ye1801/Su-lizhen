#include "main_program.h"
#include "time_handle.h"
#include <string.h>
#include "stdio.h"
#include "cJSON.h"
#include "sensor_hal.h"

/*
*************************************
变量或函数声明
*************************************
*/
void receive_json_data(void);
void send_json_data(void);
void board_sensor_collect(void);
void parse_json_data(uint8_t *json_msg);
/*
**********************************************************************************************************
变量定义
**********************************************************************************************************
*/
uint8_t rec_msg[256] = {0};
uint8_t rec_len =0;

static Timer timer_led_blink;
static Timer timer_sensor_collect;
static Timer timer_receive_msg;
static Timer timer_send_msg;


uint8_t alcohol_value = 0;  //采集的酒精数值
uint8_t alcohol_th = 0;     //酒精阈值包括按键设定的
uint8_t alcohol_app = 0;    //app发来的酒精阈值
uint8_t type_value = 0;    
uint8_t confirm=0;

/*
**********************************************************************************************************
初始化程序,开机只执行一次
**********************************************************************************************************
*/
void setup(void) {
	printf("start\r\n");
	//*************************传感器和外设初始化*************************//
	
	oled_init();
	oled_printf(0,0,"alcohol:%d",0);
	oled_printf(2,0,"threshold:%d",0);
	
	oled_refresh_gram();
	
	mqx_init();	
	
	if(SHT30_Init() == HAL_OK)
		printf("sht30 init is ok!\r\n");
	else
		printf("sht30 init is not ok!\r\n");
	
//	esp8266_init();	
	syn6288_init();
	//*************************软定时初始化*************************//
  timer_peripheral_init();

  timer_init(&timer_led_blink, led_board_toggle, 1000, 1);
	timer_init(&timer_receive_msg, receive_json_data, 100, 1);
	timer_init(&timer_send_msg, send_json_data, 1000, 1);
	timer_init(&timer_sensor_collect, board_sensor_collect, 1000, 1);

	//*************************开启软定时*************************//
  timer_start(&timer_led_blink);
	timer_start(&timer_receive_msg);
	timer_start(&timer_send_msg);
	timer_start(&timer_sensor_collect);
}
/*
**********************************************************************************************************
主程序,一直执行
**********************************************************************************************************
*/
void loop(void) {
  timer_loop();
}

//接收json数据
void receive_json_data(void) {
	
	if(esp8266_receive_msg(rec_msg,&rec_len)==TRUE) {
		parse_json_data(rec_msg);		
		printf("rec_msg:%s\r\n",rec_msg);
		memset(rec_msg,0,rec_len);
	}
}
//发送json数据
void send_json_data(void) {
  uint8_t json_msg[128]={0};
	
  sprintf((char*)json_msg,"{\\\"alcohol\\\":%d\\,\\\"th\\\":%d\\,\\\"com\\\":%d}",alcohol_value,alcohol_th,confirm);
	if(esp8266_send_msg(json_msg)==TRUE) {
		printf("send_msg %s\r\n",json_msg);
	} else {
		printf("mqtt send error\r\n");
	}
}
//采集传感器数据
void board_sensor_collect(void) {
	
	alcohol_value = mqx_get_data(0);

	oled_clear();
	oled_printf(0,0,"alcohol:%d",alcohol_value);
	oled_printf(2,0,"threshold:%d",alcohol_th);
	
	oled_refresh_gram();
	
	uint8_t dat[6] = {0};
	float temperature = 0.0;
	float humidity = 0.0;
		
	if(SHT30_Read_Dat(dat) == HAL_OK)
	{
		if(SHT30_Dat_To_Float(dat,&temperature,&humidity) == HAL_OK)
		{
			printf("TEMP:%f,HUM:%f\r\n",temperature,humidity);
		}
		else printf("sht30 check failed!\r\n");
	}
	else printf("sht30 read date failed!\r\n");

	syn6288_frame_info(2, "[v7][m1][t5]你好");
}
//匹配json数据
void parse_json_data(uint8_t *json_msg) {

  cJSON *json, *json_1,*json_2;
	
	json = cJSON_Parse((const char*)rec_msg);
	
	if(NULL == json) {
		printf("JSON Error before: [%s]\n",cJSON_GetErrorPtr());
		return;
	}
	
	json_1 = cJSON_GetObjectItem(json,"alcohol");
	if(json_1->type == cJSON_Number) {
		alcohol_app = json_1->valueint;
	}
	
	json_2 = cJSON_GetObjectItem(json,"type");
	if(json_2->type == cJSON_Number) {
		type_value = json_2->valueint;
		printf("type%d\r\n",type_value);
	}
}


