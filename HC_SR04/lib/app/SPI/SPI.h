#ifndef _SPI_H
#define _SPI_H

#include <stm32f10x_type.h>

void SPI1_Init(void);			 //初始化SPI1口
void SPI1_SetSpeed(u8 SpeedSet); //设置SPI1速度   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1总线读写一个字节


void SPI2_Configuration(void);
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
	
#endif
