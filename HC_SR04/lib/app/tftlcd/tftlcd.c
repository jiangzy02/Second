#include "tftlcd.h"
#include "stdlib.h"
#include "font.h" 
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_fsmc.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <stdio.h>
#include <stdint.h>
#include <USART1_Configuration.h>


//LCD�Ļ�����ɫ�ͱ���ɫ	
u16 FRONT_COLOR=BLACK;	//������ɫ
u16 BACK_COLOR=WHITE;  //����ɫ 

_tftlcd_data tftlcd_data; 
TFTLCD_TypeDef TFTLCD_TypeDefe;

void TFTLCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
//	GPIO_ResetBits(GPIOC,GPIO_Pin_2);//����3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG,ENABLE);//ʹ��PORTD,E,Gʱ��
	
 	//PORTD�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
  	 
	//PORTE�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);    	    	 											 

   	//	//PORTG12����������� A10	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTG�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);  
	
}

void TFTLCD_FSMC_Init(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  FSMC_ReadTimingInitStructure; 
	FSMC_NORSRAMTimingInitTypeDef  FSMC_WriteTimingInitStructure;
	
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//ʹ��FSMCʱ��
//	GPIO_ResetBits(GPIOC,GPIO_Pin_3);//����4

	FSMC_ReadTimingInitStructure.FSMC_AddressSetupTime = 0x01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
  	FSMC_ReadTimingInitStructure.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
  	FSMC_ReadTimingInitStructure.FSMC_DataSetupTime = 0x0f;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
  	FSMC_ReadTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_ReadTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
    

		FSMC_WriteTimingInitStructure.FSMC_AddressSetupTime = 0x00;	 //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  
  	FSMC_WriteTimingInitStructure.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ��		
  	FSMC_WriteTimingInitStructure.FSMC_DataSetupTime = 0x03;		 //���ݱ���ʱ��Ϊ4��HCLK	
  	FSMC_WriteTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_CLKDivision = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_DataLatency = 0x00;
  	FSMC_WriteTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 



 
  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ���Ϊ16bit   
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsyncWait=FSMC_AsyncWait_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_ReadTimingInitStructure; //��дʱ��
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_WriteTimingInitStructure;  //дʱ��

  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����

 	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // ʹ��BANK1 
	
}
	 
//д�Ĵ�������
//cmd:�Ĵ���ֵ
void LCD_WriteCmd(u16 cmd)
{
#ifdef TFTLCD_ILI9325
	TFTLCD->LCD_CMD=cmd;
#endif
}

//д����
//data:Ҫд���ֵ
void LCD_WriteData(u16 data)
{
#ifdef TFTLCD_ILI9325
	TFTLCD->LCD_DATA=data;
#endif
}

void LCD_WriteCmdData(u16 cmd,u16 data)
{
	LCD_WriteCmd(cmd);
	LCD_WriteData(data);
}


void LCD_WriteData_Color(u16 color)
{
#ifdef TFTLCD_ILI9325
			TFTLCD->LCD_DATA=color;
#endif
}

//������
//����ֵ:������ֵ
u16 LCD_ReadData(void)
{
#ifdef TFTLCD_ILI9325		
	return TFTLCD->LCD_DATA;	
#endif
}


//����LCD��ʾ����
//dir:0,������1,����
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)  //Ĭ����������
	{		
#ifdef TFTLCD_ILI9325
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0100);
		LCD_WriteCmd(0x0003);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x1030);  
		tftlcd_data.height=320;
		tftlcd_data.width=240;			
#endif
		tftlcd_data.dir=0;
		
	}
	else
	{	
#ifdef TFTLCD_ILI9325
		LCD_WriteCmd(0x0001);   
		LCD_WriteData(0x0000);
		LCD_WriteCmd(0x0003);   //���ò�����ʾ����ļĴ���
		LCD_WriteData(0x1038);  
		tftlcd_data.height=240;
		tftlcd_data.width=320;			
#endif
		tftlcd_data.dir=1;
	}	
}





void TFTLCD_Init(void)
{
	u16 i;
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);//����1
	TFTLCD_GPIO_Init();
	TFTLCD_FSMC_Init();
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);//����2
	delay_ms(50); 
	
#ifdef TFTLCD_ILI9325
	LCD_WriteCmd(0x00);	
	tftlcd_data.id=TFTLCD_TypeDefe.LCD_DATA;			
#endif
 	printf(" LCD ID:%x\r\n",tftlcd_data.id); //��ӡLCD ID
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);//����3
	
