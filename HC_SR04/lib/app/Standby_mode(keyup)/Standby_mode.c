#include <Standby_mode.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_pwr.h>

void  Standby_mode_keyup(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//ʹ��PWRʱ��
	PWR_ClearFlag(PWR_FLAG_WU);//������ѱ�־λ
	
	PWR_WakeUpPinCmd(ENABLE);//����KeyupΪ����ģʽ����Դ
	
	PWR_EnterSTANDBYMode();//�������ģʽ
	
}

