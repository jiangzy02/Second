#include "debug.h"
#include "HC-SR04.h"   //���
#include "ADC.h"       //MQ3�ƾ�Ũ�ȼ��
#include "speed.h"     //motor�ٶȿ����Լ�������
#include "dht11.h"     //��ʪ��
#include "RTC.h"       //ʵʱʱ��
#include "uartshow.h"  // ������������ʾ
#include "key_pwm.h"   //����
#include "USART2.h"    //������k210ͨ��
#include "USART3.h"    //�����봮����ͨ��
#include "UART4.h"
#include "uart5.h"     //����˿�����ͨ��
#include "UART6.h"
#include "IWDG.h"
#define  PI 3.1415926535
#define  R 3.5         //���ְ뾶3.5cm

uint8_t wendu[2] = {0};  //wendu[0]���洢�¶�����������wendu[1]���洢�¶�����С��
uint8_t shidu[2] = {0};
//ƣ�͡���绰�����̡����ơ������١������١��پ�ƥ�䡢������ʻ�����١���ת�����
uint8_t Fatigue_score=0,Call_score=0,Smoking_score=0,Drink_score=0,Sharpslowdown_score=0,
        Sharpacceleration_score=0,Rate_score=0,Continuousdriving_score=0,Overspeed_score=0,
        Sharpturn_score=0; //��Ҫ�۳��ķ�ֵ
//----------------------------��������Ҫ�۳��İٷֱȷ�ֵ
uint8_t Fatigue_score_show=0,Call_score_show=0,Smoking_score_show=0,
        Sharpslowdown_score_show=0,Sharpacceleration_score_show=0,Rate_score_show=0,
        Continuousdriving_score_show=0,Overspeed_score_show=0,Sharpturn_score_show=0;

int Smokings=0,Calls=0,Fatigues=0,Overspeed=0,Sharpslowdown=0,
    Sharpacceleration=0,Overspeeds=0,Sharpturns=0;//Υ�����
