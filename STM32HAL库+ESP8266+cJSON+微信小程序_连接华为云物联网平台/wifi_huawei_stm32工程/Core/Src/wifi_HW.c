#include "wifi_HW.h"
#include "esp8266.h"
#include <stdio.h>
#include "cJSON.h"
#include "string.h"
#include "stdlib.h"
#include "usart.h"

void wifi_init(void){
	uint8_t ret = 0;
	ret  = ESP8266_Reset();
	printf("1: %d\r\n",ret);
	ret = ESP8266_ATE(0);
	printf("2: %d\r\n",ret);
	ret = ESP8066_Mode(1);
	printf("3: %d\r\n",ret);
	ret = ESP8266_WiFi(WIFI_User, WIFI_Pass);
	printf("4: %d\r\n",ret);
	ret = ESP8266_MQTTUSERCFG(ESP8266_UserName, ESP8266_PassWord);
	printf("5: %d\r\n",ret);
	ret = ESP8266_MQTTCLIENTID(ESP8266_ClientID);
	printf("6: %d\r\n",ret);
	ret =  ESP8266_MQTTCONN(ESP8266_Domain_Name,ESP8266_Port,ESP8266_Reconnect);
	printf("7: %d\r\n",ret);
	ret =  ESP8266_MQTTSUB(HUAWEI_MQTT_commands);
	printf("8: %d\r\n",ret);
}



void report_Json(uint8_t temperature, uint8_t humidity,uint8_t adcx){
    uint8_t cmd[1024]; // 用于存储构建的AT命令
    char *str = NULL; // 指向JSON字符串的指针
    int i = 0; // 循环迭代变量
    uint8_t params_buf[1024]; // 用于存储处理过的JSON字符串
    uint16_t move_num = 0; // 用于记录字符串处理过程中的移动次数
    
    cJSON *json = cJSON_CreateObject(); // 创建一个空的JSON对象
    cJSON *properties_cjson = cJSON_CreateObject(); // 创建一个空的子JSON对象，用于存储属性
    cJSON *service = cJSON_CreateObject(); // 创建一个空的子JSON对象，用于存储服务信息
    cJSON *services_array = cJSON_CreateArray(); // 创建一个空的JSON数组，用于存储服务数组
	
	// 向属性对象中添加温度、湿度和光照强度数据
    cJSON_AddNumberToObject(properties_cjson, "temperature", temperature);
    cJSON_AddNumberToObject(properties_cjson, "humidity", humidity);
	cJSON_AddNumberToObject(properties_cjson, "light", adcx);
    // 向服务对象中添加服务ID和属性
	cJSON_AddStringToObject(service, "service_id", "yun");
    cJSON_AddItemToObject(service, "properties", properties_cjson);
	cJSON_AddItemToObject(json, "services", services_array);
	 // 将服务数组添加到JSON对象中
	cJSON_AddItemToArray(services_array, service);
    
    // 将JSON对象转换为无格式的字符串
    str = cJSON_PrintUnformatted(json);
    
    // 打印JSON格式的字符串
    //printf("json格式 = %s\r\n", str);
    
    // 为MQTT发布添加转义字符
    for(i = 0; *str != '\0'; i++){
        params_buf[i] = *str;
        // 如果下一个字符是引号或逗号，添加转义字符
        if(*(str + 1) == '"' || *(str + 1) == ','){
            params_buf[++i] = '\\';
        }
        str++;
        move_num++;
    }
    str = str - move_num; // 回退指针到JSON字符串的开始
    
    // 打印处理过的JSON字符串
    //printf("params_buf = %s\r\n", params_buf);
    
    // 构建AT命令
    sprintf((char *)cmd,"AT+MQTTPUB=0,\""HUAWEI_MQTT_report"\",\"%s\",0,0\r\n",params_buf);
    
    // 打印即将发送的AT命令
    //printf("开始发送数据:%s", cmd);

    // 发送AT命令并通过ESP8266模块
    ESP8266_Sent_AT(cmd, "OK", 500);
    
    // 清理JSON对象占用的内存
    cJSON_Delete(json);
    
    // 如果分配了额外的字符串空间，释放它
    if(str != NULL){
        free(str);
        str = NULL;
        //printf("释放str空间成功\r\n");
    }
}


void rcv_json(void){
    uint8_t *ret = NULL; // 用于存储接收到的数据帧
    cJSON *cjson = NULL; // 用于存储解析后的JSON对象
    char topic_buff[1024]; // 用于存储MQTT主题
    int num; // 用于存储接收数据的数量
    char recv_buffer[1024]; // 用于存储接收到的JSON数据
	char request_id[37];
	char device_id[256];
	uint8_t cmd[1024]; // 用于存储构建的AT命令
    
    ret = atk_mw8266d_uart_rx_get_frame(); // 获取UART接收到的数据帧
    atk_mw8266d_uart_rx_restart(); // 重启UART接收
	
    char *ptr_recv = strstr((const char *)ret,"+MQTTSUBRECV"); // 检查是否包含MQTT订阅数据标志
    
    if(ptr_recv!=NULL){ // 如果是MQTT订阅数据
        memset(device_id,0,sizeof(device_id)); 
		memset(request_id,0,sizeof(request_id)); 
        
		sscanf((char *)ret, "+MQTTSUBRECV:0,\"$oc/devices/%255[^/]/sys/commands/request_id=%36s\",%d,%255s", device_id, request_id, &num, recv_buffer);
		
		//printf("判断DeviceID:  %s\r\n",device_id);
		
		// printf("接收数据成功，开始解析  %s\r\n",recv_buffer);
		//判断DeviceID
        if(strstr(device_id,HUAWEI_MQTT_DeviceID)) {
            // printf("接收数据成功，开始解析  %s\r\n",recv_buffer);
            cjson = cJSON_Parse(recv_buffer); // 解析JSON数据
        }
        
        if(cjson==NULL) // 如果JSON解析失败
            printf("cjson 解析错误\r\n"); // 打印错误信息
        else{
            cJSON *json_data = cJSON_GetObjectItem(cjson,"paras"); // 获取JSON对象中的paras项
            if(json_data==NULL){ 
                printf("cjson  没有数据\r\n"); // 打印错误信息
                return;
            }
            else{
                // printf("cjson 内存大小为 = %d\r\n",sizeof(cjson)); // 打印JSON对象的内存大小
                // 解析数据
                if(cJSON_GetObjectItem(json_data,"led_flag")!=NULL) 
                {
                    LED_Switch = cJSON_GetObjectItem(json_data,"led_flag")->valueint; 
                    printf("csjon解析成功 LED_Switch = %d\r\n",LED_Switch); 

                }
                if(cJSON_GetObjectItem(json_data,"temp_flag")!=NULL) 
                {
                    temp_LED_Switch = cJSON_GetObjectItem(json_data,"temp_flag")->valueint; 
                    printf("csjon解析成功 temp_LED_Switch = %d\r\n",temp_LED_Switch);
                }
				char full_topic[256];    
				snprintf(full_topic, sizeof(full_topic), "%s%s", HUAWEI_MQTT_commands_response, request_id);
				sprintf((char *)cmd, "AT+MQTTPUB=0,\"%s\",\"\",0,0\r\n", full_topic);
				ESP8266_Sent_AT(cmd, "OK", 500);
            }
            cJSON_Delete(cjson); // 删除JSON对象，释放内存
            //cJSON_Delete(json_data);
        }
    }
}
