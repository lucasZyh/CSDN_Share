#include "usart.h"
#include "esp8266.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief       ATK-MW8266D����ATָ��
 * @param       cmd    : �����͵�ATָ��
 *              ack    : �ȴ�����Ӧ
 *              timeout: �ȴ���ʱʱ��
 * @retval      ATK_MW8266D_EOK     : ����ִ�гɹ�
 *              ATK_MW8266D_ETIMEOUT: �ȴ�����Ӧ��ʱ������ִ��ʧ��
 */
uint8_t ESP8266_Sent_AT(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
    atk_mw8266d_uart_rx_restart();
    atk_mw8266d_uart_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0))
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        while (timeout > 0)
        {
            ret = atk_mw8266d_uart_rx_get_frame(); 		
            if (ret != NULL)
            {
                if (strstr((const char *)ret, ack) != NULL)
                {
                    return ATK_MW8266D_EOK;
                }
                else
                {
                    atk_mw8266d_uart_rx_restart();
                }
            }
            timeout--;
            HAL_Delay(1);
        }
        
        return ATK_MW8266D_ETIMEOUT;
    }
}

// ����AT+RST
uint8_t ESP8266_Reset(void)
{
    uint8_t ret;
    
    ret = ESP8266_Sent_AT("AT+RST", "OK", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

// ����AT
uint8_t ESP8266_AT(void)
{
    uint8_t ret;
    
    ret = ESP8266_Sent_AT("AT", "OK", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ����ATK-MW8266D����ģʽ
 * @param       mode: 1��Stationģʽ
 *                    2��APģʽ
 *                    3��AP+Stationģʽ
 * @retval      ATK_MW8266D_EOK   : ����ģʽ���óɹ�
 *              ATK_MW8266D_ERROR : ����ģʽ����ʧ��
 *              ATK_MW8266D_EINVAL: mode�������󣬹���ģʽ����ʧ��
 */
uint8_t ESP8066_Mode(uint8_t mode)
{
    uint8_t ret;
    
    switch (mode)
    {
        case 1:
        {
            ret = ESP8266_Sent_AT("AT+CWMODE=1", "OK", 500);    /* Stationģʽ */
            break;
        }
        case 2:
        {
            ret = ESP8266_Sent_AT("AT+CWMODE=2", "OK", 500);    /* APģʽ */
            break;
        }
        case 3:
        {
            ret = ESP8266_Sent_AT("AT+CWMODE=3", "OK", 500);    /* AP+Stationģʽ */
            break;
        }
        default:
            return ATK_MW8266D_EINVAL;

    }
    
    if (ret == ATK_MW8266D_EOK)
        return ATK_MW8266D_EOK;
    else
        return ATK_MW8266D_ERROR;
}



/**
 * @brief       ATK-MW8266D���û���ģʽ
 * @param       cfg: 0���رջ���
 *                   1���򿪻���
 * @retval      ATK_MW8266D_EOK  : ���û���ģʽ�ɹ�
 *              ATK_MW8266D_ERROR: ���û���ģʽʧ��
 */
uint8_t ESP8266_ATE(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = ESP8266_Sent_AT("ATE0", "OK", 500);   /* �رջ��� */
            break;
        }
        case 1:
        {
            ret = ESP8266_Sent_AT("ATE1", "OK", 500);   /* �򿪻��� */
            break;
        }
        default:
            return ATK_MW8266D_EINVAL;
    }
    
    if (ret == ATK_MW8266D_EOK)
        return ATK_MW8266D_EOK;
    else
        return ATK_MW8266D_ERROR;
}

// ����WiFi
uint8_t ESP8266_WiFi(char *ssid, char *pwd)
{
    uint8_t ret;
    char cmd[126];
    
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
    ret = ESP8266_Sent_AT(cmd, "OK", 3000);
    if (ret == ATK_MW8266D_EOK)
        return ATK_MW8266D_EOK;
    else
        return ATK_MW8266D_ERROR;
}

//�����û���������
uint8_t ESP8266_MQTTUSERCFG(char *UserName, char *PassWord)
{
    uint8_t ret;
    char cmd[512];
   sprintf(cmd, "AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n",UserName,PassWord);
   ret = ESP8266_Sent_AT(cmd, "OK", 1000);
    if (ret == ATK_MW8266D_EOK)
        return ATK_MW8266D_EOK;
    else
        return ATK_MW8266D_ERROR;
}


//����ClientID
uint8_t ESP8266_MQTTCLIENTID(char *ClientID)
{
    uint8_t ret;
    char cmd[512];
   sprintf(cmd, "AT+MQTTCLIENTID=0,\"%s\"\r\n",ClientID);
   ret = ESP8266_Sent_AT(cmd, "OK", 1000);
    if (ret == ATK_MW8266D_EOK)
        return ATK_MW8266D_EOK;
    else
        return ATK_MW8266D_ERROR;
}

//���Ӱ����Ʒ�����
uint8_t ESP8266_MQTTCONN(char *Domain_Name,int Port,int Reconnect)
{
    uint8_t ret;
    char cmd[512];
   sprintf(cmd, "AT+MQTTCONN=0,\"%s\",%d,%d\r\n",Domain_Name,Port,Reconnect);
   ret = ESP8266_Sent_AT(cmd, "OK", 1000);

    if (ret == ATK_MW8266D_EOK)
        return ATK_MW8266D_EOK;
    else
        return ATK_MW8266D_ERROR;
}

//���İ����Ʒ���Topic
uint8_t ESP8266_MQTTSUB(char *Post)
{
    uint8_t ret;
    char cmd[512];
   sprintf(cmd, "AT+MQTTSUB=0,\"%s\",1\r\n",Post);
   ret = ESP8266_Sent_AT(cmd, "OK", 1000);
    if (ret == ATK_MW8266D_EOK)
        return ATK_MW8266D_EOK;
    else
        return ATK_MW8266D_ERROR;
}
