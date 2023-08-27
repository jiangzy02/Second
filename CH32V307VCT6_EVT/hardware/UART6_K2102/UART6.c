#include "UART6.h"

#include "debug.h"

#if EN_UART6_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 UART6_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��    ������ɱ�־
//bit14��    ���յ�0x0d
//bit13~0��  ���յ�����Ч�ֽ���Ŀ
u16 UART6_RX_STA=0;       //����״̬���

void Init_uart6(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOE, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6, ENABLE);
    // ��PE10��PE11��ӳ��ΪUART6_TX��UART6_RX
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

      //Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    //USART2 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx;
    USART_Init(UART6, &USART_InitStructure);

    USART_ITConfig(UART6, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(UART6, ENABLE);      //ʹ�ܴ���
}

u16 Red_Flag=0;//ǰ��β�Ʊ��
u16 Yellow_Flag=0;//ǰ��β�Ʊ��

__attribute__((interrupt("WCH-Interrupt-fast")))
void UART6_IRQHandler(void)
{
        u8 Res;
        if(USART_GetITStatus(UART6,USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
            {
            Res =USART_ReceiveData(UART6); //��ȡ���յ�������

            if((UART6_RX_STA&0x8000)==0)//����δ���
                {
                if(UART6_RX_STA&0x4000)//���յ���0x0d
                    {
                    if(Res!=0x0a)UART6_RX_STA=0;//���մ���,���¿�ʼ
                    else UART6_RX_STA|=0x8000;  //���������
                    }
                else //��û�յ�0X0D
                    {
                    if(Res==0x0d)UART6_RX_STA|=0x4000;
                    else
                        {
                        UART6_RX_BUF[UART6_RX_STA&0X3FFF]=Res ;
                        UART6_RX_STA++;
                        if(UART6_RX_STA>(USART_REC_LEN-1))UART6_RX_STA=0;//�������ݴ���,���¿�ʼ����
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


