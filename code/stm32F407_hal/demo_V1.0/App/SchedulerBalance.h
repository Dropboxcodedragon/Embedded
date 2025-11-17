/***********************************************************************
 *
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF DALA, INC.
 * The copyright notice above does not evidence any actual or intended
 * publication of such source code. 
 * (c) Copyright 2012-2022, DALA, All Rights Reserved.
 * http://www.dalacontroller.com/
*
*  File:         SchedulerBanlance.h
*  Author:       zj
 *  Description: SchedulerBanlance
 *  Created on:  2022.7.22
*********************************************************************/
#ifndef __SCHEDULER_BALANCE_H_
#define __SCHEDULER_BALANCE_H_
#include "stdint.h"

#define TASK_NUM		(4)
#define TASK_ERR_NUM	(1)


typedef enum
{
	TASK_2KHZ 	= 0,
	TASK_1KHZ 	= 1,
	TASK_500HZ 	= 2,
	TASK_125HZ 	= 3,
	TASK_31HZ	= 4,
	TASK_8HZ 	= 5,
	TASK_2HZ 	= 6,
	
}TASK_FREQUENCY;

typedef struct
{
	void (*TaskFunction)(void);
	TASK_FREQUENCY task_frequency;
	uint16_t remainder;
}TASK_T;
/*接口*/
void TaskInit(TASK_T* task_t, uint8_t task_num);
void TaskScheduler(TASK_T* task_t, uint8_t task_num);

/*应用*/
extern TASK_T task_t[TASK_NUM];
extern TASK_T task_err_t[TASK_ERR_NUM];

#endif
