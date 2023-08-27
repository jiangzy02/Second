#include  "debug.h"
#include  "uartshow.h"
#include  "RTC.h"
#include "USART3.h"


unsigned char  buf[64],str[64];
extern int Smokings,Calls,Fatigues,Overspeed,Sharpslowdown,Sharpacceleration;//违规次数
extern uint8_t Fatigue_score_show,Call_score_show,Smoking_score_show,Sharpslowdown_score_show,
        Sharpacceleration_score_show,Rate_score_show,Continuousdriving_score_show,Overspeed_score_show,
        Sharpturn_score_show,Sharpturn_score_show; //串口屏需要扣除的百分比分值
extern int Hundred,Ten,One;
extern int Sharpturns;
extern u16 Continudrives;

void Show_Time(void) //RTC
{
    sprintf((char *)buf,"page3.t6.txt=\"%d\"", calendar.w_year);//年
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t8.txt=\"%d\"", calendar.w_month);//月
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t10.txt=\"%d\"", calendar.w_date);//日
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t11.txt=\"%d\"", calendar.hour);//时
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t13.txt=\"%d\"", calendar.min);//分
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t15.txt=\"%d\"", calendar.sec);//秒
    HMISends((char *)buf);
    HMISendb(0xff);
}

void Show_Alcohol_Normal(void) //酒精浓度正常
{
    sprintf((char *)buf,"page2.t4.txt=\"正常\"");
    HMISends((char *)buf); //发送数据给page2页面的t4文本控件
    HMISendb(0xff);//结束符

    sprintf((char *)buf,"page4.t13.txt=\"酒精浓度正常\"");
    HMISends((char *)buf);
    HMISendb(0xff);
}

void Show_Alcohol_Abnormal(void) //酒精浓度异常
{
    sprintf((char *)buf,"page2.t4.txt=\"异常\"");
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page4.t13.txt=\"酒精浓度异常！\"");
    HMISends((char *)buf);
    HMISendb(0xff);
}

extern float speed,Circle,length,mileage;
extern int radCir,radspeed,radTemp,radHumi;
void Show_Speed(void) //车速、车距、转速
{
    sprintf((char *)buf,"page3.t3.txt=\"%.2fcm/s\"",speed);
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t2.txt=\"%.1fr/s\"",Circle);
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t5.txt=\"%.1fcm\"",length);
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t17.txt=\"%.1fm\"",mileage);
    HMISends((char *)buf);
    HMISendb(0xff);


    sprintf(str,"page3.z0.val=%d",radCir);//转速
    HMISends(str); //发送数据给page2页面的z0文本控件,控制指针转动幅度
    HMISendb(0xff);//结束符


    sprintf(str,"page3.z1.val=%d",radspeed);//车速
    HMISends(str);
    HMISendb(0xff);//结束符
}


void Show_Speed_Error(void) //车距异常
{
    sprintf(str,"page4.j6.val=%d",Rate_score_show);
    HMISends(str);
    HMISendb(0xff);
}

extern float temperature,humidity;
void Show_Temp_Humi(void) //温湿度正常
{
    sprintf((char *)buf,"page2.t6.txt=\"%.1f\"",temperature);
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page2.t9.txt=\"%.1f\"",humidity);
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page2.t3.txt=\"正常\"");
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page2.t5.txt=\"正常\"");
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf(str,"page2.z0.val=%d",radTemp);//T
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page2.z1.val=%d",radHumi);//湿度
    HMISends(str);
    HMISendb(0xff);//结束符
}

void Show_Temp_Humi_High(void) //温湿度过高
{
    sprintf((char *)buf,"page2.t3.txt=\"过高\"");
    HMISends((char *)buf);
    HMISendb(0xff);
}

void Fatigue_show(void) //检测到疲劳
{

    sprintf(str,"page4.n3.val=%d",Fatigues);
    HMISends(str);
    HMISendb(0xff);//结束符


    sprintf(str,"page4.j4.val=%d",Fatigue_score_show);
    HMISends(str);
    HMISendb(0xff);//结束符
}
void Call_show(void) //检测到打电话
{

    sprintf(str,"page4.n1.val=%d",Calls);
    HMISends(str);
    HMISendb(0xff);//结束符

    sprintf(str,"page4.j5.val=%d",Call_score_show);
    HMISends(str);
    HMISendb(0xff);//结束符
}


void Smoking_show(void) //检测到抽烟
{
    sprintf(str,"page4.n6.val=%d",Smokings);
    HMISends(str);
    HMISendb(0xff);//结束符

    sprintf(str,"page4.j7.val=%d",Smoking_score_show);
    HMISends(str);
    HMISendb(0xff);//结束符
}

void Overtimedriver_show(void) //连续驾驶
{
    sprintf(str,"page4.j3.val=%d",Continuousdriving_score_show);
    HMISends(str);
    HMISendb(0xff);//结束符
}

void Driver_show(void) //急加速、急减速、超速
{
    sprintf(str,"page4.j0.val=%d",Overspeed_score_show);//超速百分比分值
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.j1.val=%d",Sharpacceleration_score_show);//急加速百分比分值
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.j8.val=%d",Sharpslowdown_score_show);//急减速百分比分值
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.j2.val=%d",Sharpturn_score_show);//急转弯百分比分值
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.n5.val=%d",Overspeed);//超速次数
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.n2.val=%d",Sharpacceleration);//急加速次数
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.n0.val=%d",Sharpslowdown);//急减速次数
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.n4.val=%d",Sharpturns);//急转弯次数
    HMISends(str);
    HMISendb(0xff);//结束符
    sprintf(str,"page4.n7.val=%d",Continudrives);//连续驾驶次数
    HMISends(str);
    HMISendb(0xff);//结束符
}

void GradeA_show(void) //评估等级“优秀”
{
    sprintf((char *)buf,"page4.t23.txt=\"优秀\"");
    HMISends((char *)buf);
    HMISendb(0xff);//结束符
}

void GradeB_show(void) //评估等级“中等”
{
    sprintf((char *)buf,"page4.t23.txt=\"合格\"");
    HMISends((char *)buf);
    HMISendb(0xff);//结束符
}

void GradeC_show(void) //评估等级“不合格”
{
    sprintf((char *)buf,"page4.t23.txt=\"不合格\"");
    HMISends((char *)buf);
    HMISendb(0xff);//结束符
}


void Hundred_show(void) //总分百位
{
    sprintf((char *)buf,"page4.t8.txt=\"%d\"",Hundred);
    HMISends((char *)buf);
    HMISendb(0xff);//结束符
}

void Ten_show(void) //总分十位
{
    sprintf((char *)buf,"page4.t9.txt=\"%d\"",Ten);
    HMISends((char *)buf);
    HMISendb(0xff);//结束符
}

void One_show(void) //总分个位
{
    sprintf((char *)buf,"page4.t10.txt=\"%d\"",One);
    HMISends((char *)buf);
    HMISendb(0xff);//结束符
}
