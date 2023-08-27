#include "../USART2_TWAsr/usart2.h"

#include "debug.h"



void usart2_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʱ��GPIOB��USART3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    //USART2_TX   PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //USART2_RX   PA3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

      //Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;      //�����ȼ�4
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    //USART2 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART2, ENABLE);      //ʹ�ܴ���
}

u16 Light_Voice=0;
u16 Rainbow_Voice=0;
u16 Print_Voice=0;
u16 Flash_Voice=0;
u16 Music_Mode=0;
u16 Close_Voice=0;//�ص�
__attribute__((interrupt("WCH-Interrupt-fast")))
void USART2_IRQHandler(void)
{
        u8 Res;
        if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
            {
            Res =USART_ReceiveData(USART2); //��ȡ���յ�������


                        if(Res==0x01) {Light_Voice=1;Rainbow_Voice=0;Print_Voice=0;Flash_Voice=0;Close_Voice=0;}
                        if(Res==0x02) {Light_Voice=0;Rainbow_Voice=1;Print_Voice=0;Flash_Voice=0;Close_Voice=0;}
                        if(Res==0x03) {Light_Voice=0;Rainbow_Voice=0;Print_Voice=1;Flash_Voice=0;Close_Voice=0;}
                        if(Res==0x04) {Light_Voice=0;Rainbow_Voice=0;Print_Voice=0;Flash_Voice=1;Close_Voice=0;}
                        if(Res==0x05) {Light_Voice=0;Rainbow_Voice=0;Print_Voice=0;Flash_Voice=0;Close_Voice=1;}
                        if(Res==0x06) Music_Mode=1;
                        if(Res==0x07) Music_Mode=0;

            }
}






