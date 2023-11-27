#include <ioCC2530.h>

#define uchar unsigned char
#define uint unsigned int
void InitUart();              //初始化串口
void Uart_Send_String(unsigned char *Data,int len);

/**************************************************************** 
   串口初始化函数     
***********************************************************/
void InitUart()
{
    CLKCONCMD &= ~0x40; // 设置系统时钟源为 32MHZ晶振
    while(CLKCONSTA & 0x40);                     // 等待晶振稳定 
    CLKCONCMD &= ~0x47;                          // 设置系统主时钟频率为 32MHZ

  PERCFG&=~0x01;   //有2个备用位置，0使用备用位置1；1使用备用位置2
  P0SEL |= 0x0C;   //P0_2 RXD P0_3 TXD 外设功能 0000 1100
 
  U0CSR |= 0xC0;  //串口接收使能  1100 0000 工作UART模式+允许接受
  U0UCR |= 0x00;  //无奇偶校验，1位停止位
 
  U0GCR |= 11;           //U0GCR与U0BAUD配合     
  U0BAUD |= 216;       // 波特率设为115200 
 
  IEN0 |= 0X04;     //开串口接收中断 'URX0IE = 1',也可以写成 URX0IE=1;
  EA=1;
    
}

void Uart0_SendCh(char ch)
{
    U0DBUF = ch;
    while(UTX0IF == 0);
    UTX0IF = 0;
}
/**************************************************************** 
串口发送字符串函数    
****************************************************************/ 
void Uart_Send_String(unsigned char *Data,int len) 
{
 { 
  int j; 
  for(j=0;j<len;j++) 
  { 
     Uart0_SendCh(*Data++); 
  } 
 }
}
