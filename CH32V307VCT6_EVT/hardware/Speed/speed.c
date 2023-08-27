#include "debug.h"
#include "speed.h"

//motor模块
//PB13、PB14接L298N的N3、N4，PB5接ENA

/*******************************************************
 * motor:PB13 PB14
 *        0    0   停止
 *        0    1   正转
 *        1    0   反转
 *        1    1   停止      占空比=CCR/(arr+1)
 ******************************************************** */

void MOTOR_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB端口时钟

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIOB13与14

    GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    GPIO_ResetBits(GPIOB, GPIO_Pin_14);

}


//TIM3 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    //使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5

   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形    GPIOB.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO

   //初始化TIM3
    //溢出时间time=（arr+1）*（psc+1）/96000000
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM3 Channel2 PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
    TIM_OCInitStructure.TIM_Pulse = 50;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
    TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}

//TM2
void TIM2_inIt(void)
{
//结构体
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;


RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//配置中断
NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //TIM2通道
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //子优先级
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能
NVIC_Init(&NVIC_InitStructure); //配置

TIM_TimeBaseStructure.TIM_Period = 999; //重装载寄存器
TIM_TimeBaseStructure.TIM_Prescaler =95; //预分频
TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM2向上计数
TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //配置 TIM2

TIM_Cmd(TIM2, ENABLE); //使能
TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}


//光电传感器
void GD_inIt(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


float Circle=0;   //转速
float num=0;      //传感器脉冲输入
u32 times=0;
u8 flag=0;        //传感器触发标志
float CountSensor_Count=0;

__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM2_IRQHandler(void)                           //进入一次中断1Ms
{
if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)    //1ms
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update );
        times++;
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 1)
          flag=1;
      if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0&& flag==1)
      {
          flag=0; //清除标志
          num=num+1; //传感器触发次数
          CountSensor_Count++;
      }
      if(times == 1000) //计时1S，计算转速
      {
          Circle=num/20; //转速
          times=0;
          num=0;
      }
}
}


uint16_t CountSensor_Get(void)//圈数
{
    return CountSensor_Count/20;
}


