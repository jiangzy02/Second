#ifndef __USART3_H
#define __USART3_H

#include "debug.h"

#define USART_MAX_LEN 54//该长度要与发送数据的长度一致
void uart3_init(u32 bound);
void USART3_Server(void);
void DMA_RX_init(void);
#endif
