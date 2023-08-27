#include <delay_by_systick.h>
#include <stm32f10x_systick.h>


static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms



void delay_init(u8 SYSCLK)
{
    SysTick->CTRL&=0xfffffffb;//设置滴答时钟的时钟源：bit 2清空，选择外部时钟HCLK/8
    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us*1000;    
}

void delay_ms(u16 nms)
{        
 u32 temp;    
 SysTick->LOAD=(u32)nms*fac_ms;//时间加载
 SysTick->VAL =0x00;           //清空计数器
 SysTick->CTRL=0x01 ;          //开始倒数 
 do
 {
  temp=SysTick->CTRL;
 }
 while(temp&0x01&&!(temp&(1<<16)));//等待时间到达  
 SysTick->CTRL=0x00;       //关闭计数器
 SysTick->VAL =0X00;       //清空计数器       
}  

/***********************************************************
名字：delay_us
功能：应用程序us级别的延时实现
参数：u32 Nus
返回：None
************************************************************/         
void delay_us(u32 Nus)
{  
 u32 temp;      
 SysTick->LOAD=Nus*fac_us; //时间加载     
 SysTick->VAL=0x00;        //清空计数器
 SysTick->CTRL=0x01 ;      //开始倒数  
 do
 {
  temp=SysTick->CTRL;
 }
 while(temp&0x01&&!(temp&(1<<16)));//等待时间到达  
 SysTick->CTRL=0x00;       //关闭计数器
 SysTick->VAL =0X00;       //清空计数器    
}  
































//void delay_ms(u16 time)
//{
//			
//			FlagStatus Status;
//		  Systick_Configuration(time * 9000);//如果毫秒数记满了	
//			
//			do
//				{
//				Status = SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
//				}while(Status == RESET);//如果1ms记满
//}

//void delay_us(u16 time)
//{
//			
//			FlagStatus Status;
//		  Systick_Configuration(time * 9);//如果毫秒数记满了	
//			
//			do
//				{
//				Status = SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
//				}while(Status == RESET);//如果1us记满
//}

//void Systick_Configuration(u32 n)
//{
//	SysTick_CounterCmd(SysTick_Counter_Disable);
//	SysTick_ITConfig(DISABLE);
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//系统时钟位72M，则分频位9M
//	SysTick_SetReload(n);//1s
//	SysTick_CounterCmd(SysTick_Counter_Enable);
//}
