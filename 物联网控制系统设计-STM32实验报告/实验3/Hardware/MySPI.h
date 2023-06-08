#ifndef __MYSPI_H
#define __MYSPI_H

#include "stm32f10x.h"                  // Device header

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);
#endif
