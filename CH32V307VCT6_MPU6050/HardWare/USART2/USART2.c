#include "USART2.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
//#include "usart.h"


//USART2�����������巢�ͷ�����ת������

void Init_UART2(){

    GPIO_InitTypeDef GPIO_InitStructure;//����һ���ṹ�����
    USART_InitTypeDef  USART_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//USART2����APB1����
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  //�����ĸ�Ӧ�ù����ĸ�APB���ߣ����Ը��ݴ����Զ���ȫ���ܿ���ж�

    //TX�˿�-PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//�������ĳ�Ա����GPIO_PinȡֵΪpin2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//ģʽΪ�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHZ�ٶ�
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//
    USART_InitStructure.USART_Mode = USART_Mode_Tx;//�շ�ģʽ����
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//1λֹͣλ
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��λ����λ
    USART_Init(USART2,&USART_InitStructure);

    USART_Cmd(USART2,ENABLE);

}


