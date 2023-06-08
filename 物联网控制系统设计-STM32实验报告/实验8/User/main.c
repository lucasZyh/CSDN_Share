#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "OLED.h" 
#include "MyDMA.h"
#include "LED.h"

uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[] = {0, 0, 0, 0};

int main(){
	OLED_Init();
	LCD_Init();
	MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);//MDA初始化
	
	OLED_ShowString(1, 1, "DataA");
	OLED_ShowString(3, 1, "DataB");
	OLED_ShowHexNum(1, 8, (uint32_t)DataA, 8);
	OLED_ShowHexNum(3, 8, (uint32_t)DataB, 8);
	
	while(1){
		LED0_on();
		LED1_off();
		//显示转换前数据
		OLED_ShowHexNum(2, 1, DataA[0], 2);
		OLED_ShowHexNum(2, 4, DataA[1], 2);
		OLED_ShowHexNum(2, 7, DataA[2], 2);
		OLED_ShowHexNum(2, 10, DataA[3], 2);
		OLED_ShowHexNum(4, 1, DataB[0], 2);
		OLED_ShowHexNum(4, 4, DataB[1], 2);
		OLED_ShowHexNum(4, 7, DataB[2], 2);
		OLED_ShowHexNum(4, 10, DataB[3], 2);
		
		Delay_ms(1000);
		
		MyDMA_Transfer();//DMA数据转运
		LED1_on();
		LED0_off();
		//显示转换后数据
		OLED_ShowHexNum(2, 1, DataA[0], 2);
		OLED_ShowHexNum(2, 4, DataA[1], 2);
		OLED_ShowHexNum(2, 7, DataA[2], 2);
		OLED_ShowHexNum(2, 10, DataA[3], 2);
		OLED_ShowHexNum(4, 1, DataB[0], 2);
		OLED_ShowHexNum(4, 4, DataB[1], 2);
		OLED_ShowHexNum(4, 7, DataB[2], 2);
		OLED_ShowHexNum(4, 10, DataB[3], 2);

		Delay_ms(1000);
		
		DataA[0] ++;
		DataA[1] ++;
		DataA[2] ++;
		DataA[3] ++;
	}
}
