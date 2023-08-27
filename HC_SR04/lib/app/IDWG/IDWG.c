#include <IDWG.h>


/*************
IDWG看门狗:每过一段时间不喂狗，系统就会复位




************/


void IDWG_Configuration(void)
{

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//允许写入操作
	IWDG_SetPrescaler(IWDG_Prescaler_256);//预分频设置为256
	IWDG_SetReload(800);//tout=4*256/40*800=20480
	IWDG_ReloadCounter(); //重装载初值
	IWDG_Enable(); // 打开独立看门狗


}