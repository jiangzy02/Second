#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
/*FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"

/*FreeRTOS����*/

//START_TASK ���� ����
//����: ������ �������ȼ� ��ջ��С ��������

//����ջ����ȣ���������õ��ڴ��С
#define START_TASK_STACK_SIZE  128 //128���֣�128*4�����ֽڣ�ƫ��Ķ���

//�������ȼ�
#define START_TASK_PRIO 				1

//������
TaskHandle_t start_task_handler;
void Start_Task(void*pvParameters);//��������

#define TASK1_STACK_SIZE  128 //128���֣�128*4�����ֽڣ�ƫ��Ķ���
#define TASK1_PRIO 				 2
TaskHandle_t task1_handler;
void Task1(void*pvParameters);

#define TASK2_STACK_SIZE  128 //128���֣�128*4�����ֽڣ�ƫ��Ķ���
#define TASK2_PRIO 				3
TaskHandle_t task2_handler;
void Task2(void*pvParameters);

#define TASK3_STACK_SIZE  128 //128���֣�128*4�����ֽڣ�ƫ��Ķ���
#define TASK3_PRIO 				4
TaskHandle_t task3_handler;
void Task3(void*pvParameters);
 
/********************************************** 
  @brief       FreeRTOS������ں���
  @param(����)       ��
  @retval������ֵ��  ��
	*********************************************/
void freertos_demo(void) //��ں���
{
	xTaskCreate((TaskFunction_t 				)	Start_Task,//�������ں�����������Ĵ��뽫�����������ʼִ�С�
							(char *  								)	"Start_Task",    //�����         ���ƣ����ַ�����ʽ��ʾ��
							(configSTACK_DEPTH_TYPE ) START_TASK_STACK_SIZE,//����ջ����ȣ���������õ��ڴ��С��
							(void * 								) NULL,//���ݸ�����Ĳ������������������͵�ָ�롣
							(UBaseType_t						) START_TASK_PRIO,  //��������ȼ���ֵԽ�߱�ʾ���ȼ�Խ�ߡ�
							(TaskHandle_t * 				) &start_task_handler );//ָ����������ָ�룬���ڻ�ȡ����ľ����
   
	vTaskStartScheduler(); //����������������������������������������뿪��
}


void Start_Task(void*pvParameters)
{
	taskENTER_CRITICAL();//�����ٽ���---�ر��ж�
	xTaskCreate((TaskFunction_t 				)	Task1,
							(char *  								)	"Task1",    
							(configSTACK_DEPTH_TYPE ) TASK1_STACK_SIZE,
							(void * 								) NULL,
							(UBaseType_t						) TASK1_PRIO, 
							(TaskHandle_t * 				) &task1_handler );
							
	xTaskCreate((TaskFunction_t 				)	Task2,
							(char *  								)	"Task2",    
							(configSTACK_DEPTH_TYPE ) TASK2_STACK_SIZE,
							(void * 								) NULL,
							(UBaseType_t						) TASK2_PRIO, 
							(TaskHandle_t * 				) &task2_handler );
							
	xTaskCreate((TaskFunction_t 				)	Task3,
							(char *  								)	"Task3",    
							(configSTACK_DEPTH_TYPE ) TASK3_STACK_SIZE,
							(void * 								) NULL,
							(UBaseType_t						) TASK3_PRIO, 
							(TaskHandle_t * 				) &task3_handler );
							
	vTaskDelete(NULL);//������NULL Ҳ������������ start_task_handler
	taskEXIT_CRITICAL();//�˳��ٽ���---�������˳���ſ�ʼ������� �����ȼ��߿�ʼִ��
}

/*����һ ʵ��LED0ÿ500ms��תһ��*/
void Task1(void*pvParameters)
{
	while(1)
	{
		printf("Task1! \r\n");
		LED0_TOGGLE();
		vTaskDelay(500);
	}
}

/*����� ʵ��LED1ÿ500ms��תһ��*/	
void Task2(void*pvParameters)
{
	while(1)
	{
		printf("Task2! \r\n");
		LED1_TOGGLE();
		vTaskDelay(500);	
	}
}

/*������ ����KEY1����ɾ��Task1*/	
void Task3(void*pvParameters)
{
	uint8_t key0 = 0;
	while(1)
	{
		printf("task3!\r\n");
		key0 = key_scan(0);
		if(key0 == KEY0_PRES)
		{
			if(task1_handler != NULL)
			{
				printf("ɾ��task1\r\n");
				vTaskDelete(task1_handler);
				task1_handler=0;
			}
			
		}
		vTaskDelay(10);	
	}
}


	
