/*
 * UART4.h
 *
 *  Created on: 2023年8月2日
 *      Author: JIANGZHIYU
 */

#ifndef UART4_H_
#define UART4_H_



#include "debug.h"

#define USART_REC_LEN           200     //定义最大接收字节数 200
#define EN_UART4_RX            1       //使能（1）/禁止（0）串口1接收

extern u8  UART4_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 USART_RX_STA;                //接收状态标记

void uart4_Init(u32 bound);



#endif /* HARDWARE_UART4_MPU_UART4_H_ */
