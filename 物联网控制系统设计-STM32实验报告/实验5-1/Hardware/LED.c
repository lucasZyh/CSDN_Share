#include "stm32f10x.h"                  // Device header

void LCD_Init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    	
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

void LED_on(void){
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}
void LED_off(void){
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
}
