#ifndef _hc_sr04_H
#define _hc_sr04_H

#include <stm32f10x_type.h>
#include <GPIOweibangding.h>



extern float time ;

void hc_sr04_init(void);
float  Get_hcsr04length(void);

#endif
