#include <Soft_I2C.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>

/*
PB10 �� PB11 ģ�� I2C
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
	
		GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);//��ʼʱ��Ϊ��
}

//��SDA��������Ϊ���ģʽ
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
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�ߵ�ƽ
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�ߵ�ƽ
		delay_us(6);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�͵�ƽ
		delay_us(6);
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ���������ݵĸı�
}

void I2C_End(void)
{
		SDA_OUT();
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�͵�ƽ
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�ߵ�ƽ
		delay_us(6);
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�ߵ�ƽ
		delay_us(6);
}

void I2C_Ack(void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ
		SDA_OUT();
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�͵�ƽ
		delay_us(2);
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�ߵ�ƽ
		delay_us(5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ
}

void I2C_NAck(void)
{
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ
		SDA_OUT();
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�ߵ�ƽ
		delay_us(2);
		GPIO_SetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�ߵ�ƽ
		delay_us(5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ
}

u8 I2C_Wait_Ack(void)
{
		u8 tempTime=0;
		SDA_IN(); //SDA ����Ϊ����
		GPIO_SetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�ߵ�ƽ
		delay_us(1);

		GPIO_SetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�ߵ�ƽ
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
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ
		return 0;		
}
/*******************************************************************************
* �� �� �� : IIC_Send_Byte
* �������� : IIC ����һ���ֽ�
* �� �� : txd�� ����һ���ֽ�
* �� �� : ��
*******************************************************************************/
void I2C_Send_Byte(u8 txd)
{
		u8 t;
		SDA_OUT();
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ,����ʱ�ӿ�ʼ���ݴ���
		for(t=0;t<8;t++)
			{
				if((txd&0x80)>0) //0x80 1000 0000
							GPIO_SetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�ߵ�ƽ
				else  GPIO_ResetBits(GPIOB,GPIO_Pin_11);//��SDA��Ϊ�͵�ƽ
				
				txd<<=1;
					
				delay_us(2); //�� TEA5767 ��������ʱ���Ǳ����
				GPIO_SetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�ߵ�ƽ
				delay_us(2);
				GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ
				delay_us(2);				
			}
}

/******************************************************************************
* �� �� �� : IIC_Read_Byte
* �������� : IIC ��һ���ֽ�
* �� �� : ack=1 ʱ�� ���� ACK�� ack=0�� ���� nACK
* �� �� : Ӧ����Ӧ��
*******************************************************************************/
u8 I2C_Read_Byte(u8 ack)
{
		u8 i,receive=0;
		SDA_IN();//SDA ����Ϊ����	
		for(i=0;i<8;i++ )
			{
				GPIO_ResetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�͵�ƽ
				delay_us(2);
				GPIO_SetBits(GPIOB,GPIO_Pin_10);//��SCL��Ϊ�ߵ�ƽ
				receive<<=1;
				if( (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))==SET)
				receive++;
				delay_us(1);
			}
			if (!ack)
			I2C_NAck();//���� nACK
			else
			I2C_Ack(); //���� ACK
			
		return receive;	
}





















