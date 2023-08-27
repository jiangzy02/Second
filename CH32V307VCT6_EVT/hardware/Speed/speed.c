#include "debug.h"
#include "speed.h"

//motorģ��
//PB13��PB14��L298N��N3��N4��PB5��ENA

/*******************************************************
 * motor:PB13 PB14
 *        0    0   ֹͣ
 *        0    1   ��ת
 *        1    0   ��ת
 *        1    1   ֹͣ      ռ�ձ�=CCR/(arr+1)
 ******************************************************** */

void MOTOR_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PB�˿�ʱ��

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��GPIOB13��14

    GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    GPIO_ResetBits(GPIOB, GPIO_Pin_14);

}


//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5

   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��    GPIOB.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO

   //��ʼ��TIM3
    //���ʱ��time=��arr+1��*��psc+1��/96000000
    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM3 Channel2 PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
    TIM_OCInitStructure.TIM_Pulse = 50;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}

//TM2
void TIM2_inIt(void)
{
//�ṹ��
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;


RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//�����ж�
NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //TIM2ͨ��
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ��
NVIC_Init(&NVIC_InitStructure); //����

TIM_TimeBaseStructure.TIM_Period = 999; //��װ�ؼĴ���
TIM_TimeBaseStructure.TIM_Prescaler =95; //Ԥ��Ƶ
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM2���ϼ���
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //���� TIM2

TIM_Cmd(TIM2, ENABLE); //ʹ��
TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}


//��紫����
void GD_inIt(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


float Circle=0;   //ת��
float num=0;      //��������������
u32 times=0;
u8 flag=0;        //������������־
float CountSensor_Count=0;

__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM2_IRQHandler(void)                           //����һ���ж�1Ms
{
if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)    //1ms
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update );
        times++;
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
          flag=1;
      if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0&& flag==1)
      {
          flag=0; //�����־
          num=num+1; //��������������
          CountSensor_Count++;
      }
      if(times == 1000) //��ʱ1S������ת��
      {
          Circle=num/20; //ת��
          times=0;
          num=0;
      }
}
}


uint16_t CountSensor_Get(void)//Ȧ��
{
    return CountSensor_Count/20;
}


