#include "../USART3_DMA/USART3.h"

#include "debug.h"
#define data_length 8 //数据长度
uint16_t res_data[data_length];//存储接收到了的数据

//USART3作为接收评估板发来的数据并保存到数组里
//TX-PD8,RX-PD9
//#define USART_MAX_LEN 2
uint16_t USART3_RxBuf[USART_MAX_LEN];   //接收缓存
void uart3_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
   // NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);//时钟GPIOA、USART3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // 将PD8和PD9重映射为USART3_TX和USART3_RX
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);

    //USART3_TX   PD8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //USART3_RX   PD9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
   // USART_Cmd(USART2, ENABLE);      //使能串口
}
//DMA1的通道3对应USART3的RX
void DMA_RX_init(){
    DMA_InitTypeDef  DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);                     //DMA2时钟使能

    DMA_DeInit(DMA1_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DATAR;       //DMA外设地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)USART3_RxBuf;    //发送缓存指针
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                        //传输方向，从外设到内存
    DMA_InitStructure.DMA_BufferSize = USART_MAX_LEN;       //传输长度
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;      //外设递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;               //内存递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //外设数据宽度：BYTE
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           //内存数据宽度：BYTE
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                         //循环模式：否//（注：DMA_Mode_Normal为正常模式，DMA_Mode_Circular为循环模式）
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;               //优先级：高
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                          //内存：内存（都）
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);                           //初始化DMA1_Channel4
        //DMA_ClearFlag(DMA1_FLAG_GL4);
    //DMA_ClearFlag(DMA1_FLAG_GL6);
    DMA_Cmd(DMA1_Channel3 , DISABLE);                                       //禁用DMA通道传输
    //USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);                          //开启串口DMA接收
   // USART_Cmd(USART3, ENABLE);      //使能串口
}



void USART3_Server(){

   //uint16_t i,len;
   //len = USART_MAX_LEN - DMA_GetCurrDataCounter(DMA1_Channel6);    // 获取接收到的数据长度 单位为字节
   //DMA_SetCurrDataCounter(DMA1_Channel6,USART_MAX_LEN); // 重新赋值计数值，必须大于等于最大可能接收到的数据帧数目
   DMA_Cmd(DMA1_Channel3, ENABLE);
   USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);                          //开启串口DMA接收
   USART_Cmd(USART3, ENABLE);      //使能串口
   DMA_SetCurrDataCounter(DMA1_Channel3,USART_MAX_LEN); // 重新赋值计数值，必须大于等于最大可能接收到的数据帧数目
   //USART_ReceiveData(USART2);
   //USART_Cmd(USART3, ENABLE);      //使能串口
   // 清除空闲中断标志位(接收函数有清标志位的作用)
   //printf("data=%d\r\n",USART_ReceiveData(USART2));
   // printf("data1=%d\r\n",USART2_RxBuf[0]);
   //DMA_Cmd(DMA1_Channel6, DISABLE);                                // 关闭DMA1_Channel6不再接收数据

    while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);

    // 清除USART1的数据寄存器
   //USART_ClearFlag(USART3, USART_FLAG_RXNE);

    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC3);                                   // 清DMA1_Channel6接收完成标志位
    USART_DMACmd(USART3, USART_DMAReq_Rx, DISABLE);                          //开启串口DMA接收
    USART_Cmd(USART3, DISABLE);      //使能串口
    //DMA_SetCurrDataCounter(DMA1_Channel6,USART_MAX_LEN);            // 重新赋值计数值，必须大于等于最大可能接收到的数据帧数目
    //for (i = 0; i < len; ++i) {                                     // 把接收到的数据转移到发送数组
    //res_data[i] = USART2_RxBuf[i];
    //printf("res%d=%d\r\n",i,res_data[i]);
        }



