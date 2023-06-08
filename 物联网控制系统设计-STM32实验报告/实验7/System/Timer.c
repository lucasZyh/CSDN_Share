#include "stm32f10x.h"                  // Device header

void Timer_Init(void){
	//开启时钟，TIM2是APB1的时钟外设
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    	
	//选择时基单元的时钟，可以不选，默认上电后选择内部时钟
	TIM_InternalClockConfig(TIM2);
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定时钟分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数器模式
	TIM_TimeBaseInitStructure.TIM_Period = 5000 - 1;//ARR自动重装器的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;//PSC预分频器的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器的值，高级定时器使用
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
    //手动清除中断标志位，避免刚初始化完就进入中断
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	
	//使能中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//启动定时器
	TIM_Cmd(TIM2,ENABLE);
    
}