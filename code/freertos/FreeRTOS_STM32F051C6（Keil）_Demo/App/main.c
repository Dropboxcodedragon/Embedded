
/*----------------------------------------------------------------------------

  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "bsp.h"
#include "task.h"
#include "app_task.h"


/* 宏定义 --------------------------------------------------------------------*/
#define TASK1_STACK_SIZE          128
#define TASK1_PRIORITY            1

#define TASK2_STACK_SIZE          128
#define TASK2_PRIORITY            2

#define TASK3_STACK_SIZE          128
#define TASK3_PRIORITY            3

#define TASK4_STACK_SIZE          128
#define TASK4_PRIORITY            4


/************************************************
函数名称 ： SysInit
功    能 ： 系统初始化
参    数 ： 无
返 回 值 ： 无
*************************************************/
void SysInit(void)
{
  BSP_Initializes();
}

/************************************************
函数名称 ： AppTaskCreate
功    能 ： 创建任务
参    数 ： 无
返 回 值 ： 无
*************************************************/
void AppTaskCreate(void)
{
  xTaskCreate(vAppTask1, "Task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, NULL);
  xTaskCreate(vAppTask2, "Task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, NULL);
  xTaskCreate(vAppTask3, "Task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, NULL);
  xTaskCreate(vAppTask4, "Task4", TASK4_STACK_SIZE, NULL, TASK4_PRIORITY, NULL);
}

/************************************************
函数名称 ： main
功    能 ： 主函数入口
参    数 ： 无
返 回 值 ： int
*************************************************/
int main(void)
{
  /* 1、SYS初始化 */
  SysInit();

  /* 2、创建任务 */
  AppTaskCreate();

  /* 3、开启任务 */
  vTaskStartScheduler();

  return 0;
}


