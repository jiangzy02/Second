#include "uart5.h"


#include "stdio.h"
#include "stdlib.h"
#include <string.h>
//#include "usart.h"
uint16_t UART5_DMA_RX_Buffer[UART5_DMA_RX_BUFFER_MAX_LENGTH];
uint16_t UART5_DMA_TX_Buffer[UART5_DMA_TX_BUFFER_MAX_LENGTH];

extern float alcohol,length,temperature,humidity,speed,Circle,mileage,total;
extern u16 Fatigue_Flag;//��ֵΪ0ʱ��������״̬,��ֵΪ1ʱ��ƣ��״̬
extern u16 Callphone_Flag;//��ֵΪ0ʱ����δ�Ӵ�绰״̬����ֵΪ1ʱ�Ǵ�绰״̬
extern u16 Smoking_Flag;//��ֵΪ0ʱ����δ����״̬����ֵΪ1ʱ������״̬
//�ƹ��־
extern u16 Light_Mode;
extern u16 Rainbow_Mode;
extern u16 Print_Mode;
extern u16 Flash_Mpde;
extern u16 Close_Mode;//�ص�
extern u16 ContDriveflag;
//�����١�������
extern u16 Sharpslowdown,Sharpacceleration;
extern u8 Fatigues; //��������
extern u8 Calls;  //��绰����
extern u8 Smokings; //���̴���
extern u16 Alarm_Flag;

extern u16 Angle_Mode;  //��ת���־
extern u16 Red_Flag;    //ǰ��β�Ʊ��
extern u16 Yellow_Flag; //ǰ��β�Ʊ��
extern u16 Sharpturns;
//UART5f��������˰巢�͸������ݣ�����һ��u16����Ҫ��length+2�������¶ȡ�ʪ�ȡ����ࡢת�١�
uint16_t data[27];
//UART5_TX=PC12,UART5_RX=PD2
void Init_UART5(){

    GPIO_InitTypeDef GPIO_InitStructure;//����һ���ṹ�����
    USART_InitTypeDef  USART_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//USART5����APB1����
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  //�����ĸ�Ӧ�ù����ĸ�APB���ߣ����Ը��ݴ����Զ���ȫ���ܿ���ж�

    //TX�˿�-PC12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//�������ĳ�Ա����GPIO_PinȡֵΪpin2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//ģʽΪ�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHZ�ٶ�
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    //RX�˿�-PD2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//�������ĳ�Ա����GPIO_PinȡֵΪpin3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//ģʽΪ��������ģʽ
    GPIO_Init(GPIOD,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//
   USART_InitStructure.USART_Mode = USART_Mode_Tx;//�շ�ģʽ����
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//1λֹͣλ
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��λ����λ
    USART_Init(UART5,&USART_InitStructure);
    //USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);//��������2���жϽ���
    USART_Cmd(UART5,ENABLE);
    //USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);                          //��������DMA����
    //NVIC_InitStructure.NVIC_IRQChannel =USART2_IRQn;//ѡ�񴮿�2���ж�ͨ��
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�
    //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
    //NVIC_Init(&NVIC_InitStructure);
}
//����5��TX����DMA2��ͨ��4
void UART5_DMA_Tx_Configuration(void)
{
  DMA_InitTypeDef  DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2 , ENABLE);                     //DMA2ʱ��ʹ��
  DMA_DeInit(DMA2_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DATAR;       //DMA�����ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)UART5_DMA_TX_Buffer;    //���ͻ���ָ��
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                        //���䷽�򣬴��ڴ浽����
  DMA_InitStructure.DMA_BufferSize = UART5_DMA_TX_BUFFER_MAX_LENGTH;       //���䳤��
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;      //�������
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;               //�ڴ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //�������ݿ�ȣ�BYTE
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           //�ڴ����ݿ�ȣ�BYTE
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                         //ѭ��ģʽ����//��ע��DMA_Mode_NormalΪ����ģʽ��DMA_Mode_CircularΪѭ��ģʽ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                 //���ȼ�����
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                          //�ڴ棺�ڴ棨����
    DMA_Init(DMA2_Channel4 , &DMA_InitStructure);                           //��ʼ��DMA1_Channel4
    //DMA_ClearFlag(DMA1_FLAG_GL4);
    DMA_ClearFlag(DMA2_FLAG_GL4);
    DMA_Cmd(DMA2_Channel4 , DISABLE);                                       //����DMAͨ������
    USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE);                          //��������DMA����
}

void DMA_send(){
  int len = sizeof(data);
  memmove(UART5_DMA_TX_Buffer, (uint16_t*)data, len*sizeof(uint16_t));//��data�����Ԫ�ظ��Ƶ����ͻ�����ȥ
      //�������������ڴ�������У�DMA������������صݼ��ü�������ֵ��ֱ��������Ϊ0����ʾ���ݴ�����ɡ�
  DMA_SetCurrDataCounter(DMA2_Channel4,UART5_DMA_TX_BUFFER_MAX_LENGTH);
  DMA_Cmd(DMA2_Channel4, ENABLE);//����DMA����
  while(DMA_GetFlagStatus(DMA2_FLAG_TC4) != SET);
  DMA_Cmd(DMA2_Channel4, DISABLE);//�ر�DMA����
  DMA_ClearFlag(DMA2_FLAG_TC4);
}

uint16_t data_switch(){
      data[0]=(uint16_t)temperature*100; //���¶ȴ���data[0]
      data[1]=(uint16_t)humidity*100; //ʪ��-data1
      data[2]=(uint16_t)length*100; //����
      data[3]=alcohol*100; //�ƾ�Ũ��
      data[4]=(uint16_t)speed*100; //����
      data[5]=(uint16_t)Circle*100;//ת��
      data[6]=(uint16_t)mileage*100;//���
      data[7]=(uint16_t)total*100;//�ܷ�
      data[8]= Fatigue_Flag; //ƣ��
      data[9]=Callphone_Flag;//�Ӵ�绰
      data[10]=Smoking_Flag;//����
      data[11]=Light_Mode;//��1
      data[12]=Rainbow_Mode;//��2
      data[13]=Print_Mode;//��3
      data[14]=Flash_Mpde;//��4
      data[15]=Close_Mode;//�ص�
      data[16]=ContDriveflag;//������ʻ��־
      data[17]=(uint16_t)Sharpslowdown;//�����ٴ���
      data[18]=(uint16_t)Sharpacceleration;//������
      data[19]=(uint16_t)Fatigues;//ƣ�ʹ���
      data[20]=(uint16_t)Calls;//��绰����
      data[21]=(uint16_t)Smokings;//���̴���
      data[22]=Alarm_Flag;//���ӱ�־
      data[23]=Angle_Mode;  //��ת���־
      data[24]=Red_Flag;
      data[25]=Yellow_Flag;
      data[26]=Sharpturns;//��ת�����

    return 0;
}
