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

u32 R_data;	  //����һ��32λ���ݱ��������������
u8  hw_jsbz;  //����һ��8λ���ݵı���������ָʾ���ձ�־

void IR_Input_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
			EXTI_InitTypeDef EXTI_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);
	
			
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;//�������
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//�������룬��Ϊ�������ͷ����û�н��յ���ʱ��һֱ�Ǹߵ�ƽ����������Ϊ��������
			GPIO_Init(GPIOG,&GPIO_InitStructure);
	
			GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, GPIO_PinSource15);//ѡ�� GPIO �ܽ������ⲿ�ж���·
			EXTI_ClearITPendingBit(EXTI_Line15);//���EXTI��·����		
	
	
			EXTI_InitStructure.EXTI_Line=EXTI_Line15;//ʹ���ⲿ�ж���·0
			EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;//����EXTI��·Ϊ�ж�����
			EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�����жϴ���Ϊ�½��ش���
			EXTI_InitStructure.EXTI_LineCmd=ENABLE;
			EXTI_Init(&EXTI_InitStructure);
	

	
			/* ���� NVIC ���� */
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel; //��ȫ���ж�
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�Ϊ 0
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧ���ȼ�Ϊ 1
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ��
			NVIC_Init(&NVIC_InitStructure);
			

	
}
/*****

ͳ��ʱ�亯��

*****/


u8 HW_jssj()
{
	u8 t=0;
	while(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)//�ߵ�ƽ
	{
		t++;
		delay_us(20);
		if(t>=250) return t;//��ʱ���
	}
	return t;
}
/******

�ⲿ�ж���Ӧ����

******/

void EXTI15_10_IRQHandler(void)	  //����ң���ⲿ�ж�
{
	u8 Tim=0,Ok=0,Data,Num=0;

   while(1)
   {
	   	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)==1)
		{
			 Tim=HW_jssj();//��ô˴θߵ�ƽʱ��

			 if(Tim>=250) break;//�������õ��ź�

			 if(Tim>=200 && Tim<250)
			 {
			 	Ok=1;//�յ���ʼ�ź�
			 }
			 else if(Tim>=60 && Tim<90)
			 {
			 	Data=1;//�յ����� 1
			 }
			 else if(Tim>=10 && Tim<50)
			 {
			 	Data=0;//�յ����� 0
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

�����������

*******/
void IR_Transate(u32 R_data)
{
		switch(R_data)
		{
			case 0x00FFA25D :printf("���������ǹػ���\r\n") ; break;
			case 0x00FF629D :printf("����������mode��\r\n") ; break;
			case 0x00FFE21D :printf("���������ǽ�����\r\n") ; break;
			case 0x00FF22DD :printf("������������ͣ��\r\n") ; break;
			case 0x00FF02FD :printf("������������һ����\r\n") ; break;
			case 0x00FFC23D :printf("������������һ����\r\n") ; break;
			case 0x00FFE01F :printf("����������EQ��\r\n") ; break;
			case 0x00FFA857 :printf("����������VOL-��\r\n") ; break;
			case 0x00FF906F :printf("����������VOL+��\r\n") ; break;
			case 0x00FF6897 :printf("����������0��\r\n") ; break;
			case 0x00FF9867 :printf("����������RPT��\r\n") ; break;		
			case 0x00FFB04F :printf("����������U/SD��\r\n") ; break;
			case 0x00FF30CF :printf("����������1��\r\n") ; break;
			case 0x00FF18E7 :printf("����������2��\r\n") ; break;
			case 0x00FF7A85 :printf("����������3��\r\n") ; break;
			case 0x00FF10EF :printf("����������4��\r\n") ; break;
			case 0x00FF38C7 :printf("����������5��\r\n") ; break;
			case 0x00FF5AA5 :printf("����������6��\r\n") ; break;
			case 0x00FF42BD :printf("����������7��\r\n") ; break;
			case 0x00FF4AB5 :printf("����������8��\r\n") ; break;
			case 0x00FF52AD :printf("����������9��\r\n") ; break;
			default: break;
		}
}

/*  	������ʾ������
	
	while(1)
	{
		if(EXTI_GetITStatus(EXTI_Line15))	//���������յ�
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