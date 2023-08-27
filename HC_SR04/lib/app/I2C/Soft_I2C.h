#ifndef _Soft_I2C_H
#define _Soft_I2C_H

#include <stm32f10x_type.h>

void I2C_Configuration(void);
void SDA_OUT(void);
void SDA_IN(void);
void I2C_Start(void);
void I2C_End(void);
void I2C_Ack(void);
void I2C_NAck(void);
u8 I2C_Wait_Ack(void);
void I2C_Send_Byte(u8 txd);
u8 I2C_Read_Byte(u8 ack);
#endif
