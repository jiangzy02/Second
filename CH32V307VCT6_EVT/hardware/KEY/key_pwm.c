#include "key_pwm.h"

#include  "debug.h"
int pwm=1000;
u8 Stop=0;//ͣ����־λ

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  // ʹ��GPIOCʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  // ����PC0��1,2��3/4/5Ϊ����ģʽ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  // ��������ģʽ�����������������룬��Ϊ������������룬��������������ڻᵼ��û������
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  // �����ⲿ�ж���0��1��2��3/4/5
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);

  EXTI_InitStructure.EXTI_Line = EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // �����ش���,��Ϊ����ʱ�Ǹߵ�ƽ
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // ����NVIC�ж����ȼ�
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

u16 ContDriveflag=0;
__attribute__((interrupt("WCH-Interrupt-fast")))//�ж�������ʻ
void EXTI0_IRQHandler(void)//PC0 ������ʻ
{
    if (EXTI_GetITStatus(EXTI_Line0)!= RESET)
            {
                  Delay_Ms(15);//����
                  ContDriveflag=1;
              EXTI_ClearITPendingBit(EXTI_Line0);
            }
}

//�ж�����
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)//���ٰ�����line1��ӦPC1
    {
            Delay_Ms(15);//����
                pwm = pwm+100;

      EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
//�ж�����
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)//���ٰ�����PC2
    {
           Delay_Ms(15);//����
                pwm = pwm-100;
      EXTI_ClearITPendingBit(EXTI_Line2);
    }

}

uint8_t star_flag=0,star=0;
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line3) != RESET)//PC3��ֹͣ����������
    {
          Delay_Ms(15);//����
                Stop=1;
                //�ж��Ƿ���Ҫ������ֹͣ���
                if (Stop == 0 && star_flag == 0) {
                    return; //Stop��star_flag����0������Ҫִ���κβ���
                } else if (Stop == 1 && star_flag == 0) {
                    star = 1; //��������star=1���������
                    star_flag = 1;
                } else if (Stop == 1 && star_flag == 1) {
                    star = 0; //�����ٴΰ���star=0�����ֹͣ
                    star_flag = 0;
                }
      EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

u8 Sharpadd_flag=0;
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI4_IRQHandler(void)
{
if (EXTI_GetITStatus(EXTI_Line4) != RESET)//PC4��������
{
   Delay_Ms(15);//����
   pwm = pwm-250;//�������£�PWM��ռ�ձȼ��罵�ͣ�ģ�⼱����
   Sharpadd_flag=1;

  EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

u8 Sharpslowdown_flag=0;
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI9_5_IRQHandler(void)
{
if (EXTI_GetITStatus(EXTI_Line5) != RESET)//PC5��������
{
   Delay_Ms(15);//����
   pwm = pwm+250;//�������£�PWM��ռ�ձȼ������ߣ�ģ�⼱����
   Sharpslowdown_flag=1;

      EXTI_ClearITPendingBit(EXTI_Line5);
    }
}





