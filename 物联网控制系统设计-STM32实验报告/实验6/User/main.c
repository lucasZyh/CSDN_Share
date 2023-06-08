#include "stm32f10x.h"                  // Device header
#include "Delay.h" 
#include "OLED.h" 
#include "AD.h" 

uint16_t value;
float V;
int main(){
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"V:0.00V");
	while(1){
		value = AD_GetValue();
		V = (float)value /4095 * 3.3;
		OLED_ShowNum(1,9,value,4);
		OLED_ShowNum(2,3,V,1);
		OLED_ShowNum(2,5,(uint16_t)(V*100)%100,2);
		
	}
}
