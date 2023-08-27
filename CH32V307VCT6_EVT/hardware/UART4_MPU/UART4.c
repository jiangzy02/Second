#include "UART4.h"

#include "debug.h"

#if EN_UART4_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 UART4_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��    ������ɱ�־
//bit14��    ���յ�0x0d
//bit13~0��  ���յ�����Ч�ֽ���Ŀ
u16 UART4_RX_STA=0;       //����״̬���

void uart4_Init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ʱ��GPIOB��USART3
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

      //Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      //�����ȼ�4
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    //USART2 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx;
    USART_Init(UART4, &USART_InitStructure);

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(UART4, ENABLE);      //ʹ�ܴ���
}

u16 Angle_Mode=0;//��ת���־


__attribute__((interrupt("WCH-Interrupt-fast")))
void UART4_IRQHandler(void)
{
        u8 Res;
        if(USART_GetITStatus(UART4,USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
            {
            Res =USART_ReceiveData(UART4); //��ȡ���յ�������
            printf("Res=%d\r\n",Res);
          //  if((UART4_RX_STA&0x8000)==0)//����δ���
             //   {
            //    if(UART4_RX_STA&0x4000)//���յ���0x0d
              //      {
              //      if(Res!=0x0a)UART4_RX_STA=0;//���մ���,���¿�ʼ
               //     else UART4_RX_STA|=0x8000;  //���������
               //     }
             //   else //��û�յ�0X0D
               //     {
                //    if(Res==0x0d)UART4_RX_STA|=0x4000;
                //    else
                 //       {
                  //      UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;
                 //       UART4_RX_STA++;
                 //       if(UART4_RX_STA>(USART_REC_LEN-1))UART4_RX_STA=0;//�������ݴ���,���¿�ʼ����
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







