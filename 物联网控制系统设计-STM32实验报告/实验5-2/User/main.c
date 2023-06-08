#include "stm32f10x.h"                  // Device header
#include "OLED.h" 
#include "Timer.h" 
#include "Delay.h"

uint8_t  Caputer_Flag = 0;//捕获标准位
uint16_t Caputer_Value = 0;//捕获数值
uint8_t  Caputer_Read = 0;//计算读取脉冲时间标志位
uint16_t Capture_Period; // 自动重装载寄存器更新标志

int main(){
	uint32_t time = 0;
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1,1,"Num:");
	while(1){ 
		Delay_ms(10);
		if(Caputer_Read == 1)
		{
			time = Capture_Period * 65536 + Caputer_Value + 1;
			Caputer_Read = 0;
		}
		OLED_ShowNum(2,2,time / 1000000,3);
		OLED_ShowString(2,5,".");
		OLED_ShowNum(2,6,time % 1000000,6);
		OLED_ShowString(2,12,"s");
	}
}

//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 
	// 当要被捕获的信号的周期大于定时器的最长定时时，定时器就会溢出，产生更新中断
	// 这个时候我们需要把这个最长的定时周期加到捕获信号的时间里面去
	if (TIM_GetITStatus( TIM3, TIM_IT_Update) != RESET ) {
		Capture_Period ++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
	}

	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
	{
		if(Caputer_Flag == 0)//第一次捕获上升沿
		{
			TIM_SetCounter(TIM3, 0);//计数器清零
			Capture_Period = 0;//自动重装载寄存器更新标志清 0
			Caputer_Value = 0;//捕获时间清理
			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);//设置为下降沿捕获
			Caputer_Flag = 1;//捕获标志位置一
		}
		else
		{
			Caputer_Value = TIM_GetCapture1(TIM3);//获取捕获数据
			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising); //设置为上升沿捕获
			Caputer_Flag = 0;//捕获标志位清零
			Caputer_Read = 1;//读取时间标志位置一
		}
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
 
}

