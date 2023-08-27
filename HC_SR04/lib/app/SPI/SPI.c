#include <SPI.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <stm32f10x_spi.h>

void SPI1_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	/* SPI的IO口和SPI外设打开时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* SPI的IO口设置 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
	SPI1_ReadWriteByte(0xff);//启动传输	
}


//SPI1速度设置函数
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	SPI1->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI1->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE); //使能SPI1
} 


//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{		 			 
 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);//等待发送区空  
	
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个byte  数据
		
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据	
 		    
}

void SPI2_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		SPI_InitTypeDef SPI_InitStructure;
	
	
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 |GPIO_Pin_15;//SPI2_SCK,SPI2_MISO,SPI2_MOSI
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//双线 全双 工
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;// SPI 工作在主机模式
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;// SPI 通 信 的 数 据 帧 长 度 
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//串行同步时钟的空闲状态为高电平
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//串行同步时钟的第二个跳变沿（上升或下降） 数据被采样
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//设 置 NSS 引 脚 的 使 用 模 式软件模式
		SPI_InitStructure.SPI_BaudRatePrescaler =SPI_BaudRatePrescaler_256;//传输速度为 36M/256=140.625KHz。
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//设置数据传输顺序是 MSB 位在前
		SPI_InitStructure.SPI_CRCPolynomial = 7;//用于设置 CRC 校验多项式
		SPI_Init(SPI2, &SPI_InitStructure);
		
		SPI_Cmd(SPI2, ENABLE); //使能 SPI 外设

		
}

//SPI2 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData)
{		 			 
 
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);//等待发送区空  
	
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个byte  数据
		
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据	
 		    
}


void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
SPI2->CR1&=0XFFC7;//位 3-5 清零， 用来设置波特率
SPI2->CR1|=SPI_BaudRatePrescaler; //设置 SPI 速度
SPI_Cmd(SPI2,ENABLE); //使能 SPI2
}







