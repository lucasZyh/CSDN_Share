#include "usart.h"
#include "esp8266.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief       ATK-MW8266D发送AT指令
 * @param       cmd    : 待发送的AT指令
 *              ack    : 等待的响应
 *              timeout: 等待超时时间
 * @retval      ATK_MW8266D_EOK     : 函数执行成功
 *              ATK_MW8266D_ETIMEOUT: 等待期望应答超时，函数执行失败
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

// 发送AT+RST
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

// 发送AT
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
 * @brief       设置ATK-MW8266D工作模式
 * @param       mode: 1，Station模式
 *                    2，AP模式
 *                    3，AP+Station模式
 * @retval      ATK_MW8266D_EOK   : 工作模式设置成功
 *              ATK_MW8266D_ERROR : 工作模式设置失败
 *              ATK_MW8266D_EINVAL: mode参数错误，工作模式设置失败
 */
uint8_t ESP8066_Mode(uint8_t mode)
{
    uint8_t ret;
    
    switch (mode)
    {
        case 1:
        {
            ret = ESP8266_Sent_AT("AT+CWMODE=1", "OK", 500);    /* Station模式 */
            break;
        }
        case 2:
        {
            ret = ESP8266_Sent_AT("AT+CWMODE=2", "OK", 500);    /* AP模式 */
            break;
        }
        case 3:
        {
            ret = ESP8266_Sent_AT("AT+CWMODE=3", "OK", 500);    /* AP+Station模式 */
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
 * @brief       ATK-MW8266D设置回显模式
 * @param       cfg: 0，关闭回显
 *                   1，打开回显
 * @retval      ATK_MW8266D_EOK  : 设置回显模式成功
 *              ATK_MW8266D_ERROR: 设置回显模式失败
 */
uint8_t ESP8266_ATE(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = ESP8266_Sent_AT("ATE0", "OK", 500);   /* 关闭回显 */
            break;
        }
        case 1:
        {
            ret = ESP8266_Sent_AT("ATE1", "OK", 500);   /* 打开回显 */
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

// 连接WiFi
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

//配置用户名和密码
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


//配置ClientID
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

//连接服务器
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

//订阅Topic
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
