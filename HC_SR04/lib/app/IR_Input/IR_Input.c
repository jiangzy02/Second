#include <IR_Input.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_nvic.h>
#include <stm32f10x_it.h>
#include <stm32f10x_exti.h>
#include <delay_by_systick.h>
#include <TIM_Counter.h>
#include <stm32f10x_type.h>
#include <stdio.h>

u32 R_data;	  //定义一个32位数据变量，保存接收码
u8  hw_jsbz;  //定义一个8位数据的变量，用于指示接收标志

void IR_Input_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
			EXTI_InitTypeDef EXTI_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);
	
			
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;//红外接收
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入，因为红外接收头，在没有接收到的时候，一直是高电平，所以配置为上拉输入
			GPIO_Init(GPIOG,&GPIO_InitStructure);
	
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource15);//选择 GPIO 管脚用作外部中断线路
			EXTI_ClearITPendingBit(EXTI_Line15);//清除EXTI线路挂起		
	
	
			EXTI_InitStructure.EXTI_Line=EXTI_Line15;//使能外部中断线路0
			EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//设置EXTI线路为中断请求
			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//设置中断触发为下降沿触发
			EXTI_InitStructure.EXTI_LineCmd=ENABLE;
			EXTI_Init(&EXTI_InitStructure);
	

	
			/* 设置 NVIC 参数 */
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel; //打开全局中断
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级为 0
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应优先级为 1
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能
			NVIC_Init(&NVIC_InitStructure);
			

	
}
/*****

统计时间函数

*****/


u8 HW_jssj()
{
	u8 t=0;
	while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)//高电平
	{
		t++;
		delay_us(20);
		if(t>=250) return t;//超时溢出
	}
	return t;
}
/******

外部中断响应函数

******/

void EXTI15_10_IRQHandler(void)	  //红外遥控外部中断
{
	u8 Tim=0,Ok=0,Data,Num=0;

   while(1)
   {
	   	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)
		{
			 Tim=HW_jssj();//获得此次高电平时间

			 if(Tim>=250) break;//不是有用的信号

			 if(Tim>=200 && Tim<250)
			 {
			 	Ok=1;//收到起始信号
			 }
			 else if(Tim>=60 && Tim<90)
			 {
			 	Data=1;//收到数据 1
			 }
			 else if(Tim>=10 && Tim<50)
			 {
			 	Data=0;//收到数据 0
			 }

			 if(Ok==1)
			 {
			 	R_data<<=1;
				R_data+=Data;

				if(Num>=32)
				{
				  	break;
				}
			 }

			 Num++;
		}
   }

   EXTI_ClearITPendingBit(EXTI_Line15);	
}

/*******

按键翻译代码

*******/
void IR_Transate(u32 R_data)
{
		switch(R_data)
		{
			case 0x00FFA25D :printf("您所按的是关机键\r\n") ; break;
			case 0x00FF629D :printf("您所按的是mode键\r\n") ; break;
			case 0x00FFE21D :printf("您所按的是禁音键\r\n") ; break;
			case 0x00FF22DD :printf("您所按的是暂停键\r\n") ; break;
			case 0x00FF02FD :printf("您所按的是左一曲键\r\n") ; break;
			case 0x00FFC23D :printf("您所按的是右一曲键\r\n") ; break;
			case 0x00FFE01F :printf("您所按的是EQ键\r\n") ; break;
			case 0x00FFA857 :printf("您所按的是VOL-键\r\n") ; break;
			case 0x00FF906F :printf("您所按的是VOL+键\r\n") ; break;
			case 0x00FF6897 :printf("您所按的是0键\r\n") ; break;
			case 0x00FF9867 :printf("您所按的是RPT键\r\n") ; break;		
			case 0x00FFB04F :printf("您所按的是U/SD键\r\n") ; break;
			case 0x00FF30CF :printf("您所按的是1键\r\n") ; break;
			case 0x00FF18E7 :printf("您所按的是2键\r\n") ; break;
			case 0x00FF7A85 :printf("您所按的是3键\r\n") ; break;
			case 0x00FF10EF :printf("您所按的是4键\r\n") ; break;
			case 0x00FF38C7 :printf("您所按的是5键\r\n") ; break;
			case 0x00FF5AA5 :printf("您所按的是6键\r\n") ; break;
			case 0x00FF42BD :printf("您所按的是7键\r\n") ; break;
			case 0x00FF4AB5 :printf("您所按的是8键\r\n") ; break;
			case 0x00FF52AD :printf("您所按的是9键\r\n") ; break;
			default: break;
		}
}

/*  	主程序示例代码
	
	while(1)
	{
		if(EXTI_GetITStatus(EXTI_Line15))	//如果红外接收到
		{
				EXTI_ClearITPendingBit(EXTI_Line15);	
				EXTI15_10_IRQHandler();
				if(R_data!=0)
				{
				 IR_Transate(R_data);
				}
				R_data=0;
		}	

*/