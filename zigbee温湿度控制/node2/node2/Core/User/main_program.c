#include "main_program.h"
#include "sensor_hal.h"
#include "zigbee.h"
#include "mqx.h"
/*
*************************************
变量或函数声明
*************************************
*/
void receive_json_data(void);
void send_json_data(void);
void board_sensor_collect(void);
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


//设备id
uint16_t send_dev_id = 0x0002;
uint16_t rec_dev_id = 0;   //接收节点的id,gageway->node

uint8_t temp_value = 0;
uint8_t humi_value = 0;

int get_relay_a_state = 0;
int get_relay_b_state = 0;

int get_auto_state = 0;
int get_temp_up_state = 0;
int get_temp_down_state = 0;
int get_humi_up_state = 0;
int get_humi_down_state = 0;
/*
**********************************************************************************************************
初始化程序,开机只执行一次
**********************************************************************************************************
*/
void setup(void) {
	printf("Hello,World!\r\n");
	//*************************传感器和外设初始化*************************//
	dht11_init();
	
	relay2_init();
	relay3_init();
	
  zigbee_init();
	//*************************软定时初始化*************************//
  timer_peripheral_init();

  timer_init(&timer_led_blink, led5_board_toggle, 1000, 1);
	timer_init(&timer_receive_msg, receive_json_data, 100, 1);
	timer_init(&timer_send_msg, send_json_data, 2000, 1);
	timer_init(&timer_sensor_collect, board_sensor_collect, 1000, 1);
	timer_init(&timer_loop_scan, loop_scan, 1000, 1);

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
	

}

//接收json数据
void receive_json_data(void) {
	
  uint8_t rec_msg[256] = {0};
  uint8_t rec_len =0;

  if(zigbee_receive_msg(rec_msg,&rec_len)==TRUE) {
		rec_dev_id = (rec_msg[2]<<8)|rec_msg[3];
		
		if(rec_dev_id==send_dev_id) {
			get_auto_state =      (rec_msg[4]<<8)|rec_msg[5];
      get_relay_a_state =   (rec_msg[6]<<8)|rec_msg[7];
			get_relay_b_state =   (rec_msg[8]<<8)|rec_msg[9];
			get_temp_up_state =   (rec_msg[10]<<8)|rec_msg[11];
			get_temp_down_state = (rec_msg[12]<<8)|rec_msg[13];
			get_humi_up_state =   (rec_msg[14]<<8)|rec_msg[15];
			get_humi_down_state = (rec_msg[16]<<8)|rec_msg[17];

		}
		//printf("zigbee>>>>>>>>beep:%d,fan:%d,temp:%d,humi:%d,mq2:%d,mq135:%d,auto:%d\r\n",get_beep_state,get_fan_state,get_temp_state,get_humi_state,get_mq2_state,get_mq135_state,get_auto_state);
	}
}
//发送json数据
void send_json_data(void) {
	
//	lora接收数据  0x5f|0xf5|id_h_|id_l|temp_h|temp_l|humi_h|humi_l|lux_h|lux_l|smoke_h|smoke_l|rain_h|rain_l|0xf5|0x5f
//                0     1     2     3   4       5      6      7      8     9     10      11      12     13    14   15
	
  uint8_t seng_msg[128]={0};
	//包头
	seng_msg[0] = 0x5f;
  seng_msg[1] = 0xf5;
	//id
	seng_msg[2] = (uint8_t)((send_dev_id & 0xFF00) >> 8);
  seng_msg[3] = (uint8_t)(send_dev_id & 0x00FF);
	//temp
	seng_msg[4] = (uint8_t)((temp_value & 0xFF00) >> 8);
  seng_msg[5] = (uint8_t)(temp_value & 0x00FF);
	//humi
	seng_msg[6] = (uint8_t)((humi_value & 0xFF00) >> 8);
  seng_msg[7] = (uint8_t)(humi_value & 0x00FF);
	//lux
	seng_msg[8] = 0x00;
  seng_msg[9] = 0x00;
	//smoke
	seng_msg[10] = 0x00;
  seng_msg[11] = 0x00;
	//rain
	seng_msg[12] = 0x00;
  seng_msg[13] = 0x00;
  //包尾
	seng_msg[14] = 0xf5;
  seng_msg[15] = 0x5f;
	
	zigbee_send_msg(seng_msg,16);
	
	printf("temp:%d,humi:%d\r\n",temp_value,humi_value);

}
//采集传感器数据
void board_sensor_collect(void) {

	dht11_read_data(&temp_value,&humi_value);
	
	if(get_auto_state==0) {
		relay2_set(get_relay_a_state);
		relay3_set(get_relay_b_state);
	} else {
		if((temp_value>get_temp_up_state)||(temp_value<get_temp_down_state)) {
			relay2_set(1);
		} else {
			relay2_set(0);
		}
		
		if((humi_value>get_humi_up_state)||(humi_value<get_humi_down_state)) {
			relay3_set(1);
		} else {
			relay3_set(0);
		}
	}
}
