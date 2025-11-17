/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define phase3A_current_ADC_Pin GPIO_PIN_4
#define phase3A_current_ADC_GPIO_Port GPIOC
#define phase3B_current_ADC_Pin GPIO_PIN_5
#define phase3B_current_ADC_GPIO_Port GPIOC
#define mode_switch_in_Pin GPIO_PIN_7
#define mode_switch_in_GPIO_Port GPIOE
#define reverse_switch_in_Pin GPIO_PIN_8
#define reverse_switch_in_GPIO_Port GPIOE
#define ADC_MUX_S2_Pin GPIO_PIN_13
#define ADC_MUX_S2_GPIO_Port GPIOE
#define ADC_MUX_S1_Pin GPIO_PIN_14
#define ADC_MUX_S1_GPIO_Port GPIOE
#define ADC_MUX_S0_Pin GPIO_PIN_15
#define ADC_MUX_S0_GPIO_Port GPIOE
#define phase3B_EN_Pin GPIO_PIN_8
#define phase3B_EN_GPIO_Port GPIOD
#define phase3A_EN_Pin GPIO_PIN_9
#define phase3A_EN_GPIO_Port GPIOD
#define phase1B_EN_Pin GPIO_PIN_10
#define phase1B_EN_GPIO_Port GPIOD
#define phase1A_EN_Pin GPIO_PIN_11
#define phase1A_EN_GPIO_Port GPIOD
#define relay_pwm_ctl_Pin GPIO_PIN_12
#define relay_pwm_ctl_GPIO_Port GPIOD
#define phase2B_EN_Pin GPIO_PIN_14
#define phase2B_EN_GPIO_Port GPIOD
#define phase2A_EN_Pin GPIO_PIN_15
#define phase2A_EN_GPIO_Port GPIOD
#define phase3B_PWM_Pin GPIO_PIN_6
#define phase3B_PWM_GPIO_Port GPIOC
#define phase3A_PWM_Pin GPIO_PIN_7
#define phase3A_PWM_GPIO_Port GPIOC
#define phase2B_PWM_Pin GPIO_PIN_8
#define phase2B_PWM_GPIO_Port GPIOA
#define phase2A_PWM_Pin GPIO_PIN_9
#define phase2A_PWM_GPIO_Port GPIOA
#define phase1B_PWM_Pin GPIO_PIN_10
#define phase1B_PWM_GPIO_Port GPIOA
#define phase1A_PWM_Pin GPIO_PIN_11
#define phase1A_PWM_GPIO_Port GPIOA
#define led_red_Pin GPIO_PIN_0
#define led_red_GPIO_Port GPIOE
#define green_led_Pin GPIO_PIN_1
#define green_led_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
extern volatile uint8_t CurrentZeroOffsetReadFlg;
extern volatile uint8_t selfcheck_state;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