#ifdef TFTLCD_ILI9325
	LCD_WriteCmd(0x00E3);LCD_WriteData(0x3008); // Set internal timing
	LCD_WriteCmd(0x00E7);LCD_WriteData(0x0012); // Set internal timing
	LCD_WriteCmd(0x00EF);LCD_WriteData(0x1231); // Set internal timing
	LCD_WriteCmd(0x0001);LCD_WriteData(0x0100); // set SS and SM bit
	LCD_WriteCmd(0x0002);LCD_WriteData(0x0700); // set 1 line inversion
	LCD_WriteCmd(0x0003);LCD_WriteData(0x1030); // set GRAM write direction and BGR=1.
	LCD_WriteCmd(0x0004);LCD_WriteData(0x0000); // Resize register
	LCD_WriteCmd(0x0008);LCD_WriteData(0x0207); // set the back porch and front porch
	LCD_WriteCmd(0x0009);LCD_WriteData(0x0000); // set non-display area refresh cycle ISC[3:0]
	LCD_WriteCmd(0x000A);LCD_WriteData(0x0000); // FMARK function
	LCD_WriteCmd(0x000C);LCD_WriteData(0x0000); // RGB interface setting
	LCD_WriteCmd(0x000D);LCD_WriteData(0x0000); // Frame marker Position
	LCD_WriteCmd(0x000F);LCD_WriteData(0x0000); // RGB interface polarity
	//*************Power On sequence ****************//
	LCD_WriteCmd(0x0010);LCD_WriteData(0x0000); // SAP);WriteData(BT[3:0]);WriteData(AP);WriteData(DSTB);WriteData(SLP);WriteData(STB
	LCD_WriteCmd(0x0011);LCD_WriteData(0x0007); // DC1[2:0]);WriteData(DC0[2:0]);WriteData(VC[2:0]
	LCD_WriteCmd(0x0012);LCD_WriteData(0x0000); // VREG1OUT voltage
	LCD_WriteCmd(0x0013);LCD_WriteData(0x0000); // VDV[4:0] for VCOM amplitude
	delay_ms(20); // Dis-charge capacitor power voltage
	LCD_WriteCmd(0x0010);LCD_WriteData(0x1490); // SAP);WriteData(BT[3:0]);WriteData(AP);WriteData(DSTB);WriteData(SLP);WriteData(STB
	LCD_WriteCmd(0x0011);LCD_WriteData(0x0227); // DC1[2:0]);WriteData(DC0[2:0]);WriteData(VC[2:0]
	delay_ms(50); // Delay 50ms
	LCD_WriteCmd(0x0012);LCD_WriteData(0x001C); // Internal reference voltage= Vci;
	delay_ms(50); // Delay 50ms
	LCD_WriteCmd(0x0013);LCD_WriteData(0x1A00); // Set VDV[4:0] for VCOM amplitude
	LCD_WriteCmd(0x0029);LCD_WriteData(0x0025); // Set VCM[5:0] for VCOMH
	LCD_WriteCmd(0x002B);LCD_WriteData(0x000C); // Set Frame Rate
	delay_ms(50); // Delay 50ms
	LCD_WriteCmd(0x0020);LCD_WriteData(0x0000); // GRAM horizontal Address
	LCD_WriteCmd(0x0021);LCD_WriteData(0x0000); // GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WriteCmd(0x0030);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0031);LCD_WriteData(0x0506);
	LCD_WriteCmd(0x0032);LCD_WriteData(0x0104);
	LCD_WriteCmd(0x0035);LCD_WriteData(0x0207);
	LCD_WriteCmd(0x0036);LCD_WriteData(0x000F);
	LCD_WriteCmd(0x0037);LCD_WriteData(0x0306);
	LCD_WriteCmd(0x0038);LCD_WriteData(0x0102);
	LCD_WriteCmd(0x0039);LCD_WriteData(0x0707);
	LCD_WriteCmd(0x003C);LCD_WriteData(0x0702);
	LCD_WriteCmd(0x003D);LCD_WriteData(0x1604);
	//------------------ Set GRAM area ---------------//
	LCD_WriteCmd(0x0050);LCD_WriteData(0x0000); // Horizontal GRAM Start Address
	LCD_WriteCmd(0x0051);LCD_WriteData(0x00EF); // Horizontal GRAM End Address
	LCD_WriteCmd(0x0052);LCD_WriteData(0x0000); // Vertical GRAM Start Address
	LCD_WriteCmd(0x0053);LCD_WriteData(0x013F); // Vertical GRAM Start Address
	LCD_WriteCmd(0x0060);LCD_WriteData(0x2700); // Gate Scan Line
	LCD_WriteCmd(0x0061);LCD_WriteData(0x0001); // NDL,VLE);WriteData(REV
	LCD_WriteCmd(0x006A);LCD_WriteData(0x0000); // set scrolling line
	//-------------- Partial Display Control ---------//
	LCD_WriteCmd(0x0080);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0081);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0082);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0083);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0084);LCD_WriteData(0x0000);
	LCD_WriteCmd(0x0085);LCD_WriteData(0x0000);
	//------------ Panel Control -------------------//
	LCD_WriteCmd(0x0090);LCD_WriteData(0x0010);
	LCD_WriteCmd(0x0092);LCD_WriteData(0x0600);
	LCD_WriteCmd(0x0007);LCD_WriteData(0x0133); // 262K color and display ON

	LCD_WriteCmd(0x0010);LCD_WriteData(0x12B0); // SAP);WriteData(BT[3:0]);WriteData(AP);WriteData(DSTB);WriteData(SLP
	LCD_WriteCmd(0x0011);LCD_WriteData(0x0007);
	LCD_WriteCmd(0x0017);LCD_WriteData(0x0001); // DC1[2:0]);WriteData(DC0[2:0]);WriteData(VC[2:0]
	LCD_WriteCmd(0x0012);LCD_WriteData(0x01BD); // VREG1OUT voltage
	LCD_WriteCmd(0x0013);LCD_WriteData(0x1700); // VDV[4:0] for VCOM amplitude
	delay_ms(20); // Dis-charge capacitor power voltage
	LCD_WriteCmd(0x0010);LCD_WriteData(0x1490); // SAP);WriteData(BT[3:0]);WriteData(AP);WriteData(DSTB);WriteData(SLP);WriteData(STB
	LCD_WriteCmd(0x0011);LCD_WriteData(0x0227); // DC1[2:0]);WriteData(DC0[2:0]);WriteData(VC[2:0]
	delay_ms(50); // Delay 50ms
	LCD_WriteCmd(0x0012);LCD_WriteData(0x001C); //Inernal reference voltage =Vci;
	delay_ms(50); // Delay 50ms
	LCD_WriteCmd(0x0013);LCD_WriteData(0x1A00); // VDV[4:0] for VCOM amplitude
	LCD_WriteCmd(0x0029);LCD_WriteData(0x0025); // VCM[5:0] for VCOMH
	delay_ms(50); // Delay 50ms
	//LCD_WriteCmd(0x0007);LCD_WriteData(0x0133); // 262K color and display ON

	LCD_WriteCmd(0x0007);LCD_WriteData(0x0133);
	delay_ms(120);
	LCD_WriteCmd(0x0022);

