#include "debug.h"
#include "TIM2.h"
#include "math.h"
#include "stdlib.h"
#define angle1_THRESHOLD 50 // �ٶȱ仯ֵ����ֵ1
#define angle2_THRESHOLD 90 // �ٶȱ仯ֵ����ֵ2
float prev_angle = 0; // ��һ�β��������ٶ�ֵ
uint8_t roll_flag = 0; // ��־����
float current_angle = 0; // ��ǰ�ٶ�ֵ
//extern float Roll;
//���ʱ��time=��arr+1��*��psc+1��/96  ���ʱ�䵥λΪ��
void TIM2_init(void) {

  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // ʹ��TIM2ʱ��

  //��Ƶ96MHz
  TIM_TimeBaseStructure.TIM_Period = 9999; // ���ö�ʱ������
  TIM_TimeBaseStructure.TIM_Prescaler = 9599; // ���ö�ʱ��Ԥ��Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // ���ö�ʱ��ʱ�ӷָ�
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ü�����ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // ʹ��TIM2�ĸ����ж�

  //�ж����ȼ�NVIC����
      NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //������ռ���ȼ�
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //���ô����ȼ�
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ��ʹ��
      NVIC_Init(&NVIC_InitStructure);   //��ʼ��NVIC�Ĵ���
      TIM_Cmd(TIM2, ENABLE); // ������ʱ��
}
extern  float new_roll;
float angle_change;
__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) { // ����Ƿ����
      float current_angle = new_roll; // ��ȡ��ǰֵ
      angle_change = abs(current_angle - prev_angle); // ����仯ֵ
      if (angle_change >90&&angle_change<300) { // ���仯ֵ�Ƿ������ֵ
           //roll_flag = 1; // ���ñ�־����
           USART_SendData(USART2, 0xAA);
           //printf("777\r\n");
         }

         prev_angle = current_angle; // ������һ��ֵ
         TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // ����жϱ�־
  }
}
