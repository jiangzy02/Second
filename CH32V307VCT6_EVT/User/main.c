#include "debug.h"
#include "HC-SR04.h"   //测距
#include "ADC.h"       //MQ3酒精浓度检测
#include "speed.h"     //motor速度控制以及光电测速
#include "dht11.h"     //温湿度
#include "RTC.h"       //实时时钟
#include "uartshow.h"  // 串口屏数据显示
#include "key_pwm.h"   //调速
#include "USART2.h"    //负责与k210通信
#include "USART3.h"    //负责与串口屏通信
#include "UART4.h"
#include "uart5.h"     //与赤菟开发板通信
#include "UART6.h"
#include "IWDG.h"
#define  PI 3.1415926535
#define  R 3.5         //车轮半径3.5cm

uint8_t wendu[2] = {0};  //wendu[0]：存储温度数据整数，wendu[1]：存储温度数据小数
uint8_t shidu[2] = {0};
//疲劳、打电话、抽烟、饮酒、急减速、急加速、速距匹配、连续驾驶、超速、急转弯分数
uint8_t Fatigue_score=0,Call_score=0,Smoking_score=0,Drink_score=0,Sharpslowdown_score=0,
        Sharpacceleration_score=0,Rate_score=0,Continuousdriving_score=0,Overspeed_score=0,
        Sharpturn_score=0; //需要扣除的分值
//----------------------------串口屏需要扣除的百分比分值
uint8_t Fatigue_score_show=0,Call_score_show=0,Smoking_score_show=0,
        Sharpslowdown_score_show=0,Sharpacceleration_score_show=0,Rate_score_show=0,
        Continuousdriving_score_show=0,Overspeed_score_show=0,Sharpturn_score_show=0;

int Smokings=0,Calls=0,Fatigues=0,Overspeed=0,Sharpslowdown=0,
    Sharpacceleration=0,Overspeeds=0,Sharpturns=0;//违规次数
