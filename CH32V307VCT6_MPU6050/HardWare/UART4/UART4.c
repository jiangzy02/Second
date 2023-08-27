#include "debug.h"
#include "UART4.h"

//串口4用于发送欧拉角数据到上位机，利用金手指连接
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
    usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;        //无硬件流控
    usart_initstruct.USART_Mode = USART_Mode_Tx;                        //接收和发送
    usart_initstruct.USART_Parity = USART_Parity_No;                                    //无校验
    usart_initstruct.USART_StopBits = USART_StopBits_1;                             //1位停止位
    usart_initstruct.USART_WordLength = USART_WordLength_8b;                            //8位数据位
    USART_Init(UART4, &usart_initstruct);

    USART_Cmd(UART4, ENABLE);                                                      //使能串口


}


//串口1发送1个字符
//c:要发送的字符
void usart4_send_char(u8 c)
{
    while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕
    USART_SendData(UART4,c);
}

//传送数据给匿名四轴上位机软件(V2.6版本)
//fun:功能字. 0XA0~0XAF
//data:数据缓存区,最多28字节!!
//len:data区有效数据个数
void usart4_niming_report(u8 fun,u8*data,u8 len)
{
    u8 send_buf[32];
    u8 i;
    if(len>28)return;   //最多28字节数据
    send_buf[len+3]=0;  //校验数置零
    send_buf[0]=0X88;   //帧头
    send_buf[1]=fun;    //功能字
    send_buf[2]=len;    //数据长度
    for(i=0;i<len;i++)send_buf[3+i]=data[i];            //复制数据
    for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];   //计算校验和
    for(i=0;i<len+4;i++)usart4_send_char(send_buf[i]);  //发送数据到串口1
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



