#ifndef _tftlcd_H
#define _tftlcd_H	
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <stdint.h>
#include <stdio.h>
//定义LCD彩屏的驱动类型  可根据自己手上的彩屏背面型号来选择打开哪种驱动
#define TFTLCD_ILI9325


#define TFTLCD_DIR	0	//0：竖屏  1：横屏  默认竖屏

//TFTLCD地址结构体
typedef struct
{
	u16 LCD_CMD;
	u16 LCD_DATA;
}TFTLCD_TypeDef;


//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线 
//注意设置16位总线时STM32内部会右移一位对齐!			    
#define TFTLCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define TFTLCD             ((TFTLCD_TypeDef *) TFTLCD_BASE)
  
//TFTLCD重要参数集
typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;            //LCD 方向
}_tftlcd_data;


//LCD参数
extern _tftlcd_data tftlcd_data;	//管理LCD重要参数
//LCD的前端颜色和背景色	   
extern u16  FRONT_COLOR;//前端颜色 默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色



void LCD_WriteCmd(u16 cmd);
void LCD_WriteData(u16 data);
void LCD_WriteCmdData(u16 cmd,u16 data);
void LCD_WriteData_Color(u16 color);

void TFTLCD_Init(void);           //初始化
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);
void LCD_Clear(u16 Color);	 												//清屏
void LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color);
void LCD_DrawPoint(u16 x,u16 y);//画点
void LCD_DrawFRONT_COLOR(u16 x,u16 y,u16 color);
u16 LCD_ReadPoint(u16 x,u16 y);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn);					   						   																			
void LCD_ShowPicture(u16 x, u16 y, u16 wide, u16 high,u8 *pic);

#endif  


/*

主函数模板


*/

//int main(void)
//{
//	u16 color=0;
//	
//	
//	RCC_Configuration();
//	GPIO_Configuration();
//	USART1_Configuration();
//	GPIO_ResetBits(GPIOC,GPIO_Pin_4);//测试4
//	TFTLCD_Init();			//LCD初始化
//	GPIO_ResetBits(GPIOC,GPIO_Pin_5);//测试4
////	GPIO_ResetBits(GPIOC,GPIO_Pin_4);//测试2
//	FRONT_COLOR=RED;
//	
//	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,12,"Do you know?");
////	GPIO_ResetBits(GPIOC,GPIO_Pin_7);//测试2
//	LCD_ShowString(10,30,tftlcd_data.width,tftlcd_data.height,16,"hahahha!");
//	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,24,"Hello World!");
//	LCD_ShowFontHZ(10, 80,"祁文林");
//	LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,24,"www.prechin.cn");

//	//	GPIO_ResetBits(GPIOC,GPIO_Pin_5);//测试2
//	LCD_Fill(10,150,60,180,BLUE);
//	color=LCD_ReadPoint(20,160);
//	//LCD_Fill(25,180,45,220,GREEN);
//	printf("color=%x\r\n",color);

////	GPIO_ResetBits(GPIOC,GPIO_Pin_6);//测试2
//	LCD_ShowPicture(20,220,200,112,(u8 *)gImage_picture);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_6);//测试4
//	while(1)
//	{
//		GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);
//		delay_ms(100);
//		GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);
//		delay_ms(100);
//	}
//	 



