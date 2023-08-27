#ifndef __DHT11_H
#define __DHT11_H
#include "debug.h"

//IO��������
#define DHT11_IO_IN()  {GPIOA->CFGHR&=0XFFFF0FFF;GPIOA->CFGHR|=8<<12;}
#define DHT11_IO_OUT() {GPIOA->CFGHR&=0XFFFF0FFF;GPIOA->CFGHR|=3<<12;}

//IO��������
#define DHT11_DQ_OUT GPIO_ResetBits(GPIOA, GPIO_Pin_11) //���ݶ˿�

#define DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11
#endif
