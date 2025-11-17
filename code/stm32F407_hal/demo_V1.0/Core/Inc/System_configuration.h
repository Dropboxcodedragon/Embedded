#ifndef __SYSTEM_CONFIGURATION_H__
#define __SYSTEM_CONFIGURATION_H__

#include "stm32f4xx.h"
#include "stdbool.h"
#include "stdlib.h"
#include "main.h"
#include "string.h"
typedef volatile struct __mFuntion_Manage_
{
	bool FaultOutSet;
	bool SysPowerOnFinishFlag;										//系统上电完成标志
	uint8_t Time_500us_RunFlag;										//500us周期计数
	uint8_t Controller_Status;										//控制器状态
	uint16_t CAN_Node_ID;											//CAN节点ID
	uint32_t controller_err;
	uint8_t controller_err_byte1;
	uint8_t controller_err_byte2;
	uint8_t controller_err_byte3;
	uint8_t controller_err_byte4;
	
}__mFuntion_Manage;



#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08020000)

#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == NVIC_VectTab_RAM) || \
                                  ((VECTTAB) == NVIC_VectTab_FLASH))
																	
																	
#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)

extern __mFuntion_Manage mFuntion_Manage;
//void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void While_Run_Freq_Cnt_Isr(void);
void SysInit_main(void);
void SystemFunction_Init(void);
void FlashWriteFuse(void);
void get_FlashFuse_Status(void);


#endif 

