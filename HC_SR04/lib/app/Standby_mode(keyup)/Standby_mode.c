#include <Standby_mode.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_pwr.h>

void  Standby_mode_keyup(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//使能PWR时钟
	PWR_ClearFlag(PWR_FLAG_WU);//清楚唤醒标志位
	
	PWR_WakeUpPinCmd(ENABLE);//设置Keyup为待机模式唤醒源
	
	PWR_EnterSTANDBYMode();//进入待机模式
	
}

