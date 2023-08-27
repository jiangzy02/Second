#include "key_pwm.h"

#include  "debug.h"
int pwm=1000;
u8 Stop=0;//停车标志位

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  // 使能GPIOC时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
  // 配置PC0、1,2、3/4/5为输入模式
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  // 下拉输入模式，上升沿是下拉输入，因为如果是上拉输入，由于上拉电阻存在会导致没有跳变
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  // 配置外部中断线0、1、2、3/4/5
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);

  EXTI_InitStructure.EXTI_Line = EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // 上升沿触发,因为按下时是高电平
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // 配置NVIC中断优先级
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
__attribute__((interrupt("WCH-Interrupt-fast")))//判断连续驾驶
void EXTI0_IRQHandler(void)//PC0 连续驾驶
{
    if (EXTI_GetITStatus(EXTI_Line0)!= RESET)
            {
                  Delay_Ms(15);//消抖
                  ContDriveflag=1;
              EXTI_ClearITPendingBit(EXTI_Line0);
            }
}

//判定减速
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)//减速按键，line1对应PC1
    {
            Delay_Ms(15);//消抖
                pwm = pwm+100;

      EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
//判定加速
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI2_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET)//加速按键，PC2
    {
           Delay_Ms(15);//消抖
                pwm = pwm-100;
      EXTI_ClearITPendingBit(EXTI_Line2);
    }

}

uint8_t star_flag=0,star=0;
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line3) != RESET)//PC3，停止、启动按键
    {
          Delay_Ms(15);//消抖
                Stop=1;
                //判断是否需要启动或停止电机
                if (Stop == 0 && star_flag == 0) {
                    return; //Stop和star_flag都是0，不需要执行任何操作
                } else if (Stop == 1 && star_flag == 0) {
                    star = 1; //按键按下star=1，电机启动
                    star_flag = 1;
                } else if (Stop == 1 && star_flag == 1) {
                    star = 0; //按键再次按下star=0，电机停止
                    star_flag = 0;
                }
      EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

u8 Sharpadd_flag=0;
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI4_IRQHandler(void)
{
if (EXTI_GetITStatus(EXTI_Line4) != RESET)//PC4，急加速
{
   Delay_Ms(15);//消抖
   pwm = pwm-250;//按键按下，PWM波占空比急剧降低，模拟急减速
   Sharpadd_flag=1;

  EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

u8 Sharpslowdown_flag=0;
__attribute__((interrupt("WCH-Interrupt-fast")))
void EXTI9_5_IRQHandler(void)
{
if (EXTI_GetITStatus(EXTI_Line5) != RESET)//PC5，急减速
{
   Delay_Ms(15);//消抖
   pwm = pwm+250;//按键按下，PWM波占空比急剧升高，模拟急加速
   Sharpslowdown_flag=1;

      EXTI_ClearITPendingBit(EXTI_Line5);
    }
}





