#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "OLED.h" 
#include "ESP.h" 
#include "MyUSART.h"
uint8_t Switch1;
uint8_t Switch2;
int main(){
	OLED_Init();
	MyUSART_Init(); 
	
	uint8_t Judge=0;
	OLED_Init();
	OLED_ShowString(1,1,"Linking...");
	do
	{
		Judge = esp_Init();
		OLED_ShowString(1,1,"error code:    ");
		OLED_ShowNum(2,1,Judge,1);
	}while(Judge);
	
	OLED_ShowString(3,1,"Lock    Switch");
//	OLED_ShowString(1,1,"Tempera  Humidi");
	
	while(1){
		OLED_ShowChar(4,2,Switch1);
		OLED_ShowChar(4,13,Switch2);
	}
}
