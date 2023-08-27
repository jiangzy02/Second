#include "debug.h"
#include "UART4.h"

//����4���ڷ���ŷ�������ݵ���λ�������ý���ָ����
void Usart4_Init(unsigned int baud)
{

    GPIO_InitTypeDef gpio_initstruct;
    USART_InitTypeDef usart_initstruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    //Pc10   TXD
    gpio_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_initstruct.GPIO_Pin = GPIO_Pin_10;
    gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_initstruct);

    usart_initstruct.USART_BaudRate = baud;
    usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;        //��Ӳ������
    usart_initstruct.USART_Mode = USART_Mode_Tx;                        //���պͷ���
    usart_initstruct.USART_Parity = USART_Parity_No;                                    //��У��
    usart_initstruct.USART_StopBits = USART_StopBits_1;                             //1λֹͣλ
    usart_initstruct.USART_WordLength = USART_WordLength_8b;                            //8λ����λ
    USART_Init(UART4, &usart_initstruct);

    USART_Cmd(UART4, ENABLE);                                                      //ʹ�ܴ���


}


//����1����1���ַ�
//c:Ҫ���͵��ַ�
void usart4_send_char(u8 c)
{
    while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������
    USART_SendData(UART4,c);
}

//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart4_niming_report(u8 fun,u8*data,u8 len)
{
    u8 send_buf[32];
    u8 i;
    if(len>28)return;   //���28�ֽ�����
    send_buf[len+3]=0;  //У��������
    send_buf[0]=0X88;   //֡ͷ
    send_buf[1]=fun;    //������
    send_buf[2]=len;    //���ݳ���
    for(i=0;i<len;i++)send_buf[3+i]=data[i];            //��������
    for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];   //����У���
    for(i=0;i<len+4;i++)usart4_send_char(send_buf[i]);  //�������ݵ�����1
}


void USART4_SEND_DATA_U8(u8 data)
{
    USART_SendData(UART4,data);
    while(!USART_GetFlagStatus(UART4,USART_FLAG_TC));
}

void USART4_SEND_BUF_U8(u8*buf,u8 len)
{
    while(len)
    {
        USART4_SEND_DATA_U8(*buf);
        buf++;
        len--;
    }
}



