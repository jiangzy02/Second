#include <temp.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
void ADC_temp_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//打开ADC1的时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 分频因子6时钟为12MHz
	ADC_TempSensorVrefintCmd(ENABLE);//打开ADC内部温度传感器
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC工作模式 , ADC1和ADC2独立工作
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;//1个转换在规则序列中，也就是只转换规则序列1
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器
	ADC_ResetCalibration(ADC1);//重置指定的ADC的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));//获取ADC重置校准寄存器的状态
	ADC_StartCalibration(ADC1);//开始指定ADC的校准状态
	while(ADC_GetCalibrationStatus(ADC1));//获取指定ADC的校准程序
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能或者失能指定的ADC的软件转换启动功能
	
	
	
	
}

u16 Get_ADC_Temp_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);	//ADC1,ADC通道,239.5个周期,提高采样时间可以提高精确度
	for(t=0;t<times;t++)
	{
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能指定的ADC1的软件转换启动功能	
		while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
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
	adc_value=Get_ADC_Temp_Value(ADC_Channel_16,10);	//读取通道16内部温度传感器通道,10次取平均
	temperture=(float)adc_value*(3.3/4096);		//电压值
	temperture=(1.43-temperture)/0.0043+25; //转换为温度值 
	temp=temperture*100;					//扩大100倍.
	return temp;

}
