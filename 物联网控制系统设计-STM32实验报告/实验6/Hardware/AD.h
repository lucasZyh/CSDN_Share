#ifndef __AD_H__
#define __AD_H__
#include "stm32f10x.h"                  // Device header

void AD_Init(void);
uint16_t AD_GetValue(void);
#endif
