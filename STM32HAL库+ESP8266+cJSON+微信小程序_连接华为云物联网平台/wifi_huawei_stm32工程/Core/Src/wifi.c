#include "wifi.h"
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
	ret =  ESP8266_MQTTSUB(ESP8266_Post_re);
	printf("8: %d\r\n",ret);
	
	if (ret != 0)
        printf("Error to join ap!\r\n");
}



void create_Json(uint8_t temperature, uint8_t humidity){
    uint8_t cmd[1024]; // 用于存储构建的AT命令
    char *str = NULL; // 指向JSON字符串的指针
    int i = 0; // 循环迭代变量
    uint8_t params_buf[1024]; // 用于存储处理过的JSON字符串
    uint16_t move_num = 0; // 用于记录字符串处理过程中的移动次数
    
    cJSON *json = cJSON_CreateObject(); // 创建一个空的JSON对象
    cJSON *params_cjson = cJSON_CreateObject(); // 创建一个空的子JSON对象
    
    // 向子JSON对象添加数据
    cJSON_AddNumberToObject(params_cjson, "Humidity", humidity);
    cJSON_AddNumberToObject(params_cjson, "temperature", temperature);
    cJSON_AddNumberToObject(params_cjson, "LEDSwitch", LED_Switch);
    
    // 向主JSON对象添加数据
    cJSON_AddItemToObject(json, "method", cJSON_CreateString("thing.service.property.post"));
    cJSON_AddItemToObject(json, "id", cJSON_CreateString("99119635"));
    cJSON_AddItemToObject(json, "params", params_cjson);
    cJSON_AddItemToObject(json, "version", cJSON_CreateString("1.0.0"));
    
    // 将JSON对象转换为无格式的字符串
    str = cJSON_PrintUnformatted(json);
    
    // 打印JSON格式的字符串
    printf("json格式 = %s\r\n", str);
    
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
    printf("params_buf = %s\r\n", params_buf);
    
    // 构建AT命令
    sprintf((char *)cmd,"AT+MQTTPUB=0,\""ESP8266_Post"\",\"%s\",0,0\r\n",params_buf);
    
    // 打印即将发送的AT命令
    printf("开始发送数据:%s\r\n", cmd);

    // 发送AT命令并通过ESP8266模块
    ESP8266_Sent_AT(cmd, "OK", 500);
    
    // 清理JSON对象占用的内存
    cJSON_Delete(json);
    
    // 如果分配了额外的字符串空间，释放它
    if(str != NULL){
        free(str);
        str = NULL;
        printf("释放str空间成功\r\n");
    }
}



/*
void create_Json(uint8_t temperature,uint8_t humidity){
	uint8_t cmd[1024];
	char *str = NULL;
	int i=0;
	uint8_t params_buf[1024];
	uint16_t move_num = 0;    													 //温度获取变量
	
	cJSON *json = cJSON_CreateObject();
	cJSON *params_cjson = cJSON_CreateObject(); 
	
	cJSON_AddNumberToObject(params_cjson,"Humidity",humidity);
	cJSON_AddNumberToObject(params_cjson,"temperature",temperature);
	cJSON_AddNumberToObject(params_cjson,"LEDSwitch",LED_Switch);
	
	cJSON_AddItemToObject(json, "method", cJSON_CreateString("thing.service.property.post"));
	cJSON_AddItemToObject(json, "id", cJSON_CreateString("99119635"));
	cJSON_AddItemToObject(json, "params", params_cjson);
	cJSON_AddItemToObject(json,"version",cJSON_CreateString("1.0.0"));
	str = cJSON_PrintUnformatted(json);
	
	printf("json格式 = %s\r\n",str);
	
	// 加转义字符
	for(i=0;*str!='\0';i++)
	{
		params_buf[i] = *str;
		if(*(str+1)=='"'||*(str+1)==',')
		{
			params_buf[++i] = '\\';
		}
		str++;
		move_num++;
		
	}
	str = str - move_num;
	printf("params_buf = %s\r\n",params_buf);
	
	
	// 整理所有数据
	sprintf((char *)cmd,"AT+MQTTPUB=0,\""ESP8266_Post"\",\"%s\",0,0\r\n",params_buf);
	
	printf("开始发送数据:%s\r\n",cmd);

	ESP8266_Sent_AT(cmd, "OK", 500);
	cJSON_Delete(json);
	if(str!=NULL){
		free(str);
		str = NULL;
		printf("释放str空间成功\r\n");
	}
}
*/



