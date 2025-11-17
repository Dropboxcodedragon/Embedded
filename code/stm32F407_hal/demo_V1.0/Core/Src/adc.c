/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */
#include "stm32f4xx_hal.h"
uint16_t aADCTripleConvertedValue1[ADC_DMA_BufSize] = {0};
uint16_t aADCTripleConvertedValue2[ADC_DMA_BufSize] = {0};
uint8_t ADC_DMA_Address = 0;
volatile uint16_t ADC_ActiveBuffer_AddressStart = 0;

volatile uint16_t aADCTripleConvertedValue[ADC_DMA_BufSize*2];		//�������ģʽDMA buffer

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_AnalogWDGConfTypeDef AnalogWDGConfig = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_CC1;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 12;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the analog watchdog
  */
  AnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_ALL_REG;
  AnalogWDGConfig.HighThreshold = 4095;
  AnalogWDGConfig.LowThreshold = 0;
  AnalogWDGConfig.ITMode = ENABLE;
  if (HAL_ADC_AnalogWDGConfig(&hadc1, &AnalogWDGConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 7;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 8;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 9;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = 10;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = 11;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 12;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = phase3A_current_ADC_Pin|phase3B_current_ADC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_NORMAL;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */
//	HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)aADCTripleConvertedValue, ADC_DMA_BufSize);
  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOC, phase3A_current_ADC_Pin|phase3B_current_ADC_Pin);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);

    /* ADC1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(ADC_IRQn);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void User_ADC_Init(void)
{
	  // ��������ADCͬ��ģʽ
    // ע�⣺��������ADC2��ADC3��HAL_ADC_Start��
    HAL_ADC_Start(&hadc3);
		HAL_ADC_Start(&hadc2);
		HAL_ADC_Start(&hadc1);
//ADC�������ⲿ������ADCת�������������У����ǵ����ⲿ��������ת�����ʧ���ˣ�
//	CLEAR_BIT(ADC1->CR2, ADC_CR2_EXTEN);

//
	  /* DMA2_Stream0 enable */
//  DMA_Cmd(ADC_DMA_Stream, ENABLE);
  /* Enable DMA request after last transfer (multi-ADC mode) ******************/
//  ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
//	DMA_ITConfig(ADC_DMA_Stream, DMA_IT_TC, ENABLE);		//DMA��������ж�

// ����ADC1��DMA���䣨���ݻ������׵�ַ��
//		HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)aADCTripleConvertedValue1, ADC_DMA_BufSize);
		HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)aADCTripleConvertedValue, ADC_DMA_BufSize);
		ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
		DMA_ITConfig(ADC_DMA_Stream, DMA_IT_TC, ENABLE);
}

//volatile uint8_t	ADC_DMA_Address = 0;
//volatile uint16_t ADC_ActiveBuffer_AddressStart = 0;
volatile uint8_t ADC_DMA_Update_Flag = 0;				//ADC�������±�־

#if 0
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
		HAL_ADC_Stop(&hadc1);
		HAL_ADC_Stop(&hadc3);
		HAL_ADC_Stop(&hadc2);
		HAL_ADCEx_MultiModeStop_DMA(&hadc1);
		if(0 == ADC_DMA_Address)
		{
			ADC_DMA_Address = 1;
			ADC_ActiveBuffer_AddressStart = 0;
			// ע�⣺��������ADC2��ADC3��HAL_ADC_Start��
			HAL_ADC_Start(&hadc1);
			HAL_ADC_Start(&hadc3);
			HAL_ADC_Start(&hadc2);
				// ����ADC1��DMA���䣨���ݻ������׵�ַ��
			HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t*)&aADCTripleConvertedValue1, ADC_DMA_BufSize);
		}else 
		{
			ADC_DMA_Address = 0;
			ADC_ActiveBuffer_AddressStart = ADC_DMA_BufSize;
			// ע�⣺��������ADC2��ADC3��HAL_ADC_Start��

//			HAL_ADC_Start(&hadc1);
			HAL_ADC_Start(&hadc3);
			HAL_ADC_Start(&hadc2);
				// ����ADC1��DMA���䣨���ݻ������׵�ַ��
			HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t*)&aADCTripleConvertedValue2, ADC_DMA_BufSize);
		}
	
		ADC_DMA_Update_Flag = 0;											//��λ��־

}
#else

