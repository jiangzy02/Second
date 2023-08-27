
#ifndef _temp_H
#define _temp_H

#include <stm32f10x_type.h>

void ADC_temp_init(void);
u16 Get_ADC_Temp_Value(u8 ch,u8 times);
int Get_temperture(void);

#endif
