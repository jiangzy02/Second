#include <lcd_wave.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_dac.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <stm32f10x_tim.h>
#include <tftlcd.h>

u16 ydata=80;
u16 xdata=240;
void lcd_wave(float value)
{
	
	xdata=xdata-1;//xÏò×óÒÆÒ»¸ö
	if(xdata==0)
	{
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
	}
	}
	
	if(value>=0.00 && value < 0.05)
	{
	 LCD_DrawPoint(xdata,80);
	}
	
	else if(value>=0.05 && value < 0.10)
	{
	 LCD_DrawPoint(xdata,79);
	}
	
	else if(value>=0.10 && value < 0.15)
	{
	 LCD_DrawPoint(xdata,78);
	}
	else if(value>=0.15 && value < 0.20)
	{
	 LCD_DrawPoint(xdata,77);
	}
	else if(value>=0.20 && value < 0.25)
	{
	 LCD_DrawPoint(xdata,76);
	}
	else if(value>=0.25 && value < 0.30)
	{
	 LCD_DrawPoint(xdata,75);
	}
	else if(value>=0.30 && value < 0.35)
	{
	 LCD_DrawPoint(xdata,74);
	}
	else if(value>=0.35 && value < 0.40)
	{
	 LCD_DrawPoint(xdata,73);
	}
	else if(value>=0.40 && value < 0.45)
	{
	 LCD_DrawPoint(xdata,72);
	}
	else if(value>=0.50 && value < 0.55)
	{
	 LCD_DrawPoint(xdata,71);
	}
	
	else if(value>=0.55 && value < 0.60)
	{
	 LCD_DrawPoint(xdata,70);
	}
	else if(value>=0.60 && value < 0.65)
	{
	 LCD_DrawPoint(xdata,69);
	}
	else if(value>=0.65 && value < 0.70)
	{
	 LCD_DrawPoint(xdata,68);
	}
	else if(value>=0.70 && value < 0.75)
	{
	 LCD_DrawPoint(xdata,67);
	}
	else if(value>=0.75 && value < 0.80)
	{
	 LCD_DrawPoint(xdata,66);
	}
	else if(value>=0.80 && value < 0.85)
	{
	 LCD_DrawPoint(xdata,65);
	}
	else if(value>=0.85 && value < 0.90)
	{
	 LCD_DrawPoint(xdata,64);
	}
	else if(value>=0.90 && value < 0.95)
	{
	 LCD_DrawPoint(xdata,63);
	}
	else if(value>=0.95&& value < 1.00)
	{
	 LCD_DrawPoint(xdata,62);
	}
	
	else if(value>=1.00 && value < 1.05)
	{
	 LCD_DrawPoint(xdata,61);
	}
	else if(value>=1.05 && value < 1.10)
	{
	 LCD_DrawPoint(xdata,60);
	}
	else if(value>=1.10 && value < 1.15)
	{
	 LCD_DrawPoint(xdata,59);
	}
	else if(value>=1.15 && value < 1.20)
	{
	 LCD_DrawPoint(xdata,58);
	}
	else if(value>=1.20 && value < 1.25)
	{
	 LCD_DrawPoint(xdata,57);
	}
	else if(value>=1.25 && value < 1.30)
	{
	 LCD_DrawPoint(xdata,56);
	}
	else if(value>=1.30 && value < 1.35)
	{
	 LCD_DrawPoint(xdata,55);
	}
	else if(value>=1.35 && value < 1.40)
	{
	 LCD_DrawPoint(xdata,54);
	}
	else if(value>=1.40 && value < 1.45)
	{
	 LCD_DrawPoint(xdata,53);
	}
	else if(value>=1.45 && value < 1.50)
	{
	 LCD_DrawPoint(xdata,52);
	}
	else if(value>=1.50&& value < 1.55)
	{
	 LCD_DrawPoint(xdata,51);
	}
	else if(value>=1.55&& value <1.60)
	{
	 LCD_DrawPoint(xdata,50);
	}
	else if(value>=1.60 && value < 1.65)
	{
	 LCD_DrawPoint(xdata,49);
	}
	else if(value>= 1.65&& value < 1.70)
	{
	 LCD_DrawPoint(xdata,48);
	}
	else if(value>=1.70 && value < 1.75)
	{
	 LCD_DrawPoint(xdata,47);
	}
		else if(value>=1.75 && value < 1.80)
	{
	 LCD_DrawPoint(xdata,46);
	}
	else if(value>=1.80 && value < 1.85)
	{
	 LCD_DrawPoint(xdata,45);
	}
	else if(value>=1.85 && value < 1.90)
	{
	 LCD_DrawPoint(xdata,44);
	}
	else if(value>=1.90 && value <1.95)
	{
	 LCD_DrawPoint(xdata,43);
	}
	else if(value>=1.95&& value < 2.00)
	{
	 LCD_DrawPoint(xdata,42);
	}
	
	
	else if(value>=2.00 && value < 2.05)
	{
	 LCD_DrawPoint(xdata,41);
	}
	else if(value>=2.05 && value < 2.10)
	{
	 LCD_DrawPoint(xdata,40);
	}
	else if(value>=2.10 && value < 2.15)
	{
	 LCD_DrawPoint(xdata,39);
	}
	else if(value>=2.15 && value < 2.20)
	{
	 LCD_DrawPoint(xdata,38);
	}
	else if(value>=2.20 && value < 2.25)
	{
	 LCD_DrawPoint(xdata,37);
	}
	else if(value>=2.25 && value < 2.30)
	{
	 LCD_DrawPoint(xdata,36);
	}
	else if(value>=2.30 && value < 2.35)
	{
	 LCD_DrawPoint(xdata,35);
	}
	else if(value>=2.35 && value < 2.40)
	{
	 LCD_DrawPoint(xdata,34);
	}
	else if(value>=2.40 && value < 2.45)
	{
	 LCD_DrawPoint(xdata,33);
	}
	else if(value>=2.45 && value < 2.50)
	{
	 LCD_DrawPoint(xdata,32);
	}
	else if(value>=2.50&& value < 2.55)
	{
	 LCD_DrawPoint(xdata,31);
	}
	else if(value>=2.55&& value <2.60)
	{
	 LCD_DrawPoint(xdata,30);
	}
	else if(value>=2.60 && value < 2.65)
	{
	 LCD_DrawPoint(xdata,29);
	}
	else if(value>= 2.65&& value < 2.70)
	{
	 LCD_DrawPoint(xdata,28);
	}
	else if(value>=2.70 && value < 2.75)
	{
	 LCD_DrawPoint(xdata,27);
	}
		else if(value>=2.75 && value < 2.80)
	{
	 LCD_DrawPoint(xdata,26);
	}
	else if(value>=2.80 && value < 2.85)
	{
	 LCD_DrawPoint(xdata,25);
	}
	else if(value>=2.85 && value < 2.90)
	{
	 LCD_DrawPoint(xdata,24);
	}
	else if(value>=2.90 && value <2.95)
	{
	 LCD_DrawPoint(xdata,23);
	}
	else if(value>=2.95&& value < 3.00)
	{
	 LCD_DrawPoint(xdata,22);
	}
	
	else if(value>=3.00 && value < 3.05)
	{
	 LCD_DrawPoint(xdata,21);
	}
	else if(value>=3.05 && value < 3.10)
	{
	 LCD_DrawPoint(xdata,20);
	}
	else if(value>=3.10 && value < 3.15)
	{
	 LCD_DrawPoint(xdata,19);
	}
	else if(value>=3.15 && value < 3.20)
	{
	 LCD_DrawPoint(xdata,18);
	}
	else if(value>=3.20 && value < 3.25)
	{
	 LCD_DrawPoint(xdata,17);
	}
	else if(value>=3.25 && value < 3.30)
	{
	 LCD_DrawPoint(xdata,16);
	}
}



