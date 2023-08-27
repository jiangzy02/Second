#ifndef _ADC_H
#define _ADC_H

#include <stm32f10x_type.h>

void ADC_Configuration(void);
u16 Get_ADC_Value(u8 ch,u8 times);

#endif
