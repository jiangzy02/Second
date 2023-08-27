#include <ADC.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
void ADC_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		ADC_InitTypeDef ADC_InitStructure; 
		
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);//����ADC�ķ�Ƶ���ӣ����ܳ���14MHz��ADC ʱ��Ϊ 72/6=12MHz
		
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1; //ADC1_IN1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	//adc��������
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1 �� ADC2 �����ڶ���ģʽ
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;//ɨ��ģʽΪ��ͨ��ģʽ
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//ģ��ת�������ڵ���ģʽ
		ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;//��ֹ������⣬ ʹ���������
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ��룬��������� ADC_DR �Ĵ�����[0:11]λ��
		ADC_InitStructure.ADC_NbrOfChannel = 1;//�涨��˳����й���ת���� ADC ͨ������ĿΪ1
		ADC_Init(ADC1, &ADC_InitStructure);
	
	
		ADC_Cmd(ADC1, ENABLE);//���� AD ת����
		ADC_ResetCalibration(ADC1);//����ָ���� ADC ��У׼�Ĵ���
			while(ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���λУ׼����
		ADC_StartCalibration(ADC1);//��ʼָ�� ADC ��У׼״̬
		  while(ADC_GetCalibrationStatus(ADC1)); //�ȴ�У׼����
			
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ�ܻ���ʧ��ָ���� ADC�����ת����������
		
}

u16 Get_ADC_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	
	ADC_RegularChannelConfig(ADC1, ch, 1,ADC_SampleTime_239Cycles5); //ADC1,ADC ͨ��,239.5 ������,��߲���ʱ�������߾�ȷ��

	for(t=0;t<times;t++)
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ��ָ���� ADC1 �����ת����������
			
			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
		
			temp_val=ADC_GetConversionValue(ADC1)+temp_val;	
			delay_ms(5);
		}

	return (temp_val/times);
}


/*
adc����������
int main(void)
{
	u16 value=0;
	float vol;
	u8 flag=0;
	
	RCC_Configuration();
	GPIO_Configuration();
	USART1_Configuration();
	ADC_Configuration();
	Key();
	
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
		if(flag)
		{
		value=Get_ADC_Value(ADC_Channel_1,20);
		printf("��� AD ֵΪ�� %d\r\n",value);
		vol=(float)value*(3.3/4096);
		printf("����ѹֵΪ�� %.2f\r\n",vol);
		delay_ms(10);
		flag=0;			
		}
		
		if(K_UP==1)
		{
			delay_ms(10);
				if(K_UP==1)	
				{
					flag=1;
				}
		}
	}
		
}
*/








