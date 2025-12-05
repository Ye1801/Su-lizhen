#include "main_program.h"
#include "sensor_hal.h"
#include "zigbee.h"

/*
*************************************
变量或函数声明
*************************************
*/
void receive_json_data(void);
void send_json_data(void);
void board_sensor_collect(void);
void parse_json_data(uint8_t *json_msg);
void loop_scan(void);
/*
**********************************************************************************************************
变量定义
**********************************************************************************************************
*/
static Timer timer_led_blink;
static Timer timer_sensor_collect;
static Timer timer_receive_msg;
static Timer timer_send_msg;
static Timer timer_loop_scan;


uint8_t temp_value = 0;
uint8_t humi_value = 0;
uint16_t mq2_value = 0;
uint16_t mq135_value = 0;

uint16_t rec_dev_id = 0;   //接收节点的id,node->gageway
uint16_t send_dev_id = 0;  //发送到节点的数据,gateway->node

int get_dev_id = 0;
int get_beep_state = 0;
int get_fan_state = 0;

int get_auto_state = 0;
int get_temp_state = 0;
int get_humi_state = 0;
int get_mq2_state = 0;
int get_mq135_state = 0;

int dev_switch = 1;
/*
**********************************************************************************************************
初始化程序,开机只执行一次
**********************************************************************************************************
*/
void setup(void) {
	printf("Hello,World!\r\n");
	//*************************传感器和外设初始化*************************//

	esp8266_init();
	zigbee_init();
	//*************************软定时初始化*************************//
  timer_peripheral_init();

  timer_init(&timer_led_blink, led5_board_toggle, 1000, 1);
	timer_init(&timer_receive_msg, receive_json_data, 100, 1);
	timer_init(&timer_send_msg, send_json_data, 2000, 1);
	timer_init(&timer_sensor_collect, board_sensor_collect, 1000, 1);
	timer_init(&timer_loop_scan, loop_scan, 100, 1);

	//*************************开启软定时*************************//
  timer_start(&timer_led_blink);
	timer_start(&timer_receive_msg);
	timer_start(&timer_send_msg);
	timer_start(&timer_sensor_collect);
  timer_start(&timer_loop_scan);
}
/*
**********************************************************************************************************
主程序,一直执行
**********************************************************************************************************
*/
void loop(void) {
  timer_loop();
}

void loop_scan(void) {
	
//	lora接收数据  0x5f|0xf5|id_h_|id_l|temp_h|temp_l|humi_h|humi_l|lux_h|lux_l|smoke_h|smoke_l|rain_h|rain_l|0xf5|0x5f
//                 0     1     2     3   4       5      6      7      8     9     10      11      12     13    14   15
	uint8_t rec_msg[128]={0};
	uint8_t seng_msg[128]={0};

	uint8_t rec_len =0;
	
  if(zigbee_receive_msg(rec_msg,&rec_len)==TRUE) {
		rec_dev_id = (rec_msg[2]<<8)|rec_msg[3];
		
		temp_value = (rec_msg[4]<<8)|rec_msg[5];
	  humi_value = (rec_msg[6]<<8)|rec_msg[7];
		mq2_value = (rec_msg[8]<<8)|rec_msg[9];
		mq135_value = (rec_msg[10]<<8)|rec_msg[11];
		
		sprintf((char*)seng_msg,"{\\\"id\\\":%d\\,\\\"temp\\\":%d\\,\\\"humi\\\":%d\\,\\\"mq2\\\":%d\\,\\\"mq135\\\":%d}",rec_dev_id,temp_value,humi_value,mq2_value,mq135_value);
		if(esp8266_send_msg(seng_msg)==TRUE) {
			printf("send_msg %s\r\n",seng_msg);
		} else {
			printf("mqtt send error\r\n");
		}
	}
}

//接收json数据
void receive_json_data(void) {
	
//	发送数据  0x5f|0xf5|id_h_|id_l|temp_h|temp_l|humi_h|humi_l|lux_h|lux_l|smoke_h|smoke_l|rain_h|rain_l|0xf5|0x5f
//            0     1     2     3   4       5      6      7      8     9     10      11      12     13    14   15
	
  uint8_t wifi_rec_msg[256] = {0};
  uint8_t wifi_rec_len =0;
	
	uint8_t zigbee_send_data[256] = {0};
	
	if(esp8266_receive_msg(wifi_rec_msg,&wifi_rec_len)==TRUE) {
    parse_json_data(wifi_rec_msg);	

			//包头
	  zigbee_send_data[0] = 0x5f;
    zigbee_send_data[1] = 0xf5;
	  zigbee_send_data[2] = (uint8_t)((get_dev_id & 0xFF00) >> 8);
    zigbee_send_data[3] = (uint8_t)(get_dev_id & 0x00FF);
		
		zigbee_send_data[4] = (uint8_t)((get_beep_state & 0xFF00) >> 8);
    zigbee_send_data[5] = (uint8_t)(get_beep_state & 0x00FF);
		
		
		zigbee_send_data[6] = (uint8_t)((get_fan_state & 0xFF00) >> 8);
    zigbee_send_data[7] = (uint8_t)(get_fan_state & 0x00FF);
		
		
		zigbee_send_data[8] = (uint8_t)((get_temp_state & 0xFF00) >> 8);
    zigbee_send_data[9] = (uint8_t)(get_temp_state & 0x00FF);
		
		zigbee_send_data[10] = (uint8_t)((get_humi_state & 0xFF00) >> 8);
    zigbee_send_data[11] = (uint8_t)(get_humi_state & 0x00FF);
		
		zigbee_send_data[12] =(uint8_t)((get_mq2_state & 0xFF00) >> 8);
    zigbee_send_data[13] = (uint8_t)(get_mq2_state & 0x00FF);
		
		zigbee_send_data[14] =(uint8_t)((get_mq135_state & 0xFF00) >> 8);
    zigbee_send_data[15] = (uint8_t)(get_mq135_state & 0x00FF);
		
		zigbee_send_data[16] =(uint8_t)((get_auto_state & 0xFF00) >> 8);
    zigbee_send_data[17] = (uint8_t)(get_auto_state & 0x00FF);
		
	  zigbee_send_data[18] = 0xf5;
    zigbee_send_data[19] = 0x5f;
		
		zigbee_send_msg(zigbee_send_data,20);
		
    printf("rec_msg:%s,id:%d,beep:%d,fan:%d,temp:%d,humi:%d,mq2:%d,mq135:%d,auto:%d\r\n",wifi_rec_msg,get_dev_id,get_beep_state,get_fan_state,get_temp_state,get_humi_state,get_mq2_state,get_mq135_state,get_auto_state);
	}
}
//发送json数据
void send_json_data(void) {


}
//采集传感器数据
void board_sensor_collect(void) {

	
}
//匹配json数据
void parse_json_data(uint8_t *json_msg) {

	sscanf((const char *)json_msg,"{\"beep\":%d,\"fan\":%d,\"auto\":%d,\"temp\":%d,\"humi\":%d,\"id\":%d,\"mq135\":%d,\"mq2\":%d}",
		&get_beep_state,&get_fan_state,&get_auto_state,&get_temp_state,&get_humi_state,&get_dev_id,&get_mq135_state,&get_mq2_state);
	printf(">>>>>>>>>>>>%s\r\n",json_msg);
}
