#include "W25Q64.h"

//初始化
void W25Q64_Init(void)
{
	MySPI_Init();
}
/**
  * @brief  获取ID号
  * @param  MID厂商ID  DID设备ID
  * @retval 
  */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	
	MySPI_SwapByte(W25Q64_JEDEC_ID);//读ID号指令发送
	
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);//厂商ID 
	
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);//设备ID高八位
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);//设备ID低八位
	
	MySPI_Stop();
}

/**
  * @brief  写使能
  * @param  
  * @retval 
  */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);//发送指令
	MySPI_Stop();
}

/**
  * @brief  查看芯片是否处于忙状态
  * @param  
  * @retval 
  */
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);//发送读状态寄存器1指令
	Timeout = 100000;
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)//获取最低位进行查忙判断
	{
		//避免死循环，程序卡死
		Timeout --;
		if (Timeout == 0)
		{
			break;
		}
	}
	MySPI_Stop();
}

/**
  * @brief  页编程
  * @param  Address24位地址  DataArray  Count
  * @retval 
  */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	uint16_t i;
	
	W25Q64_WriteEnable();
	MySPI_Start();
	
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);//发送页编程指令 
	
	MySPI_SwapByte(Address >> 16);//发送高位地址
	MySPI_SwapByte(Address >> 8);//发送中间地址
	MySPI_SwapByte(Address);//发送低位地址
	
	for (i = 0; i < Count; i ++)//写入多个数据
	{
		MySPI_SwapByte(DataArray[i]);
	}
	
	MySPI_Stop();
	W25Q64_WaitBusy();
}

/**
* @brief  扇区擦除
  * @param  
  * @retval 
  */
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();
	MySPI_Start();
	
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);//发送指令
	
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	
	MySPI_Stop();
	W25Q64_WaitBusy();
}

/**
  * @brief  读数据
  * @param  
  * @retval 
  */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);//发送指令 
	
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	
	for (i = 0; i < Count; i ++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	
	MySPI_Stop();
}
