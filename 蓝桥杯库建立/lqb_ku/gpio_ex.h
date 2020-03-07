
#ifndef	__GPIO_EX_H
#define	__GPIO_EX_H


#include "GPIO.h"

u8 GPIO_WritePin(u8 GPIO , u8 Pinx , bit Level);
u8 GPIO_ReadPin(u8 GPIO , u8 Pinx );
u8 GPIO_TogglePin(u8 GPIO , u8 Pinx );

#endif
