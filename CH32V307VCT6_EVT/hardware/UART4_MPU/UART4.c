#include "UART4.h"

#include "debug.h"

#if EN_UART4_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 UART4_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，    接收完成标志
//bit14，    接收到0x0d
//bit13~0，  接收到的有效字节数目
u16 UART4_RX_STA=0;       //接收状态标记

void uart4_Init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//时钟GPIOB、USART3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    //USART2_TX   PC10
   // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //GPIO_Init(GPIOC, &GPIO_InitStructure);
    //USART2_RX   PC11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

      //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      //子优先级4
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx;
    USART_Init(UART4, &USART_InitStructure);

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(UART4, ENABLE);      //使能串口
}

u16 Angle_Mode=0;//急转弯标志


__attribute__((interrupt("WCH-Interrupt-fast")))
void UART4_IRQHandler(void)
{
        u8 Res;
        if(USART_GetITStatus(UART4,USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
            {
            Res =USART_ReceiveData(UART4); //读取接收到的数据
            printf("Res=%d\r\n",Res);
          //  if((UART4_RX_STA&0x8000)==0)//接收未完成
             //   {
            //    if(UART4_RX_STA&0x4000)//接收到了0x0d
              //      {
              //      if(Res!=0x0a)UART4_RX_STA=0;//接收错误,重新开始
               //     else UART4_RX_STA|=0x8000;  //接收完成了
               //     }
             //   else //还没收到0X0D
               //     {
                //    if(Res==0x0d)UART4_RX_STA|=0x4000;
                //    else
                 //       {
                  //      UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;
                 //       UART4_RX_STA++;
                 //       if(UART4_RX_STA>(USART_REC_LEN-1))UART4_RX_STA=0;//接收数据错误,重新开始接收
                  //      }
                 //   }
               // }
          //  if (UART4_RX_STA&0x8000) {

                        if(Res==0xAA) {
                            Angle_Mode=1;

                        }

                   // UART4_RX_STA=0;
          //  }
         }
}
#endif







