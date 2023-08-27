#include "USART2.h"

#include "debug.h"
//#if EN_USART2_RX   //如果使能了接收

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，    接收完成标志
//bit14，    接收到0x0d
//bit13~0，  接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记

void usart2_start(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//时钟GPIOB、USART3
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

      //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART2, ENABLE);      //使能串口
}

u16 Fatigue_Flag=0;//当值为0时，是清醒状态,当值为1时是疲劳状态
u16 Callphone_Flag=0;//当值为0时，是未接打电话状态，当值为1时是打电话状态
u16 Smoking_Flag=0;//当值为0时，是未吸烟状态，当值为1时是吸烟状态
u16 Fatigue_State=0;
u16 Callphone_State=0;
u16 Smoking_state=0;

__attribute__((interrupt("WCH-Interrupt-fast")))
void USART2_IRQHandler(void)
{
        u8 Res;
        if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
            {
            Res =USART_ReceiveData(USART2); //读取接收到的数据

            if((USART2_RX_STA&0x8000)==0)//接收未完成
                {
                if(USART2_RX_STA&0x4000)//接收到了0x0d
                    {
                    if(Res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
                    else USART2_RX_STA|=0x8000;  //接收完成了
                    }
                else //还没收到0X0D
                    {
                    if(Res==0x0d)USART2_RX_STA|=0x4000;
                    else
                        {
                        USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
                        USART2_RX_STA++;
                        if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收
                        }
                    }
                }
            if (USART2_RX_STA&0x8000) {

                    if(USART2_RX_BUF[0]==0x41) //K210检测到抽烟后，连续接收到其发送的0x41
                        {

                        Smoking_Flag=1;

                        }
                    if(USART2_RX_BUF[0]==0x42)//K210检测到接打电话后，连续接收到其发送的0x42
                    {
                        Callphone_Flag=1;

                    }
                    if(USART2_RX_BUF[0]==0x43)//K210检测疲劳驾驶后，连续接收到其发送的0x43
                    {
                        Fatigue_Flag=1;

                    }

                    USART2_RX_STA=0;


            }
         }



}


//#endif




