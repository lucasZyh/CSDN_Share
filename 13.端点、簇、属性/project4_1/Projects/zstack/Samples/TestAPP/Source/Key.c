#include<iocc2530.h>
#include "TestApp.h"
#include "OSAL_Timers.h"
extern unsigned char TestAPP_TaskID;
void delay()
{
   int i,j;
   for(i=0;i<1000;i++)
     for(j=0;j<30;j++);
}
void KeysIntCfg()
{//Key3  Key4   Key5
     
     P1SEL &=~0X02;
     P1DIR &=~0X02;
     IEN2|=0x10;//开P1IE组中断
     P1IEN|=0x02;//开Key3组内中断
     PICTL|=0x02;//设置P1_1为下降沿
     
     P2SEL &=~0X01;
     P2DIR &=~0X01;
     IEN2|=0x02;
     P2IEN|=0x01;
     PICTL|=0x08;//设置P2_0为下降沿
     
     P0SEL &=~0X20;
     P0DIR &=~0X20;
     P0IE=1;//或者写成 IEN1|=0x20
     P0IEN|=0x20;
     PICTL|=0x01;//设置P0_5为下降沿
     
     
     EA=1;      //开总中断
}

#pragma vector=P1INT_VECTOR
__interrupt void Key3_ISR() //P1_1
{
     
     if(P1IFG & 0X02)
     {
        osal_start_timerEx(TestAPP_TaskID,TestAPP_EVT,25);
     }
     P1IFG =0;
     P1IF=0;
}
#pragma vector=P2INT_VECTOR
__interrupt void Key4_ISR()//P2_0
{

     if(P2IFG & 0X01)
     { 
        osal_start_timerEx(TestAPP_TaskID,TestAPP_EVT,25);
     }
     P2IFG =0;
     P2IF=0;
}
#pragma vector=P0INT_VECTOR
__interrupt void Key5_ISR()//P0_5
{

    if(P0IFG & 0X20)
    {
       osal_start_timerEx(TestAPP_TaskID,TestAPP_EVT,25);
    }
     P0IFG =0;
     P0IF=0;
}