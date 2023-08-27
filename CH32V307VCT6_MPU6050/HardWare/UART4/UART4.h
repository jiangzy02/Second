/*
 * USART3.h
 *
 *  Created on: 2023Äê8ÔÂ5ÈÕ
 *      Author: James
 */

#ifndef UART4_H_
#define USART4_H_

void Usart4_Init(unsigned int baud);

void usart4_send_char(u8 c);
void usart4_niming_report(u8 fun,u8*data,u8 len);
void USART4_SEND_DATA_U8(u8 data);
void USART4_SEND_BUF_U8(u8*buf,u8 len);
#endif /* HARDWARE_USART3_USART3_H_ */
