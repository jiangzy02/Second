#include <TIM_Counter.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_nvic.h>
#include <stm32f10x_it.h>
#include <stm32f10x_type.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_exti.h>
#include <stdio.h>

 

void TIM_Counter(void)
{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能TIM2的时钟
		
		TIM_TimeBaseStructure.TIM_Period = 65535;
		TIM_TimeBaseStructure.TIM_Prescaler = 71;//72MHx/72=1us,
		TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
		TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);	
		TIM_Cmd(TIM2,DISABLE);
}



