#include <tone.h>
#include <stm32f10x_gpio.h>
//do音调
	//低do ，262hz ，3816us
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

	//中do ，523hz ，1912us
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

	//高do 1047hz 955us
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



//re音调
//低re 294hz，3401us
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

//中re， 587hz ，1703us
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
//高re 1175hz，851us
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


//mi音调
//低mi，330hz，3030us
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


//中mi ，659hz，1517us
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

//高mi 1319hz，758us
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


//fa音
//低fa 349hz，2865us
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


//中fa，698hz，1432hz
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

//高fa ，1397hz，751us
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


//so音调
//低so 392hz，2551us
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


//中so，784hz，1275us
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

//高so 1568hz，637us
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



//la音调
//低la 440hz，2272us
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


//中la，880hz，1136us
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

//高la 1760hz，568us
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

//si音调
//低si 494hz，2024us
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

//中si，988hz，1012us
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

//高si 1967hz,508us
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
