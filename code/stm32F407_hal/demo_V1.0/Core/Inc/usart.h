/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdbool.h"

/* USER CODE END Includes */

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */
#define UART_BAUDRATE_9600					 1
#define UART_BAUDRATE_38400					 2
#define UART_BAUDRATE_57600					 3
#define UART_BAUDRATE_115200				 4


#define USART_PakageSend_Num					8					//���ڷ������ݸ���
#define USART_PakageRecv_Num					8					//���ڽ������ݸ���

#define USARTx_TX_BUFFERSIZE             48					//���ڷ��ͻ���
#define USARTx_RX_BUFFERSIZE             48      		//���ڽ��ջ���

extern volatile uint8_t USARTx_DMA_RX_Buffer[USARTx_RX_BUFFERSIZE]; 
extern volatile uint8_t USARTx_DMA_TX_Buffer[USARTx_TX_BUFFERSIZE]; 

/* USER CODE END Private defines */

void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */

void User_USART2_UART_Init(uint8_t baud_rate);
void USER_USART2_RxCpltCallback(UART_HandleTypeDef *huart);
void UART_Poll(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

