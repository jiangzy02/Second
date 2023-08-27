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
	
		DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)&USART1->DR; //&USART1->DR������&ȡ��ַ��ǿ��ת��Ϊ32λ��
		DMA_InitStructure.DMA_MemoryBaseAddr = mar ; 
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; //�ݴ��䷽��Ϊ�洢��������
		DMA_InitStructure.DMA_BufferSize =ndtr ; 
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //�������ݿ��Ϊ8λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //�洢�����ݿ��ѡ��8λ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //��������������ģʽ
		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA ͨ�� x ӵ�������ȼ�
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA ͨ�� x û������Ϊ�ڴ浽�ڴ洫��
		DMA_Init(DMA1_Channel4, &DMA_InitStructure);
		
		DMA_Cmd(DMA1_Channel4, ENABLE);//ʹ�� DMA1_Channel4 
	
	
}



void DMAx_Enable(u16 ndtr)
{
 
	DMA_Cmd(DMA1_Channel4, DISABLE);                      //�ر�DMA���� 
	 
 
	DMA_Cmd(DMA1_Channel4, ENABLE);                      //����DMA���� 
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
//				USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);  //ʹ�ܴ���1��DMA���� 
//				DMAx_Enable(send_buf_len);    //��ʼһ��DMA����
//			
//				while(1)
//				{
//					if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=0)//�ж�ͨ��4�������
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