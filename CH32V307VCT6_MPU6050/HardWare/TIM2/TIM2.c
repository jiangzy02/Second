#include "debug.h"
#include "TIM2.h"
#include "math.h"
#include "stdlib.h"
#define angle1_THRESHOLD 50 // 速度变化值的阈值1
#define angle2_THRESHOLD 90 // 速度变化值的阈值2
float prev_angle = 0; // 上一次测量到的速度值
uint8_t roll_flag = 0; // 标志变量
float current_angle = 0; // 当前速度值
//extern float Roll;
//溢出时间time=（arr+1）*（psc+1）/96  溢出时间单位为秒
void TIM2_init(void) {

  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能TIM2时钟

  //主频96MHz
  TIM_TimeBaseStructure.TIM_Period = 9999; // 设置定时器周期
  TIM_TimeBaseStructure.TIM_Prescaler = 9599; // 设置定时器预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 设置定时器时钟分割
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 设置计数器模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能TIM2的更新中断

  //中断优先级NVIC设置
      NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //设置抢占优先级
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //设置从优先级
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道使能
      NVIC_Init(&NVIC_InitStructure);   //初始化NVIC寄存器
      TIM_Cmd(TIM2, ENABLE); // 启动定时器
}
extern  float new_roll;
float angle_change;
__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) { // 检查是否溢出
      float current_angle = new_roll; // 获取当前值
      angle_change = abs(current_angle - prev_angle); // 计算变化值
      if (angle_change >90&&angle_change<300) { // 检查变化值是否大于阈值
           //roll_flag = 1; // 设置标志变量
           USART_SendData(USART2, 0xAA);
           //printf("777\r\n");
         }

         prev_angle = current_angle; // 更新上一次值
         TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除中断标志
  }
}
