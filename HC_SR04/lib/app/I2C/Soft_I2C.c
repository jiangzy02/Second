#include <Soft_I2C.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>

/*
PB10 和 PB11 模拟 I2C
*/
void I2C_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1|RCC_APB1Periph_I2C2,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
	
		GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);//初始时置为高
}

//将SDA引脚配置为输出模式
void SDA_OUT(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void SDA_IN(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void I2C_Start(void)
{
		SDA_OUT();
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//将SCL置为高电平
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//将SDA置为高电平
		delay_us(6);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);//将SDA置为低电平
		delay_us(6);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平，用于数据的改变
}

void I2C_End(void)
{
		SDA_OUT();
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);//将SDA置为低电平
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//将SCL置为高电平
		delay_us(6);
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//将SDA置为高电平
		delay_us(6);
}

void I2C_Ack(void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平
		SDA_OUT();
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);//将SDA置为低电平
		delay_us(2);
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//将SCL置为高电平
		delay_us(5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平
}

void I2C_NAck(void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平
		SDA_OUT();
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//将SDA置为高电平
		delay_us(2);
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//将SCL置为高电平
		delay_us(5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平
}

u8 I2C_Wait_Ack(void)
{
		u8 tempTime=0;
		SDA_IN(); //SDA 设置为输入
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//将SDA置为高电平
		delay_us(1);

		GPIO_SetBits(GPIOB,GPIO_Pin_10);//将SCL置为高电平
		delay_us(1);
	
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==SET)
				{
					tempTime++;
						if(tempTime>250)
							{
							I2C_End();
							return 1;
							}
				}
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平
		return 0;		
}
/*******************************************************************************
* 函 数 名 : IIC_Send_Byte
* 函数功能 : IIC 发送一个字节
* 输 入 : txd： 发送一个字节
* 输 出 : 无
*******************************************************************************/
void I2C_Send_Byte(u8 txd)
{
		u8 t;
		SDA_OUT();
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平,拉低时钟开始数据传输
		for(t=0;t<8;t++)
			{
				if((txd&0x80)>0) //0x80 1000 0000
							GPIO_SetBits(GPIOB,GPIO_Pin_11);//将SDA置为高电平
				else  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//将SDA置为低电平
				
				txd<<=1;
					
				delay_us(2); //对 TEA5767 这三个延时都是必须的
				GPIO_SetBits(GPIOB,GPIO_Pin_10);//将SCL置为高电平
				delay_us(2);
				GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平
				delay_us(2);				
			}
}

/******************************************************************************
* 函 数 名 : IIC_Read_Byte
* 函数功能 : IIC 读一个字节
* 输 入 : ack=1 时， 发送 ACK， ack=0， 发送 nACK
* 输 出 : 应答或非应答
*******************************************************************************/
u8 I2C_Read_Byte(u8 ack)
{
		u8 i,receive=0;
		SDA_IN();//SDA 设置为输入	
		for(i=0;i<8;i++ )
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_10);//将SCL置为低电平
				delay_us(2);
				GPIO_SetBits(GPIOB,GPIO_Pin_10);//将SCL置为高电平
				receive<<=1;
				if( (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))==SET)
				receive++;
				delay_us(1);
			}
			if (!ack)
			I2C_NAck();//发送 nACK
			else
			I2C_Ack(); //发送 ACK
			
		return receive;	
}





















