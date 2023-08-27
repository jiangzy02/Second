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
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC的分频因子，不能超过14MHz。ADC 时钟为 72/6=12MHz
		
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1; //ADC1_IN1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	//adc参数配置
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1 和 ADC2 工作在独立模式
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;//扫描模式为单通道模式
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//模数转换工作在单次模式
		ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;//禁止触发检测， 使用软件触发
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐，即储存放在 ADC_DR 寄存器的[0:11]位内
		ADC_InitStructure.ADC_NbrOfChannel = 1;//规定了顺序进行规则转换的 ADC 通道的数目为1
		ADC_Init(ADC1, &ADC_InitStructure);
	
	
		ADC_Cmd(ADC1, ENABLE);//开启 AD 转换器
		ADC_ResetCalibration(ADC1);//重置指定的 ADC 的校准寄存器
			while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准结束
		ADC_StartCalibration(ADC1);//开始指定 ADC 的校准状态
		  while(ADC_GetCalibrationStatus(ADC1)); //等待校准结束
			
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能或者失能指定的 ADC的软件转换启动功能
		
}

u16 Get_ADC_Value(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	
	ADC_RegularChannelConfig(ADC1, ch, 1,ADC_SampleTime_239Cycles5); //ADC1,ADC 通道,239.5 个周期,提高采样时间可以提高精确度

	for(t=0;t<times;t++)
		{
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能指定的 ADC1 的软件转换启动功能
			
			while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
		
			temp_val=ADC_GetConversionValue(ADC1)+temp_val;	
			delay_ms(5);
		}

	return (temp_val/times);
}


/*
adc主函数案例
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
		printf("检测 AD 值为： %d\r\n",value);
		vol=(float)value*(3.3/4096);
		printf("检测电压值为： %.2f\r\n",vol);
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








