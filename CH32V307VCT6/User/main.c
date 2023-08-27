#include "debug.h"
#include "JQ8900.h"
#include "WS2812.h"
#include "esp8266.h"
#include "onenet.h"
#include "../Hardware/UART6_ESP01/UART6.h"
#include "../Hardware/USART2_TWAsr/usart2.h"
#include "../Hardware/USART3_DMA/USART3.h"

//���ֵ�Ч(����������)
u16 Light_Mode;
u16 Rainbow_Mode;
u16 Print_Mode;
u16 Flash_Mpde;
u16 Close_Mode;//�ص�
//���ֵ�Ч���������ƣ�
extern u16 Light_Voice;
extern u16 Rainbow_Voice;
extern u16 Print_Voice;
extern u16 Flash_Voice;
extern u16 Music_Mode;//���ֲ���
extern u16 Close_Voice;//�ص�
u16 Continudrive; //������ʻ��־
u16 Fatigue_Flag;//��ֵΪ0ʱ��������״̬����ֵΪ1ʱ��ƣ��״̬
u16 Callphone_Flag;//��ֵΪ0ʱ����δ�Ӵ�绰״̬����ֵΪ1ʱ�Ǵ�绰״̬
u16 Smoking_Flag;//��ֵΪ0ʱ����δ����״̬����ֵΪ1ʱ������״̬
u16 Sharpslowdown; //�����ٴ���
u16 Sharpacceleration;//�����ٴ���
u16 Sharpturns;
u16 Fatigues; //��������
u16 Calls;  //��绰����
u16 Smokings; //���̴���
u8 Overspeed=0;//���ٴ���
u8 Speed_Flag=0; //���ٱ�ʶ
u16 alarm_flag;
u16 Angle_Mode;  //��ת���־
u16 Red_Flag;    //ǰ��β�Ʊ��
u16 Yellow_Flag; //ǰ��β�Ʊ��


extern uint16_t USART3_RxBuf[USART_MAX_LEN];   //���ջ���
float alcohol,length,temperature,humidity,speed,Circle,mileage,rate,total;
/*****************************
USART2����λ��USART3ͨ��  PD9��PC12,PD8��PD2
WS2812:PA1 ---TIM5 5V
JQ8900��PD10��һ�ߴ���Z���� 5v
�����������֣�USART2-RX  5v
******************************/

int main(void)
{
    unsigned short timeCount = 0;    //���ͼ������
    unsigned char *dataPtr = NULL;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);  //��ӡ���Դ���
    WS281x_Init();
    uart3_init(115200);//������������������ݵĴ���
    DMA_RX_init();
    OnUart_GPIO();
    usart2_init(9600); //����
   // IWDG_Feed_Init(IWDG_Prescaler_32, 8000); // 3.2s IWDG reset
    Usart6_Init(115200);//esp8266����
    ESP8266_Init();                 //��ʼ��ESP8266
    while(OneNet_DevLink())         //����OneNET
    Delay_Ms(500);
while(1)
    {
        USART3_Server();//����DMA�������������������
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
        Angle_Mode     =USART3_RxBuf[23];//��ת��
        Red_Flag       =USART3_RxBuf[24];
        Yellow_Flag    =USART3_RxBuf[25];
        Sharpturns     =USART3_RxBuf[26];//��ת�����
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
            show_number8();    //�������¶��쳣��
        }
        if (alcohol>0.9){
            show_number2();    //�����ƣ�����ݳ���
            Delay_Ms(1000);

        }


      rate = length/speed;       //'������'
      if (rate<1){               //�������
           show_number1();       //����������������Σ�գ��뱣�ֳ��ࡱ
           Delay_Ms(500);
         }
      if (speed > 60) {
             show_number7();
            }

      if (speed>40) {
      if (Angle_Mode) {
          show_number12();//�������̡�
        }
      }
  //K210�������
      if (Fatigue_Flag) {   //����ƣ��
          show_number3();        //��ƣ�ͼ�ʻ����ע����Ϣ��
          }
      if (Callphone_Flag) { //�Ӵ�绰
          show_number4();       //����ʻ�У�����Ӵ�绰��
           }

      if (Smoking_Flag) {    //����
          show_number5();        //����ʻ�У�������̡�
          }
      if(Continudrive) { //������ʻ
          show_number6();       //��������ʻ����ע����Ϣ��
      }
      if (Red_Flag) {
              show_number10();  //����ע�⣬ǰ��ɲ����
    }
      if (Yellow_Flag) {
            show_number11();     //����ע��ǰ��ת��3
    }
   //���ֵ�Ч
       if (Light_Mode||Light_Voice)  WS281x_RainbowCycle(5);
       if (Rainbow_Mode||Rainbow_Voice) WS281x_Rainbow(5);
       if (Print_Mode||Print_Voice)  WS281x_ColorWipe(100, 20);
       if (Flash_Mpde||Flash_Voice)  WS281x_TheaterChaseRainbow(5);
       if (Close_Mode||Close_Voice)  WS281x_CloseAll();
   //����
       if (alarm_flag==1) {
           show_number9();
    }
   //����
       if (Music_Mode) {
           show_number13();
    }
   //OneNet�����ϴ�����
       if(++timeCount >= 5)              //���ͼ��5s
                {
                    OneNet_SendData();   //��������
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

