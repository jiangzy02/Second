#include <IDWG.h>


/*************
IDWG���Ź�:ÿ��һ��ʱ�䲻ι����ϵͳ�ͻḴλ




************/


void IDWG_Configuration(void)
{

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//����д�����
	IWDG_SetPrescaler(IWDG_Prescaler_256);//Ԥ��Ƶ����Ϊ256
	IWDG_SetReload(800);//tout=4*256/40*800=20480
	IWDG_ReloadCounter(); //��װ�س�ֵ
	IWDG_Enable(); // �򿪶������Ź�


}