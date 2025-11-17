/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

extern TIM_HandleTypeDef htim1;

extern TIM_HandleTypeDef htim2;

extern TIM_HandleTypeDef htim3;

extern TIM_HandleTypeDef htim4;

extern TIM_HandleTypeDef htim8;

/* USER CODE BEGIN Private defines */

typedef struct _Cmd_Data_Handle_
{
	int16_t		Motor_TargetPWM[3];		//Ŀ��ռ�ձ�
	uint16_t	Motor_Accel[3];				//������
	uint16_t	Motor_Decel[3];				//������
	int16_t		Motor_CurPWM[3];			//������ռ�ձ�
	int16_t		Motor_Current[3];			//�����ĵ���
	uint32_t	Motor_Stop_Bits;			//ֹͣλ
	uint32_t	Motor_RunStates;			//����״̬����������ֹͣ
	uint32_t	System_ErrBits1;			//������1
	uint32_t	System_ErrBits2;			//������2
	int16_t		PCB_Temperature1;			//�¶�1
	int16_t		PCB_Temperature2;			//�¶�2
	int16_t		PCB_Temperature3;			//�¶�3
	uint32_t	Hard_Verison;					//Ӳ���汾��
	uint32_t	Soft_Verison;					//����汾��
	uint32_t	DeviceTypeString;			//�豸����
	int16_t		BatVoltage;						//��ص�ѹ
	uint32_t	Controller_InputState;//����״̬
	
	uint8_t		HeartBeat_Detect_EN;	//�����źż��ʹ��
	uint16_t	HeartBeat_TimeOutValue;//�����źų�ʱʱ��
}_Cmd_Data_Handle_;

typedef enum
{
	PWM_CH1 = 1,
	PWM_CH2 = 2,
	PWM_CH3 = 3,
	PWM_CH4 = 4,
}_PWM_chx;

#define TIM8_PRESCALER 3
#define TIM8_PERIOD 1399

#define TIM1_PRESCALER 3
#define TIM1_PERIOD 1399

/* USER CODE END Private defines */

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM8_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */
void User_Tim_Init(void);
void set_TIM1_Duty(_PWM_chx chx,float duty);
void set_TIM8_Duty(_PWM_chx chx,float duty);
void set_TIM4_Duty(_PWM_chx chx,float duty);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

