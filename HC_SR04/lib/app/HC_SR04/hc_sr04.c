#include <hc_sr04.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <stm32f10x_tim.h>

float time=0;

void hc_sr04_init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);//触发信号
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//echo信号
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}


float  Get_hcsr04length(void)
{
	u32 i=0;
	
	GPIO_SetBits(GPIOC,GPIO_Pin_2);
	delay_us(20);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2); //TRIG发送触发信号
	
	while(PCI(3)==0)
	{
		TIM_SetCounter(TIM2, 0);
		TIM_Cmd(TIM2,DISABLE);
	}
	while(PCI(3)==1)
	{
		TIM_Cmd(TIM2,ENABLE);
	}
	time=TIM_GetCounter(TIM2);
	return time;
}

