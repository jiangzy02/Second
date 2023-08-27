#ifndef _USART2_H
#define _USART2_H

#include "debug.h"

#define UART2_DMA_RX_BUFFER_MAX_LENGTH     255
#define UART2_DMA_TX_BUFFER_MAX_LENGTH     44//这个根据发送的数据大小判断，一个unit16_t类型的占2个字节

//uint8_t USART2_DMA_RX_Buffer[USART2_DMA_RX_BUFFER_MAX_LENGTH];
//uint8_t USART2_DMA_TX_Buffer[USART2_DMA_TX_BUFFER_MAX_LENGTH];

void Init_UART2(void);


#endif