void HAL_ADC_ConvCpltCallback1(ADC_HandleTypeDef* hadc)
{
		ADC_DMA->LIFCR |= 0x30;		//����ж���ɱ�־
		ADC1->CR2 &= (uint32_t)(~ADC_CR2_ADON);				//�ر�ADC1
		ADC2->CR2 &= (uint32_t)(~ADC_CR2_ADON);				//�ر�ADC1
		ADC3->CR2 &= (uint32_t)(~ADC_CR2_ADON);				//�ر�ADC1
		if(0 == ADC_DMA_Address)
		{
			ADC_DMA_Stream->M0AR = (uint32_t)&aADCTripleConvertedValue[ADC_DMA_BufSize];			//�����µĴ洢��ַ
			ADC_DMA_Address = 1;
			ADC_ActiveBuffer_AddressStart = 0;
		}else 
		{
			ADC_DMA_Stream->M0AR = (uint32_t)&aADCTripleConvertedValue[0];			//�����µĴ洢��ַ
			ADC_DMA_Address = 0;
			ADC_ActiveBuffer_AddressStart = ADC_DMA_BufSize;
		}
	
		ADC_DMA_Stream->CR  &= ~(uint32_t)DMA_SxCR_EN;
		ADC_DMA_Stream->NDTR =  ADC_DMA_BufSize;										//���¼��ش������ݴ�С
		ADC_DMA_Stream->CR  |=  (uint32_t)DMA_SxCR_EN;				//ʹ��DMA����
		ADC3->CR2 |= (uint32_t)ADC_CR2_ADON;					//����ʹ��ADC1
		ADC2->CR2 |= (uint32_t)ADC_CR2_ADON;					//����ʹ��ADC1
		ADC1->CR2 |= (uint32_t)ADC_CR2_ADON;					//����ʹ��ADC1
		ADC_DMA_Update_Flag = 0;											//��λ��־

}

#endif

/**
  * @brief  Enables or disables the ADC DMA request after last transfer in multi ADC mode       
  * @param  NewState: new state of the selected ADC DMA request after last transfer.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   if Enabled, DMA requests are issued as long as data are converted and 
  *         DMA mode for multi ADC mode (selected using ADC_CommonInit() function 
  *         by ADC_CommonInitStruct.ADC_DMAAccessMode structure member) is 
  *          ADC_DMAAccessMode_1, ADC_DMAAccessMode_2 or ADC_DMAAccessMode_3.     
  * @retval None
  */
void ADC_MultiModeDMARequestAfterLastTransferCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the selected ADC DMA request after last transfer */
    ADC->CCR |= (uint32_t)ADC_CCR_DDS;
  }
  else
  {
    /* Disable the selected ADC DMA request after last transfer */
    ADC->CCR &= (uint32_t)(~ADC_CCR_DDS);
  }
}

void DMA_ITConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
  assert_param(IS_DMA_CONFIG_IT(DMA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Check if the DMA_IT parameter contains a FIFO interrupt */
  if ((DMA_IT & DMA_IT_FE) != 0)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA FIFO interrupts */
      DMAy_Streamx->FCR |= (uint32_t)DMA_IT_FE;
    }    
    else 
    {
      /* Disable the selected DMA FIFO interrupts */
      DMAy_Streamx->FCR &= ~(uint32_t)DMA_IT_FE;  
    }
  }

  /* Check if the DMA_IT parameter contains a Transfer interrupt */
  if (DMA_IT != DMA_IT_FE)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DMA transfer interrupts */
      DMAy_Streamx->CR |= (uint32_t)(DMA_IT  & TRANSFER_IT_ENABLE_MASK);
    }
    else
    {
      /* Disable the selected DMA transfer interrupts */
      DMAy_Streamx->CR &= ~(uint32_t)(DMA_IT & TRANSFER_IT_ENABLE_MASK);
    }    
  }
}



void HAL_AD_RegisterCallback(void)
{
//	HAL_DMA_RegisterCallback(&hdma_adc1,HAL_DMA_XFER_M1CPLT_CB_ID,);
//	HAL_DMA_RegisterCallback(&hdma_adc1,HAL_DMA_XFER_ABORT_CB_ID,ADC_DMAConvCplt);
	
}

/* USER CODE END 1 */
