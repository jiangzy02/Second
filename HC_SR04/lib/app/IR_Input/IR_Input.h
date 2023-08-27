
#ifndef _IR_Input_H
#define _IR_Input_H

#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>

void IR_Input_Init(void);
u8 HW_jssj(void);
void IR_Transate(u32 R_data);
//定义全局变量
extern u32 R_data;
extern u8  hw_jsbz;


#endif

