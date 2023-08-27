#ifndef _Key_H
#define _Key_H

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define K_UP 	GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_0)
#define K_DOWN  GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_3)
#define K_LEFT  GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_2)
#define K_RIGHT GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_4)

void Key(void);

#endif
