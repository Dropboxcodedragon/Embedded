/* USER CODE BEGIN Header */
/*
 * FreeRTOS Kernel V10.3.1
 * Portion Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Portion Copyright (C) 2019 StMicroelectronics, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */
/* USER CODE END Header */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * These parameters and more are described within the 'configuration' section of the
 * FreeRTOS API documentation available on the FreeRTOS.org web site.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* USER CODE BEGIN Includes */
/* Section where include file can be added */
/* USER CODE END Includes */

/* Ensure definitions are only used by the compiler, and not by the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
  #include <stdint.h>
  extern uint32_t SystemCoreClock;
#endif
#ifndef CMSIS_device_header
#define CMSIS_device_header "stm32f4xx.h"
#endif /* CMSIS_device_header */

/* FPU (浮点运算单元)使能配置
 * 0 - 禁用FPU
 * 1 - 启用FPU
 * 当前配置：禁用FPU功能 */
#define configENABLE_FPU                         0

/* MPU (内存保护单元)使能配置
 * 0 - 禁用MPU
 * 1 - 启用MPU
 * 当前配置：禁用MPU功能 */
#define configENABLE_MPU                         0

/* 调度器类型配置
 * 0 - 使用协作式调度器
 * 1 - 使用抢占式调度器
 * 当前配置：使用抢占式调度器 */
#define configUSE_PREEMPTION                     1

/* 静态内存分配支持配置
 * 0 - 不支持静态内存分配
 * 1 - 支持静态内存分配（通过API函数如xTaskCreateStatic()创建任务）
 * 当前配置：支持静态内存分配 */
#define configSUPPORT_STATIC_ALLOCATION          1

/* 动态内存分配支持配置
 * 0 - 不支持动态内存分配
 * 1 - 支持动态内存分配（通过API函数如xTaskCreate()创建任务）
 * 当前配置：支持动态内存分配 */
#define configSUPPORT_DYNAMIC_ALLOCATION         1

/* 空闲任务钩子函数使能配置
 * 0 - 不使用空闲任务钩子
 * 1 - 使用空闲任务钩子（需要用户实现vApplicationIdleHook()函数）
 * 当前配置：不使用空闲任务钩子 */
#define configUSE_IDLE_HOOK                      0

/* 滴答定时器钩子函数使能配置
 * 0 - 不使用滴答定时器钩子
 * 1 - 使用滴答定时器钩子（需要用户实现vApplicationTickHook()函数）
 * 当前配置：不使用滴答定时器钩子 */
#define configUSE_TICK_HOOK                      0

/* CPU时钟频率配置
 * 设置为SystemCoreClock，通常在系统初始化时定义
 * 当前配置：使用系统定义的SystemCoreClock值 */
#define configCPU_CLOCK_HZ                       ( SystemCoreClock )

/* 滴答定时器中断频率配置（单位：Hz）
 * 决定了系统的时间基准，这里设置为1000Hz意味着每个tick是1ms
 * 当前配置：1000Hz（1ms的tick周期） */
#define configTICK_RATE_HZ                       ((TickType_t)1000)

/* 最大任务优先级数量配置
 * FreeRTOS中，数字越大优先级越高
 * 当前配置：支持56个不同的任务优先级 */
#define configMAX_PRIORITIES                     ( 56 )

/* 最小任务堆栈大小配置（单位：字，非字节）
 * 这个值是针对空闲任务和使用xTaskCreateStatic()创建的任务的最小堆栈大小
 * 当前配置：128个字 */
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)

/* 堆总大小配置（单位：字节）
 * 定义了FreeRTOS动态内存分配可用的总空间
 * 当前配置：15360字节（约15KB） */
#define configTOTAL_HEAP_SIZE                    ((size_t)15360)

/* 任务名称最大长度配置（包括终止符）
 * 定义了任务名称字符串的最大长度
 * 当前配置：16个字符 */
#define configMAX_TASK_NAME_LEN                  ( 16 )

/* 跟踪功能使能配置
 * 0 - 禁用跟踪功能
 * 1 - 启用跟踪功能，用于可视化任务执行情况
 * 当前配置：启用跟踪功能 */
#define configUSE_TRACE_FACILITY                 1

