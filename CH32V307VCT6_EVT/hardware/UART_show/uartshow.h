#ifndef HARDWARE_UART_SHOW_UARTSHOW_H_
#define HARDWARE_UART_SHOW_UARTSHOW_H_

void Show_Time(void);  //ʵʱʱ��
void Show_Alcohol_Normal(void);   //�ƾ�Ũ������
void Show_Alcohol_Abnormal(void);  //�ƾ�Ũ���쳣
void Show_Speed(void);  //���١����ࡢת��
void Show_Speed_Error(void);  //���೵�ٲ�ƥ��
void Show_Temp_Humi(void);   //��ʪ��
void Show_Temp_Humi_High(void); //��ʪ�ȹ���
void Fatigue_show(void);//ƣ��
void Call_show(void); //��绰
void Smoking_show(void); //����
void Overtimedriver_show(void); //��ʱ���ʻ
void Driver_show(void); //�����١������١�����
void GradeA_show(void); //�����ȼ������㡱 score=100
void GradeB_show(void); //�����ȼ����ϸ� score>=80
void GradeC_show(void); //�����ȼ������ϸ� score<80
void Hundred_show(void); //�ְܷ�λ
void Ten_show(void); //�ܷ�ʮλ
void One_show(void); //�ָܷ�λ

#endif /* HARDWARE_UART_SHOW_UARTSHOW_H_ */
