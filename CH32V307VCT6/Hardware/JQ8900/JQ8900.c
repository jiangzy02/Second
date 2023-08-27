#include "JQ8900.h"
#include "debug.h"
#include <stdint.h>


//函   OnUart_GPIO(void)
//功   能：语音模块一线串口IO口
//输入参数: void
//输出参数: void
//说   明：

void OnUart_GPIO(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_ResetBits(GPIOD, GPIO_Pin_10);//将PC4的引脚拉低
    GPIO_Init(GPIOD, &GPIO_InitStructure);


}


void delay1_us(u32 nTimer)
{
    u32 i=0;
    for(i=0;i<nTimer;i++){
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
        __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    }
}

//
//函   数：SendData(u8 adder)
//功   能：语音模块一线串口
//输入参数: adder要发送的0x数
//输出参数: void
//说   明：
//
void SendData(u8 addr)//发送函数。
{
    u8 i;
     /*发送时关掉中断，防止中断影响时序  */
    GPIO_WriteBit(GPIOD, GPIO_Pin_10, SET); /*开始拉高*/
    Delay_Us(1000);
    GPIO_WriteBit(GPIOD, GPIO_Pin_10, RESET); /*开始引导码*/
    Delay_Us(3200);/*此处延时最少要大于2ms*/
    for ( i = 0; i < 8; i++ ) /*总共8位数据  */
    {
        GPIO_WriteBit(GPIOD, GPIO_Pin_10, SET);
        if ( addr & 0x01 ) /*3:1表示数据位1,每个位用两个脉冲表示  */
        {
            Delay_Us(600);
            GPIO_WriteBit(GPIOD, GPIO_Pin_10, RESET);
            Delay_Us(200);
        }
        else              /*1：3表示数据位0 ,每个位用两个脉冲表示  */
        {
            Delay_Us(200);
            GPIO_WriteBit(GPIOD, GPIO_Pin_10, RESET);
            Delay_Us(600);
        }
        addr >>= 1;
    }
    GPIO_WriteBit(GPIOD, GPIO_Pin_10, SET);
       //恢复中断
}


void show_number1(void)//00001.mp3，“存在危险，请保持车距”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1200);
    //选取曲目1播放
    SendData(0x0a);//清空数字
    SendData(0x01);//曲目数字，对应00001.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1700);
    //开始播放
}

void show_number2(void)//00002.mp3，语音报警“饮酒，请勿驾车”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(800);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x02);//曲目数字，对应00002.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1200);
    //开始播放
}

void show_number3(void)//00003.mp3，语音报警“疲劳驾驶，请注意休息”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1200);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x03);//曲目数字，对应00003.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
}

void show_number4(void)//00004.mp3，语音报警“行驶中，请勿接打电话”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1200);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x04);//曲目数字，对应00004.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
}


void show_number5(void)//00005.mp3，语音报警“行驶中，请勿抽烟”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x05);//曲目数字，对应00005.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}


void show_number6(void)//00006.mp3，“连续驾驶，请注意休息”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x06);//曲目数字，对应00006.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

void show_number7(void)//00007.mp3，“您已超速，请注意安全”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x07);//曲目数字，对应00007.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

void show_number8(void)//00007.mp3，“车内温度异常”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(800);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x08);//曲目数字，对应00008.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1300);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

void show_number9(void)//00007.mp3，“定时时间到，请注意”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x09);//曲目数字，对应00009.mp3
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

void show_number10(void)//00007.mp3，“前车刹车，请注意” yellow
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x0001);//曲目数字，对应00010.mp3
    SendData(0x0000);
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

void show_number11(void)//00007.mp3，“请注意前车” red
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x0001);//曲目数字，对应00011.mp3
    SendData(0x0001);
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

void show_number12(void)//“危险驾驶，请注意”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x0001);//曲目数字，对应00010.mp3
    SendData(0x0002);
    SendData(0x0b);//选曲播放
    Delay_Ms(1500);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

void show_number13(void)//“15s音乐”
{
    //设置音量为20
    SendData(0x0a);    //清空数字
    SendData(0x02);    //音量20
    SendData(0x00);
    SendData(0x0c);    //设置音量
    Delay_Ms(1000);
    //选取曲目2播放
    SendData(0x0a);//清空数字
    SendData(0x0001);//曲目数字，对应00010.mp3
    SendData(0x0003);
    SendData(0x0b);//选曲播放
    Delay_Ms(15000);
    //开始播放
    //SendData(0x11);//开始播放
    //delay1_ms(2000);
}

