#ifndef __JQ8900_H
#define __JQ8900_H

#include "debug.h"

void SendData ( u8 addr );    //���ͺ�����
void OnUart_GPIO(void);       //GPIO
void delay1_us(u32 nTimer);
void show_number1(void);//������Σ�գ��뱣�ֳ��ࡱ
void show_number2(void);//�����ƣ�����ݳ���
void show_number3(void);//��ƣ�ͼ�ʻ����ע����Ϣ��
void show_number4(void);//����ʻ�У�����Ӵ�绰��
void show_number5(void);//����ʻ�У�������̡�
void show_number6(void);//��������ʻ����ע����Ϣ��
void show_number7(void);//�����ѳ��٣���ע�ⰲȫ��
void show_number8(void);//�������¶��쳣��
void show_number9(void);//����ʱʱ��ʱ�䵽����ע�⡱
void show_number10(void);//��ǰ��ɲ������ע�⡱
void show_number11(void);//����ע��ǰ����
void show_number12(void);//��Σ�ռ�ʻ����ע�⡱
void show_number13(void);//"15s����"

#endif

