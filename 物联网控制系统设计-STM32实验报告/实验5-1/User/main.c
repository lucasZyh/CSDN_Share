#include "stm32f10x.h"                  // Device header
#include "OLED.h" 
#include "Timer.h" 
#include "LED.h"
#include "Delay.h"

uint16_t num = 0;

int main(){
	LCD_Init();
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Num:");
	while(1){ 
		OLED_ShowNum(2,2,num / 2,3);
	}
}

void TIM2_IRQHandler(void){
	//判断中断
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET){
		num++;
		if(num % 2 == 1)
			LED_on();
		if(num % 2 == 0)
			LED_off();
		//清除中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

