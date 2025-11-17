/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void red_on(void);
void red_off(void);
// M3ʹ�ܺ���
void M3A_EN_High(void);
void M3A_EN_Low(void);
void M3B_EN_High(void);
void M3B_EN_Low(void);

// M2ʹ�ܺ���
void M2A_EN_High(void);
void M2A_EN_Low(void);
void M2B_EN_High(void);
void M2B_EN_Low(void);

// M1ʹ�ܺ���
void M1A_EN_High(void);
void M1A_EN_Low(void);
void M1B_EN_High(void);
void M1B_EN_Low(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

