/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/
#include <stdlib.h>
#include "debug.h"
#include "MPU6050IIC.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "math.h"
#include "USART2.h"
#include "TIM2.h"
#include "nmswj.h"
#include "UART4.h"
#include "IWDG.h"
//����ŷ����
float Pitch,Roll,Yaw;        //ŷ����
short Aacx,Aacy,Aacz;       //���ٶȴ�����ԭʼ����
short Gyrox,Gyroy,Gyroz;    //������ԭʼ����
float new_roll;
short temp;

//���߷�ʽ
//iic  PB6-scl PB7-sda
//��λ�� ����4 PC10-TX
//�������ݸ������� ����2 PA2-TX
// ���巽����ת���Ƕȴ�����ֵ�����ͱ�־λ
//extern uint8_t roll_flag; // ��־����
//extern float angle_change;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);//��ӡ����
	Usart4_Init(256000);//����ŷ�������ݵ���λ��;
	MPU_Init();
	mpu_dmp_init();
    Init_UART2();//������115200�����ͱ�ʶ����������
    TIM2_init();//һ�������жϣ�����һ���ڽǶȵı仯
    IWDG_Feed_Init(32, 2000);//��1.5����û��ι����������ϵͳ
   // Delay_Ms(100);

	while(1)
    {
	    //printf("111\r\n");

	       //�õ�ŷ���ǣ����ô���һ���͵���λ��
	        MPU_Get_Accelerometer(&Aacx,&Aacy,&Aacz);   //�õ����ٶȴ���������
	        MPU_Get_Gyroscope(&Gyrox,&Gyroy,&Gyroz);    //�õ�����������

	        while(mpu_dmp_get_data(&Pitch, &Roll, &Yaw)!=0){

           }
	            printf("roll=%f\r\n",Roll);
	       // printf("111\r\n");
            //printf("aacx is:%d,aacy=%d,aacz=%d \r\n",Aacx,Aacy,Aacz);


          //������λ���汾1
            mpu6050_send_data(Aacx,Aacy,Aacz,Gyrox,Gyroy,Gyroz);
            usart4_report_imu(Aacx,Aacy,Aacz,Gyrox,Gyroy,Gyroz,(int)(Roll*100),(int)(Pitch*100),(int)(Yaw*10));//����2

            //������λ���汾2
          //  SEND_OULA_ANGLE((short)(Roll*100),(short)(-Pitch*100),(short)(-Yaw*100));
            Delay_Ms(100);

           //ͨ����ʱ��仯ֵ��һ���󵼵Ʒ�����˲ʱ�Ƕȱ仯

           if(Roll<0&&Roll>-180){
               new_roll=Roll+360;}
            //�ﵽĳЩ����ʱ����Ϣ���͸�����
            if(Roll>=0&&Roll<=180) {
              new_roll=Roll;
        }
           IWDG_ReloadCounter(); //Feed dog
  }
}

