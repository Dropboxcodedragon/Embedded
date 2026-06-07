/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "semphr.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myledTask02 */
osThreadId_t myledTask02Handle;
const osThreadAttr_t myledTask02_attributes = {
  .name = "myledTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/******************************************************************************************************/
QueueHandle_t semphore_handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartledTask02(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
//    semphore_handle = xSemaphoreCreateBinary();/* 创建型信号量 */
		semphore_handle = xSemaphoreCreateCounting(10000 , 0);  /* 创建计数型信号量 */

    if(semphore_handle != NULL)
    {
    }
		/* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myledTask02 */
  myledTask02Handle = osThreadNew(StartledTask02, NULL, &myledTask02_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
	uint32_t i = 0,j = 0;
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
    BaseType_t err;
  /* Infinite loop */
  for(;;)
  {
		//
//			if(semphore_handle != NULL)
//			{
//					err = xSemaphoreGive(semphore_handle);
//					if(err == pdPASS)
//					{
//						i++;
//					}
//					else 
//					{
//						j++;
//					}
//			}
			//
			if(semphore_handle != NULL)
			{
					xSemaphoreGive(semphore_handle);      /* 释放信号量 */
			}
			osDelay(250);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartledTask02 */
/**
* @brief Function implementing the myledTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartledTask02 */
void StartledTask02(void *argument)
{
  /* USER CODE BEGIN StartledTask02 */
    uint32_t rev = 0;
    BaseType_t err;
  /* Infinite loop */
  for(;;)
  {
		//
//        err = xSemaphoreTake(semphore_handle,portMAX_DELAY); /* 获取信号量并死等 */
//        if(err == pdTRUE)
//        {
//					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
//        }
//				else 
//				{
//					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
//				}
			//
				err = xSemaphoreTake(semphore_handle,portMAX_DELAY); /* 获取信号量并死等 */
        if(err == pdTRUE)
        {
           i = uxSemaphoreGetCount(semphore_handle);
						if(i%2 == 0)
						{
							HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
						}
        }
				osDelay(500);
  }
  /* USER CODE END StartledTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

