#include "JQ8900.h"
#include "debug.h"
#include <stdint.h>


//��   OnUart_GPIO(void)
//��   �ܣ�����ģ��һ�ߴ���IO��
//�������: void
//�������: void
//˵   ����

void OnUart_GPIO(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_ResetBits(GPIOD, GPIO_Pin_10);//��PC4����������
    GPIO_Init(GPIOD, &GPIO_InitStructure);


}


void delay1_us(u32 nTimer)
{
    u32 i=0;
    for(i=0;i<nTimer;i++){
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    }
}

//
//��   ����SendData(u8 adder)
//��   �ܣ�����ģ��һ�ߴ���
//�������: adderҪ���͵�0x��
//�������: void
//˵   ����
//
void SendData(u8 addr)//���ͺ�����
{
    u8 i;
     /*����ʱ�ص��жϣ���ֹ�ж�Ӱ��ʱ��  */
    GPIO_WriteBit(GPIOD, GPIO_Pin_10, SET); /*��ʼ����*/
    Delay_Us(1000);
    GPIO_WriteBit(GPIOD, GPIO_Pin_10, RESET); /*��ʼ������*/
    Delay_Us(3200);/*�˴���ʱ����Ҫ����2ms*/
    for ( i = 0; i < 8; i++ ) /*�ܹ�8λ����  */
    {
        GPIO_WriteBit(GPIOD, GPIO_Pin_10, SET);
        if ( addr & 0x01 ) /*3:1��ʾ����λ1,ÿ��λ�����������ʾ  */
        {
            Delay_Us(600);
            GPIO_WriteBit(GPIOD, GPIO_Pin_10, RESET);
            Delay_Us(200);
        }
        else              /*1��3��ʾ����λ0 ,ÿ��λ�����������ʾ  */
        {
            Delay_Us(200);
            GPIO_WriteBit(GPIOD, GPIO_Pin_10, RESET);
            Delay_Us(600);
        }
        addr >>= 1;
    }
    GPIO_WriteBit(GPIOD, GPIO_Pin_10, SET);
       //�ָ��ж�
}


void show_number1(void)//00001.mp3��������Σ�գ��뱣�ֳ��ࡱ
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1200);
    //ѡȡ��Ŀ1����
    SendData(0x0a);//�������
    SendData(0x01);//��Ŀ���֣���Ӧ00001.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1700);
    //��ʼ����
}

void show_number2(void)//00002.mp3���������������ƣ�����ݳ���
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(800);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x02);//��Ŀ���֣���Ӧ00002.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1200);
    //��ʼ����
}

void show_number3(void)//00003.mp3������������ƣ�ͼ�ʻ����ע����Ϣ��
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1200);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x03);//��Ŀ���֣���Ӧ00003.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
}

void show_number4(void)//00004.mp3��������������ʻ�У�����Ӵ�绰��
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1200);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x04);//��Ŀ���֣���Ӧ00004.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
}


void show_number5(void)//00005.mp3��������������ʻ�У�������̡�
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x05);//��Ŀ���֣���Ӧ00005.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}


void show_number6(void)//00006.mp3����������ʻ����ע����Ϣ��
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x06);//��Ŀ���֣���Ӧ00006.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

void show_number7(void)//00007.mp3�������ѳ��٣���ע�ⰲȫ��
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x07);//��Ŀ���֣���Ӧ00007.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

void show_number8(void)//00007.mp3���������¶��쳣��
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(800);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x08);//��Ŀ���֣���Ӧ00008.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1300);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

void show_number9(void)//00007.mp3������ʱʱ�䵽����ע�⡱
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x09);//��Ŀ���֣���Ӧ00009.mp3
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

void show_number10(void)//00007.mp3����ǰ��ɲ������ע�⡱ yellow
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x0001);//��Ŀ���֣���Ӧ00010.mp3
    SendData(0x0000);
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

void show_number11(void)//00007.mp3������ע��ǰ���� red
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x0001);//��Ŀ���֣���Ӧ00011.mp3
    SendData(0x0001);
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

void show_number12(void)//��Σ�ռ�ʻ����ע�⡱
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x0001);//��Ŀ���֣���Ӧ00010.mp3
    SendData(0x0002);
    SendData(0x0b);//ѡ������
    Delay_Ms(1500);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

void show_number13(void)//��15s���֡�
{
    //��������Ϊ20
    SendData(0x0a);    //�������
    SendData(0x02);    //����20
    SendData(0x00);
    SendData(0x0c);    //��������
    Delay_Ms(1000);
    //ѡȡ��Ŀ2����
    SendData(0x0a);//�������
    SendData(0x0001);//��Ŀ���֣���Ӧ00010.mp3
    SendData(0x0003);
    SendData(0x0b);//ѡ������
    Delay_Ms(15000);
    //��ʼ����
    //SendData(0x11);//��ʼ����
    //delay1_ms(2000);
}

