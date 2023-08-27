#ifndef __JQ8900_H
#define __JQ8900_H

#include "debug.h"

void SendData ( u8 addr );    //发送函数。
void OnUart_GPIO(void);       //GPIO
void delay1_us(u32 nTimer);
void show_number1(void);//“存在危险，请保持车距”
void show_number2(void);//“饮酒，请勿驾车”
void show_number3(void);//“疲劳驾驶，请注意休息”
void show_number4(void);//“行驶中，请勿接打电话”
void show_number5(void);//“行驶中，请勿抽烟”
void show_number6(void);//“连续驾驶，请注意休息”
void show_number7(void);//“您已超速，请注意安全”
void show_number8(void);//“车内温度异常”
void show_number9(void);//“定时时间时间到，请注意”
void show_number10(void);//“前车刹车，请注意”
void show_number11(void);//“请注意前车”
void show_number12(void);//“危险驾驶，请注意”
void show_number13(void);//"15s音乐"

#endif

