/***********************************************************************
*
* THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF DALA, INC.
* The copyright notice above does not evidence any actual or intended
* publication of such source code.
* (c) Copyright 2012-2022, DALA, All Rights Reserved.
* http://www.dalacontroller.com/
*
* File: SchedulerBanlance.c
* Author: zj
* Description: SchedulerBanlance
* Created on: 2022.7.22
*********************************************************************/
#include "SchedulerBalance.h"
#include "main.h"
#include "String.h"
#include "usart.h"
#include "can.h"
#include "CAN_mid.h"

/* 以下为任务重定义 */

//void TaskIdle(void)
//{
//}

TASK_T task_err_t[TASK_ERR_NUM]={
{.TaskFunction = UART_Poll, .task_frequency = TASK_1KHZ},
};

TASK_T task_t[TASK_NUM]={
///*TASK_2KHZ 1*/
//{.TaskFunction = TaskIdle, .task_frequency = TASK_2KHZ},

/////*TASK_1KHZ 2*/
//{.TaskFunction = USART_Timeout_Manage, .task_frequency = TASK_1KHZ},
///*TASK_500HZ 4*/
//{.TaskFunction = UART_Poll, .task_frequency = TASK_1KHZ},
///*TASK_125HZ 16*/
{.TaskFunction = CAN_Send, .task_frequency = TASK_2HZ},

///*TASK_31HZ 64*/
//{.TaskFunction = USART_Pakage_Send, .task_frequency = TASK_31HZ},
{.TaskFunction = UART_Poll, .task_frequency = TASK_2HZ},
/////*TASK_8HZ 256*/

/////*TASK_2HZ 1024*/
//{.TaskFunction = TaskIdle, .task_frequency = TASK_2HZ},

};

/**************cpu 均衡调度*************/
/**
  * @brief 初始化任务
  *         
  * @param  
  *         
  * @retval 
  */
void TaskInit(TASK_T* task_t, uint8_t task_num)
{
	static uint16_t task_2k_cnt = 0;
	static uint16_t task_1k_cnt = 0;
	static uint16_t task_500hz_cnt = 0;
	static uint16_t task_125hz_cnt = 0;
	static uint16_t task_31hz_cnt = 0;
	static uint16_t task_8hz_cnt = 0;
	static uint16_t task_2hz_cnt =0;
	
	for(uint8_t i=0; i<task_num; i++)
	{
		if(task_t[i].task_frequency == TASK_2KHZ)
		{
			task_t[i].remainder = task_2k_cnt&0;
			task_2k_cnt++;
		}
		else if(task_t[i].task_frequency == TASK_1KHZ)
		{
			task_t[i].remainder = task_1k_cnt&1;
			task_1k_cnt++;
		}
		else if(task_t[i].task_frequency == TASK_500HZ)
		{
			task_t[i].remainder = task_500hz_cnt&3;
			task_500hz_cnt++;
		}
		else if(task_t[i].task_frequency == TASK_125HZ)
		{
			task_t[i].remainder = task_125hz_cnt&15;
			task_125hz_cnt++;
		}
		else if(task_t[i].task_frequency == TASK_31HZ)
		{
			task_t[i].remainder = task_31hz_cnt&63;
			task_31hz_cnt++;
		}
		else if(task_t[i].task_frequency == TASK_8HZ)
		{
			task_t[i].remainder = task_8hz_cnt&255;
			task_8hz_cnt++;
		}
		else if(task_t[i].task_frequency == TASK_2HZ)
		{
			task_t[i].remainder = task_2hz_cnt&1023;
			task_2hz_cnt++;
		}
		else {}
	}
}
/**
  * @brief 任务调度,最多支持255个任务
  *         
  * @param  
  *         
  * @retval 
  */
void TaskScheduler(TASK_T* task_t, uint8_t task_num)
{
	static uint16_t task_cnt = 0;
	
	static uint16_t task_cnt_2khz  = 0;
	static uint16_t task_cnt_1khz  = 0;
	static uint16_t task_cnt_500hz = 0;
	static uint16_t task_cnt_125hz = 0;
	static uint16_t task_cnt_31hz  = 0;
	static uint16_t task_cnt_8hz   = 0;
	static uint16_t task_cnt_2hz   = 0;
	
	for(uint8_t i=0; i<task_num; i++)
	{
		if(task_t[i].task_frequency == TASK_2KHZ)
		{
			if((task_cnt_2khz&0) == task_t[i].remainder)
			{
				if(task_t[i].TaskFunction != NULL )
				{
					task_t[i].TaskFunction();
				}		
			}
		}
		else if(task_t[i].task_frequency == TASK_1KHZ)
		{
			if((task_cnt_1khz&1) == task_t[i].remainder)
			{
				if(task_t[i].TaskFunction != NULL )
				{
					task_t[i].TaskFunction();
				}				
			}
		}
		else if(task_t[i].task_frequency == TASK_500HZ)
		{
			if((task_cnt_500hz&3) == task_t[i].remainder)
			{
				if(task_t[i].TaskFunction != NULL )
				{
					task_t[i].TaskFunction();
				}				
			}
		}
		else if(task_t[i].task_frequency == TASK_125HZ)
		{
			if((task_cnt_125hz&15) == task_t[i].remainder)
			{
				if(task_t[i].TaskFunction != NULL )
				{
					task_t[i].TaskFunction();
				}				
			}
		}
		else if(task_t[i].task_frequency == TASK_31HZ)
		{
			if((task_cnt_31hz&63) == task_t[i].remainder)
			{
				if(task_t[i].TaskFunction != NULL )
				{
					task_t[i].TaskFunction();
				}			
			}
		}
		else if(task_t[i].task_frequency == TASK_8HZ)
		{
			if((task_cnt_8hz&255) == task_t[i].remainder)
			{
				if(task_t[i].TaskFunction != NULL )
				{
					task_t[i].TaskFunction();
				}				
			}
		}
		else if(task_t[i].task_frequency == TASK_2HZ)
		{
			if((task_cnt_2hz&1023) == task_t[i].remainder)
			{
				if(task_t[i].TaskFunction != NULL )
				{
					task_t[i].TaskFunction();
				}	
			}
		}
		else {}
	}
	task_cnt ++;
	if(task_cnt == 1024)
	{
		task_cnt = 0;
	}

	task_cnt_2khz  ++;
	task_cnt_1khz  ++;
	task_cnt_500hz ++;
	task_cnt_125hz ++;
	task_cnt_31hz  ++;
	task_cnt_8hz   ++;
	task_cnt_2hz   ++;
	
	if(task_cnt_2khz == 1)
	{
		task_cnt_2khz  = 0;
	}
	if(task_cnt_1khz == 2)
	{
		task_cnt_1khz  = 0;
	}
	if(task_cnt_500hz == 4)
	{
		task_cnt_500hz  = 0;
	}	
	if(task_cnt_125hz == 16)
	{
		task_cnt_125hz  = 0;
	}	
	if(task_cnt_31hz == 64)
	{
		task_cnt_31hz  = 0;
	}	
	if(task_cnt_8hz == 256)
	{
		task_cnt_8hz  = 0;
	}
	if(task_cnt_2hz == 1024)
	{
		task_cnt_2hz  = 0;
	}
	
}



