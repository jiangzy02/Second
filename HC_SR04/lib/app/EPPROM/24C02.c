#include <24C02.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_dac.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <Soft_I2C.h>


void	AT24C02_Init(void)
{
		I2C_Configuration();
}


/*******************************************************************************
* �� �� ��         : AT24CXX_ReadOneByte
* ��������		   : ��AT24CXXָ����ַ����һ������
* ��    ��         : ReadAddr:��ʼ�����ĵ�ַ 
* ��    ��         : ����������
*******************************************************************************/
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{
	u8 temp=0;		  	    																 
  I2C_Start();  
	
	I2C_Send_Byte(0XA0);   //����������ַ0XA0,д����

	I2C_Wait_Ack(); 
    I2C_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	I2C_Wait_Ack();	    
	I2C_Start();  	 	   
	I2C_Send_Byte(0XA1);           //�������ģʽ			   
	I2C_Wait_Ack();	 
    temp=I2C_Read_Byte(0);		   
    I2C_End();//����һ��ֹͣ����	    
	return temp;

}
	
//u8 AT24CXX_ReadOneByte(u16 ReadAddr)
//{
//	u8 temp=0;		  	    																 
//  I2C_Start();  
//	
//	I2C_Send_Byte(0XA1);   //����������ַ0XA0,д����
//	I2C_Wait_Ack();	    
//  temp=I2C_Read_Byte(ReadAddr); 	   			   
//	I2C_End();//����һ��ֹͣ����	 	 
//    		   
//       
//	return temp;

//}
/*******************************************************************************
* �� �� ��         : AT24CXX_WriteOneByte
* ��������		   : ��AT24CXXָ����ַд��һ������
* ��    ��         : WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ 
					 DataToWrite:Ҫд�������
* ��    ��         : ��
*******************************************************************************/
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    I2C_Start();  

		I2C_Send_Byte(0XA0);   //����������ַ0XA0,д����
	 
	I2C_Wait_Ack();	   
    I2C_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	I2C_Wait_Ack(); 	 										  		   
	I2C_Send_Byte(DataToWrite);     //�����ֽ�							   
	I2C_Wait_Ack();  		    	   
    I2C_End();//����һ��ֹͣ���� 
	delay_ms(10);	 
}

/*******************************************************************************
* �� �� ��         : AT24CXX_Check
* ��������		   : ���AT24CXX�Ƿ�����
* ��    ��         : ��
* ��    ��         : 1:���ʧ�ܣ�0:���ɹ�
*******************************************************************************/
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0x36)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X36);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X36)return 0;
	}
	return 1;											  
}







/*******************************************************************************
* �� �� ��         : AT24CXX_WriteLenByte
* ��������		   : ��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
					 ����д��16bit����32bit������
* ��    ��         : WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ 
					 DataToWrite:Ҫд�������
					 Len        :Ҫд�����ݵĳ���2,4
* ��    ��         : ��
*******************************************************************************/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}


/*******************************************************************************
* �� �� ��         : AT24CXX_ReadLenByte
* ��������		   : ��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
					 ���ڶ���16bit����32bit������
* ��    ��         : ReadAddr   :��ʼ�����ĵ�ַ 
					 Len        :Ҫ�������ݵĳ���2,4
* ��    ��         : ��ȡ������
*******************************************************************************/
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}



/*******************************************************************************
* �� �� ��         : AT24CXX_Read
* ��������		   : ��AT24CXX�����ָ����ַ��ʼ����ָ������������
* ��    ��         : ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
					 pBuffer  :���������׵�ַ
					 NumToRead:Ҫ�������ݵĸ���
* ��    ��         : ��
*******************************************************************************/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} 

/*******************************************************************************
* �� �� ��         : AT24CXX_Write
* ��������		   : ��AT24CXX�����ָ����ַ��ʼд��ָ������������
* ��    ��         : WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
					 pBuffer  :���������׵�ַ
					 NumToRead:Ҫ�������ݵĸ���
* ��    ��         : ��
*******************************************************************************/
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}



