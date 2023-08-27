#include "debug.h"
#include "stdio.h"


#define HCSR04_PORT     GPIOD
#define HCSR04_CLK      RCC_APB2Periph_GPIOD
#define HCSR04_TRIG     GPIO_Pin_4
#define HCSR04_ECHO     GPIO_Pin_3
uint64_t time=0;            //����������������ʱ
uint64_t time_end=0;        //�����������洢�ز��ź�ʱ��


u16 msHcCount = 0;

void Hcsr04_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB2PeriphClockCmd(HCSR04_CLK, ENABLE);

    //IO�ڳ�ʼ��
    GPIO_InitStructure.GPIO_Pin =HCSR04_TRIG;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //����IO�����ģʽΪ�������
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);

    //IO�ڳ�ʼ��
    GPIO_InitStructure.GPIO_Pin =   HCSR04_ECHO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //����IO������ģʽ��������
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //ʹ�ܶ�ʱ��ʱ��
    //���ʱ��time=��arr+1��*��psc+1��/144  ���ʱ��Ϊ1000us
    TIM_TimeBaseStructure.TIM_Period = 1000-1;//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =SystemCoreClock / 1000000 - 1; // Ԥ��Ƶϵ��ΪCPUʱ��/1000000-1
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //����ʱ�ӷָ�

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ָ���Ĳ�����ʼ��TIM3��ʱ�������λ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    //ʹ��ָ����TIM3�жϣ��򿪸����ж�

     //�ж����ȼ�NVIC����
     NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //������ռ���ȼ�
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //���ô����ȼ�
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ��ʹ��
     NVIC_Init(&NVIC_InitStructure);   //��ʼ��NVIC�Ĵ���

     TIM_Cmd(TIM4,DISABLE);
}



void OpenTimer()
{
    TIM_SetCounter(TIM4,0); //����TIM3�����Ĵ�����ֵ
    msHcCount = 0;
    TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��TIM3
}

void CloseTimer()
{
    TIM_Cmd(TIM4, DISABLE);   //ֹͣʹ�ܶ�ʱ��TIM3
}

 //��ʱ��4�жϷ������
__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//���TIM4�ĸ����ж��Ƿ���
    {
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIM4�����жϱ�־
            msHcCount++;
    }
}




u32 GetEchoTimer(void)
{
    u32 t = 0;
    t = msHcCount*1000;    //��ʱ��ת��Ϊ΢��
    t += TIM_GetCounter(TIM4);//��ȡ��ǰ��������ֵ
    TIM4->CNT = 0; //���������
    Delay_Ms(50);
    return t;
}



float Hcsr04GetLength(void )
{
    u32 t = 0;
    int i = 0;
    float lengthTemp = 0;
    float sum = 0;
    while(i!=5)
    {
        GPIO_SetBits(GPIOD,GPIO_Pin_4); //IO��PD2���һ���ߵ�ƽ
        Delay_Us(20);
        GPIO_ResetBits(GPIOD,GPIO_Pin_4);//IO��PD2���һ���͵�ƽ
        while(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==0);
        OpenTimer();   //��ʼ��ʱ
        i = i + 1;
        while(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==1);
        CloseTimer();  //������ʱ
        t = GetEchoTimer();
        lengthTemp = ((float)t/58.0);   //���㵥���������
        sum = lengthTemp + sum ;
    }
    lengthTemp = sum/5.0;   //����ξ���ƽ��ֵ
    return lengthTemp;

}



