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
//定义欧拉角
float Pitch,Roll,Yaw;        //欧拉角
short Aacx,Aacy,Aacz;       //加速度传感器原始数据
short Gyrox,Gyroy,Gyroz;    //陀螺仪原始数据
float new_roll;
short temp;

//接线方式
//iic  PB6-scl PB7-sda
//上位机 串口4 PC10-TX
//发送数据给评估板 串口2 PA2-TX
// 定义方向盘转动角度大于阈值，发送标志位
//extern uint8_t roll_flag; // 标志变量
//extern float angle_change;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);//打印调试
	Usart4_Init(256000);//发送欧拉角数据到上位机;
	MPU_Init();
	mpu_dmp_init();
    Init_UART2();//波特率115200，发送标识符到评估板
    TIM2_init();//一秒的溢出中断，计算一秒内角度的变化
    IWDG_Feed_Init(32, 2000);//若1.5秒内没有喂狗，则重启系统
   // Delay_Ms(100);

	while(1)
    {
	    //printf("111\r\n");

	       //得到欧拉角，并用串口一发送到上位机
	        MPU_Get_Accelerometer(&Aacx,&Aacy,&Aacz);   //得到加速度传感器数据
	        MPU_Get_Gyroscope(&Gyrox,&Gyroy,&Gyroz);    //得到陀螺仪数据

	        while(mpu_dmp_get_data(&Pitch, &Roll, &Yaw)!=0){

           }
	            printf("roll=%f\r\n",Roll);
	       // printf("111\r\n");
            //printf("aacx is:%d,aacy=%d,aacz=%d \r\n",Aacx,Aacy,Aacz);


          //匿名上位机版本1
            mpu6050_send_data(Aacx,Aacy,Aacz,Gyrox,Gyroy,Gyroz);
            usart4_report_imu(Aacx,Aacy,Aacz,Gyrox,Gyroy,Gyroz,(int)(Roll*100),(int)(Pitch*100),(int)(Yaw*10));//代码2

            //匿名上位机版本2
          //  SEND_OULA_ANGLE((short)(Roll*100),(short)(-Pitch*100),(short)(-Yaw*100));
            Delay_Ms(100);

           //通过短时间变化值、一阶求导灯方法求瞬时角度变化

           if(Roll<0&&Roll>-180){
               new_roll=Roll+360;}
            //达到某些条件时将信息发送给板子
            if(Roll>=0&&Roll<=180) {
              new_roll=Roll;
        }
           IWDG_ReloadCounter(); //Feed dog
  }
}

