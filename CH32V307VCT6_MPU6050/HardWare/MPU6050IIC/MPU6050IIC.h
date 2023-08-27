#ifndef __MPU6050IIC_H
#define __MPU6050IIC_H

#include "debug.h"

//#define GPIO_Pin_SDA GPIO_Pin_9
//#define GPIO_Pin_SCL GPIO_Pin_8
//#define GPIOX GPIOB

//IO��������
//#define SDA_IN() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|3<<4;}
#define SDA_IN() {GPIOB->CFGLR&=0X0FFFFFFF;GPIOB->CFGLR|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CFGLR&=0X0FFFFFFF;GPIOB->CFGLR|=(u32)3<<28;}

//IO��������
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

//IIC��������
void IIC_Init(void);//��ʼ��IIC��IO��
void IIC_Start(void); //IIC��ʼ�ź�
void IIC_Stop(void);//IIC�����ź�
void IIC_Ack(void);//����ACKӦ���ź�
void IIC_NAck(void);//������ACKӦ���ź�
u8 IIC_Wait_Ack(void); //�ȴ�Ӧ���ź�
void IIC_Send_Byte(u8 txd);//IIC����һ���ֽ�
u8 IIC_Read_Byte(u8 ack);//IIC��һ���ֽ�
void SDA_OUT_init();
void SDA_IN_init();
#endif



