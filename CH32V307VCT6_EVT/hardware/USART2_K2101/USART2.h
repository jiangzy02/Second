#ifndef __USART2_H
#define __USART2_H

#include "debug.h"

#define USART_REC_LEN           200     //�����������ֽ��� 200
//#define EN_USART2_RX            0       //ʹ�ܣ�1��/��ֹ��0�����ڽ���

extern u8  USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART2_RX_STA;                //����״̬���

void usart2_start(u32 bound);

#endif
