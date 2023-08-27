#ifndef _DS18B20_H
#define _DS18B20_H

#include <GPIOweibangding.h>
#include <stm32f10x_type.h>

#define DS18B20_PORT 			GPIOG  
#define DS18B20_PIN 			(GPIO_Pin_11)
#define DS18B20_PORT_RCC		RCC_APB2Periph_GPIOG
#define	DS18B20_DQ_OUT PGO(11) //���ݶ˿�	PG11
#define	DS18B20_DQ_IN  PGI(11)  //���ݶ˿�	PG11 

u8 DS18B20_Init(void);			//��ʼ��DS18B20
float DS18B20_GetTemperture(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Reset(void);			//��λDS18B20   
#endif
