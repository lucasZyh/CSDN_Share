#ifndef _WIFI_H_
#define _WIFI_H_
#include "stm32f1xx_hal.h"

#define WIFI_User 				"****"
#define WIFI_Pass   			"****"
#define ESP8266_UserName 		"****"//�������Ӱ����Ƶ�UserName
#define ESP8266_PassWord		"****"//�������Ӱ����Ƶ�PassWord
#define ESP8266_ClientID		"****"//�������Ӱ����Ƶ�ClientID��ע��,��Ҫ���ת���ַ���=> \\,
#define ESP8266_Domain_Name		"****"//�������Ӱ����Ƶ�Domain_Name
#define ESP8266_Port 			1883												 //�������Ӱ����ƵĶ˿ں�
#define ESP8266_Reconnect		1                    //�����Ƿ��Զ�����   0�����Զ�����   1���Զ�����
#define ESP8266_Post_re			"/sys/***/DHT11_Test/thing/event/property/post_reply"//���İ����Ƶ�Topic
#define ESP8266_Post			"/sys/***/DHT11_Test/thing/event/property/post"//���İ����Ƶ�Topic


#define  ESP8266_SET          "/sys/***/DHT11_Test/thing/service/property/set"


extern uint8_t temperature;
extern uint8_t humidity;
extern uint8_t LED_Switch;
void wifi_init(void);
void create_Json(uint8_t temperature,uint8_t humidity);
void rcv_json(void);
#endif /* WIFI_WIFI_H_ */
