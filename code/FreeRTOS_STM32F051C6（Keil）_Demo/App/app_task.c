
#include "app_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"


/************************************************
函数名称 ： vAppTask1
功    能 ： 应用任务1
参    数 ： pvParameters --- 可选参数
返 回 值 ： 无
*************************************************/
void vAppTask1(void *pvParameters)
{
  for(;;)
  {
    LED1_TOGGLE;
    vTaskDelay(50);
  }
}

/************************************************
函数名称 ： vAppTask2
功    能 ： 应用任务2
参    数 ： pvParameters --- 可选参数
返 回 值 ： 无
*************************************************/
void vAppTask2(void *pvParameters)
{
  for(;;)
  {
    LED2_TOGGLE;
    vTaskDelay(100);
  }
}

/************************************************
函数名称 ： vAppTask3
功    能 ： 应用任务3
参    数 ： pvParameters --- 可选参数
返 回 值 ： 无
*************************************************/
void vAppTask3(void *pvParameters)
{
  for(;;)
  {
    LED3_TOGGLE;
    vTaskDelay(150);
  }
}

/************************************************
函数名称 ： vAppTask4
功    能 ： 应用任务4
参    数 ： pvParameters --- 可选参数
返 回 值 ： 无
*************************************************/
void vAppTask4(void *pvParameters)
{
  for(;;)
  {
    LED4_TOGGLE;
    vTaskDelay(200);
  }
}


