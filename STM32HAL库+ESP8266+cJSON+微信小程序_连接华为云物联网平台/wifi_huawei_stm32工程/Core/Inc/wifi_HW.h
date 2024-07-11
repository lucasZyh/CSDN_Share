#ifndef _WIFI_HW_H_
#define _WIFI_HW_H_

#include "stm32f4xx_hal.h"

// Wi-Fi用户名和密码
#define WIFI_User 						 "***"  // Wi-Fi网络名称
#define WIFI_Pass   					 "***"  // Wi-Fi网络密码

// ESP8266设备在华为云IoT平台的认证信息
#define ESP8266_UserName 				 "***"  // 用户名，通常为设备ID
#define ESP8266_PassWord				 "***"  // 密码或密钥
#define ESP8266_ClientID				 "***"  // MQTT客户端ID
#define ESP8266_Domain_Name				 "***"  // 华为云IoT平台的域名
#define ESP8266_Port 					 1883  // MQTT服务端口
#define ESP8266_Reconnect				 1  // 是否允许设备在断开连接后尝试重新连接

// 华为云MQTT服务相关设置
#define HUAWEI_MQTT_ServiceID			 "***"  // 服务ID
#define HUAWEI_MQTT_DeviceID	         "***"  // 设备ID
#define HUAWEI_MQTT_commands             "$oc/devices/***/sys/commands/#"  // 命令订阅主题
#define HUAWEI_MQTT_commands_response    "$oc/devices/***/sys/commands/response/request_id="  // 命令响应主题
#define HUAWEI_MQTT_report               "$oc/devices/***/sys/properties/report"  // 属性上报主题




extern uint8_t temperature;
extern uint8_t humidity;
extern uint8_t LED_Switch;
extern uint8_t temp_LED_Switch;
void wifi_init(void);
void report_Json(uint8_t temperature,uint8_t humidity,uint8_t adcx);
void rcv_json(void);
#endif