#endif

	LCD_Display_Dir(TFTLCD_DIR);		//0������  1������  Ĭ������
	LCD_Clear(WHITE);
}

//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ��Ⱥ͸߶�,�������0!!
//�����С:width*height. 
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{    
#ifdef TFTLCD_ILI9325
	if(tftlcd_data.dir==0)//�������Ϊ����
	{
		LCD_WriteCmd(0x0050);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0051);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0052);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0053);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0020);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0021);   
	    LCD_WriteData(sy);	
	}   	
	else
	{
		LCD_WriteCmd(0x0052);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0053);  
	    LCD_WriteData(width);
		LCD_WriteCmd(0x0050);   
	    LCD_WriteData(sy);
		LCD_WriteCmd(0x0051);   
	    LCD_WriteData(height);
	
		LCD_WriteCmd(0x0021);   
	    LCD_WriteData(sx);
		LCD_WriteCmd(0x0020);   
	    LCD_WriteData(sy);	
	}
	LCD_WriteCmd(0x0022);
#endif
}

//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	uint16_t i, j ;

	LCD_Set_Window(0, 0, tftlcd_data.width-1, tftlcd_data.height-1);	 //��������
  	for(i=0; i<tftlcd_data.width; i++)
	{
		for (j=0; j<tftlcd_data.height; j++)
		{
			LCD_WriteData_Color(color);
		}
	} 
}


//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 xState,u16 yState,u16 xEnd,u16 yEnd,u16 color)
{          
	uint16_t temp;

    if((xState > xEnd) || (yState > yEnd))
    {
        return;
    }   
	LCD_Set_Window(xState, yState, xEnd, yEnd); 
    xState = xEnd - xState + 1;
	yState = yEnd - yState + 1;

	while(xState--)
	{
	 	temp = yState;
		while (temp--)
	 	{			
			LCD_WriteData_Color(color);	
		}
	}	
} 

