#ifndef __74LS164_8LED_H__
#define __74LS164_8LED_H__
#include<ioCC2530.h>
#define  LS164_DATA  P1_3
#define  LS164_CLK   P1_2
#define  UCHAR  unsigned char 
void LS164_Cfg();
void LS164_BYTE(UCHAR Data);//P1.3  DATA   P1.2  CLK
#endif