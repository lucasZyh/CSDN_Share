#ifndef __MyUSART_H
#define __MyUSART_H
#include "stdio.h"
void MyUSART_Init(void);
char* MyUSART_GetString(void);
void MyUSART_SendString(char* str);
#endif
