#ifndef _SPI_H
#define _SPI_H

#include <stm32f10x_type.h>

void SPI1_Init(void);			 //��ʼ��SPI1��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�


void SPI2_Configuration(void);
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
	
#endif
