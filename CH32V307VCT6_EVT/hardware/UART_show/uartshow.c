#include  "debug.h"
#include  "uartshow.h"
#include  "RTC.h"
#include "USART3.h"


unsigned char  buf[64],str[64];
extern int Smokings,Calls,Fatigues,Overspeed,Sharpslowdown,Sharpacceleration;//Υ�����
extern uint8_t Fatigue_score_show,Call_score_show,Smoking_score_show,Sharpslowdown_score_show,
        Sharpacceleration_score_show,Rate_score_show,Continuousdriving_score_show,Overspeed_score_show,
        Sharpturn_score_show,Sharpturn_score_show; //��������Ҫ�۳��İٷֱȷ�ֵ
extern int Hundred,Ten,One;
extern int Sharpturns;
extern u16 Continudrives;

void Show_Time(void) //RTC
{
    sprintf((char *)buf,"page3.t6.txt=\"%d\"", calendar.w_year);//��
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t8.txt=\"%d\"", calendar.w_month);//��
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t10.txt=\"%d\"", calendar.w_date);//��
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t11.txt=\"%d\"", calendar.hour);//ʱ
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t13.txt=\"%d\"", calendar.min);//��
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page3.t15.txt=\"%d\"", calendar.sec);//��
    HMISends((char *)buf);
    HMISendb(0xff);
}

void Show_Alcohol_Normal(void) //�ƾ�Ũ������
{
    sprintf((char *)buf,"page2.t4.txt=\"����\"");
    HMISends((char *)buf); //�������ݸ�page2ҳ���t4�ı��ؼ�
    HMISendb(0xff);//������

    sprintf((char *)buf,"page4.t13.txt=\"�ƾ�Ũ������\"");
    HMISends((char *)buf);
    HMISendb(0xff);
}

void Show_Alcohol_Abnormal(void) //�ƾ�Ũ���쳣
{
    sprintf((char *)buf,"page2.t4.txt=\"�쳣\"");
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page4.t13.txt=\"�ƾ�Ũ���쳣��\"");
    HMISends((char *)buf);
    HMISendb(0xff);
}

extern float speed,Circle,length,mileage;
extern int radCir,radspeed,radTemp,radHumi;
void Show_Speed(void) //���١����ࡢת��
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


    sprintf(str,"page3.z0.val=%d",radCir);//ת��
    HMISends(str); //�������ݸ�page2ҳ���z0�ı��ؼ�,����ָ��ת������
    HMISendb(0xff);//������


    sprintf(str,"page3.z1.val=%d",radspeed);//����
    HMISends(str);
    HMISendb(0xff);//������
}


void Show_Speed_Error(void) //�����쳣
{
    sprintf(str,"page4.j6.val=%d",Rate_score_show);
    HMISends(str);
    HMISendb(0xff);
}

extern float temperature,humidity;
void Show_Temp_Humi(void) //��ʪ������
{
    sprintf((char *)buf,"page2.t6.txt=\"%.1f\"",temperature);
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page2.t9.txt=\"%.1f\"",humidity);
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page2.t3.txt=\"����\"");
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf((char *)buf,"page2.t5.txt=\"����\"");
    HMISends((char *)buf);
    HMISendb(0xff);
    sprintf(str,"page2.z0.val=%d",radTemp);//T
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page2.z1.val=%d",radHumi);//ʪ��
    HMISends(str);
    HMISendb(0xff);//������
}

void Show_Temp_Humi_High(void) //��ʪ�ȹ���
{
    sprintf((char *)buf,"page2.t3.txt=\"����\"");
    HMISends((char *)buf);
    HMISendb(0xff);
}

void Fatigue_show(void) //��⵽ƣ��
{

    sprintf(str,"page4.n3.val=%d",Fatigues);
    HMISends(str);
    HMISendb(0xff);//������


    sprintf(str,"page4.j4.val=%d",Fatigue_score_show);
    HMISends(str);
    HMISendb(0xff);//������
}
void Call_show(void) //��⵽��绰
{

    sprintf(str,"page4.n1.val=%d",Calls);
    HMISends(str);
    HMISendb(0xff);//������

    sprintf(str,"page4.j5.val=%d",Call_score_show);
    HMISends(str);
    HMISendb(0xff);//������
}


void Smoking_show(void) //��⵽����
{
    sprintf(str,"page4.n6.val=%d",Smokings);
    HMISends(str);
    HMISendb(0xff);//������

    sprintf(str,"page4.j7.val=%d",Smoking_score_show);
    HMISends(str);
    HMISendb(0xff);//������
}

void Overtimedriver_show(void) //������ʻ
{
    sprintf(str,"page4.j3.val=%d",Continuousdriving_score_show);
    HMISends(str);
    HMISendb(0xff);//������
}

void Driver_show(void) //�����١������١�����
{
    sprintf(str,"page4.j0.val=%d",Overspeed_score_show);//���ٰٷֱȷ�ֵ
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.j1.val=%d",Sharpacceleration_score_show);//�����ٰٷֱȷ�ֵ
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.j8.val=%d",Sharpslowdown_score_show);//�����ٰٷֱȷ�ֵ
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.j2.val=%d",Sharpturn_score_show);//��ת��ٷֱȷ�ֵ
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.n5.val=%d",Overspeed);//���ٴ���
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.n2.val=%d",Sharpacceleration);//�����ٴ���
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.n0.val=%d",Sharpslowdown);//�����ٴ���
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.n4.val=%d",Sharpturns);//��ת�����
    HMISends(str);
    HMISendb(0xff);//������
    sprintf(str,"page4.n7.val=%d",Continudrives);//������ʻ����
    HMISends(str);
    HMISendb(0xff);//������
}

void GradeA_show(void) //�����ȼ������㡱
{
    sprintf((char *)buf,"page4.t23.txt=\"����\"");
    HMISends((char *)buf);
    HMISendb(0xff);//������
}

void GradeB_show(void) //�����ȼ����еȡ�
{
    sprintf((char *)buf,"page4.t23.txt=\"�ϸ�\"");
    HMISends((char *)buf);
    HMISendb(0xff);//������
}

void GradeC_show(void) //�����ȼ������ϸ�
{
    sprintf((char *)buf,"page4.t23.txt=\"���ϸ�\"");
    HMISends((char *)buf);
    HMISendb(0xff);//������
}


void Hundred_show(void) //�ְܷ�λ
{
    sprintf((char *)buf,"page4.t8.txt=\"%d\"",Hundred);
    HMISends((char *)buf);
    HMISendb(0xff);//������
}

void Ten_show(void) //�ܷ�ʮλ
{
    sprintf((char *)buf,"page4.t9.txt=\"%d\"",Ten);
    HMISends((char *)buf);
    HMISendb(0xff);//������
}

void One_show(void) //�ָܷ�λ
{
    sprintf((char *)buf,"page4.t10.txt=\"%d\"",One);
    HMISends((char *)buf);
    HMISendb(0xff);//������
}
