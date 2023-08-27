#ifndef HARDWARE_UART_SHOW_UARTSHOW_H_
#define HARDWARE_UART_SHOW_UARTSHOW_H_

void Show_Time(void);  //实时时钟
void Show_Alcohol_Normal(void);   //酒精浓度正常
void Show_Alcohol_Abnormal(void);  //酒精浓度异常
void Show_Speed(void);  //车速、车距、转速
void Show_Speed_Error(void);  //车距车速不匹配
void Show_Temp_Humi(void);   //温湿度
void Show_Temp_Humi_High(void); //温湿度过高
void Fatigue_show(void);//疲劳
void Call_show(void); //打电话
void Smoking_show(void); //抽烟
void Overtimedriver_show(void); //长时间驾驶
void Driver_show(void); //急加速、急减速、超速
void GradeA_show(void); //评估等级“优秀” score=100
void GradeB_show(void); //评估等级“合格” score>=80
void GradeC_show(void); //评估等级“不合格” score<80
void Hundred_show(void); //总分百位
void Ten_show(void); //总分十位
void One_show(void); //总分个位

#endif /* HARDWARE_UART_SHOW_UARTSHOW_H_ */
