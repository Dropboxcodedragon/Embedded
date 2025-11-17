#include "System_configuration.h"
#include "can.h"
#include "usart.h"
#include "adc.h"
#include "gpio.h"
#include "dma.h"
#include "tim.h"
#include "SchedulerBalance.h"
#include "H_Motor_Mid.h"
#include "function_M1.h"
#include "function_ZFS.h"
#include "ADC_Mid.h"

__mFuntion_Manage	 mFuntion_Manage;

/************************************************************************************************
**函数名:		SystemFunction_Init	
**功能:			系统功能初始化
**返回值:			
**参数:			
**备注:
**修改记录:
*************************************************************************************************/
void SystemFunction_Init(void)
{
	memset((uint8_t*)&mFuntion_Manage,0,sizeof(__mFuntion_Manage));
  

}

/************************************************************************************************
**函数名:		FlashWriteFuse	
**功能:			烧熔丝
**返回值:			
**参数:			
**备注:
**修改记录:
*************************************************************************************************/
void FlashWriteFuse(void)
{  
}
/************************************************************************************************
**函数名:		get_FlashFuse_Status	
**功能:			判断熔丝位状态
**返回值:			
**参数:			
**备注:
**修改记录:
*************************************************************************************************/
void get_FlashFuse_Status(void)
{
}
void HAL_RegisterCallback(void)
{
//	HAL_UART_RegisterRxEventCallback(&huart2, HAL_UARTEx_RxEventCallback);
//	HAL_UART_RegisterCallback(&huart2, HAL_UART_TX_COMPLETE_CB_ID, HAL_UART_TxCpltCallback);
//	
////	HAL_CAN_RegisterCallback(&hcan2, HAL_CAN_RX_FIFO0_FULL_CB_ID, HAL_CAN_RxFifo0FullCallback);
//	HAL_CAN_RegisterCallback(&hcan2, HAL_CAN_RX_FIFO0_MSG_PENDING_CB_ID, HAL_CAN_RxFifo0MsgPendingCallback);
//	HAL_ADC_RegisterCallback(&hadc1, HAL_ADC_CONVERSION_COMPLETE_CB_ID, HAL_ADC_ConvCpltCallback);
	HAL_AD_RegisterCallback();

}

/************************************************************************************************
**函数名:		SysInit_main	
**功能:			main函数初始化
**返回值:			
**参数:			
**备注:
**修改记录:
*************************************************************************************************/
void SysInit_main(void)
{
  //启动CAN
  User_CAN2_Init(CAN_BAUDRATE_500K);
  //启动串口
  User_USART2_UART_Init(UART_BAUDRATE_115200);
  //启动DMA
  //启动ADC
	ADC_MUX_Param_Init();
	User_ADC_Init();
  //启动定时器
	User_Tim_Init();
  //启动中断

	HAL_RegisterCallback();

  mFuntion_Manage.SysPowerOnFinishFlag = true;
	ZFS_PWM_Planner_Init(&ZFS_PWM_Planner);
	M1_PWM_Planner_Init(&M1_PWM_Planner);
  TaskInit(task_t, TASK_NUM);//任务初始化

}
//开机保持继电器满电压输出，2s后保持80%输出
uint16_t relay_hold_cnt = 0;
#define HOLD_CNT 2000*2
void relay_adjust(float cap_voltage, float voltage)
{
	float put_duty = 0.0f;
	if(cap_voltage>voltage)
	{
		put_duty = voltage/cap_voltage;
	}
	else
	{
		put_duty = 1.0f;
	}
	if(relay_hold_cnt<HOLD_CNT)
	{
		set_TIM4_Duty(PWM_CH1,put_duty);
		relay_hold_cnt++;
	}
	else
	{
		set_TIM4_Duty(PWM_CH1,put_duty*0.8f);
	}
}
/************************************************************************************************
**函数名:		While_Run_Freq_Cnt_Isr	
**功能:			While运行频率计数ISR
**返回值:			
**参数:			
**备注:
**修改记录:
*************************************************************************************************/
uint8_t system_cnt = 0;
float PWM_duty_test = 0.001f;
float PWM_duty_test1 = 0.000f;
void While_Run_Freq_Cnt_Isr(void)
{
  mFuntion_Manage.Time_500us_RunFlag = 1;
	if(system_cnt == 0)
	{
		red_on();
		system_cnt = 1;
	}
	else
	{
		red_off();
		system_cnt = 0;
	}
	if(selfcheck_state == 1)
	{
		M1_PWM_Planning();
		ZeroFlux_Control(0.0f,&ZFS_PWM_Planner);
		relay_adjust(ADCVoltage_List.cap_volt, 12.0f);
	}

//	if(PWM_duty_test<0.5f)
//	{
//		PWM_duty_test+=0.0002f;
////		M3B_EN_High();
////		set_TIM8_Duty(PWM_CH1,PWM_duty_test);
////		M3_Motor_PWM(Backward,PWM_duty_test);
////		M2_Motor_PWM(Forward,PWM_duty_test);
////		M1_Motor_PWM(Forward,PWM_duty_test);
//	}
//	else if(PWM_duty_test<0.998f)
//	{
//		PWM_duty_test+=0.0002f;
////		M3B_EN_Low();
////		set_TIM8_Duty(PWM_CH1,0.0f);
//		M3_PWM_Disable();
//		M2_PWM_Disable();
//		M1_PWM_Disable();
//	}
//	else
//	{
//		PWM_duty_test = 0.0002f;
////		set_TIM8_Duty(PWM_CH1,0.0f);
//		M3_PWM_Disable();
//		M2_PWM_Disable();
//		M1_PWM_Disable();
//	}
//	if(PWM_duty_test<0.998f)
//	{
//		PWM_duty_test+=0.001f;
//		set_TIM1_Duty(PWM_CH1,PWM_duty_test);
//		set_TIM1_Duty(PWM_CH2,PWM_duty_test);
//		set_TIM1_Duty(PWM_CH3,PWM_duty_test);
//		set_TIM1_Duty(PWM_CH4,PWM_duty_test);
//		set_TIM8_Duty(PWM_CH1,PWM_duty_test);
//		set_TIM8_Duty(PWM_CH2,PWM_duty_test);
//	}
//	else
//	{
//		PWM_duty_test = 0.001f;
//		set_TIM1_Duty(PWM_CH1,0.0f);
//		set_TIM1_Duty(PWM_CH2,0.0f);
//		set_TIM1_Duty(PWM_CH3,0.0f);
//		set_TIM1_Duty(PWM_CH4,0.0f);
//		set_TIM8_Duty(PWM_CH1,0.0f);
//		set_TIM8_Duty(PWM_CH2,0.0f);

//	}
		
}
/****************************** BEFIN ********************************
**
**@Name       : NVID_
**@Brief      : None
**@Param None 
**@Return     : None
**@Author     : @zhaofeng
**@Data	      : 2025-04-15
******************************* END *********************************/
//void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
//{ 
//  /* Check the parameters */
//  assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
//  assert_param(IS_NVIC_OFFSET(Offset));  
//   
//  SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
//}



