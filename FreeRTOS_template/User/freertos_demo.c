#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
/*FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"

/*FreeRTOS配置*/

//START_TASK 任务 配置
//包括: 任务句柄 任务优先级 堆栈大小 创建任务

//任务栈的深度，即任务可用的内存大小
#define START_TASK_STACK_SIZE  128 //128是字，128*4才是字节，偏大的定义

//任务优先级
#define START_TASK_PRIO 				1

//任务句柄
TaskHandle_t start_task_handler;
void Start_Task(void*pvParameters);//函数声明

#define TASK1_STACK_SIZE  128 //128是字，128*4才是字节，偏大的定义
#define TASK1_PRIO 				 2
TaskHandle_t task1_handler;
void Task1(void*pvParameters);

#define TASK2_STACK_SIZE  128 //128是字，128*4才是字节，偏大的定义
#define TASK2_PRIO 				3
TaskHandle_t task2_handler;
void Task2(void*pvParameters);

#define TASK3_STACK_SIZE  128 //128是字，128*4才是字节，偏大的定义
#define TASK3_PRIO 				4
TaskHandle_t task3_handler;
void Task3(void*pvParameters);
 
/********************************************** 
  @brief       FreeRTOS例程入口函数
  @param(参数)       无
  @retval（返回值）  无
	*********************************************/
void freertos_demo(void) //入口函数
{
	xTaskCreate((TaskFunction_t 				)	Start_Task,//任务的入口函数，即任务的代码将从这个函数开始执行。
							(char *  								)	"Start_Task",    //任务的         名称，以字符串形式表示。
							(configSTACK_DEPTH_TYPE ) START_TASK_STACK_SIZE,//任务栈的深度，即任务可用的内存大小。
							(void * 								) NULL,//传递给任务的参数，可以是任意类型的指针。
							(UBaseType_t						) START_TASK_PRIO,  //任务的优先级，值越高表示优先级越高。
							(TaskHandle_t * 				) &start_task_handler );//指向任务句柄的指针，用于获取任务的句柄。
   
	vTaskStartScheduler(); //开启任务调度器函数，创建完任务后这个函数必须开启
}


void Start_Task(void*pvParameters)
{
	taskENTER_CRITICAL();//进入临界区---关闭中断
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
							
	vTaskDelete(NULL);//可以是NULL 也可以是任务句柄 start_task_handler
	taskEXIT_CRITICAL();//退出临界区---创建完退出后才开始任务调度 按优先级高开始执行
}

/*任务一 实现LED0每500ms翻转一次*/
void Task1(void*pvParameters)
{
	while(1)
	{
		printf("Task1! \r\n");
		LED0_TOGGLE();
		vTaskDelay(500);
	}
}

/*任务二 实现LED1每500ms翻转一次*/	
void Task2(void*pvParameters)
{
	while(1)
	{
		printf("Task2! \r\n");
		LED1_TOGGLE();
		vTaskDelay(500);	
	}
}

/*任务三 按键KEY1按下删除Task1*/	
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
				printf("删除task1\r\n");
				vTaskDelete(task1_handler);
				task1_handler=0;
			}
			
		}
		vTaskDelay(10);	
	}
}


	
