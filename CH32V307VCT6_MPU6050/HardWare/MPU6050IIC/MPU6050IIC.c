#include "debug.h"
#include "MPU6050IIC.h"

//��ʼ��IIC�ӿ�����
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
    //GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_6);
}
void SDA_OUT_init(){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void SDA_IN_init(){
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}
//IIC��ʼ�ź�
void IIC_Start(void)
{
    SDA_OUT();
    //SDA_OUT_init();
    IIC_SDA_1;
    IIC_SCL_1;
    //delay_us(2);
    Delay_Us(2);
    IIC_SDA_0;
    //delay_us(2);
    Delay_Us(2);
    IIC_SCL_0;
}

//IIC�����ź�
void IIC_Stop(void)
{
   SDA_OUT();
   // SDA_OUT_init();
    IIC_SCL_0;
    IIC_SDA_0;
    //delay_us(2);
    Delay_Us(2);
    IIC_SCL_1;
    IIC_SDA_1;
   // delay_us(2);
    Delay_Us(2);
}

//����ACKӦ���ź�
void IIC_Ack(void)
{
    IIC_SCL_0;
    SDA_OUT();
   // SDA_OUT_init();
    IIC_SDA_0;
    //delay_us(2);
    Delay_Us(2);
    IIC_SCL_1;
   // delay_us(2);
    Delay_Us(2);
    IIC_SCL_0;
}

//������ACKӦ���ź�
void IIC_NAck(void)
{
    IIC_SCL_0;
    SDA_OUT();
    //SDA_OUT_init();
    IIC_SDA_1;
    //delay_us(2);
    Delay_Us(2);
    IIC_SCL_1;
   // delay_us(2);
    Delay_Us(2);
    IIC_SCL_0;
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
    u8 Time=0;
    SDA_IN();
    //SDA_IN_init();
    IIC_SDA_1;
    //delay_us(2);
    Delay_Us(2);
    IIC_SCL_1;
    //delay_us(2);
    Delay_Us(2);
    while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
    {
        Time++;
        if(Time>250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_0;
    return 0;
}

//IIC����һ���ֽ�
void IIC_Send_Byte(u8 txd)
{
    u8 t;
   // SDA_OUT_init();
    SDA_OUT();
    IIC_SCL_0;
    for(t=0;t<8;t++)
    {
        //IIC_SDA=(txd&0x80)>>7;
        if ((txd & 0x80) >> 7) {
                GPIO_SetBits(GPIOB, GPIO_Pin_7);
            } else {
                GPIO_ResetBits(GPIOB,GPIO_Pin_7);
            }
        //IIC_SDA=(txd&(1<<7))>>(7);
        txd<<=1;
        IIC_SCL_1;

        //delay_us(2);
        Delay_Us(2);
        IIC_SCL_0;
        //delay_us(2);
        Delay_Us(2);
    }
}

//IIC��һ���ֽ�
//ack=1 ����ACK
//ack=0 ����NACK
u8 IIC_Read_Byte(u8 ack)
{
    u8 i,receive=0;
    //SDA_IN_init();
    SDA_IN();
    for(i=0;i<8;i++)
    {
        IIC_SCL_0;
        //delay_us(2);
        Delay_Us(2);
        IIC_SCL_1;
        receive<<=1;
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))receive++;
        //delay_us(2);
        Delay_Us(2);
    }
    if(!ack) IIC_NAck();
    else IIC_Ack();
    return receive;
}
