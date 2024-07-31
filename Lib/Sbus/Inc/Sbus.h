#ifndef __Sbus_h__
#define __Sbus_h__

#include "SbusTypes.h"
#include "main.h"
#include <string.h>

void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
int SbusStart(void);

#endif //__Sbus_h__