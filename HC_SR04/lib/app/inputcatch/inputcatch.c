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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//ʹ��TIM5ʱ��
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//����PA0�İ�����Ϊ����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//����Ϊ����ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	TIM_TimeBaseStructure.TIM_Period = 1000;//1ms����
	TIM_TimeBaseStructure.TIM_Prescaler = 71;//��Ƶ71+1=72��72MhZ/72=1MHz   ,1us 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, & TIM_TimeBaseStructure);
	
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//��ʱ��5ͨ��1
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//�����������ز���
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//ֱ��ӳ�䵽ti
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x00;
	TIM_ICInit(TIM5, &TIM_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//�򿪸����жϺͲ����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQChannel|USART1_IRQChannel;//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��
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
			TIM_SetCounter(TIM5,0);//����tim5ֵΪ0
			GPIO_ResetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
			TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);//���ô�����Ϊ�½���
			TIM_Cmd(TIM5,ENABLE);
			flag=0;
				while(ok)
				{
						if(TIM_GetITStatus(TIM5, TIM_IT_Update)==SET)//��������������
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
			printf("�����жϴ�����%d\r\n",time);
			GPIO_SetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
			TIM_ClearITPendingBit(TIM5,TIM_IT_CC1);
			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);	
			flag=1;
			count=TIM_GetCounter(TIM5);
			count=count+time*1000;//����һ�θ��£�����ǹ���1ms�����Գ���1000
			time=0;

		}
			else TIM_ClearITPendingBit(TIM5,TIM_IT_Update);//����½���û����
}
	
	
