/**
  ********************************  STM32F0xx  *********************************
  * @文件名     ： bsp.h
  * @作者       ： strongerHuang
  * @标准库     ： V1.5.0
  * @文件版本   ： V1.0.0
  * @日期       ： 2017年08月24日
  * @摘要       ： BSP板级支持包头文件
  ******************************************************************************/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _BSP_H
#define _BSP_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "stm32f0xx.h"


/* 宏定义 --------------------------------------------------------------------*/
#define LED1_PIN                  GPIO_Pin_8
#define LED1_GPIO_PORT            GPIOA
#define LED1_GPIO_CLK             RCC_AHBPeriph_GPIOA
  
#define LED2_PIN                  GPIO_Pin_9
#define LED2_GPIO_PORT            GPIOA
#define LED2_GPIO_CLK             RCC_AHBPeriph_GPIOA

#define LED3_PIN                  GPIO_Pin_10
#define LED3_GPIO_PORT            GPIOA
#define LED3_GPIO_CLK             RCC_AHBPeriph_GPIOA

#define LED4_PIN                  GPIO_Pin_11
#define LED4_GPIO_PORT            GPIOA
#define LED4_GPIO_CLK             RCC_AHBPeriph_GPIOA

/* LED开关 */
#define LED1_ON                   GPIO_SetBits(LED1_GPIO_PORT, LED1_PIN)
#define LED1_OFF                  GPIO_ResetBits(LED1_GPIO_PORT, LED1_PIN)
#define LED1_TOGGLE               (LED1_GPIO_PORT->ODR ^= LED1_PIN)

#define LED2_ON                   GPIO_SetBits(LED2_GPIO_PORT, LED2_PIN)
#define LED2_OFF                  GPIO_ResetBits(LED2_GPIO_PORT, LED2_PIN)
#define LED2_TOGGLE               (LED2_GPIO_PORT->ODR ^= LED2_PIN)

#define LED3_ON                   GPIO_SetBits(LED3_GPIO_PORT, LED3_PIN)
#define LED3_OFF                  GPIO_ResetBits(LED3_GPIO_PORT, LED3_PIN)
#define LED3_TOGGLE               (LED3_GPIO_PORT->ODR ^= LED3_PIN)

#define LED4_ON                   GPIO_SetBits(LED4_GPIO_PORT, LED4_PIN)
#define LED4_OFF                  GPIO_ResetBits(LED4_GPIO_PORT, LED4_PIN)
#define LED4_TOGGLE               (LED4_GPIO_PORT->ODR ^= LED4_PIN)

/* 函数申明 ------------------------------------------------------------------*/
void BSP_Initializes(void);


#endif /* _BSP_H */

/**** Copyright (C)2017 strongerHuang. All Rights Reserved **** END OF FILE ****/
