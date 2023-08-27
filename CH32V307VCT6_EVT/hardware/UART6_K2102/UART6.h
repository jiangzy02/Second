#ifndef __UART6_H
#define __UART6_H

#include "debug.h"

#define USART_REC_LEN           200     //�����������ֽ��� 200
#define EN_UART6_RX            1       //ʹ�ܣ�1��/��ֹ��0������1����

extern u8  UART6_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 UART6_RX_STA;                //����״̬���

void Init_uart6(u32 bound);


#endif
