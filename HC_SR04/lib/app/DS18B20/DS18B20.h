#ifndef _DS18B20_H
#define _DS18B20_H

#include <GPIOweibangding.h>
#include <stm32f10x_type.h>

#define DS18B20_PORT 			GPIOG  
#define DS18B20_PIN 			(GPIO_Pin_11)
#define DS18B20_PORT_RCC		RCC_APB2Periph_GPIOG
#define	DS18B20_DQ_OUT PGO(11) //数据端口	PG11
#define	DS18B20_DQ_IN  PGI(11)  //数据端口	PG11 

u8 DS18B20_Init(void);			//初始化DS18B20
float DS18B20_GetTemperture(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);		//读出一个字节
u8 DS18B20_Read_Bit(void);		//读出一个位
u8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Reset(void);			//复位DS18B20   
#endif
