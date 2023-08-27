#include <DAC.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_dac.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>

void DAC_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能APB2外设的GPIOA的时钟	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能 DAC 时钟
	
	/*配置PA4或者PA5的引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	//DAC参数配置
	DAC_InitStructure.DAC_Trigger=DAC_Trigger_None; //不使用触发功能TEN1=0
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、 幅值设,使用波形时才使用此参数
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;//DAC1 输出缓存关闭 BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitStructure); //初始化 DAC 通道 1
	
	DAC_Cmd(DAC_Channel_1, ENABLE); //使能 DAC 通道 1
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);//12 位右对齐： 用户必须将数据加载到 DAC_DHR12Rx [11:0] 位（存储到DHRx[11:0] 位） 。
	
}


/*
int main(void)
{
	int dac_value=0;
	u16 dacval;
	float dac_vol;
	
	RCC_Configuration();
	GPIO_Configuration();
	DAC_Configuration();
	USART1_Configuration();
	Key();
	
	
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
	
		if(K_UP==1)
		{
			delay_ms(10);
				if(K_UP==1)
				{
					dac_value=dac_value+400;
						if(dac_value>=4000)
						{
							dac_value=4095;
						}
				DAC_SetChannel1Data(DAC_Align_12b_R,dac_value);
						
				dacval=DAC_GetDataOutputValue(DAC_Channel_1);
				dac_vol=(float)dacval*(3.3/4096);
				printf("输出 DAC 电压值为： %.2fV\r\n",dac_vol);
				}
		}
		else if(K_DOWN==0)
		{
			delay_ms(10);
				if(K_DOWN==0)
				{
					dac_value=dac_value-400;
						if(dac_value<=0)
						{
							dac_value=0;
						}
				DAC_SetChannel1Data(DAC_Align_12b_R,dac_value);
						
				dacval=DAC_GetDataOutputValue(DAC_Channel_1);
				dac_vol=(float)dacval*(3.3/4096);
				printf("输出 DAC 电压值为： %.2fV\r\n",dac_vol);
				}	
		}
		delay_ms(10);
	}
}
*/

