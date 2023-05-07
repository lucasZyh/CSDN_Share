#include "stm32f10x.h" // Device header

/**
  * @brief  LED初始化
  * @param  
  * @retval 
  */
void LCD_Init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽开漏
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);//置高电平
}
/**
  * @brief  LED1电平反转
  * @param  
  * @retval 
  */
void LED1_Turn(void){
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)//判断高低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);//置高电平
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);//置低电平
	}
}
/**
  * @brief  LED2电平反转
  * @param  
  * @retval 
  */
void LED2_Turn(void){
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)//判断高低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);//置高电平
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);//置低电平
	}
}
/**
  * @brief  LED3电平反转
  * @param  
  * @retval 
  */
void LED3_Turn(void){
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == 0)//判断高低电平
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);//置高电平
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);//置低电平
	}
}
