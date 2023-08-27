#include <delay_by_systick.h>
#include <stm32f10x_systick.h>


static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms



void delay_init(u8 SYSCLK)
{
    SysTick->CTRL&=0xfffffffb;//���õδ�ʱ�ӵ�ʱ��Դ��bit 2��գ�ѡ���ⲿʱ��HCLK/8
    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us*1000;    
}

void delay_ms(u16 nms)
{        
 u32 temp;    
 SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����
 SysTick->VAL =0x00;           //��ռ�����
 SysTick->CTRL=0x01 ;          //��ʼ���� 
 do
 {
  temp=SysTick->CTRL;
 }
 while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��  
 SysTick->CTRL=0x00;       //�رռ�����
 SysTick->VAL =0X00;       //��ռ�����       
}  

/***********************************************************
���֣�delay_us
���ܣ�Ӧ�ó���us�������ʱʵ��
������u32 Nus
���أ�None
************************************************************/         
void delay_us(u32 Nus)
{  
 u32 temp;      
 SysTick->LOAD=Nus*fac_us; //ʱ�����     
 SysTick->VAL=0x00;        //��ռ�����
 SysTick->CTRL=0x01 ;      //��ʼ����  
 do
 {
  temp=SysTick->CTRL;
 }
 while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��  
 SysTick->CTRL=0x00;       //�رռ�����
 SysTick->VAL =0X00;       //��ռ�����    
}  
































//void delay_ms(u16 time)
//{
//			
//			FlagStatus Status;
//		  Systick_Configuration(time * 9000);//���������������	
//			
//			do
//				{
//				Status = SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
//				}while(Status == RESET);//���1ms����
//}

//void delay_us(u16 time)
//{
//			
//			FlagStatus Status;
//		  Systick_Configuration(time * 9);//���������������	
//			
//			do
//				{
//				Status = SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
//				}while(Status == RESET);//���1us����
//}

//void Systick_Configuration(u32 n)
//{
//	SysTick_CounterCmd(SysTick_Counter_Disable);
//	SysTick_ITConfig(DISABLE);
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//ϵͳʱ��λ72M�����Ƶλ9M
//	SysTick_SetReload(n);//1s
//	SysTick_CounterCmd(SysTick_Counter_Enable);
//}
