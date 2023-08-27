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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//ʹ��APB2�����GPIOA��ʱ��	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//ʹ�� DAC ʱ��
	
	/*����PA4����PA5������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	//DAC��������
	DAC_InitStructure.DAC_Trigger=DAC_Trigger_None; //��ʹ�ô�������TEN1=0
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ� ��ֵ��,ʹ�ò���ʱ��ʹ�ô˲���
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable;//DAC1 �������ر� BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitStructure); //��ʼ�� DAC ͨ�� 1
	
	DAC_Cmd(DAC_Channel_1, ENABLE); //ʹ�� DAC ͨ�� 1
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);//12 λ�Ҷ��룺 �û����뽫���ݼ��ص� DAC_DHR12Rx [11:0] λ���洢��DHRx[11:0] λ�� ��
	
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
				printf("��� DAC ��ѹֵΪ�� %.2fV\r\n",dac_vol);
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
				printf("��� DAC ��ѹֵΪ�� %.2fV\r\n",dac_vol);
				}	
		}
		delay_ms(10);
	}
}
*/