extern u8 Sharpadd_flag,Sharpslowdown_flag;//�����ټ����ٱ�־
extern u16 ContDriveflag; //������ʻ��־
u16 Continudrives=0; //������ʻ����
int Hundred,Ten,One;//�ַܷ���
extern u16 Fatigue_Flag;//��ֵΪ0ʱ��������״̬,��ֵΪ1ʱ��ƣ��״̬
extern u16 Callphone_Flag;//��ֵΪ0ʱ����δ�Ӵ�绰״̬����ֵΪ1ʱ�Ǵ�绰״̬
extern u16 Smoking_Flag;//��ֵΪ0ʱ����δ����״̬����ֵΪ1ʱ������״̬
u16 Alarm_Flag=0; //���ӱ�ʶ��
extern uint8_t star; //ͣ����־λ'��һ�α仯һ�� 0 1�仯'
int radCir=0,radspeed=0,radTemp=0,radHumi=0;//�ĸ�ָ��ת���Ƕ�
float adcx,alcohol,length,temperature,humidity,speed,omiga,rate,mileage,laps,total;//����������
extern float Circle;//ת��
extern int pwm;//ռ�ձ�
u8 Alarm_Sec;
extern u8 alarm_state;
int is_over_speed=0;
int is_ratedown=0;
int Speed_Flag=0,Rate_Flag=0;
extern u16 Angle_Mode;  //��ת���־
extern u16 Red_Flag;
extern u16 Yellow_Flag;
extern u16 Angle_Mode;
/*********************************************************************
���������Ŷ��壺
PC0--KEY0--����ģ��������ʻ
PC1--KEY1--����
PC2--KEY2--����
PC3--KEY3--��������
PC4--KEY4--������
PC5--KEY5--������
L298N:PB13-N3��PB14-N4��PB5-ENA
MQ3:PA1-AO��Ϊģ����������           5V
DHT11:DAT-PA11          5V
GD:OUT-PB12             5V
HCSR04_TRIG  PD4        5V
HCSR04_ECHO  PD3
USART2��k210ͨ�ţ�PA2-��k210��RX-9   PA3-��k210��TX-10
USART3�봮����ͨ�ţ�PB10-�Ӵ�����RX  PB11-�Ӵ�����TX  12V
uart4��TX-PC10��  RX-PC11 ��ȡMPU��ֵ
UART5������USART3 TX=PC12��PD9,UART5_RX=PD2��PD8
uart6��TX��PE10��k210��9  RX PE11-10   �� k2102
*****************************************************************************/

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);
	Adc_Init();               //ADC�����ƾ�������ʼ��
	Hcsr04_Init();            //��ഫ������ʼ��
	DHT11_Init();             //��ʪ��
    Init_uart6(115200); //K2102
	uart4_Init(115200); //MPU
	uart3_init();       //��������ʼ�� ������115200
    usart2_start(115200);       //k210ͨ�Ŵ��ڳ�ʼ��
	RTC_Init();
	MOTOR_Init();//�����������
	TIM3_PWM_Init(2999,0);//����Ƶ��PWM Ƶ��=96000/(2999+1)=16KHz
	TIM2_inIt();
    GD_inIt();
	KEY_Init();
	IWDG_Feed_Init(IWDG_Prescaler_32, 4000); // 3.2s IWDG reset
    Init_UART5();//��λ��ͨ�ţ�����˷�������
    UART5_DMA_Tx_Configuration();

    while(1)
    {
   //���ݲ���-------------------------------------------------------------
       DHT11_Read_Data(wendu,shidu);   //DHT11��ȡ�¶ȡ�ʪ��ֵ
       temperature = wendu[0]+(float)(wendu[1]*0.1);
       humidity = shidu[0]+(float)(shidu[1]*0.1);
       adcx = Get_Adc_Average(ADC_Channel_1,10);  //ADC�ƾ�Ũ��ת��
       alcohol = (adcx*5/4096*0.36-0.808);        //�ƾ�Ũ�Ȼ���
       length = Hcsr04GetLength();  //��ó���ֵ
       laps = CountSensor_Get();    //�����ۼ�ת��Ȧ��,���6r/s
       mileage = 2*PI*R*laps/100;   //��ʻ���,��λ��
       speed  = Circle*2*PI*R;      //���٣����130cm/s
       rate   = length/speed;       //�����복�ٱȡ�������������
    //--------------------------------------------------------------------
   //�����յ�����������������ָ��ʱ
       if (alarm_state==1) {
           Alarm_Sec=calendar.sec;
           alarm_state=0;
    }
       if(calendar.sec + 1 == Alarm_Sec)
       {
           Alarm_Flag = 1;
       }
    //----------------------------------------------------------------------------

      //�ϴ�ָ����������
       radCir =(Circle/6)*215-50; //ת��ָ��ģ��
       radspeed = (speed/132)*215-80;//����ָ��ģ��
       radTemp = ((temperature+20)/100)*215-20;//�¶�ָ��ģ��
       radHumi = (humidity/100)*215-25;//ʪ��ָ��ģ��
      //-----------------------------------------------------

       //����ⲿ�жϽ��յ�������ʻ
       if (ContDriveflag==1) {
         Continudrives += 1;
         Continuousdriving_score += 10;


       }

       data_switch();//�����в�õ����ݱ��u16��ʽ�Ž�data�������ô��ڷ���
       DMA_send();

       if (ContDriveflag==1)ContDriveflag=0;
       if (pwm>=0&&Sharpadd_flag){ //������
       Sharpacceleration = Sharpacceleration+1;//�����ٴ���+1
       Sharpacceleration_score += 5;//�����ٵ��·�ֵ-5
       Sharpadd_flag=0;
       }

       if(pwm<=1500&&Sharpslowdown_flag==1){
       Sharpslowdown = Sharpslowdown+1;//�����ٴ���+1
       Sharpslowdown_score += 5;//�����ٵ��·�ֵ-5
       Sharpslowdown_flag=0;
       }
       if (pwm<0)pwm=0;
       if (pwm>1500)pwm=1500;

       if(Alarm_Flag==1){
           Alarm_Flag = 0;
           Alarm_Sec=0;
       }


  if (alcohol<0.9) //�ƾ�Ũ�������ſ�����������
      {
            Show_Alcohol_Normal();   //��������ʾ�ƾ�Ũ������
       if (star==0){ //���ֹͣת��
            GPIO_ResetBits(GPIOB, GPIO_Pin_13);
            GPIO_ResetBits(GPIOB, GPIO_Pin_14);
       }
       if (star==1){ //�����������
            GPIO_SetBits(GPIOB, GPIO_Pin_13);  //������ʽ
            GPIO_ResetBits(GPIOB, GPIO_Pin_14);
            TIM_SetCompare2(TIM3,pwm);   //pwm=CCR/(arr+1)��ͨ����������ռ�ձ�
            //ռ�ձ� = (pwm / (2999 + 1)) x 100% ��������pwm�ı�ֵ��100�������ٸı�ֵ250
        }

            // �ж��Ƿ���
           if (speed > 60) {
                    if (!is_over_speed) {
                        Overspeed++; // ��һ�γ��٣����ٴ�����һ
                        Overspeed_score += 5;//��Ϊ���ٷ�ֵ-5
                        is_over_speed = 1;
                    } else {
                        // �ѳ��٣���������
                    }
                } else {
                    is_over_speed = 0;
                }

           if (length/speed<1){   //���೵�ٱ�С��1ʱ
            if (!is_ratedown) {
                Rate_Flag++;  //���೵�ٱȱ�ʶ������
                Rate_score += 15;//һ���쳣���۳�15��
                is_ratedown=1;
            }
            else {
                // �ѳ����������������
            }
            }else {
                is_ratedown=0;
            }
        //��ת��
           if (speed>40) {
            if (Angle_Mode) {
                Sharpturns += 1;
                Sharpturn_score += 5;
                Angle_Mode=0;
            }
        }
        //K210��ⲿ��
            if (Fatigue_Flag) { //��⵽ƣ��
                  Fatigues=Fatigues+1; //����+1
                  Fatigue_score += 10;//��ֵ-5
                  Fatigue_Flag = 0;
            }
            if (Callphone_Flag) { //��⵽��绰
                  Calls=Calls+1;//����+1
                  Call_score += 5;//��ֵ-5
                  Callphone_Flag=0;
                  }
             if (Smoking_Flag) { //��⵽����
                 Smokings=Smokings+1; //����+1
                 Smoking_score += 5;//��ֵ-5
                 Smoking_Flag=0;
            }
             if (Red_Flag) {
                Red_Flag=0;
            }
             if (Yellow_Flag) {
                Yellow_Flag=0;
            }

   //��������
    total=100-Sharpacceleration_score-Sharpslowdown_score-Overspeed_score-Continuousdriving_score-
          Call_score-Smoking_score-Fatigue_score-Rate_score-Sharpturn_score;

       if (total<0)  total=0;
       Hundred=total/100;
       Ten=(int)(total/10)%10;
       One=(int)total%10;
   }

  else if(alcohol>=0.9){  //�ƾ�Ũ���쳣���ܷ�Ϊ��,�����ȼ�����ʾ�����ƽ�ֹ�ݳ���
       Hundred=0;
       Ten=0;
       One=0;
       total=0;
       Show_Alcohol_Abnormal(); //��������ʾ�ƾ�Ũ���쳣
    }

   //��������ʾ����
        if(total==100) GradeA_show(); //�����ȼ������㡱 score=100
        if(total>=80&&total<100) GradeB_show(); //�����ȼ����ϸ� 80=<score<100
        if(total<80) GradeC_show(); //�����ȼ������ϸ� score<80
        if (temperature>=40) Show_Temp_Humi_High(); //��ʪ�ȹ�����ʾ

  //�ٷֱȷ�ֵ
        Fatigue_score_show=100-Fatigue_score;
        Call_score_show=100-Call_score;
        Smoking_score_show=100-Smoking_score;
        Sharpslowdown_score_show=100-Sharpslowdown_score;
        Sharpacceleration_score_show=100-Sharpacceleration_score;
        Rate_score_show=100-Rate_score;
        Continuousdriving_score_show=100-Continuousdriving_score;
        Overspeed_score_show=100-Overspeed_score;
        Sharpturn_score_show=100-Sharpturn_score;

        Show_Temp_Humi(); //������������ʪ����ʾ
        Show_Time();   //������ʵʱʱ����ʾ
        Show_Speed();       //��������ʾ���١����ࡢת��
        Show_Speed_Error(); //�����쳣
        Fatigue_show(); //��⵽ƣ��
        Call_show(); //��⵽��绰
        Smoking_show(); //��⵽����
        Overtimedriver_show();//����
        Driver_show(); //�����١������١�����
        Hundred_show(); //�ְܷ�λ
        Ten_show(); //�ܷ�ʮλ
        One_show(); //�ָܷ�λ
        IWDG_ReloadCounter(); //Feed dog


    }
}




