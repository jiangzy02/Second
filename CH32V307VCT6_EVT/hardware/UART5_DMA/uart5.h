#ifndef _UART5_H
#define _UART5_H

#include "debug.h"

#define UART5_DMA_RX_BUFFER_MAX_LENGTH     255
#define UART5_DMA_TX_BUFFER_MAX_LENGTH     54//这个根据发送的数据大小判断，一个unit16_t类型的占2个字节

//uint8_t USART2_DMA_RX_Buffer[USART2_DMA_RX_BUFFER_MAX_LENGTH];
//uint8_t USART2_DMA_TX_Buffer[USART2_DMA_TX_BUFFER_MAX_LENGTH];

void Init_UART5(void);
void UART5_DMA_Tx_Configuration(void);
//void USART2_SendByte(USART_TypeDef * USARTx,uint8_t data);
uint16_t get_temperature(void);
uint16_t get_humi(void);
uint16_t data_switch();
void DMA_send();
#endif
