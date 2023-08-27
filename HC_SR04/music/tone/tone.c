#include <tone.h>
#include <stm32f10x_gpio.h>
//do����
	//��do ��262hz ��3816us
void low_do(void)
{
	u16 i;
	
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(3816);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(3816);
	}
	
}

	//��do ��523hz ��1912us
void middle_do(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(1912);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(1912);
	}
	
}

	//��do 1047hz 955us
void high_do(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(955);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(955);
	}
}



//re����
//��re 294hz��3401us
void low_re(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(3401);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(3401);
	}
}

//��re�� 587hz ��1703us
void middle_re(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(1703);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(1703);
	}
}
//��re 1175hz��851us
void high_re(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(851);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(851);
	}
}


//mi����
//��mi��330hz��3030us
void low_mi(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(3030);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(3030);
	}

}


//��mi ��659hz��1517us
void middle_mi(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(1517);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(1517);
	}

}

//��mi 1319hz��758us
void high_mi(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(758);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(758);
	}

}


//fa��
//��fa 349hz��2865us
void low_fa(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(2865);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(2865);
	}

}


//��fa��698hz��1432hz
void middle_fa(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(1432);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(1432);
	}
}

//��fa ��1397hz��751us
void high_fa(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(751);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(751);
	}

}


//so����
//��so 392hz��2551us
void low_so(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(2551);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(2551);
	}

}


//��so��784hz��1275us
void middle_so(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(1275);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(1275);
	}
}

//��so 1568hz��637us
void high_so(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(637);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(637);
	}

}



//la����
//��la 440hz��2272us
void low_la(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(2272);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(2272);
	}
}


//��la��880hz��1136us
void middle_la(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(1136);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(1136);
	}
}

//��la 1760hz��568us
void high_la(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(568);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(568);
	}
}

//si����
//��si 494hz��2024us
void low_si(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(2024);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(2024);
	}
}

//��si��988hz��1012us
void middle_si(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(1012);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(1012);
	}

}

//��si 1967hz,508us
void high_si(void)
{
	u16 i;
	for(i=0;i<30;i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		delay_us(508);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		delay_us(508);
	}
}
