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
    uint8_t cmd[1024]; // ���ڴ洢������AT����
    char *str = NULL; // ָ��JSON�ַ�����ָ��
    int i = 0; // ѭ����������
    uint8_t params_buf[1024]; // ���ڴ洢�������JSON�ַ���
    uint16_t move_num = 0; // ���ڼ�¼�ַ�����������е��ƶ�����
    
    cJSON *json = cJSON_CreateObject(); // ����һ���յ�JSON����
    cJSON *params_cjson = cJSON_CreateObject(); // ����һ���յ���JSON����
    
    // ����JSON�����������
    cJSON_AddNumberToObject(params_cjson, "Humidity", humidity);
    cJSON_AddNumberToObject(params_cjson, "temperature", temperature);
    cJSON_AddNumberToObject(params_cjson, "LEDSwitch", LED_Switch);
    
    // ����JSON�����������
    cJSON_AddItemToObject(json, "method", cJSON_CreateString("thing.service.property.post"));
    cJSON_AddItemToObject(json, "id", cJSON_CreateString("99119635"));
    cJSON_AddItemToObject(json, "params", params_cjson);
    cJSON_AddItemToObject(json, "version", cJSON_CreateString("1.0.0"));
	
    
    // ��JSON����ת��Ϊ�޸�ʽ���ַ���
    str = cJSON_PrintUnformatted(json);
    
    // ��ӡJSON��ʽ���ַ���
    printf("json��ʽ = %s\r\n", str);
    
    // ΪMQTT�������ת���ַ�
    for(i = 0; *str != '\0'; i++){
        params_buf[i] = *str;
        // �����һ���ַ������Ż򶺺ţ����ת���ַ�
        if(*(str + 1) == '"' || *(str + 1) == ','){
            params_buf[++i] = '\\';
        }
        str++;
        move_num++;
    }
    str = str - move_num; // ����ָ�뵽JSON�ַ����Ŀ�ʼ
    
    // ��ӡ�������JSON�ַ���
    printf("params_buf = %s\r\n", params_buf);
    
    // ����AT����
    sprintf((char *)cmd,"AT+MQTTPUB=0,\""ESP8266_Post"\",\"%s\",0,0\r\n",params_buf);
    
    // ��ӡ�������͵�AT����
    printf("��ʼ��������:%s\r\n", cmd);

    // ����AT���ͨ��ESP8266ģ��
    ESP8266_Sent_AT(cmd, "OK", 500);
    
    // ����JSON����ռ�õ��ڴ�
    cJSON_Delete(json);
    
    // ��������˶�����ַ����ռ䣬�ͷ���
    if(str != NULL){
        free(str);
        str = NULL;
        printf("�ͷ�str�ռ�ɹ�\r\n");
    }
}



void rcv_json(void){
	uint8_t cmd[1024]; // ���ڴ洢������AT����
    uint8_t *ret = NULL; // ���ڴ洢���յ�������֡
    cJSON *cjson = NULL; // ���ڴ洢�������JSON����
	cJSON *re_json = NULL;
	char *str = NULL;
    char topic_buff[1024]; // ���ڴ洢MQTT����
    int num; // ���ڴ洢�������ݵ�����
    char recv_buffer[1024]; // ���ڴ洢���յ���JSON����
    
    ret = atk_mw8266d_uart_rx_get_frame(); // ��ȡUART���յ�������֡
    atk_mw8266d_uart_rx_restart(); // ����UART����
	
    char *ptr_recv = strstr((const char *)ret,"+MQTTSUBRECV"); // ����Ƿ����MQTT�������ݱ�־
    
    if(ptr_recv!=NULL){ // �����MQTT��������
        memset(topic_buff,0,sizeof(topic_buff)); // ������⻺����
        
        sscanf((char *)ret,"+MQTTSUBRECV:0,%[^,],%d,%s",topic_buff,&num,recv_buffer); // �������ݣ���ȡ���⡢����������JSON����
        
        if(strstr(topic_buff,ESP8266_SET)) { // �����������ض����
            printf("�������ݳɹ�����ʼ����  %s\r\n",recv_buffer); // ��ӡ���յ�������
            cjson = cJSON_Parse(recv_buffer); // ����JSON����
			
        }
        
        if(cjson==NULL) // ���JSON����ʧ��
            printf("cjson ��������\r\n"); // ��ӡ������Ϣ
        else{
            cJSON *json_data = cJSON_GetObjectItem(cjson,"params"); // ��ȡJSON�����е�params��
            if(json_data==NULL){ // ���params�����
                printf("cjson  û������\r\n"); // ��ӡ������Ϣ
                return;
            }
            else{
                printf("cjson �ڴ��СΪ = %d\r\n",sizeof(cjson)); // ��ӡJSON������ڴ��С
                // ��������
                if(cJSON_GetObjectItem(json_data,"LEDSwitch")!=NULL) // �������LEDSwitch��
                {
                    LED_Switch = cJSON_GetObjectItem(json_data,"LEDSwitch")->valueint; // ��ȡLEDSwitch��ֵ
                    printf("csjon�����ɹ� LED_Switch = %d\r\n",LED_Switch); // ��ӡLEDSwitch��ֵ
					
					//������Ӧ
					sprintf((char *)cmd,"AT+MQTTPUB=0,\""ESP8266_Post_re"\",\"{\\\"code\\\": 200, \\\"data\\\": {}, \\\"id\\\": \\\"%s\\\", \\\"message\\\": \\\"success\\\", \\\"version\\\": \\\"1.0.0\\\"}\",0,0\r\n",cJSON_GetObjectItem(cjson,"id")->valuestring);
					printf("��ʼ��������:%s\r\n", cmd);
					ESP8266_Sent_AT(cmd, "OK", 500);
					//------
                }
            }
            cJSON_Delete(cjson); // ɾ��JSON�����ͷ��ڴ�
			
			//������Ӧ
            cJSON_Delete(re_json);
			if(str != NULL){
				free(str);
				str = NULL;
				printf("�ͷ�str�ռ�ɹ�\r\n");
			}
        }
    }
}
