#ifndef __UART6_H
#define __UART6_H

#include "debug.h"

#define USART_REC_LEN           200     //定义最大接收字节数 200
#define EN_UART6_RX            1       //使能（1）/禁止（0）串口1接收

extern u8  UART6_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 UART6_RX_STA;                //接收状态标记

void Init_uart6(u32 bound);


#endif