//����
//x,y:����
//FRONT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_Set_Window(x, y, x, y);  //���õ��λ��
	LCD_WriteData_Color(FRONT_COLOR);	
}

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_DrawFRONT_COLOR(u16 x,u16 y,u16 color)
{	   
	LCD_Set_Window(x, y, x, y);
	LCD_WriteData_Color(color);	
} 

//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	u16 r1,r2,r3;
	
	if(x>=tftlcd_data.width||y>=tftlcd_data.height)return 0;	//�����˷�Χ,ֱ�ӷ���		     
	LCD_Set_Window(x, y, x, y);
	
#ifdef TFTLCD_ILI9325
	LCD_WriteCmd(0x0022);
	r=LCD_ReadData();//dummy Read     		 				    
	r=LCD_ReadData();//ʵ��������ɫ
	r1=r&0xf800;
	r2=r&0x07e0;
	r3=r&0x001f;
	return (r3<<11)|((r2>>5)<<5)|(r1>>11);
#endif
	
 	return r;						
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

void LCD_DrawLine_Color(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawFRONT_COLOR(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 


// ��һ��ʮ�ֵı��
// x����ǵ�X����
// y����ǵ�Y����
// color����ǵ���ɫ
void LCD_DrowSign(uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;

    /* ���� */
    LCD_Set_Window(x-1, y-1, x+1, y+1);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color);   
    }

    /* ���� */
    LCD_Set_Window(x-4, y, x+4, y);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }

    /* ���� */
    LCD_Set_Window(x, y-4, x, y+4);
    for(i=0; i<9; i++)
    {
		LCD_WriteData_Color(color); 
    }
}

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 



//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=ascii_1608[num][t];	//����1608����
		else if(size==24)temp=ascii_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
			else if(mode==0)LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=tftlcd_data.height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=tftlcd_data.width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
//	printf(" width:%x\r\n",width); //��ӡLCD ID
//	printf(" height:%x\r\n",height); //��ӡLCD ID
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}

/****************************************************************************
*��������LCD_ShowFontHZ
*��  �룺x��������ʾ��X����
*      * y��������ʾ��Y����
*      * cn��Ҫ��ʾ�ĺ���
*      * wordColor�����ֵ���ɫ
*      * backColor��������ɫ
*��  ����
*��  �ܣ�д���ſ��庺��
****************************************************************************/
#if 0
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)	 
{  
	u8 i, j, wordNum;
	u16 color;
	while (*cn != '\0')
	{
		LCD_Set_Window(x, y, x+31, y+28);
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_WriteData_Color(FRONT_COLOR); 						
						} 						
						else
						{
							LCD_WriteData_Color(BACK_COLOR); 
						} 
						color<<=1;
					}//for(j=0;j<8;j++)����
				}    
			}
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
	}
}
#endif


#if 1
void LCD_ShowFontHZ(u16 x, u16 y, u8 *cn)
{
	u8 i, j, wordNum;
	u16 color;
	u16 x0=x; 
	u16 y0=y; 
	while (*cn != '\0')
	{
		for (wordNum=0; wordNum<20; wordNum++)
		{	//wordNumɨ���ֿ������
			if ((CnChar32x29[wordNum].Index[0]==*cn)
			     &&(CnChar32x29[wordNum].Index[1]==*(cn+1)))
			{
				for(i=0; i<116; i++) 
				{	//MSK��λ��
					color=CnChar32x29[wordNum].Msk[i];
					for(j=0;j<8;j++) 
					{
						if((color&0x80)==0x80)
						{
							LCD_DrawFRONT_COLOR(x,y,FRONT_COLOR);
						} 						
						else
						{
							LCD_DrawFRONT_COLOR(x,y,BACK_COLOR);
						} 
						color<<=1;
						x++;
						if((x-x0)==32)
						{
							x=x0;
							y++;
							if((y-y0)==29)
							{
								y=y0;
							}
						}
					}//for(j=0;j<8;j++)����
				}	
			}
			
		} //for (wordNum=0; wordNum<20; wordNum++)���� 	
		cn += 2;
		x += 32;
		x0=x;
	}
}	
#endif

void LCD_ShowPicture(u16 x, u16 y, u16 wide, u16 high,u8 *pic)
{
	u16 temp = 0;
	long tmp=0,num=0;
	LCD_Set_Window(x, y, x+wide-1, y+high-1);
	num = wide * high*2 ;
	do
	{  
		temp = pic[tmp + 1];
		temp = temp << 8;
		temp = temp | pic[tmp];
		
		LCD_WriteData_Color(temp);//�����ʾ
		tmp += 2;
	}
	while(tmp < num);	
}