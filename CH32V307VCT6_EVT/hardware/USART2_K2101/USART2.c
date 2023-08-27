#include "USART2.h"

#include "debug.h"
//#if EN_USART2_RX   //���ʹ���˽���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��    ������ɱ�־
//bit14��    ���յ�0x0d
//bit13~0��  ���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���

void usart2_start(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʱ��GPIOB��USART3
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

      //Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    //USART2 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART2, ENABLE);      //ʹ�ܴ���
}

u16 Fatigue_Flag=0;//��ֵΪ0ʱ��������״̬,��ֵΪ1ʱ��ƣ��״̬
u16 Callphone_Flag=0;//��ֵΪ0ʱ����δ�Ӵ�绰״̬����ֵΪ1ʱ�Ǵ�绰״̬
u16 Smoking_Flag=0;//��ֵΪ0ʱ����δ����״̬����ֵΪ1ʱ������״̬
u16 Fatigue_State=0;
u16 Callphone_State=0;
u16 Smoking_state=0;

__attribute__((interrupt("WCH-Interrupt-fast")))
void USART2_IRQHandler(void)
{
        u8 Res;
        if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
            {
            Res =USART_ReceiveData(USART2); //��ȡ���յ�������

            if((USART2_RX_STA&0x8000)==0)//����δ���
                {
                if(USART2_RX_STA&0x4000)//���յ���0x0d
                    {
                    if(Res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
                    else USART2_RX_STA|=0x8000;  //���������
                    }
                else //��û�յ�0X0D
                    {
                    if(Res==0x0d)USART2_RX_STA|=0x4000;
                    else
                        {
                        USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
                        USART2_RX_STA++;
                        if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����
                        }
                    }
                }
            if (USART2_RX_STA&0x8000) {

                    if(USART2_RX_BUF[0]==0x41) //K210��⵽���̺��������յ��䷢�͵�0x41
                        {

                        Smoking_Flag=1;

                        }
                    if(USART2_RX_BUF[0]==0x42)//K210��⵽�Ӵ�绰���������յ��䷢�͵�0x42
                    {
                        Callphone_Flag=1;

                    }
                    if(USART2_RX_BUF[0]==0x43)//K210���ƣ�ͼ�ʻ���������յ��䷢�͵�0x43
                    {
                        Fatigue_Flag=1;

                    }

                    USART2_RX_STA=0;


            }
         }



}


//#endif




