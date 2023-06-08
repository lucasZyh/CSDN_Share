#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	
	Delay_us(1000);
	OLED_ShowString(1, 1, "ID:");
	ID = MPU6050_ReadID();
	OLED_ShowHexNum(1, 4, ID, 2);
	
	while (1)
	{
		MPU6050_ReadData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 9, GX, 5);
		OLED_ShowSignedNum(3, 9, GY, 5);
		OLED_ShowSignedNum(4, 9, GZ, 5);
	}
}
