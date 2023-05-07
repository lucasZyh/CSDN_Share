#include "stm32f10x.h"                  // Device header
#include "MyUSART.h"

void MyUSART_Init(void)
{
	//开启时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//初始化引脚
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//TX引脚，复用推挽输出;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//RX引脚，浮空输入或上拉输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//初始化USART
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;//设置比特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制（不适应）
	USART_InitStruct.USART_Mode = USART_Mode_Tx| USART_Mode_Rx;//串口模式（发送,接收）
	USART_InitStruct.USART_Parity = USART_Parity_No;//校验位（不校验）
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//字长
	
	USART_Init(USART1,&USART_InitStruct);
	USART_Cmd(USART1,ENABLE);
}

//重定向printf
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1,(uint8_t) ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	return ch;
}

/**
  * @brief  接收数据
  * @param  
  * @retval 
  */
uint8_t MyUSART_ReceiveData(void)
{	
	uint8_t RxData;
	if (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET)
	{
		RxData = USART_ReceiveData(USART1);
	}
	return RxData;
}

