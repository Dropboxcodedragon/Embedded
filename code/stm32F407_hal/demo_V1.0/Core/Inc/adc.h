/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define TIMx_Master TIM2 //����ʱ��

#define ADC_EXT_Tigger_TIMER_IRQHandler TIM3_IRQHandler

//typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define TRANSFER_IT_ENABLE_MASK (uint32_t)(DMA_SxCR_TCIE | DMA_SxCR_HTIE | \
                                           DMA_SxCR_TEIE | DMA_SxCR_DMEIE)

//#define ADC_CDR_ADDRESS													((uint32_t)0x40012308)
//#define ADC_DMA_BufSize													144//270//90	


#define ADC_Prescaler_Div												ADC_Prescaler_Div4
#define ADC_DMA																	DMA2
#define ADC_MODE 																ADC_TripleMode_RegSimult
#define ADC_DMA_Channel 												DMA_Channel_0
#define ADC_DMA_Stream          								DMA2_Stream0
#define ADC_DMA_AccessMode											ADC_DMAAccessMode_1		
#define ADC_DMA_ExtTrigConvEdge									ADC_ExternalTrigConvEdge_Rising
#define ADC_DMA_ExtTrigConv  										ADC_ExternalTrigConv_T4_CC4
#define ADC_DMA_IRQ															DMA2_Stream0_IRQn
#define ADC_DMA_IRQHandler											DMA2_Stream0_IRQHandler
#define ADC_DMA_TC_FLG													DMA_IT_TCIF0
#define ADC_DMA_HT_FLG													DMA_IT_HTIF0
#define ADC_CDR_ADDRESS													((uint32_t)0x40012308)
#define ADC_DMA_BufSize													144//270//90	


extern volatile uint8_t ADC_DMA_Update_Flag;				//ADC�������±�־



extern volatile uint16_t aADCTripleConvertedValue[ADC_DMA_BufSize*2];		//�������ģʽDMA buffer
extern volatile uint16_t ADC_ActiveBuffer_AddressStart;



/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */
void User_ADC_Init(void);
void HAL_AD_RegisterCallback(void);
void HAL_ADC_ConvCpltCallback1(ADC_HandleTypeDef* hadc);
void ADC_MultiModeDMARequestAfterLastTransferCmd(FunctionalState NewState);
void DMA_ITConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT, FunctionalState NewState);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

