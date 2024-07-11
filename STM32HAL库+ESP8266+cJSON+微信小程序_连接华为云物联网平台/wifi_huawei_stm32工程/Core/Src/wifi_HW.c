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
    uint8_t cmd[1024]; // ���ڴ洢������AT����
    char *str = NULL; // ָ��JSON�ַ�����ָ��
    int i = 0; // ѭ����������
    uint8_t params_buf[1024]; // ���ڴ洢�������JSON�ַ���
    uint16_t move_num = 0; // ���ڼ�¼�ַ�����������е��ƶ�����
    
    cJSON *json = cJSON_CreateObject(); // ����һ���յ�JSON����
    cJSON *properties_cjson = cJSON_CreateObject(); // ����һ���յ���JSON�������ڴ洢����
    cJSON *service = cJSON_CreateObject(); // ����һ���յ���JSON�������ڴ洢������Ϣ
    cJSON *services_array = cJSON_CreateArray(); // ����һ���յ�JSON���飬���ڴ洢��������
	
	// �����Զ���������¶ȡ�ʪ�Ⱥ͹���ǿ������
    cJSON_AddNumberToObject(properties_cjson, "temperature", temperature);
    cJSON_AddNumberToObject(properties_cjson, "humidity", humidity);
	cJSON_AddNumberToObject(properties_cjson, "light", adcx);
    // ������������ӷ���ID������
	cJSON_AddStringToObject(service, "service_id", "yun");
    cJSON_AddItemToObject(service, "properties", properties_cjson);
	cJSON_AddItemToObject(json, "services", services_array);
	 // ������������ӵ�JSON������
	cJSON_AddItemToArray(services_array, service);
    
    // ��JSON����ת��Ϊ�޸�ʽ���ַ���
    str = cJSON_PrintUnformatted(json);
    
    // ��ӡJSON��ʽ���ַ���
    //printf("json��ʽ = %s\r\n", str);
    
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
    //printf("params_buf = %s\r\n", params_buf);
    
    // ����AT����
    sprintf((char *)cmd,"AT+MQTTPUB=0,\""HUAWEI_MQTT_report"\",\"%s\",0,0\r\n",params_buf);
    
    // ��ӡ�������͵�AT����
    //printf("��ʼ��������:%s", cmd);

    // ����AT���ͨ��ESP8266ģ��
    ESP8266_Sent_AT(cmd, "OK", 500);
    
    // ����JSON����ռ�õ��ڴ�
    cJSON_Delete(json);
    
    // ��������˶�����ַ����ռ䣬�ͷ���
    if(str != NULL){
        free(str);
        str = NULL;
        //printf("�ͷ�str�ռ�ɹ�\r\n");
    }
}


void rcv_json(void){
    uint8_t *ret = NULL; // ���ڴ洢���յ�������֡
    cJSON *cjson = NULL; // ���ڴ洢�������JSON����
    char topic_buff[1024]; // ���ڴ洢MQTT����
    int num; // ���ڴ洢�������ݵ�����
    char recv_buffer[1024]; // ���ڴ洢���յ���JSON����
	char request_id[37];
	char device_id[256];
	uint8_t cmd[1024]; // ���ڴ洢������AT����
    
    ret = atk_mw8266d_uart_rx_get_frame(); // ��ȡUART���յ�������֡
    atk_mw8266d_uart_rx_restart(); // ����UART����
	
    char *ptr_recv = strstr((const char *)ret,"+MQTTSUBRECV"); // ����Ƿ����MQTT�������ݱ�־
    
    if(ptr_recv!=NULL){ // �����MQTT��������
        memset(device_id,0,sizeof(device_id)); 
		memset(request_id,0,sizeof(request_id)); 
        
		sscanf((char *)ret, "+MQTTSUBRECV:0,\"$oc/devices/%255[^/]/sys/commands/request_id=%36s\",%d,%255s", device_id, request_id, &num, recv_buffer);
		
		//printf("�ж�DeviceID:  %s\r\n",device_id);
		
		// printf("�������ݳɹ�����ʼ����  %s\r\n",recv_buffer);
		//�ж�DeviceID
        if(strstr(device_id,HUAWEI_MQTT_DeviceID)) {
            // printf("�������ݳɹ�����ʼ����  %s\r\n",recv_buffer);
            cjson = cJSON_Parse(recv_buffer); // ����JSON����
        }
        
        if(cjson==NULL) // ���JSON����ʧ��
            printf("cjson ��������\r\n"); // ��ӡ������Ϣ
        else{
            cJSON *json_data = cJSON_GetObjectItem(cjson,"paras"); // ��ȡJSON�����е�paras��
            if(json_data==NULL){ 
                printf("cjson  û������\r\n"); // ��ӡ������Ϣ
                return;
            }
            else{
                // printf("cjson �ڴ��СΪ = %d\r\n",sizeof(cjson)); // ��ӡJSON������ڴ��С
                // ��������
                if(cJSON_GetObjectItem(json_data,"led_flag")!=NULL) 
                {
                    LED_Switch = cJSON_GetObjectItem(json_data,"led_flag")->valueint; 
                    printf("csjon�����ɹ� LED_Switch = %d\r\n",LED_Switch); 

                }
                if(cJSON_GetObjectItem(json_data,"temp_flag")!=NULL) 
                {
                    temp_LED_Switch = cJSON_GetObjectItem(json_data,"temp_flag")->valueint; 
                    printf("csjon�����ɹ� temp_LED_Switch = %d\r\n",temp_LED_Switch);
                }
				char full_topic[256];    
				snprintf(full_topic, sizeof(full_topic), "%s%s", HUAWEI_MQTT_commands_response, request_id);
				sprintf((char *)cmd, "AT+MQTTPUB=0,\"%s\",\"\",0,0\r\n", full_topic);
				ESP8266_Sent_AT(cmd, "OK", 500);
            }
            cJSON_Delete(cjson); // ɾ��JSON�����ͷ��ڴ�
            //cJSON_Delete(json_data);
        }
    }
}