void rcv_json(void){
    uint8_t *ret = NULL; // 用于存储接收到的数据帧
    cJSON *cjson = NULL; // 用于存储解析后的JSON对象
    char topic_buff[1024]; // 用于存储MQTT主题
    int num; // 用于存储接收数据的数量
    char recv_buffer[1024]; // 用于存储接收到的JSON数据
    
    ret = atk_mw8266d_uart_rx_get_frame(); // 获取UART接收到的数据帧
    atk_mw8266d_uart_rx_restart(); // 重启UART接收
	
    char *ptr_recv = strstr((const char *)ret,"+MQTTSUBRECV"); // 检查是否包含MQTT订阅数据标志
    
    if(ptr_recv!=NULL){ // 如果是MQTT订阅数据
        memset(topic_buff,0,sizeof(topic_buff)); // 清空主题缓冲区
        
        sscanf((char *)ret,"+MQTTSUBRECV:0,%[^,],%d,%s",topic_buff,&num,recv_buffer); // 解析数据，提取主题、数据数量和JSON数据
        
        if(strstr(topic_buff,ESP8266_SET)) { // 如果主题包含特定标记
            printf("接收数据成功，开始解析  %s\r\n",recv_buffer); // 打印接收到的数据
            cjson = cJSON_Parse(recv_buffer); // 解析JSON数据
        }
        
        if(cjson==NULL) // 如果JSON解析失败
            printf("cjson 解析错误\r\n"); // 打印错误信息
        else{
            cJSON *json_data = cJSON_GetObjectItem(cjson,"params"); // 获取JSON对象中的params项
            if(json_data==NULL){ // 如果params项不存在
                printf("cjson  没有数据\r\n"); // 打印错误信息
                return;
            }
            else{
                printf("cjson 内存大小为 = %d\r\n",sizeof(cjson)); // 打印JSON对象的内存大小
                // 解析数据
                if(cJSON_GetObjectItem(json_data,"LEDSwitch")!=NULL) // 如果存在LEDSwitch键
                {
                    LED_Switch = cJSON_GetObjectItem(json_data,"LEDSwitch")->valueint; // 提取LEDSwitch的值
                    printf("csjon解析成功 LED_Switch = %d\r\n",LED_Switch); // 打印LEDSwitch的值
                }
            }
            cJSON_Delete(cjson); // 删除JSON对象，释放内存
            //cJSON_Delete(json_data);
        }
    }
}
/*
void rcv_json(void){
	uint8_t *ret = NULL;
	cJSON *cjson = NULL;
	char topic_buff[1024];
	int num;
	char recv_buffer[1024];
	
	ret = atk_mw8266d_uart_rx_get_frame(); 
	atk_mw8266d_uart_rx_restart();

	char *ptr_recv = strstr((const char *)ret,"+MQTTSUBRECV");
	
	if(ptr_recv!=NULL){
		memset(topic_buff,0,sizeof(topic_buff));

		sscanf((char *)ret,"+MQTTSUBRECV:0,%[^,],%d,%s",topic_buff,&num,recv_buffer);
		
		if(strstr(topic_buff,ESP8266_SET)) {
			printf("接收数据成功，开始解析  %s\r\n",recv_buffer);
			cjson = cJSON_Parse(recv_buffer);
		}
		
		if(cjson==NULL)
			printf("cjson 解析错误\r\n");
		else{
			cJSON *json_data = cJSON_GetObjectItem(cjson,"params");
			if(json_data==NULL){
				printf("cjson  没有数据\r\n");
				return;
			}
			else{
				printf("cjson 内存大小为 = %d\r\n",sizeof(cjson));
//					printf("数据接收：%s\r\n",esp_buff);
					// ====================================解析数据=========================================
				if(cJSON_GetObjectItem(json_data,"LEDSwitch")!=NULL)
				{
					LED_Switch = cJSON_GetObjectItem(json_data,"LEDSwitch")->valueint;
					printf("csjon解析成功 LED_Switch = %d\r\n",LED_Switch);
				}
			}
			cJSON_Delete(cjson);
			//cJSON_Delete(json_data);
		}
	}
	
}
*/	

