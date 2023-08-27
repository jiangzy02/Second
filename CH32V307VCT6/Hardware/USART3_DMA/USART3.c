#include "../USART3_DMA/USART3.h"

#include "debug.h"
#define data_length 8 //���ݳ���
uint16_t res_data[data_length];//�洢���յ��˵�����

//USART3��Ϊ���������巢�������ݲ����浽������
//TX-PD8,RX-PD9
//#define USART_MAX_LEN 2
uint16_t USART3_RxBuf[USART_MAX_LEN];   //���ջ���
void uart3_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
   // NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);//ʱ��GPIOA��USART3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // ��PD8��PD9��ӳ��ΪUSART3_TX��USART3_RX
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

    //USART2 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    //USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
   // USART_Cmd(USART2, ENABLE);      //ʹ�ܴ���
}
//DMA1��ͨ��3��ӦUSART3��RX
void DMA_RX_init(){
    DMA_InitTypeDef  DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);                     //DMA2ʱ��ʹ��

    DMA_DeInit(DMA1_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DATAR;       //DMA�����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)USART3_RxBuf;    //���ͻ���ָ��
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                        //���䷽�򣬴����赽�ڴ�
    DMA_InitStructure.DMA_BufferSize = USART_MAX_LEN;       //���䳤��
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;      //�������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;               //�ڴ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;   //�������ݿ�ȣ�BYTE
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;           //�ڴ����ݿ�ȣ�BYTE
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                         //ѭ��ģʽ����//��ע��DMA_Mode_NormalΪ����ģʽ��DMA_Mode_CircularΪѭ��ģʽ��
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;               //���ȼ�����
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                          //�ڴ棺�ڴ棨����
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);                           //��ʼ��DMA1_Channel4
        //DMA_ClearFlag(DMA1_FLAG_GL4);
    //DMA_ClearFlag(DMA1_FLAG_GL6);
    DMA_Cmd(DMA1_Channel3 , DISABLE);                                       //����DMAͨ������
    //USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);                          //��������DMA����
   // USART_Cmd(USART3, ENABLE);      //ʹ�ܴ���
}



void USART3_Server(){

   //uint16_t i,len;
   //len = USART_MAX_LEN - DMA_GetCurrDataCounter(DMA1_Channel6);    // ��ȡ���յ������ݳ��� ��λΪ�ֽ�
   //DMA_SetCurrDataCounter(DMA1_Channel6,USART_MAX_LEN); // ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ
   DMA_Cmd(DMA1_Channel3, ENABLE);
   USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);                          //��������DMA����
   USART_Cmd(USART3, ENABLE);      //ʹ�ܴ���
   DMA_SetCurrDataCounter(DMA1_Channel3,USART_MAX_LEN); // ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ
   //USART_ReceiveData(USART2);
   //USART_Cmd(USART3, ENABLE);      //ʹ�ܴ���
   // ��������жϱ�־λ(���պ��������־λ������)
   //printf("data=%d\r\n",USART_ReceiveData(USART2));
   // printf("data1=%d\r\n",USART2_RxBuf[0]);
   //DMA_Cmd(DMA1_Channel6, DISABLE);                                // �ر�DMA1_Channel6���ٽ�������

    while(DMA_GetFlagStatus(DMA1_FLAG_TC3)==RESET);

    // ���USART1�����ݼĴ���
   //USART_ClearFlag(USART3, USART_FLAG_RXNE);

    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC3);                                   // ��DMA1_Channel6������ɱ�־λ
    USART_DMACmd(USART3, USART_DMAReq_Rx, DISABLE);                          //��������DMA����
    USART_Cmd(USART3, DISABLE);      //ʹ�ܴ���
    //DMA_SetCurrDataCounter(DMA1_Channel6,USART_MAX_LEN);            // ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ
    //for (i = 0; i < len; ++i) {                                     // �ѽ��յ�������ת�Ƶ���������
    //res_data[i] = USART2_RxBuf[i];
    //printf("res%d=%d\r\n",i,res_data[i]);
        }



