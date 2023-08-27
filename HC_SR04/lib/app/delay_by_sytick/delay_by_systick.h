
#ifndef _delay_by_systick_H
#define _delay_by_systick_H

#include <stm32f10x_type.h>


void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 Nus);



//void Systick_Configuration(u32 n);

//void delay_ms(u16 time);
//void delay_us(u16 time);
////void delay_s(u8 time);

#endif
