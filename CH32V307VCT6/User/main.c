#include "debug.h"
#include "JQ8900.h"
#include "WS2812.h"
#include "esp8266.h"
#include "onenet.h"
#include "../Hardware/UART6_ESP01/UART6.h"
#include "../Hardware/USART2_TWAsr/usart2.h"
#include "../Hardware/USART3_DMA/USART3.h"

//四种灯效(串口屏控制)
u16 Light_Mode;
u16 Rainbow_Mode;
u16 Print_Mode;
u16 Flash_Mpde;
u16 Close_Mode;//关灯
//四种灯效（语音控制）
extern u16 Light_Voice;
extern u16 Rainbow_Voice;
extern u16 Print_Voice;
extern u16 Flash_Voice;
extern u16 Music_Mode;//音乐播放
extern u16 Close_Voice;//关灯
u16 Continudrive; //连续驾驶标志
u16 Fatigue_Flag;//当值为0时，是清醒状态，当值为1时是疲劳状态
u16 Callphone_Flag;//当值为0时，是未接打电话状态，当值为1时是打电话状态
u16 Smoking_Flag;//当值为0时，是未吸烟状态，当值为1时是吸烟状态
u16 Sharpslowdown; //急减速次数
u16 Sharpacceleration;//急加速次数
u16 Sharpturns;
u16 Fatigues; //犯困次数
u16 Calls;  //打电话次数
u16 Smokings; //抽烟次数
u8 Overspeed=0;//超速次数
u8 Speed_Flag=0; //超速标识
u16 alarm_flag;
u16 Angle_Mode;  //急转弯标志
u16 Red_Flag;    //前车尾灯变红
u16 Yellow_Flag; //前车尾灯变黄


extern uint16_t USART3_RxBuf[USART_MAX_LEN];   //接收缓存
float alcohol,length,temperature,humidity,speed,Circle,mileage,rate,total;
/*****************************
USART2与下位机USART3通信  PD9连PC12,PD8连PD2
WS2812:PA1 ---TIM5 5V
JQ8900：PD10，一线串口Z输入 5v
智能语音助手：USART2-RX  5v
******************************/

int main(void)
{
    unsigned short timeCount = 0;    //发送间隔变量
    unsigned char *dataPtr = NULL;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);  //打印调试串口
    WS281x_Init();
    uart3_init(115200);//接收来自评估板的数据的串口
    DMA_RX_init();
    OnUart_GPIO();
    usart2_init(9600); //天问
   // IWDG_Feed_Init(IWDG_Prescaler_32, 8000); // 3.2s IWDG reset
    Usart6_Init(115200);//esp8266串口
    ESP8266_Init();                 //初始化ESP8266
    while(OneNet_DevLink())         //接入OneNET
    Delay_Ms(500);
while(1)
    {
        USART3_Server();//负责DMA接收来自评估板的数据
        temperature = (float)USART3_RxBuf[0]/100;
        humidity    = (float)USART3_RxBuf[1]/100;
        length      = (float)USART3_RxBuf[2]/100;
        alcohol     = (float)USART3_RxBuf[3]/100;
        speed       = (float)USART3_RxBuf[4]/100;
        Circle      = (float)USART3_RxBuf[5]/100;
        mileage     = (float)USART3_RxBuf[6]/100;
        total       = (float)USART3_RxBuf[7]/100;
        Fatigue_Flag   =USART3_RxBuf[8];
        Callphone_Flag =USART3_RxBuf[9];
        Smoking_Flag   =USART3_RxBuf[10];
        Light_Mode     =USART3_RxBuf[11];
        Rainbow_Mode   =USART3_RxBuf[12];
        Print_Mode     =USART3_RxBuf[13];
        Flash_Mpde     =USART3_RxBuf[14];
        Close_Mode     =USART3_RxBuf[15];
        Continudrive   =USART3_RxBuf[16];
        Sharpslowdown  =USART3_RxBuf[17];
        Sharpacceleration=USART3_RxBuf[18];
        Fatigues       =USART3_RxBuf[19];
        Calls          =USART3_RxBuf[20];
        Smokings       =USART3_RxBuf[21];
        alarm_flag     =USART3_RxBuf[22];
        Angle_Mode     =USART3_RxBuf[23];//急转弯
        Red_Flag       =USART3_RxBuf[24];
        Yellow_Flag    =USART3_RxBuf[25];
        Sharpturns     =USART3_RxBuf[26];//急转弯次数
        printf("222\r\n");
        /*
        printf("temperature=%f\r\n",temperature);
        printf("humidity=%f\r\n",humidity);
        printf("        length=%f\r\n",        length);
        printf("alcohol=%f\r\n",alcohol);
        printf("speed=%f\r\n",speed);
        printf("Circle=%f\r\n",Circle);
        printf("mileage=%f\r\n",mileage);
        printf("total=%f\r\n",total);
        printf("Fatigue_Flag=%d\r\n",Fatigue_Flag);
        printf("Callphone_Flag=%d\r\n",Callphone_Flag);
        printf("Smoking_Flag=%d\r\n",Smoking_Flag);
        printf("Sharpacceleration=%d\r\n",Sharpacceleration);
        printf("Fatigues=%d\r\n",Fatigues);
        printf("Angle_Mode=%d\r\n",Angle_Mode);
        printf("Sharpturns=%d\r\n",Sharpturns);

*/



        if (temperature>=40) {
            show_number8();    //“车内温度异常”
        }
        if (alcohol>0.9){
            show_number2();    //“饮酒，请勿驾车”
            Delay_Ms(1000);

        }


      rate = length/speed;       //'三秒间隔'
      if (rate<1){               //车距过近
           show_number1();       //语音报警、“存在危险，请保持车距”
           Delay_Ms(500);
         }
      if (speed > 60) {
             show_number7();
            }

      if (speed>40) {
      if (Angle_Mode) {
          show_number12();//“方向盘”
        }
      }
  //K210检测数据
      if (Fatigue_Flag) {   //存在疲劳
          show_number3();        //“疲劳驾驶，请注意休息”
          }
      if (Callphone_Flag) { //接打电话
          show_number4();       //“行驶中，请勿接打电话”
           }

      if (Smoking_Flag) {    //吸烟
          show_number5();        //“行驶中，请勿抽烟”
          }
      if(Continudrive) { //连续驾驶
          show_number6();       //“连续驾驶，请注意休息”
      }
      if (Red_Flag) {
              show_number10();  //“请注意，前车刹车”
    }
      if (Yellow_Flag) {
            show_number11();     //“请注意前车转向”3
    }
   //四种灯效
       if (Light_Mode||Light_Voice)  WS281x_RainbowCycle(5);
       if (Rainbow_Mode||Rainbow_Voice) WS281x_Rainbow(5);
       if (Print_Mode||Print_Voice)  WS281x_ColorWipe(100, 20);
       if (Flash_Mpde||Flash_Voice)  WS281x_TheaterChaseRainbow(5);
       if (Close_Mode||Close_Voice)  WS281x_CloseAll();
   //闹钟
       if (alarm_flag==1) {
           show_number9();
    }
   //音乐
       if (Music_Mode) {
           show_number13();
    }
   //OneNet数据上传部分
       if(++timeCount >= 5)              //发送间隔5s
                {
                    OneNet_SendData();   //发送数据
                    timeCount = 0;
                    ESP8266_Clear();
                }
                dataPtr = ESP8266_GetIPD(0);
                if(dataPtr != NULL)
                    OneNet_RevPro(dataPtr);
                Delay_Ms(10);

            //    IWDG_ReloadCounter(); //Feed dog
    }
}

