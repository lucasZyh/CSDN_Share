#ifndef __ESP8266_H__
#define __ESP8266_H__
#include "stm32f4xx_hal.h"

#define ATK_MW8266D_EOK         0   /* û�д��� */
#define ATK_MW8266D_ERROR       1   /* ͨ�ô��� */
#define ATK_MW8266D_ETIMEOUT    2   /* ��ʱ���� */
#define ATK_MW8266D_EINVAL      3   /* �������� */

										
uint8_t ESP8266_Sent_AT(char *cmd, char *ack, uint32_t timeout); 
uint8_t ESP8266_Reset(void);
uint8_t ESP8066_Mode(uint8_t mode);
uint8_t ESP8266_AT(void);
uint8_t ESP8266_ATE(uint8_t cfg);
uint8_t ESP8266_WiFi(char *ssid, char *pwd);
uint8_t ESP8266_MQTTUSERCFG(char *UserName, char *PassWord);
uint8_t ESP8266_MQTTCLIENTID(char *ClientID);
uint8_t ESP8266_MQTTCONN(char *Domain_Name,int Port,int Reconnect);
uint8_t ESP8266_MQTTSUB(char *Post);

#endif
