//Ӳ������
#include "../UART6_ESP01/UART6.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>



/*
************************************************************
*   �������ƣ�   Usart6_Init
*
*   �������ܣ�   ����6��ʼ��
*
*   ��ڲ�����   baud���趨�Ĳ�����
*
*   ���ز�����   ��
*
*   ˵����     TX-Pc0     RX-PC1
************************************************************
*/
void Usart6_Init(unsigned int baud)
{

    GPIO_InitTypeDef gpio_initstruct;
    USART_InitTypeDef usart_initstruct;
    NVIC_InitTypeDef nvic_initstruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6, ENABLE);

    //PC0   TXD
    gpio_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_initstruct.GPIO_Pin = GPIO_Pin_0;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_initstruct);

    //PC1   RXD
    gpio_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpio_initstruct.GPIO_Pin = GPIO_Pin_1;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_initstruct);

    usart_initstruct.USART_BaudRate = baud;
    usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;        //��Ӳ������
    usart_initstruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                        //���պͷ���
    usart_initstruct.USART_Parity = USART_Parity_No;                                    //��У��
    usart_initstruct.USART_StopBits = USART_StopBits_1;                             //1λֹͣλ
    usart_initstruct.USART_WordLength = USART_WordLength_8b;                            //8λ����λ
    USART_Init(UART6, &usart_initstruct);

    USART_Cmd(UART6, ENABLE);                                                      //ʹ�ܴ���

    USART_ITConfig(UART6, USART_IT_RXNE, ENABLE);                                  //ʹ�ܽ����ж�

    nvic_initstruct.NVIC_IRQChannel = UART6_IRQn;
    nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;
    nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_initstruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&nvic_initstruct);

}

/*
************************************************************
*   �������ƣ�   Usart_SendString
*
*   �������ܣ�   �������ݷ���
*
*   ��ڲ�����   USARTx��������
*               str��Ҫ���͵�����
*               len�����ݳ���
*
*   ���ز�����   ��
*
*   ˵����
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

    unsigned short count = 0;

    for(; count < len; count++)
    {
        USART_SendData(USARTx, *str++);                                 //��������
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);     //�ȴ��������
    }

}

/*
************************************************************
*   �������ƣ�   UsartPrintf
*
*   �������ܣ�   ��ʽ����ӡ
*
*   ��ڲ�����   USARTx��������
*               fmt����������
*
*   ���ز�����   ��
*
*   ˵����
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

    unsigned char UsartPrintfBuf[296];
    va_list ap;
    unsigned char *pStr = UsartPrintfBuf;

    va_start(ap, fmt);
    vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);                         //��ʽ��
    va_end(ap);

    while(*pStr != 0)
    {
        USART_SendData(USARTx, *pStr++);
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
    }

}
