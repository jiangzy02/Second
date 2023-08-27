#ifndef __DHT11_H
#define __DHT11_H
#include "debug.h"

//IO方向设置
#define DHT11_IO_IN()  {GPIOA->CFGHR&=0XFFFF0FFF;GPIOA->CFGHR|=8<<12;}
#define DHT11_IO_OUT() {GPIOA->CFGHR&=0XFFFF0FFF;GPIOA->CFGHR|=3<<12;}

//IO操作函数
#define DHT11_DQ_OUT GPIO_ResetBits(GPIOA, GPIO_Pin_11) //数据端口

#define DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11
#endif
