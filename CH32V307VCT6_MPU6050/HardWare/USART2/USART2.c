#include "USART2.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
//#include "usart.h"


//USART2负责向评估板发送方向盘转角数据

void Init_UART2(){

    GPIO_InitTypeDef GPIO_InitStructure;//声明一个结构体对象
    USART_InitTypeDef  USART_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//USART2挂载APB1总线
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  //对于哪个应用挂载哪个APB总线，可以根据代码自动补全功能快捷判断

    //TX端口-PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//这个对象的成员变量GPIO_Pin取值为pin2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//模式为复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHZ速度
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//
    USART_InitStructure.USART_Mode = USART_Mode_Tx;//收发模式并存
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//1位停止位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//八位数据位
    USART_Init(USART2,&USART_InitStructure);

    USART_Cmd(USART2,ENABLE);

}


