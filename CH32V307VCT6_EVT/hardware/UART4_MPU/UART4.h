/*
 * UART4.h
 *
 *  Created on: 2023��8��2��
 *      Author: JIANGZHIYU
 */

#ifndef UART4_H_
#define UART4_H_



#include "debug.h"

#define USART_REC_LEN           200     //�����������ֽ��� 200
#define EN_UART4_RX            1       //ʹ�ܣ�1��/��ֹ��0������1����

extern u8  UART4_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 USART_RX_STA;                //����״̬���

void uart4_Init(u32 bound);



#endif /* HARDWARE_UART4_MPU_UART4_H_ */
