#include "USART3.h"



void uart3_init(void)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//时钟GPIOB、USART3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    //USART3_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //USART3_RX   PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

      //Usart3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;      //子优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
    //USART3 初始化设置
    USART_InitStructure.USART_BaudRate = 115200;//串口屏115200
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART3, ENABLE);                    //使能串口
}

u16 Light_Mode=0;
u16 Rainbow_Mode=0;
u16 Print_Mode=0;
u16 Flash_Mpde=0;
u16 Close_Mode=0;//关灯
u8  alarm_state=0;
__attribute__((interrupt("WCH-Interrupt-fast")))
void USART3_IRQHandler(void)
{
    u8 Res;
if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
        {
        Res =USART_ReceiveData(USART3); //读取接收到的数据

        if(Res==0x11) {Light_Mode=1;Rainbow_Mode=0;Print_Mode=0;Flash_Mpde=0;Close_Mode=0;}
        if(Res==0x12) {Light_Mode=0;Rainbow_Mode=1;Print_Mode=0;Flash_Mpde=0;Close_Mode=0;}
        if(Res==0x13) {Light_Mode=0;Rainbow_Mode=0;Print_Mode=1;Flash_Mpde=0;Close_Mode=0;}
        if(Res==0x14) {Light_Mode=0;Rainbow_Mode=0;Print_Mode=0;Flash_Mpde=1;Close_Mode=0;}
        if(Res==0x15) {Light_Mode=0;Rainbow_Mode=0;Print_Mode=0;Flash_Mpde=0;Close_Mode=1;}
        if(Res==0x18) {alarm_state=1;}
        }

}


 void HMISends(char *buf1){        //字符串发送函数
    u8 i=0;
    while(1){
    if(buf1[i]!=0){
        USART_SendData(USART3,buf1[i]);  //发送一个字节
        while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};//等待发送结束
        i++;}
     else
     return ;
        }
    }
void HMISendb(u8 k)              //字节发送函数
{
    u8 i;
     for(i=0;i<3;i++)
     {
     if(k!=0)
        {
            USART_SendData(USART3,k);  //发送一个字节
            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};//等待发送结束
        }
     else
     return ;

     }
}


/*
float length,speed;
extern float Circle;
void speed_shift()  //速度与车距
{
    length=Hcsr04GetLength();
    speed
    if (length<=10&&speed>5) {
        n=0;
    }
    else if (10<Speed<=20) {
        n=1;
    }
    else if (20<Speed<=30) {
        n=2;
    }
    else if (30<Speed<=40) {
        n=3;
    }
}


*/

