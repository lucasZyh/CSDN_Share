#ifndef _WIFI_H_
#define _WIFI_H_
#include "stm32f4xx_hal.h"

#define WIFI_User 				"iQOO Neo9 Pro"
#define WIFI_Pass   			"52ke7ak3pjg3b82"
#define ESP8266_UserName 		"DHT11_Test&i9aijXXkHe1"		 //设置连接阿里云的UserName
#define ESP8266_PassWord		"89a809896e6efb2aa592b8c58eaa5116f127bddfc28905877cc0cbf3f19a566f"//设置连接阿里云的PassWord
#define ESP8266_ClientID		"i9aijXXkHe1.DHT11_Test|securemode=2\\,signmethod=hmacsha256\\,timestamp=1709970932908|"//设置连接阿里云的ClientID
#define ESP8266_Domain_Name		"iot-06z00hdpbi49q9b.mqtt.iothub.aliyuncs.com"//设置连接阿里云的Domain_Name
#define ESP8266_Port 			1883												 //设置连接阿里云的端口号
#define ESP8266_Reconnect		1                    //设置是否自动重连   0：不自动重连   1：自动重连
#define ESP8266_Post_re			"/sys/i9aijXXkHe1/DHT11_Test/thing/event/property/post_reply"//订阅阿里云的Topic
#define ESP8266_Post			"/sys/i9aijXXkHe1/DHT11_Test/thing/event/property/post"//订阅阿里云的Topic


#define  ESP8266_SET          "/sys/i9aijXXkHe1/DHT11_Test/thing/service/property/set"


extern uint8_t temperature;
extern uint8_t humidity;
extern uint8_t LED_Switch;
void wifi_init(void);
void create_Json(uint8_t temperature,uint8_t humidity);
void rcv_json(void);
#endif /* WIFI_WIFI_H_ */
