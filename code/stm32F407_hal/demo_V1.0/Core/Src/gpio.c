/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */
  #include "stm32f4xx_hal_gpio.h"

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, ADC_MUX_S2_Pin|ADC_MUX_S1_Pin|ADC_MUX_S0_Pin|led_red_Pin
                          |green_led_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, phase3B_EN_Pin|phase3A_EN_Pin|phase1B_EN_Pin|phase1A_EN_Pin
                          |phase2B_EN_Pin|phase2A_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : mode_switch_in_Pin reverse_switch_in_Pin */
  GPIO_InitStruct.Pin = mode_switch_in_Pin|reverse_switch_in_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : ADC_MUX_S2_Pin ADC_MUX_S1_Pin ADC_MUX_S0_Pin */
  GPIO_InitStruct.Pin = ADC_MUX_S2_Pin|ADC_MUX_S1_Pin|ADC_MUX_S0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : phase3B_EN_Pin phase3A_EN_Pin phase1B_EN_Pin phase1A_EN_Pin
                           phase2B_EN_Pin phase2A_EN_Pin */
  GPIO_InitStruct.Pin = phase3B_EN_Pin|phase3A_EN_Pin|phase1B_EN_Pin|phase1A_EN_Pin
                          |phase2B_EN_Pin|phase2A_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : led_red_Pin green_led_Pin */
  GPIO_InitStruct.Pin = led_red_Pin|green_led_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void red_on(void)
{
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_SET);
}
void red_off(void)
{
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_RESET);
}

void M3A_EN_High(void)
{
	HAL_GPIO_WritePin(phase3A_EN_GPIO_Port, phase3A_EN_Pin, GPIO_PIN_SET);
}
void M3A_EN_Low(void)
{
	HAL_GPIO_WritePin(phase3A_EN_GPIO_Port, phase3A_EN_Pin, GPIO_PIN_RESET);
}
void M3B_EN_High(void)
{
	HAL_GPIO_WritePin(phase3B_EN_GPIO_Port, phase3B_EN_Pin, GPIO_PIN_SET);
}
void M3B_EN_Low(void)
{
	HAL_GPIO_WritePin(phase3B_EN_GPIO_Port, phase3B_EN_Pin, GPIO_PIN_RESET);
}


void M2A_EN_High(void)
{
	HAL_GPIO_WritePin(phase2A_EN_GPIO_Port, phase2A_EN_Pin, GPIO_PIN_SET);
}
void M2A_EN_Low(void)
{
	HAL_GPIO_WritePin(phase2A_EN_GPIO_Port, phase2A_EN_Pin, GPIO_PIN_RESET);
}
void M2B_EN_High(void)
{
	HAL_GPIO_WritePin(phase2B_EN_GPIO_Port, phase2B_EN_Pin, GPIO_PIN_SET);
}
void M2B_EN_Low(void)
{
	HAL_GPIO_WritePin(phase2B_EN_GPIO_Port, phase2B_EN_Pin, GPIO_PIN_RESET);
}

void M1A_EN_High(void)
{
	HAL_GPIO_WritePin(phase1A_EN_GPIO_Port, phase1A_EN_Pin, GPIO_PIN_SET);
}
void M1A_EN_Low(void)
{
	HAL_GPIO_WritePin(phase1A_EN_GPIO_Port, phase1A_EN_Pin, GPIO_PIN_RESET);
}
void M1B_EN_High(void)
{
	HAL_GPIO_WritePin(phase1B_EN_GPIO_Port, phase1B_EN_Pin, GPIO_PIN_SET);
}
void M1B_EN_Low(void)
{
	HAL_GPIO_WritePin(phase1B_EN_GPIO_Port, phase1B_EN_Pin, GPIO_PIN_RESET);
}
/* USER CODE END 2 */