extern u8 Sharpadd_flag,Sharpslowdown_flag;//急加速急减速标志
extern u16 ContDriveflag; //连续驾驶标志
u16 Continudrives=0; //连续驾驶次数
int Hundred,Ten,One;//总分分数
extern u16 Fatigue_Flag;//当值为0时，是清醒状态,当值为1时是疲劳状态
extern u16 Callphone_Flag;//当值为0时，是未接打电话状态，当值为1时是打电话状态
extern u16 Smoking_Flag;//当值为0时，是未吸烟状态，当值为1时是吸烟状态
u16 Alarm_Flag=0; //闹钟标识符
extern uint8_t star; //停车标志位'按一次变化一次 0 1变化'
int radCir=0,radspeed=0,radTemp=0,radHumi=0;//四个指针转动角度
float adcx,alcohol,length,temperature,humidity,speed,omiga,rate,mileage,laps,total;//传感器数据
extern float Circle;//转速
extern int pwm;//占空比
u8 Alarm_Sec;
extern u8 alarm_state;
int is_over_speed=0;
int is_ratedown=0;
int Speed_Flag=0,Rate_Flag=0;
extern u16 Angle_Mode;  //急转弯标志
extern u16 Red_Flag;
extern u16 Yellow_Flag;
extern u16 Angle_Mode;
/*********************************************************************
各外设引脚定义：
PC0--KEY0--按下模拟连续驾驶
PC1--KEY1--减速
PC2--KEY2--加速
PC3--KEY3--按下启动
PC4--KEY4--急加速
PC5--KEY5--急减速
L298N:PB13-N3、PB14-N4，PB5-ENA
MQ3:PA1-AO作为模拟输入引脚           5V
DHT11:DAT-PA11          5V
GD:OUT-PB12             5V
HCSR04_TRIG  PD4        5V
HCSR04_ECHO  PD3
USART2与k210通信：PA2-接k210的RX-9   PA3-接k210的TX-10
USART3与串口屏通信：PB10-接串口屏RX  PB11-接串口屏TX  12V
uart4的TX-PC10接  RX-PC11 获取MPU数值
UART5连赤菟USART3 TX=PC12连PD9,UART5_RX=PD2连PD8
uart6的TX—PE10接k210—9  RX PE11-10   连 k2102
*****************************************************************************/

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);
	Adc_Init();               //ADC测量酒精度数初始化
	Hcsr04_Init();            //测距传感器初始化
	DHT11_Init();             //温湿度
    Init_uart6(115200); //K2102
	uart4_Init(115200); //MPU
	uart3_init();       //串口屏初始化 波特率115200
    usart2_start(115200);       //k210通信串口初始化
	RTC_Init();
	MOTOR_Init();//用于启动电机
	TIM3_PWM_Init(2999,0);//不分频。PWM 频率=96000/(2999+1)=16KHz
	TIM2_inIt();
    GD_inIt();
	KEY_Init();
	IWDG_Feed_Init(IWDG_Prescaler_32, 4000); // 3.2s IWDG reset
    Init_UART5();//上位机通信，向赤菟发送数据
    UART5_DMA_Tx_Configuration();

    while(1)
    {
   //数据测量-------------------------------------------------------------
       DHT11_Read_Data(wendu,shidu);   //DHT11读取温度、湿度值
       temperature = wendu[0]+(float)(wendu[1]*0.1);
       humidity = shidu[0]+(float)(shidu[1]*0.1);
       adcx = Get_Adc_Average(ADC_Channel_1,10);  //ADC酒精浓度转换
       alcohol = (adcx*5/4096*0.36-0.808);        //酒精浓度换算
       length = Hcsr04GetLength();  //测得车距值
       laps = CountSensor_Get();    //车轮累计转动圈数,最大6r/s
       mileage = 2*PI*R*laps/100;   //行驶里程,单位米
       speed  = Circle*2*PI*R;      //车速：最大130cm/s
       rate   = length/speed;       //车距与车速比‘三秒间隔’定理
    //--------------------------------------------------------------------
   //当接收到串口屏发来的闹钟指令时
       if (alarm_state==1) {
           Alarm_Sec=calendar.sec;
           alarm_state=0;
    }
       if(calendar.sec + 1 == Alarm_Sec)
       {
           Alarm_Flag = 1;
       }
    //----------------------------------------------------------------------------

      //上传指针至串口屏
       radCir =(Circle/6)*215-50; //转速指针模块
       radspeed = (speed/132)*215-80;//车速指针模块
       radTemp = ((temperature+20)/100)*215-20;//温度指针模块
       radHumi = (humidity/100)*215-25;//湿度指针模块
      //-----------------------------------------------------

       //如果外部中断接收到连续驾驶
       if (ContDriveflag==1) {
         Continudrives += 1;
         Continuousdriving_score += 10;


       }

       data_switch();//把所有测得的数据变成u16形式放进data数组中用串口发送
       DMA_send();

       if (ContDriveflag==1)ContDriveflag=0;
       if (pwm>=0&&Sharpadd_flag){ //急加速
       Sharpacceleration = Sharpacceleration+1;//急减速次数+1
       Sharpacceleration_score += 5;//急减速导致分值-5
       Sharpadd_flag=0;
       }

       if(pwm<=1500&&Sharpslowdown_flag==1){
       Sharpslowdown = Sharpslowdown+1;//急加速次数+1
       Sharpslowdown_score += 5;//急加速导致分值-5
       Sharpslowdown_flag=0;
       }
       if (pwm<0)pwm=0;
       if (pwm>1500)pwm=1500;

       if(Alarm_Flag==1){
           Alarm_Flag = 0;
           Alarm_Sec=0;
       }


  if (alcohol<0.9) //酒精浓度正常才可以启动车辆
      {
            Show_Alcohol_Normal();   //串口屏显示酒精浓度正常
       if (star==0){ //电机停止转动
            GPIO_ResetBits(GPIOB, GPIO_Pin_13);
            GPIO_ResetBits(GPIOB, GPIO_Pin_14);
       }
       if (star==1){ //按键启动电机
            GPIO_SetBits(GPIOB, GPIO_Pin_13);  //启动方式
            GPIO_ResetBits(GPIOB, GPIO_Pin_14);
            TIM_SetCompare2(TIM3,pwm);   //pwm=CCR/(arr+1)，通过按键控制占空比
            //占空比 = (pwm / (2999 + 1)) x 100% 正常加速pwm改变值是100，急加速改变值250
        }

            // 判断是否超速
           if (speed > 60) {
                    if (!is_over_speed) {
                        Overspeed++; // 第一次超速，超速次数加一
                        Overspeed_score += 5;//因为超速分值-5
                        is_over_speed = 1;
                    } else {
                        // 已超速，不做处理
                    }
                } else {
                    is_over_speed = 0;
                }

           if (length/speed<1){   //车距车速比小于1时
            if (!is_ratedown) {
                Rate_Flag++;  //车距车速比标识符自增
                Rate_score += 15;//一旦异常，扣除15分
                is_ratedown=1;
            }
            else {
                // 已车距过近，不做处理
            }
            }else {
                is_ratedown=0;
            }
        //急转弯
           if (speed>40) {
            if (Angle_Mode) {
                Sharpturns += 1;
                Sharpturn_score += 5;
                Angle_Mode=0;
            }
        }
        //K210监测部分
            if (Fatigue_Flag) { //检测到疲劳
                  Fatigues=Fatigues+1; //次数+1
                  Fatigue_score += 10;//分值-5
                  Fatigue_Flag = 0;
            }
            if (Callphone_Flag) { //检测到打电话
                  Calls=Calls+1;//次数+1
                  Call_score += 5;//分值-5
                  Callphone_Flag=0;
                  }
             if (Smoking_Flag) { //检测到抽烟
                 Smokings=Smokings+1; //次数+1
                 Smoking_score += 5;//分值-5
                 Smoking_Flag=0;
            }
             if (Red_Flag) {
                Red_Flag=0;
            }
             if (Yellow_Flag) {
                Yellow_Flag=0;
            }

   //分数部分
    total=100-Sharpacceleration_score-Sharpslowdown_score-Overspeed_score-Continuousdriving_score-
          Call_score-Smoking_score-Fatigue_score-Rate_score-Sharpturn_score;

       if (total<0)  total=0;
       Hundred=total/100;
       Ten=(int)(total/10)%10;
       One=(int)total%10;
   }

  else if(alcohol>=0.9){  //酒精浓度异常，总分为零,评估等级处显示“饮酒禁止驾车”
       Hundred=0;
       Ten=0;
       One=0;
       total=0;
       Show_Alcohol_Abnormal(); //串口屏显示酒精浓度异常
    }

   //串口屏显示部分
        if(total==100) GradeA_show(); //评估等级“优秀” score=100
        if(total>=80&&total<100) GradeB_show(); //评估等级“合格” 80=<score<100
        if(total<80) GradeC_show(); //评估等级“不合格” score<80
        if (temperature>=40) Show_Temp_Humi_High(); //温湿度过高显示

  //百分比分值
        Fatigue_score_show=100-Fatigue_score;
        Call_score_show=100-Call_score;
        Smoking_score_show=100-Smoking_score;
        Sharpslowdown_score_show=100-Sharpslowdown_score;
        Sharpacceleration_score_show=100-Sharpacceleration_score;
        Rate_score_show=100-Rate_score;
        Continuousdriving_score_show=100-Continuousdriving_score;
        Overspeed_score_show=100-Overspeed_score;
        Sharpturn_score_show=100-Sharpturn_score;

        Show_Temp_Humi(); //串口屏正常温湿度显示
        Show_Time();   //串口屏实时时钟显示
        Show_Speed();       //串口屏显示车速、车距、转速
        Show_Speed_Error(); //车距异常
        Fatigue_show(); //检测到疲劳
        Call_show(); //检测到打电话
        Smoking_show(); //检测到抽烟
        Overtimedriver_show();//超速
        Driver_show(); //急加速、急减速、超速
        Hundred_show(); //总分百位
        Ten_show(); //总分十位
        One_show(); //总分个位
        IWDG_ReloadCounter(); //Feed dog


    }
}




