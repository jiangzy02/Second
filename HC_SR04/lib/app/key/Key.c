#include <stm32f10x_gpio.h>
#include <Key.h>
#include <stm32f10x_rcc.h>

#define K_UP 	GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_0)
#define K_DOWN  GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_3)
#define K_LEFT  GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_2)
#define K_RIGHT GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_4)

//������Ч��ӦֵK_UP==1,K_DOWN==0,K_LEFT==0,K_RIGHT==0

void Key(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE,ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);		//key_up��ʼ��
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_Init(GPIOE, &GPIO_InitStructure);		//key_down,key_right,key_left��ʼ��
	GPIO_SetBits(GPIOE , GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_4 );



}