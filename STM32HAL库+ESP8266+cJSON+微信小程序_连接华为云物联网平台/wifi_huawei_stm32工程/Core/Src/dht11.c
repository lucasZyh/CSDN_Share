/**
 ****************************************************************************************************
 * @file        dht11.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-26
 * @brief       DHT11������ʪ�ȴ����� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20200426
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "dht11.h"
#include "delay.h"

/**
 * @brief       ��λDHT11
 * @param       ��
 * @retval      ��
 */
static void dht11_reset(void)
{
    DHT11_DQ_OUT(0);    /* ����DQ */
    delay_ms(20);       /* ��������18ms */
    DHT11_DQ_OUT(1);    /* DQ=1 */
    delay_us(30);       /* ��������10~35us */
}

/**
 * @brief       �ȴ�DHT11�Ļ�Ӧ
 * @param       ��
 * @retval      0, DHT11����
 *              1, DHT11�쳣/������
 */
uint8_t dht11_check(void)
{
    uint8_t retry = 0;
    uint8_t rval = 0;

    while (DHT11_DQ_IN && retry < 100)  /* DHT11������Լ83us */
    {
        retry++;
        delay_us(1);
    }

    if (retry >= 100)
    {
        rval = 1;
    }
    else
    {
        retry = 0;

        while (!DHT11_DQ_IN && retry < 100) /* DHT11���ͺ���ٴ�����Լ87us */
        {
            retry++;
            delay_us(1);
        }
        if (retry >= 100) rval = 1;
    }
    
    return rval;
}

/**
 * @brief       ��DHT11��ȡһ��λ
 * @param       ��
 * @retval      ��ȡ����λֵ: 0 / 1
 */
uint8_t dht11_read_bit(void)
{
    uint8_t retry = 0;

    while (DHT11_DQ_IN && retry < 100)  /* �ȴ���Ϊ�͵�ƽ */
    {
        retry++;
        delay_us(1);
    }

    retry = 0;

    while (!DHT11_DQ_IN && retry < 100) /* �ȴ���ߵ�ƽ */
    {
        retry++;
        delay_us(1);
    }

    delay_us(40);       /* �ȴ�40us */

    if (DHT11_DQ_IN)    /* ��������״̬���� bit */
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

/**
 * @brief       ��DHT11��ȡһ���ֽ�
 * @param       ��
 * @retval      ����������
 */
static uint8_t dht11_read_byte(void)
{
    uint8_t i, data = 0;

    for (i = 0; i < 8; i++)         /* ѭ����ȡ8λ���� */
    {
        data <<= 1;                 /* ��λ���������, ������һλ */
        data |= dht11_read_bit();   /* ��ȡ1bit���� */
    }

    return data;
}

/**
 * @brief       ��DHT11��ȡһ������
 * @param       temp: �¶�ֵ(��Χ:-20~60��)
 * @param       humi: ʪ��ֵ(��Χ:5%~95%)
 * @retval      0, ����.
 *              1, ʧ��
 */
uint8_t dht11_read_data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5];
    uint8_t i;
    dht11_reset();

    if (dht11_check() == 0)
    {
        for (i = 0; i < 5; i++)     /* ��ȡ40λ���� */
        {
            buf[i] = dht11_read_byte();
        }

        if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])
        {
            *humi = buf[0];
            *temp = buf[2];
        }
    }
    else
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief       ��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
 * @param       ��
 * @retval      0, ����
 *              1, ������/������
 */
uint8_t dht11_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    DHT11_DQ_GPIO_CLK_ENABLE();     /* ����DQ����ʱ�� */

    gpio_init_struct.Pin = DHT11_DQ_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_OD;            /* ��©��� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(DHT11_DQ_GPIO_PORT, &gpio_init_struct);   /* ��ʼ��DHT11_DQ���� */
    /* DHT11_DQ����ģʽ����,��©���,����, �����Ͳ���������IO������, ��©�����ʱ��(=1), Ҳ���Զ�ȡ�ⲿ�źŵĸߵ͵�ƽ */

    dht11_reset();
    return dht11_check();
}
























