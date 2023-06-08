#include "stm32f10x.h"                  // Device header

void Timer_Init(void){
	//����ʱ�ӣ�TIM2��APB1��ʱ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    	
	//ѡ��ʱ����Ԫ��ʱ�ӣ����Բ�ѡ��Ĭ���ϵ��ѡ���ڲ�ʱ��
	TIM_InternalClockConfig(TIM2);
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//������ģʽ
	TIM_TimeBaseInitStructure.TIM_Period = 5000 - 1;//ARR�Զ���װ����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;//PSCԤ��Ƶ����ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�ظ���������ֵ���߼���ʱ��ʹ��
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
    //�ֶ�����жϱ�־λ������ճ�ʼ����ͽ����ж�
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	
	//ʹ���ж�
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	//����NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//������ʱ��
	TIM_Cmd(TIM2,ENABLE);
    
}