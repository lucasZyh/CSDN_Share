#include "MySPI.h"

/**
  * @brief  引脚封装
  * @param  
  * @retval 
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

/**
  * @brief  SPI初始化
  * @param  
  * @retval 
  */
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	MySPI_W_SS(1);//SS置高电平，不选中从机
	MySPI_W_SCK(0);//SPI模式0
}

/**
  * @brief  起始信号
  * @param  SS置低电平 
  * @retval 
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

/**
  * @brief  终止信号
  * @param  SS置高电平
  * @retval 
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

/**
  * @brief  交互数据     模式0   SS下降沿->移出数据->SCK上升沿->移入数据->SCK下降沿->移出数据
  * @param  ByteSend     需要发送出去的数据
  * @retval ByteReceive  需要接收到的数据
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;
	
	for (i = 0; i < 8; i ++)
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i));
		MySPI_W_SCK(1);
		if (MySPI_R_MISO() == 1){ByteReceive |= (0x80 >> i);}
		MySPI_W_SCK(0);
	}
	
	return ByteReceive;
}
/**
*模式2，在模式0的基础上，把出现SCK的地方，1改0，0改1
*/


/**
  * @brief  交互数据     模式1
  * @param  ByteSend     需要发送出去的数据
  * @retval ByteReceive  需要接收到的数据
  */
uint8_t MySPI_SwapByte1(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;
	
	for (i = 0; i < 8; i ++)
	{
		MySPI_W_SCK(1);
		MySPI_W_MOSI(ByteSend & (0x80 >> i));
		MySPI_W_SCK(0);
		if (MySPI_R_MISO() == 1){ByteReceive |= (0x80 >> i);}

	}
	
	return ByteReceive;
}
/**
*模式3，在模式1的基础上，把出现SCK的地方，1改0，0改1
*/
