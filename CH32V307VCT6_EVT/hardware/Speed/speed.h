#ifndef HARDWARE_SPEED_SPEED_H_
#define HARDWARE_SPEED_SPEED_H_


void MOTOR_Init();
void TIM3_PWM_Init(u16 arr,u16 psc);
uint16_t CountSensor_Get(void);
void GD_inIt(void);
void TIM2_inIt(void);

#endif /* HARDWARE_SPEED_SPEED_H_ */
