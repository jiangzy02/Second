#ifndef _USART_H_
#define _USART_H_


#include "debug.h"


//#define USART_DEBUG     USART1      //���Դ�ӡ��ʹ�õĴ�����


//void Usart1_Init(unsigned int baud);

void Usart6_Init(unsigned int baud);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);

#endif