/* 16位滴答计数使能配置
 * 0 - 使用32位计数器存储tick值
 * 1 - 使用16位计数器存储tick值（仅在资源极其受限的系统中使用）
 * 当前配置：使用32位计数器 */
#define configUSE_16_BIT_TICKS                   0

/* 互斥量功能使能配置
 * 0 - 禁用互斥量功能
 * 1 - 启用互斥量功能，允许创建和使用互斥量
 * 当前配置：启用互斥量功能 */
#define configUSE_MUTEXES                        1

/* 队列注册表大小配置
 * 定义了可以注册的队列和信号量的最大数量
 * 当前配置：最多可以注册8个队列或信号量 */
#define configQUEUE_REGISTRY_SIZE                8

/* 递归互斥量功能使能配置
 * 0 - 禁用递归互斥量功能
 * 1 - 启用递归互斥量功能，允许任务多次获取同一个互斥量
 * 当前配置：启用递归互斥量功能 */
#define configUSE_RECURSIVE_MUTEXES              1

/* 计数信号量功能使能配置
 * 0 - 禁用计数信号量功能
 * 1 - 启用计数信号量功能
 * 当前配置：启用计数信号量功能 */
#define configUSE_COUNTING_SEMAPHORES            1

/* 端口优化的任务选择算法使能配置
 * 0 - 不使用端口优化的任务选择算法
 * 1 - 使用特定硬件平台优化的任务选择算法（通常用于ARM Cortex-M系列）
 * 当前配置：不使用端口优化的任务选择算法 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  0
/* USER CODE BEGIN MESSAGE_BUFFER_LENGTH_TYPE */
/* Defaults to size_t for backward compatibility, but can be changed
   if lengths will always be less than the number of bytes in a size_t. */
#define configMESSAGE_BUFFER_LENGTH_TYPE         size_t
/* USER CODE END MESSAGE_BUFFER_LENGTH_TYPE */

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                    0
#define configMAX_CO_ROUTINE_PRIORITIES          ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS                         1
#define configTIMER_TASK_PRIORITY                ( 2 )
#define configTIMER_QUEUE_LENGTH                 10
#define configTIMER_TASK_STACK_DEPTH             256

/* CMSIS-RTOS V2 flags */
#define configUSE_OS2_THREAD_SUSPEND_RESUME  1
#define configUSE_OS2_THREAD_ENUMERATE       1
#define configUSE_OS2_EVENTFLAGS_FROM_ISR    1
#define configUSE_OS2_THREAD_FLAGS           1
#define configUSE_OS2_TIMER                  1
#define configUSE_OS2_MUTEX                  1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet             1
#define INCLUDE_uxTaskPriorityGet            1
#define INCLUDE_vTaskDelete                  1
#define INCLUDE_vTaskCleanUpResources        0
#define INCLUDE_vTaskSuspend                 1
#define INCLUDE_vTaskDelayUntil              1
#define INCLUDE_vTaskDelay                   1
#define INCLUDE_xTaskGetSchedulerState       1
#define INCLUDE_xTimerPendFunctionCall       1
#define INCLUDE_xQueueGetMutexHolder         1
#define INCLUDE_uxTaskGetStackHighWaterMark  1
#define INCLUDE_xTaskGetCurrentTaskHandle    1
#define INCLUDE_eTaskGetState                1

/*
 * The CMSIS-RTOS V2 FreeRTOS wrapper is dependent on the heap implementation used
 * by the application thus the correct define need to be enabled below
 */
#define USE_FreeRTOS_HEAP_4

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
 /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
 #define configPRIO_BITS         __NVIC_PRIO_BITS
#else
 #define configPRIO_BITS         4
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   15

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
/* USER CODE BEGIN 1 */
#define configASSERT( x ) if ((x) == 0) {taskDISABLE_INTERRUPTS(); for( ;; );}
/* USER CODE END 1 */

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler

/* IMPORTANT: After 10.3.1 update, Systick_Handler comes from NVIC (if SYS timebase = systick), otherwise from cmsis_os2.c */

#define USE_CUSTOM_SYSTICK_HANDLER_IMPLEMENTATION 0

/* USER CODE BEGIN Defines */
/* Section where parameter definitions can be added (for instance, to override default ones in FreeRTOS.h) */
/* USER CODE END Defines */

#endif /* FREERTOS_CONFIG_H */
