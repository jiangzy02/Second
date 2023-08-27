#include <inputcatch.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_nvic.h>
#include <stm32f10x_type.h>
#include <stm32f10x_it.h>
#include <stdio.h>
u8 flag=1;
u16 time=0;
u32 count;
u8 ok=1;
void TIM5_CH1_InputConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//使能TIM5时钟
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//利用PA0的按键作为输入
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//配置为下拉模式
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	TIM_TimeBaseStructure.TIM_Period = 1000;//1ms记满
	TIM_TimeBaseStructure.TIM_Prescaler = 71;//分频71+1=72，72MhZ/72=1MHz   ,1us 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInit(TIM5, & TIM_TimeBaseStructure);
	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//定时器5通道1
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//捕获极性上升沿捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//直接映射到ti
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM5, &TIM_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//打开更新中断和捕获中断
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQChannel|USART1_IRQChannel;//配置中断优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5,ENABLE); //使能定时器
}



int TIM5_IRQHandler(void)
{
	count=0;
	if(flag==1)
	{
			if(TIM_GetITStatus(TIM5, TIM_IT_CC1)==SET)
		{
			ok=1;
			TIM_Cmd(TIM5,DISABLE);
			TIM_SetCounter(TIM5,0);//设置tim5值为0
			GPIO_ResetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
			TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);//设置触发沿为下降沿
			TIM_Cmd(TIM5,ENABLE);
			flag=0;
				while(ok)
				{
						if(TIM_GetITStatus(TIM5, TIM_IT_Update)==SET)//如果发生了溢出了
						{
							time=time+1;
							text();
						}
						
				}
		}	
	}
	return count;
}


void text(void)
{
			if(TIM_GetITStatus(TIM5, TIM_IT_CC1)==SET)
		{
			TIM_Cmd(TIM5,DISABLE);
			ok=0;
			printf("更新中断次数是%d\r\n",time);
			GPIO_SetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
			TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);	
			flag=1;
			count=TIM_GetCounter(TIM5);
			count=count+time*1000;//发生一次更新，则就是过了1ms，所以乘以1000
			time=0;

		}
			else TIM_ClearITPendingBit(TIM5,TIM_IT_Update);//如果下降沿没触发
}
	
	
