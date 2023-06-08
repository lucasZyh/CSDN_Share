#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Timer.h"

uint32_t CountOfToggle;//��������
uint8_t flag = 0;//��־λ

int main(void)
{
	OLED_Init();
	Timer_Init();
	LED_Init();
	
	OLED_ShowString(1, 1, "Num:");
	
	while (1)
	{
		OLED_ShowNum(1, 5, CountOfToggle / 2, 5);
		if(flag == 1)
		{
			LED1_Turn();
			flag = 0;
			CountOfToggle++;
		}
	}
}

void TIM2_IRQHandler(void)
{
	//�ж��ж�
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		flag = 1;
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
