#include "UART6.h"

#include "debug.h"

#if EN_UART6_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 UART6_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，    接收完成标志
//bit14，    接收到0x0d
//bit13~0，  接收到的有效字节数目
u16 UART6_RX_STA=0;       //接收状态标记

void Init_uart6(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6, ENABLE);
    // 将PE10和PE11重映射为UART6_TX和UART6_RX
    GPIO_PinRemapConfig(GPIO_FullRemap_USART6, ENABLE);

    //UART6_TX   PE10
   // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //GPIO_Init(GPIOE, &GPIO_InitStructure);
    //UART6_RX   PE1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

      //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = UART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx;
    USART_Init(UART6, &USART_InitStructure);

    USART_ITConfig(UART6, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(UART6, ENABLE);      //使能串口
}

u16 Red_Flag=0;//前车尾灯变红
u16 Yellow_Flag=0;//前车尾灯变黄

__attribute__((interrupt("WCH-Interrupt-fast")))
void UART6_IRQHandler(void)
{
        u8 Res;
        if(USART_GetITStatus(UART6,USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
            {
            Res =USART_ReceiveData(UART6); //读取接收到的数据

            if((UART6_RX_STA&0x8000)==0)//接收未完成
                {
                if(UART6_RX_STA&0x4000)//接收到了0x0d
                    {
                    if(Res!=0x0a)UART6_RX_STA=0;//接收错误,重新开始
                    else UART6_RX_STA|=0x8000;  //接收完成了
                    }
                else //还没收到0X0D
                    {
                    if(Res==0x0d)UART6_RX_STA|=0x4000;
                    else
                        {
                        UART6_RX_BUF[UART6_RX_STA&0X3FFF]=Res ;
                        UART6_RX_STA++;
                        if(UART6_RX_STA>(USART_REC_LEN-1))UART6_RX_STA=0;//接收数据错误,重新开始接收
                        }
                    }
                }
            if (UART6_RX_STA&0x8000) {

                    if(UART6_RX_BUF[0]==0x45)
                    {
                        Red_Flag=1;
                    }
                    if(UART6_RX_BUF[0]==0x46)
                    {
                        Yellow_Flag=1;
                    }

                    UART6_RX_STA=0;


            }
         }



}
#endif


