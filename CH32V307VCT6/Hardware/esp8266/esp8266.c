//��Ƭ��ͷ�ļ�
#include "debug.h"
//�����豸����
#include "esp8266.h"
//Ӳ������
#include <string.h>
#include <stdio.h>

#include "../UART6_ESP01/UART6.h"
//AT+CWJAPָ����������WiFi���磬����Ĳ����У�ONENET��ʾWiFi��������ƣ���IOT@Chinamobile123����WiFi��������롣
#define ESP8266_WIFI_INFO       "AT+CWJAP=\"OEN\",\"12345678\"\r\n"
//AT+CIPSTARTָ����������TCP������������Ĳ����У�TCP��ʾʹ��TCPЭ�����ӷ�������183.230.40.39��ʾOneNET��������IP��ַ����6002����OneNET�������Ķ˿ںš�
#define ESP8266_ONENET_INFO     "AT+CIPSTART=\"TCP\",\"183.230.40.39\",6002\r\n"
//���ջ�������С
unsigned char esp8266_buf[256];
//cnt�ǽ��ռ�����
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;


//==========================================================
//  �������ƣ�   ESP8266_Clear
//
//  �������ܣ�   ��ջ���
//
//  ��ڲ�����   ��
//
//  ���ز�����   ��
//
//  ˵����
//==========================================================
void ESP8266_Clear(void)
{

    memset(esp8266_buf, 0, sizeof(esp8266_buf));
    esp8266_cnt = 0;

}

//==========================================================
//  �������ƣ�   ESP8266_WaitRecive
//
//  �������ܣ�   �ȴ��������
//
//  ��ڲ�����   ��
//
//  ���ز�����   REV_OK-�������     REV_WAIT-���ճ�ʱδ���
//
//  ˵����     ѭ�����ü���Ƿ�������
//==========================================================
_Bool ESP8266_WaitRecive(void)
{

    if(esp8266_cnt == 0)                            //������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
        return REV_WAIT;

    if(esp8266_cnt == esp8266_cntPre)               //�����һ�ε�ֵ�������ͬ����˵���������
    {
        esp8266_cnt = 0;                            //��0���ռ���

        return REV_OK;                              //���ؽ�����ɱ�־
    }

    esp8266_cntPre = esp8266_cnt;                   //��Ϊ��ͬ

    return REV_WAIT;                                //���ؽ���δ��ɱ�־

}

//==========================================================
//  �������ƣ�   ESP8266_SendCmd
//
//  �������ܣ�   ��������
//
//  ��ڲ�����   cmd������
//              res����Ҫ���ķ���ָ��
//
//  ���ز�����   0-�ɹ�    1-ʧ��
//
//  ˵����
//==========================================================
_Bool ESP8266_SendCmd(char *cmd, char *res)
{

    unsigned char timeOut = 200;

    Usart_SendString(UART6, (unsigned char *)cmd, strlen((const char *)cmd));

    while(timeOut--)
    {
        if(ESP8266_WaitRecive() == REV_OK)                          //����յ�����
        {
            if(strstr((const char *)esp8266_buf, res) != NULL)      //����������ؼ���
            {
                ESP8266_Clear();                                    //��ջ���

                return 0;
            }
        }

        //DelayXms(10);
        Delay_Ms(10);
    }

    return 1;

}

//==========================================================
//  �������ƣ�   ESP8266_SendData
//
//  �������ܣ�   ��������
//
//  ��ڲ�����   data������
//              len������
//
//  ���ز�����   ��
//
//  ˵����
//==========================================================
void ESP8266_SendData(unsigned char *data, unsigned short len)
{

    char cmdBuf[32];

    ESP8266_Clear();                                //��ս��ջ���
    sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);      //��������
    if(!ESP8266_SendCmd(cmdBuf, ">"))               //�յ���>��ʱ���Է�������
    {
        Usart_SendString(UART6, data, len);        //�����豸������������
    }

}

//==========================================================
//  �������ƣ�   ESP8266_GetIPD
//
//  �������ܣ�   ��ȡƽ̨���ص�����
//
//  ��ڲ�����   �ȴ���ʱ��(����10ms)
//
//  ���ز�����   ƽ̨���ص�ԭʼ����
//
//  ˵����     ��ͬ�����豸���صĸ�ʽ��ͬ����Ҫȥ����
//              ��ESP8266�ķ��ظ�ʽΪ  "+IPD,x:yyy"    x�������ݳ��ȣ�yyy����������
//==========================================================
unsigned char *ESP8266_GetIPD(unsigned short timeOut)
{
    char *ptrIPD = NULL;
    do
    {
        if(ESP8266_WaitRecive() == REV_OK)                              //����������
        {
            ptrIPD = strstr((char *)esp8266_buf, "IPD,");               //������IPD��ͷ
            if(ptrIPD == NULL)                                          //���û�ҵ���������IPDͷ���ӳ٣�������Ҫ�ȴ�һ�ᣬ�����ᳬ���趨��ʱ��
            {
            }
            else
            {
                ptrIPD = strchr(ptrIPD, ':');                           //�ҵ�':'
                if(ptrIPD != NULL)
                {
                    ptrIPD++;
                    return (unsigned char *)(ptrIPD);
                }
                else
                    return NULL;
            }
        }
        Delay_Ms(5); //��ʱ�ȴ�
    } while(timeOut--);

    return NULL;                                                        //��ʱ��δ�ҵ������ؿ�ָ��

}
//==========================================================
//  �������ƣ�   ESP8266_Init
//
//  �������ܣ�   ��ʼ��ESP8266
//
//  ��ڲ�����   ��
//
//  ���ز�����   ��
//
//  ˵����
//==========================================================
void ESP8266_Init(void)
{
    ESP8266_Clear();
    printf("1. AT\r\n");
    while(ESP8266_SendCmd("AT\r\n", "OK"))//����ָ��
    Delay_Ms(500);
    printf("2. CWMODE\r\n");
    while(ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK"))//����STAģʽ
    Delay_Ms(500);
    printf("3. AT+CWDHCP\r\n");
    while(ESP8266_SendCmd("AT+CWDHCP=1,1\r\n", "OK"))//
    Delay_Ms(500);
    printf("4. CWJAP\r\n");
    while(ESP8266_SendCmd(ESP8266_WIFI_INFO, "GOT IP"))
    Delay_Ms(500);
    printf("5. CIPSTART\r\n");
    while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
    Delay_Ms(500);
    printf("6. ESP8266 Init OK\r\n");
}

__attribute__((interrupt("WCH-Interrupt-fast")))
void UART6_IRQHandler(void)
{

    if(USART_GetITStatus(UART6, USART_IT_RXNE) != RESET) //�����ж�
    {
        if(esp8266_cnt >= sizeof(esp8266_buf))  esp8266_cnt = 0; //��ֹ���ڱ�ˢ��
        esp8266_buf[esp8266_cnt++] = UART6->DATAR;

        USART_ClearFlag(UART6, USART_FLAG_RXNE);

    }
}
