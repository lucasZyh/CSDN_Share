#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "LED.h"

//****************实验一 跑马灯*****************
int main(){
	LCD_Init();//LED初始化
	while(1){
		//LED1闪烁
		LED1_Turn();
		Delay_ms(200);
		LED1_Turn();
		Delay_ms(200);
		//LED2闪烁
		LED2_Turn();
		Delay_ms(200);
		LED2_Turn();
		Delay_ms(200);
		//LED3闪烁
		LED3_Turn();
		Delay_ms(200);
		LED3_Turn();
		Delay_ms(200);
	}
}



