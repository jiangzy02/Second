#ifndef __MPU6050IIC_H
#define __MPU6050IIC_H

#include "debug.h"

//#define GPIO_Pin_SDA GPIO_Pin_9
//#define GPIO_Pin_SCL GPIO_Pin_8
//#define GPIOX GPIOB

//IO方向设置
//#define SDA_IN() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|3<<4;}
#define SDA_IN() {GPIOB->CFGLR&=0X0FFFFFFF;GPIOB->CFGLR|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CFGLR&=0X0FFFFFFF;GPIOB->CFGLR|=(u32)3<<28;}

//IO操作函数
//#define IIC_SCL PBout(8)
//#define IIC_SDA PBout(9)
//#define READ_SDA PBin(9)

//PCout(12)
//PCout(11)
//PCout(12)
 //PCout(11)
#define IIC_SCL_0 GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define IIC_SDA_0 GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define IIC_SCL_1 GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define IIC_SDA_1 GPIO_SetBits(GPIOB,GPIO_Pin_7)
//#define READ_SDA PCin(11)

//IIC操作函数
void IIC_Init(void);//初始化IIC的IO口
void IIC_Start(void); //IIC开始信号
void IIC_Stop(void);//IIC结束信号
void IIC_Ack(void);//产生ACK应答信号
void IIC_NAck(void);//不产生ACK应答信号
u8 IIC_Wait_Ack(void); //等待应答信号
void IIC_Send_Byte(u8 txd);//IIC发送一个字节
u8 IIC_Read_Byte(u8 ack);//IIC读一个字节
void SDA_OUT_init();
void SDA_IN_init();
#endif



