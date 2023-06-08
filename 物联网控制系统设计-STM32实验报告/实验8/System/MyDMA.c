#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size){
	
	MyDMA_Size = Size;
	
	//开启时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//初始化
	DMA_InitTypeDef DMA_InitStructure;
	//外设
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;//起始地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//数据宽度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//是否自增
	//存储器
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;//起始地址
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//数据宽度
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//是否自增
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向
	DMA_InitStructure.DMA_BufferSize = Size;//缓存区大小，赋值给传输计数器
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//传输模式，是否自动重装
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//选择硬件触发还是软件触发
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//优先级
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, DISABLE);
	
}
void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//等待转运完成
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	//清理标志位
	DMA_ClearFlag(DMA1_FLAG_TC1);
}	
