#include <RTC.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_type.h>
#include <delay_by_systick.h>
#include <stm32f10x_pwr.h>
#include <stm32f10x_rtc.h>
#include <stm32f10x_bkp.h>
#include <stm32f10x_it.h>
#include <stm32f10x_nvic.h>
#include <stdio.h>

_calendar calendar;//时钟结构体 
//月份数据表											 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  
//平年的月份日期表
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};


void RTC_Configuration(void)
{
			u8 temp=0;
	
			NVIC_InitTypeDef NVIC_InitStructure;
	/*	使能电源时钟和后备域时钟， 开启 RTC 后备寄存器写访问*/
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//打开电源时钟
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);//打开 RTC 后备域时钟
			PWR_BackupAccessCmd(ENABLE);//打开后备寄存器访问
	/*	复位备份区域,开启外部低速振荡器*/
		if (BKP_ReadBackupRegister(BKP_DR1) != 0xA0A0)//检查是否配置过
		{
	//	BKP_DeInit(); //复位备份区域	 视情况擦出数据
			RCC_LSEConfig(RCC_LSE_ON);//开启外部 32.768K RTC 时钟
	
			while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);//等待低速晶振就位							
			
	/*	选择 RTC 时钟， 并使能		*/
			
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); //选择 LSE 作为 RTC 时钟
			RCC_RTCCLKCmd(ENABLE);//使能 RTC 时钟
	
			RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成
			RTC_WaitForSynchro(); //等待 RTC 寄存器同步
		
			RTC_ITConfig(RTC_IT_SEC, ENABLE);//秒中断允许
			RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成
			
	/*	设置 RTC 的分频以及配置 RTC 时钟		*/
	
			RTC_EnterConfigMode();// 允许配置
	
			RTC_SetPrescaler(32767);//设置 RTC 时钟分频数，分频后为1s
			RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成
		
	
			RTC_Set(2019,3,31,20,03,30);  //设置时间	
			
			RTC_ExitConfigMode();//退出配置模式， 更新配置
	
			//备份区域写用户数据, BKP_DR1 中写入 0XA0A0 代表我们已经初始化过时钟
			BKP_WriteBackupRegister(BKP_DR1, 0XA0A0);
			
		}
		else  //系统继续计时
		{
			RTC_WaitForSynchro(); //等待最近一次对 RTC 寄存器的写操作完成
			RTC_ITConfig(RTC_IT_SEC, ENABLE); //使能 RTC 秒中断
			RTC_WaitForLastTask(); //等待最近一次对 RTC 寄存器的写操作完成
		}
			
		/*配置中断优先级*/
		NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		RTC_Get();//更新时间	
}

/*******************************************************************************
* 函 数 名         : RTC_Set
* 函数功能		   : RTC设置日期时间函数（以1970年1月1日为基准，把输入的时钟转换为秒钟）
						1970~2099年为合法年份
* 输    入         : syear：年  smon：月  sday：日
					hour：时   min：分	 sec：秒			
* 输    出         : 0,成功
        			 1,失败
*******************************************************************************/
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
    seccount+=(u32)min*60;	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟  
	PWR_BackupAccessCmd(ENABLE);	//使能RTC和后备寄存器访问 
	RTC_SetCounter(seccount);	//设置RTC计数器的值

	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
	return 0;	    
}



void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//秒钟中断
	{							
		RTC_Get();//更新时间  
		printf("RTC Time:%d-%d-%d %d:%d:%d\n",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);//输出闹铃时间	
				
 	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)//闹钟中断
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);		//清闹钟中断	  	
		RTC_Get();				//更新时间   
		printf("Alarm Time:%d-%d-%d %d:%d:%d\n",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);//输出闹铃时间	
		
  	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//清闹钟中断
	RTC_WaitForLastTask();	
	
}

//判断是否是闰年函数
//月份   1  2  3  4  5  6  7  8  9  10 11 12
//闰年   31 29 31 30 31 30 31 31 30 31 30 31
//非闰年 31 28 31 30 31 30 31 31 30 31 30 31
//输入:年份
//输出:该年份是不是闰年.1,是.0,不是
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //必须能被4整除
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	

//初始化闹钟		  
//以1970年1月1日为基准
//1970~2099年为合法年份
//syear,smon,sday,hour,min,sec：闹钟的年月日时分秒   
//返回值:0,成功;其他:错误代码.
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
    seccount+=(u32)min*60;	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去 			    
	//设置时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟   
	PWR_BackupAccessCmd(ENABLE);	//使能后备寄存器访问  
	//上面三步是必须的!
	
	RTC_SetAlarm(seccount);
 
	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
	
	return 0;	    
}


//得到当前的时间
//返回值:0,成功;其他:错误代码.
u8 RTC_Get(void)
{
	static u16 daycnt=0;
	u32 timecount=0; 
	u32 temp=0;
	u16 temp1=0;	  
    timecount=RTC_GetCounter();	 
 	temp=timecount/86400;   //得到天数(秒钟数对应的)
	if(daycnt!=temp)//超过一天了
	{	  
		daycnt=temp;
		temp1=1970;	//从1970年开始
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//是闰年
			{
				if(temp>=366)temp-=366;//闰年的秒钟数
				else {temp1++;break;}  
			}
			else temp-=365;	  //平年 
			temp1++;  
		}   
		calendar.w_year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超过了一个月
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)//当年是不是闰年/2月份
			{
				if(temp>=29)temp-=29;//闰年的秒钟数
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
				else break;
			}
			temp1++;  
		}
		calendar.w_month=temp1+1;	//得到月份
		calendar.w_date=temp+1;  	//得到日期 
	}
	temp=timecount%86400;     		//得到秒钟数   	   
	calendar.hour=temp/3600;     	//小时
	calendar.min=(temp%3600)/60; 	//分钟	
	calendar.sec=(temp%3600)%60; 	//秒钟
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//获取星期   
	return 0;
}	 

//获得现在是星期几
//功能描述:输入公历日期得到星期(只允许1901-2099年)
//输入参数：公历年月日 
//返回值：星期号																						 
u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// 如果为21世纪,年份数加100  
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}			  

/*
int main(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	USART1_Configuration();
	RTC_Configuration();
	
	
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		delay_ms(100);
		
		delay_ms(10);
	}
}
*/