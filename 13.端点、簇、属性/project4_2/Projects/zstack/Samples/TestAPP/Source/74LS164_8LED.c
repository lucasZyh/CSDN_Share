#include<ioCC2530.h>
#include"74LS164_8LED.h"
static UCHAR LED_Map[]={0x3f,0x06,0x5b,0x4f,
                        0x66,0x6d,0x7d,0x07,
                        0x7f,0x6f,0x00,\
                        0x39,/*'C'Э����*/\
                        0x77,/*'R'·����*/\
                        0x79/*'E'�ն�*/};
void LS164_Cfg()
{
    P1SEL &=~0x0C;//xxxx 00xx  ����Ϊ��ͨIOģʽ
    P1DIR |=0x0C;//xxxx 11xx   ����Ϊ���ģʽ
}
void LS164_BYTE(UCHAR Index) //P1.3  DATA   P1.2  CLK
{  
    UCHAR i=0;
    UCHAR Data=LED_Map[Index];
    for(;i<8;i++)
    {
        if(0x80 & Data)
        {
            LS164_DATA=1;            
        }
        else
        {
            LS164_DATA=0; 
        }
        Data=Data << 1;
        LS164_CLK=0;
        LS164_CLK=1;
    }
}