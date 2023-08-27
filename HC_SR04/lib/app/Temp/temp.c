#include <temp.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
void ADC_temp_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//��ADC1��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); // ��Ƶ����6ʱ��Ϊ12MHz
	ADC_TempSensorVrefintCmd(ENABLE);//��ADC�ڲ��¶ȴ�����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC����ģʽ , ADC1��ADC2��������
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
	ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;//1��ת���ڹ��������У�Ҳ����ֻת����������1
	ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
	ADC_Cmd(ADC1, ENABLE);//����ADת����
	ADC_ResetCalibration(ADC1);//����ָ����ADC��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//��ȡADC����У׼�Ĵ�����״̬
	ADC_StartCalibration(ADC1);//��ʼָ��ADC��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));//��ȡָ��ADC��У׼����
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ�ܻ���ʧ��ָ����ADC�����ת����������
	
	
	
	
}

u16 Get_ADC_Temp_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);	//ADC1,ADCͨ��,239.5������,��߲���ʱ�������߾�ȷ��
	for(t=0;t<times;t++)
	{
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ��ָ����ADC1�����ת����������	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
		temp_val+=ADC_GetConversionValue(ADC1);
		delay_ms(5);
	}
	return temp_val/times;
} 

int Get_temperture(void)
{
	u32 adc_value;
	int temp;
 	double temperture;
	adc_value=Get_ADC_Temp_Value(ADC_Channel_16,10);	//��ȡͨ��16�ڲ��¶ȴ�����ͨ��,10��ȡƽ��
	temperture=(float)adc_value*(3.3/4096);		//��ѹֵ
	temperture=(1.43-temperture)/0.0043+25; //ת��Ϊ�¶�ֵ 
	temp=temperture*100;					//����100��.
	return temp;

}
