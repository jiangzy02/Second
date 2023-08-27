#include <stdio.h>
#include <stm32f10x_lib.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <delay_by_systick.h>
#include <GPIOweibangding.h>
#include <TIM_Counter.h>
#include <USART1_Configuration.h>
#include <hc_sr04.h>

void RCC_Configuration(void);
void GPIO_Configuration(void);

float Distance=0;

int fputc(int ch,FILE *p) 
		{
		USART_SendData(USART1,(u8)ch);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		return ch;
		}

int main(void)
{
	delay_init(72);	
	RCC_Configuration();
	GPIO_Configuration();
	TIM_Counter();
	USART1_Configuration();
	hc_sr04_init();
	
	
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);

		
		Distance =(Get_hcsr04length()*340/2/1000);
		printf("距离是%.2f\r\n",Distance);
		delay_ms(1000);
		
	}
}

void RCC_Configuration(void)
{
	//----------使用外部RC晶振-----------
	RCC_DeInit();			//初始化为缺省值
	RCC_HSEConfig(RCC_HSE_ON);	//使能外部的高速时钟
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);	//等待外部的高速时钟
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//Enable Prefetch Buffer
	FLASH_SetLatency(FLASH_Latency_2);		//Flash 2 wait state
	
	RCC_HCLKConfig(RCC_SYSCLK_Div1);		//HCLK = SYSCLK
	RCC_PCLK2Config(RCC_HCLK_Div1);			//PCLK2 =  HCLK
	RCC_PCLK1Config(RCC_HCLK_Div2);			//PCLK1 = HCLK/2
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);	//PLLCLK = 8MHZ * 9 =72MHZ
	RCC_PLLCmd(ENABLE);			//Enable PLLCLK

	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	//Wait till PLLCLK is ready
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	//Select PLL as system clock
	while(RCC_GetSYSCLKSource()!=0x08);		//Wait till PLL is used as system clock source
	
	//--------打开相应的外设时钟--------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);	//使能APB2外设的GPIOC的时钟	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_0);

}

