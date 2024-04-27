#ifndef _WIFI_H_
#define _WIFI_H_
#include "stm32f1xx_hal.h"

#define WIFI_User 				"****"
#define WIFI_Pass   			"****"
#define ESP8266_UserName 		"****"//设置连接阿里云的UserName
#define ESP8266_PassWord		"****"//设置连接阿里云的PassWord
#define ESP8266_ClientID		"****"//设置连接阿里云的ClientID，注意,需要添加转义字符，=> \\,
#define ESP8266_Domain_Name		"****"//设置连接阿里云的Domain_Name
#define ESP8266_Port 			1883												 //设置连接阿里云的端口号
#define ESP8266_Reconnect		1                    //设置是否自动重连   0：不自动重连   1：自动重连
#define ESP8266_Post_re			"/sys/***/DHT11_Test/thing/event/property/post_reply"//订阅阿里云的Topic
#define ESP8266_Post			"/sys/***/DHT11_Test/thing/event/property/post"//订阅阿里云的Topic


#define  ESP8266_SET          "/sys/***/DHT11_Test/thing/service/property/set"


extern uint8_t temperature;
extern uint8_t humidity;
extern uint8_t LED_Switch;
void wifi_init(void);
void create_Json(uint8_t temperature,uint8_t humidity);
void rcv_json(void);
#endif /* WIFI_WIFI_H_ */
