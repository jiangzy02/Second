#include <DMA.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <stm32f10x_dma.h>
#include <stm32f10x_usart.h>
#include <key.h>
void DMA_Configuration(u32 mar,u16 ndtr)
{
		DMA_InitTypeDef DMA_InitStructure;
	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1|RCC_AHBPeriph_DMA2, ENABLE);
	
		DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&USART1->DR; //&USART1->DR，其中&取地址，强制转换为32位，
		DMA_InitStructure.DMA_MemoryBaseAddr = mar ; 
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; //据传输方向为存储器到外设
		DMA_InitStructure.DMA_BufferSize =ndtr ; 
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不变
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址递增
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设数据宽度为8位
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //存储器数据宽度选择8位
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //工作在正常缓存模式
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA 通道 x 拥有中优先级
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA 通道 x 没有设置为内存到内存传输
		DMA_Init(DMA1_Channel4, &DMA_InitStructure);
		
		DMA_Cmd(DMA1_Channel4, ENABLE);//使能 DMA1_Channel4 
	
	
}



void DMAx_Enable(u16 ndtr)
{
 
	DMA_Cmd(DMA1_Channel4, DISABLE);                      //关闭DMA传输 
	 
 
	DMA_Cmd(DMA1_Channel4, ENABLE);                      //开启DMA传输 
}	  



//int main(void)
//{
//	RCC_Configuration();
//	GPIO_Configuration();
//	Key();
//	
//	DMA_Configuration((u32)send_buf,send_buf_len);
//	Send_Data(send_buf);
//	USART1_Configuration();
//	
//	while(1)
//	{
//		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
//		delay_ms(100);
//		GPIO_SetBits(GPIOC,GPIO_Pin_0);
//		delay_ms(100);
//		if(K_UP==1)
//		{
//				USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //使能串口1的DMA发送 
//				DMAx_Enable(send_buf_len);    //开始一次DMA传输
//			
//				while(1)
//				{
//					if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0)//判断通道4传输完成
//					{
//						DMA_ClearFlag(DMA1_FLAG_TC4);
//						break;
//					}
//					GPIO_ResetBits(GPIOC,GPIO_Pin_1);
//					delay_ms(100);
//					GPIO_SetBits(GPIOC,GPIO_Pin_1);
//					delay_ms(100);
//				}		
//		}
//	}
//}