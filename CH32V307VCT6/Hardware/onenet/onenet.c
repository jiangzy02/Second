//��Ƭ��ͷ�ļ�
#include "debug.h"

//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"
#include "MqttKit.h"

//Ӳ������
#include <string.h>
#include <stdio.h>

#include "../UART6_ESP01/UART6.h"
#include "../USART3_DMA/USART3.h"

//��ƷID��PROID����OneNETƽ̨�ϴ����Ĳ�Ʒ��Ψһ��ʶ�����������ֲ�ͬ�Ĳ�Ʒ��
#define PROID       "610694"
//��Ȩ��Ϣ��AUTH_INFO����������֤�豸��ݵ���Կ������ȷ��ֻ�о�����Ȩ���豸�������ӵ�OneNETƽ̨
#define AUTH_INFO   "test"
//�豸ID��DEVID����OneNETƽ̨�ϴ������豸��Ψһ��ʶ�����������ֲ�ͬ���豸��
#define DEVID       "1100462854"


extern unsigned char esp8266_buf[256];
extern uint16_t USART3_RxBuf[USART_MAX_LEN];   //���ջ���

//==========================================================
//  �������ƣ�   OneNet_DevLink
//
//  �������ܣ�   ��onenet��������
//
//  ��ڲ�����   ��
//
//  ���ز�����   1-�ɹ�    0-ʧ��
//
//  ˵����     ��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{

    MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};                 //Э���

    unsigned char *dataPtr;

    _Bool status = 1;

    printf("OneNet_DevLink\r\n" "PROID: %s, AUIF: %s,   DEVID:%s\r\n" , PROID, AUTH_INFO, DEVID);

    if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
    {
        ESP8266_SendData(mqttPacket._data, mqttPacket._len);            //�ϴ�ƽ̨

        dataPtr = ESP8266_GetIPD(250);                                  //�ȴ�ƽ̨��Ӧ
        if(dataPtr != NULL)
        {
            if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
            {
                switch(MQTT_UnPacketConnectAck(dataPtr))
                {
                    case 0:printf("Tips:  ���ӳɹ�\r\n");status = 0;break;

                    case 1:printf("WARN:  ����ʧ�ܣ�Э�����\r\n");break;
                    case 2:printf("WARN:  ����ʧ�ܣ��Ƿ���clientid\r\n");break;
                    case 3:printf("WARN:  ����ʧ�ܣ�������ʧ��\r\n");break;
                    case 4:printf("WARN:  ����ʧ�ܣ��û������������\r\n");break;
                    case 5:printf("WARN:  ����ʧ�ܣ��Ƿ�����(����token�Ƿ�)\r\n");break;

                    default:printf("ERR:  ����ʧ�ܣ�δ֪����\r\n");break;
                }
            }
        }

        MQTT_DeleteBuffer(&mqttPacket);                             //ɾ��
    }
    else
        printf("WARN: MQTT_PacketConnect Failed\r\n");

    return status;

}
//�������������������
extern u16 Sharpslowdown; //�����ٴ���
extern u16 Sharpacceleration;//�����ٴ���
extern u16 Fatigues; //��������
extern u16 Calls;  //��绰����
extern u16 Smokings; //���̴���
extern u8 Overspeed;//���ٴ���
extern u8 Sharpturns;

unsigned char OneNet_FillBuf(char *buf)
{

    char text[64];

    memset(text, 0, sizeof(text));

    strcpy(buf, ",;");

    memset(text, 0, sizeof(text));
    sprintf(text, "Overspeed,%d;",Overspeed);//����
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Calls,%d;",Calls);//�Ӵ�绰
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Sharpslowdown,%d;",Sharpslowdown);//������
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Sharpacceleration,%d;",Sharpacceleration);//������
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Smokings,%d;",Smokings);//����
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Fatigues,%d;",Fatigues);//����
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Sharpturns,%d;",Sharpturns);//
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Mileage,%d;",USART3_RxBuf[6]/100);//���
    strcat(buf, text);

    memset(text, 0, sizeof(text));
    sprintf(text, "Total,%d;",USART3_RxBuf[7]/100);//�ܷ�
    strcat(buf, text);


    return strlen(buf);

}

//==========================================================
//  �������ƣ�   OneNet_SendData
//
//  �������ܣ�   �ϴ����ݵ�ƽ̨
//
//  ��ڲ�����   type���������ݵĸ�ʽ
//
//  ���ز�����   ��
//
//  ˵����
//==========================================================
void OneNet_SendData(void)
{

    MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};                                             //Э���

    char buf[256];

    short body_len = 0, i = 0;

    printf("Tips: OneNet_SendData-MQTT\r\n");

    memset(buf, 0, sizeof(buf));

    body_len = OneNet_FillBuf(buf);                                                                 //��ȡ��ǰ��Ҫ���͵����������ܳ���

    if(body_len)
    {
        if(MQTT_PacketSaveData(DEVID, body_len, NULL, 5, &mqttPacket) == 0)                         //���
        {
            for(; i < body_len; i++)
                mqttPacket._data[mqttPacket._len++] = buf[i];

            ESP8266_SendData(mqttPacket._data, mqttPacket._len);                                    //�ϴ����ݵ�ƽ̨
            printf("Send %d Bytes\r\n", mqttPacket._len);

            MQTT_DeleteBuffer(&mqttPacket);                                                         //ɾ��
        }
        else
            printf("WARN: EDP_NewBuffer Failed\r\n");
    }

}

//==========================================================
//  �������ƣ�   OneNet_RevPro
//
//  �������ܣ�   ƽ̨�������ݼ��
//
//  ��ڲ�����   dataPtr��ƽ̨���ص�����
//
//  ���ز�����   ��
//
//  ˵����
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{

    MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};                             //Э���

    char *req_payload = NULL;
    char *cmdid_topic = NULL;

    unsigned short req_len = 0;

    unsigned char type = 0;

    short result = 0;

    char *dataPtr = NULL;
    char numBuf[10];
    int num = 0;

    type = MQTT_UnPacketRecv(cmd);
    switch(type)
    {
        case MQTT_PKT_CMD:                                                          //�����·�

            result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);   //���topic����Ϣ��
            if(result == 0)
            {
                printf("cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);

                if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)  //����ظ����
                {
                    printf("Tips: Send CmdResp\r\n");

                    ESP8266_SendData(mqttPacket._data, mqttPacket._len);            //�ظ�����
                    MQTT_DeleteBuffer(&mqttPacket);                                 //ɾ��
                }
            }

        break;

        case MQTT_PKT_PUBACK:                                                       //����Publish��Ϣ��ƽ̨�ظ���Ack

            if(MQTT_UnPacketPublishAck(cmd) == 0)
               printf("Tips: MQTT Publish Send OK\r\n");

        break;

        default:
            result = -1;
        break;
    }

    ESP8266_Clear();                                    //��ջ���

    if(result == -1)
        return;

    dataPtr = strchr(req_payload, '}');                 //����'}'

    if(dataPtr != NULL && result != -1)                 //����ҵ���
    {
        dataPtr++;

        while(*dataPtr >= '0' && *dataPtr <= '9')       //�ж��Ƿ����·��������������
        {
            numBuf[num++] = *dataPtr++;
        }
        numBuf[num] = 0;

        num = atoi((const char *)numBuf);               //תΪ��ֵ��ʽ
    }

    if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
    {
        MQTT_FreeBuffer(cmdid_topic);
        MQTT_FreeBuffer(req_payload);
    }

}
