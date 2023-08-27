#include "debug.h"
#include "stdio.h"


#define HCSR04_PORT     GPIOD
#define HCSR04_CLK      RCC_APB2Periph_GPIOD
#define HCSR04_TRIG     GPIO_Pin_4
#define HCSR04_ECHO     GPIO_Pin_3
uint64_t time=0;            //声明变量，用来计时
uint64_t time_end=0;        //声明变量，存储回波信号时间


u16 msHcCount = 0;

void Hcsr04_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB2PeriphClockCmd(HCSR04_CLK, ENABLE);

    //IO口初始化
    GPIO_InitStructure.GPIO_Pin =HCSR04_TRIG;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //设置IO口输出模式为推挽输出
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);

    //IO口初始化
    GPIO_InitStructure.GPIO_Pin =   HCSR04_ECHO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //设置IO口输入模式浮空输入
    GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //使能定时器时钟
    //溢出时间time=（arr+1）*（psc+1）/144  溢出时间为1000us
    TIM_TimeBaseStructure.TIM_Period = 1000-1;//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =SystemCoreClock / 1000000 - 1; // 预分频系数为CPU时钟/1000000-1
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //设置时钟分割

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//根据指定的参数初始化TIM3的时间基数单位
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);    //使能指定的TIM3中断，打开更新中断

     //中断优先级NVIC设置
     NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //设置抢占优先级
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //设置从优先级
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道使能
     NVIC_Init(&NVIC_InitStructure);   //初始化NVIC寄存器

     TIM_Cmd(TIM4,DISABLE);
}



void OpenTimer()
{
    TIM_SetCounter(TIM4,0); //设置TIM3计数寄存器的值
    msHcCount = 0;
    TIM_Cmd(TIM4, ENABLE);   //使能定时器TIM3
}

void CloseTimer()
{
    TIM_Cmd(TIM4, DISABLE);   //停止使能定时器TIM3
}

 //定时器4中断服务程序
__attribute__((interrupt("WCH-Interrupt-fast")))
void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)//检查TIM4的更新中断是否发生
    {
      TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM4更新中断标志
            msHcCount++;
    }
}




u32 GetEchoTimer(void)
{
    u32 t = 0;
    t = msHcCount*1000;    //将时间转化为微秒
    t += TIM_GetCounter(TIM4);//获取当前计数器的值
    TIM4->CNT = 0; //清零计数器
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
        GPIO_SetBits(GPIOD,GPIO_Pin_4); //IO口PD2输出一个高电平
        Delay_Us(20);
        GPIO_ResetBits(GPIOD,GPIO_Pin_4);//IO口PD2输出一个低电平
        while(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==0);
        OpenTimer();   //开始计时
        i = i + 1;
        while(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)==1);
        CloseTimer();  //结束计时
        t = GetEchoTimer();
        lengthTemp = ((float)t/58.0);   //计算单次物体距离
        sum = lengthTemp + sum ;
    }
    lengthTemp = sum/5.0;   //求五次距离平均值
    return lengthTemp;

}



