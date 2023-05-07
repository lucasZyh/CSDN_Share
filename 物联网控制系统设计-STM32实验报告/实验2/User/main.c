#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "LED.h"
#include "MyUSART.h"


uint8_t Dta = 0;

int main(){
	LCD_Init();
	MyUSART_Init();
	
	printf("Hello World\r\n");
	while(1){
		//接收数据
		Dta = MyUSART_ReceiveData();
		

		if(Dta == 1)//LED1闪烁
		{
			LED1_Turn();
			Delay_ms(100);
			LED1_Turn();
			Delay_ms(100);
		}
		else if(Dta == 2)//LED2闪烁
		{
			LED2_Turn();
			Delay_ms(100);
			LED2_Turn();
			Delay_ms(100);
		}
		else if(Dta == 3)//LED3闪烁
		{
			LED3_Turn();
			Delay_ms(100);
			LED3_Turn();
			Delay_ms(100);
		}
		else//LED熄灭
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
		}
		
	}
}

