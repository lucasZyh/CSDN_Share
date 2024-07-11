#ifndef _WIFI_HW_H_
#define _WIFI_HW_H_

#include "stm32f4xx_hal.h"

// Wi-Fi�û���������
#define WIFI_User 						 "***"  // Wi-Fi��������
#define WIFI_Pass   					 "***"  // Wi-Fi��������

// ESP8266�豸�ڻ�Ϊ��IoTƽ̨����֤��Ϣ
#define ESP8266_UserName 				 "***"  // �û�����ͨ��Ϊ�豸ID
#define ESP8266_PassWord				 "***"  // �������Կ
#define ESP8266_ClientID				 "***"  // MQTT�ͻ���ID
#define ESP8266_Domain_Name				 "***"  // ��Ϊ��IoTƽ̨������
#define ESP8266_Port 					 1883  // MQTT����˿�
#define ESP8266_Reconnect				 1  // �Ƿ������豸�ڶϿ����Ӻ�����������

// ��Ϊ��MQTT�����������
#define HUAWEI_MQTT_ServiceID			 "***"  // ����ID
#define HUAWEI_MQTT_DeviceID	         "***"  // �豸ID
#define HUAWEI_MQTT_commands             "$oc/devices/***/sys/commands/#"  // ���������
#define HUAWEI_MQTT_commands_response    "$oc/devices/***/sys/commands/response/request_id="  // ������Ӧ����
#define HUAWEI_MQTT_report               "$oc/devices/***/sys/properties/report"  // �����ϱ�����




extern uint8_t temperature;
extern uint8_t humidity;
extern uint8_t LED_Switch;
extern uint8_t temp_LED_Switch;
void wifi_init(void);
void report_Json(uint8_t temperature,uint8_t humidity,uint8_t adcx);
void rcv_json(void);
#endif
