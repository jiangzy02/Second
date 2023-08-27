#include "uart5.h"


#include "stdio.h"
#include "stdlib.h"
#include <string.h>
//#include "usart.h"
uint16_t UART5_DMA_RX_Buffer[UART5_DMA_RX_BUFFER_MAX_LENGTH];
uint16_t UART5_DMA_TX_Buffer[UART5_DMA_TX_BUFFER_MAX_LENGTH];

extern float alcohol,length,temperature,humidity,speed,Circle,mileage,total;
extern u16 Fatigue_Flag;//当值为0时，是清醒状态,当值为1时是疲劳状态
extern u16 Callphone_Flag;//当值为0时，是未接打电话状态，当值为1时是打电话状态
extern u16 Smoking_Flag;//当值为0时，是未吸烟状态，当值为1时是吸烟状态
//灯光标志
extern u16 Light_Mode;
extern u16 Rainbow_Mode;
extern u16 Print_Mode;
extern u16 Flash_Mpde;
extern u16 Close_Mode;//关灯
extern u16 ContDriveflag;
//急加速、急减速
extern u16 Sharpslowdown,Sharpacceleration;
extern u8 Fatigues; //犯困次数
extern u8 Calls;  //打电话次数
extern u8 Smokings; //抽烟次数
extern u16 Alarm_Flag;

extern u16 Angle_Mode;  //急转弯标志
extern u16 Red_Flag;    //前车尾灯变红
extern u16 Yellow_Flag; //前车尾灯变黄
extern u16 Sharpturns;
//UART5f负责向赤菟板发送各种数据，这里一个u16数据要把length+2，发送温度、湿度、车距、转速、
uint16_t data[27];
//UART5_TX=PC12,UART5_RX=PD2
void Init_UART5(){

    GPIO_InitTypeDef GPIO_InitStructure;//声明一个结构体对象
    USART_InitTypeDef  USART_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//USART5挂载APB1总线
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  //对于哪个应用挂载哪个APB总线，可以根据代码自动补全功能快捷判断

    //TX端口-PC12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//这个对象的成员变量GPIO_Pin取值为pin2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//模式为复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHZ速度
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    //RX端口-PD2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//这个对象的成员变量GPIO_Pin取值为pin3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//模式为浮空输入模式
    GPIO_Init(GPIOD,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//
   USART_InitStructure.USART_Mode = USART_Mode_Tx;//收发模式并存
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//1位停止位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//八位数据位
    USART_Init(UART5,&USART_InitStructure);
    //USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);//开启串口2的中断接收
    USART_Cmd(UART5,ENABLE);
    //USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);                          //开启串口DMA发送
    //NVIC_InitStructure.NVIC_IRQChannel =USART2_IRQn;//选择串口2的中断通道
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级
    //NVIC_Init(&NVIC_InitStructure);
}
//串口5的TX对于DMA2的通道4
void UART5_DMA_Tx_Configuration(void)
{
  DMA_InitTypeDef  DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2 , ENABLE);                     //DMA2时钟使能
  DMA_DeInit(DMA2_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DATAR;       //DMA外设地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)UART5_DMA_TX_Buffer;    //发送缓存指针
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                        //传输方向，从内存到外设
  DMA_InitStructure.DMA_BufferSize = UART5_DMA_TX_BUFFER_MAX_LENGTH;       //传输长度
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;      //外设递增
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;               //内存递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //外设数据宽度：BYTE
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           //内存数据宽度：BYTE
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                         //循环模式：否//（注：DMA_Mode_Normal为正常模式，DMA_Mode_Circular为循环模式）
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                 //优先级：高
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                          //内存：内存（都）
    DMA_Init(DMA2_Channel4 , &DMA_InitStructure);                           //初始化DMA1_Channel4
    //DMA_ClearFlag(DMA1_FLAG_GL4);
    DMA_ClearFlag(DMA2_FLAG_GL4);
    DMA_Cmd(DMA2_Channel4 , DISABLE);                                       //禁用DMA通道传输
    USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE);                          //开启串口DMA发送
}

void DMA_send(){
  int len = sizeof(data);
  memmove(UART5_DMA_TX_Buffer, (uint16_t*)data, len*sizeof(uint16_t));//把data数组的元素复制到发送缓冲区去
      //开启计数器，在传输过程中，DMA控制器会持续地递减该计数器的值，直到计数器为0，表示数据传输完成。
  DMA_SetCurrDataCounter(DMA2_Channel4,UART5_DMA_TX_BUFFER_MAX_LENGTH);
  DMA_Cmd(DMA2_Channel4, ENABLE);//开启DMA传输
  while(DMA_GetFlagStatus(DMA2_FLAG_TC4) != SET);
  DMA_Cmd(DMA2_Channel4, DISABLE);//关闭DMA传输
  DMA_ClearFlag(DMA2_FLAG_TC4);
}

uint16_t data_switch(){
      data[0]=(uint16_t)temperature*100; //将温度存入data[0]
      data[1]=(uint16_t)humidity*100; //湿度-data1
      data[2]=(uint16_t)length*100; //车距
      data[3]=alcohol*100; //酒精浓度
      data[4]=(uint16_t)speed*100; //车速
      data[5]=(uint16_t)Circle*100;//转速
      data[6]=(uint16_t)mileage*100;//里程
      data[7]=(uint16_t)total*100;//总分
      data[8]= Fatigue_Flag; //疲劳
      data[9]=Callphone_Flag;//接打电话
      data[10]=Smoking_Flag;//抽烟
      data[11]=Light_Mode;//光1
      data[12]=Rainbow_Mode;//光2
      data[13]=Print_Mode;//光3
      data[14]=Flash_Mpde;//光4
      data[15]=Close_Mode;//关灯
      data[16]=ContDriveflag;//连续驾驶标志
      data[17]=(uint16_t)Sharpslowdown;//急减速次数
      data[18]=(uint16_t)Sharpacceleration;//急加速
      data[19]=(uint16_t)Fatigues;//疲劳次数
      data[20]=(uint16_t)Calls;//打电话次数
      data[21]=(uint16_t)Smokings;//抽烟次数
      data[22]=Alarm_Flag;//闹钟标志
      data[23]=Angle_Mode;  //急转弯标志
      data[24]=Red_Flag;
      data[25]=Yellow_Flag;
      data[26]=Sharpturns;//急转弯次数

    return 0;
}
