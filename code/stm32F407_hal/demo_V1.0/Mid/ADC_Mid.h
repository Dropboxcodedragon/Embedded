#ifndef __ADC_MID_H__
#define __ADC_MID_H__

#include "main.h"

#define MUX_NUM 0x01
#define MUX_CHANNEL_NUM 0x08
#define ADC_NUM 0x01
#define ADC_CHANNEL_NUM 0x0B


/****************************模拟复用器通道定义*************************/
#define MUX_Sel_000 0			//pot_low
#define MUX_Sel_001 1			//3_A
#define MUX_Sel_010 2			//3_B
#define MUX_Sel_011 3			//speed_pot
#define MUX_Sel_100 4			//1_A
#define MUX_Sel_101 5			//2_B
#define MUX_Sel_110 6			//1_B
#define MUX_Sel_111 7			//2_A

/************************状态阈值索引*******************************/
#define LowThreshold_Index 0  //低输入索引
#define OpenThreshold_Index 1 //开路索引
#define HighThreshold_Index 2 //高输入索引

/************************输入状态*******************************/
typedef enum
{
	Input_Low = 0,	  //低电平
	Input_Open = 1,	  //开路
	Input_High = 2,	  //高电平
	Input_Closed = 3, //闭合：对应开关信号只有低电平、开路、高电平。而对应油门信号只有开路及闭合状态
} InputStatus;

typedef struct
{
	uint8_t Channel_Index;			  //通道索引
	uint8_t ADC_Index;				  //通道索引
	InputStatus *Channel_InState; //通道状态指针
	float *Channel_VoltageFilter; //通道电压指针
	float Channel_Gain;			  //通道增益
	uint32_t R1;
	uint32_t R2;
	float filter_p1;
	float filter_p2;
	uint16_t Channel_ADCVaule;  //通道ADC的值
	float Channel_Voltage; //通道电压指针
} _Analog_Mux_Handle;


typedef volatile struct __ADCVoltage_List_
{
	/*v3.00*/
	float Null_Volatge;
	
	//MUX1
	float pot_low_volt;
	float M3_A_volt;
	float M3_B_volt;
	float speed_pot_volt;
	float M1_A_volt;
	float M2_B_volt;
	float M1_B_volt;
	float M2_A_volt;
	//ADC2 0~9
	float cap_volt;
	float bat_volt;
	float temperature1_volt;
	float temperature2_volt;
	float temperature3_volt;
	float pot_wiper_volt;
	float hall1_volt;
	float hall2_volt;
	float hall3_volt;
	//ADC2 12~13
	float M2_A_current_volt;
	float M2_B_current_volt;

	// 新增的平均电压值
	float pot_low_volt_Avg; // pot_low_volt平均电压
	float speed_pot_volt_Avg; // speed_pot_volt平均电压
	float M3_A_volt_Avg;
	float M3_B_volt_Avg;
	float M2_A_volt_Avg;
	float M2_B_volt_Avg;
	float M1_A_volt_Avg; // M1 A相平均电压
	float M1_B_volt_Avg; // M1 B相平均电压

	float cap_volt_Avg; // cap_volt平均电压
	float bat_volt_Avg;
	float temperature1_volt_Avg; // temperature1_volt平均电压
	float temperature2_volt_Avg; // temperature2_volt平均电压
	float temperature3_volt_Avg; // temperature3_volt平均电压
	float pot_wiper_volt_Avg; // pot_wiper_volt平均电压
	float hall1_volt_Avg; // hall1_volt平均电压
	float hall2_volt_Avg; // hall2_volt平均电压
	float hall3_volt_Avg; // hall3_volt平均电压
	float M2_A_current_volt_Avg; // M2_A_volt平均电压
	float M2_B_current_volt_Avg; // M2_B_volt平均电压

} __ADCVoltage_List;

typedef volatile struct __InputStatus_List_
{
    // MUX1相关状态
    InputStatus pot_low_InState;       // pot_low_volt状态
    InputStatus M3_A_InState;          // M3_A_volt_volt状态
    InputStatus M3_B_InState;          // M3_B_volt_volt状态
    InputStatus speed_pot_InState;     // speed_pot_volt状态
    InputStatus M1_A_InState;          // M1_A_volt_volt状态
    InputStatus M2_B_InState;          // M2_B_volt_volt状态
    InputStatus M1_B_InState;          // M1_B_volt_volt状态
    InputStatus M2_A_InState;          // M2_A_volt_volt状态
    
    // ADC2相关状态
    InputStatus cap_InState;           // cap_volt状态
    InputStatus bat_volt_InState;      // bat_volt_volt状态
    InputStatus temperature1_InState;  // temperature1_volt状态
    InputStatus temperature2_InState;  // temperature2_volt状态
    InputStatus temperature3_InState;  // temperature3_volt状态
    InputStatus pot_wiper_InState;     // pot_wiper_volt状态
    InputStatus hall1_InState;         // hall1_volt状态
    InputStatus hall2_InState;         // hall2_volt状态
    InputStatus hall3_InState;         // hall3_volt状态
    
    // ADC2 12~13相关状态
    InputStatus M2_A_InState2;        // M2_A_volt状态
    InputStatus M2_B_InState2;        // M2_B_volt状态
} __InputStatus_List;

extern _Analog_Mux_Handle Analog_Mux_Data[MUX_NUM][MUX_CHANNEL_NUM];
extern _Analog_Mux_Handle ADC_Data[ADC_NUM][ADC_CHANNEL_NUM];
extern __ADCVoltage_List ADCVoltage_List;


#define ADC_Current_NUM				6																						//ADC电流个数

//ADC的DMA缓存是ADC1-0、ADC2-0、ADC3-0、ADC1-1、ADC2-1、ADC3-1...循环存放的

//------------ADC采样缓存地址定义
#define M1_A_Current_ADC_Buffer_Index 2
#define M1_B_Current_ADC_Buffer_Index M1_A_Current_ADC_Buffer_Index+3
#define M2_A_Current_ADC_Buffer_Index 1
#define M2_B_Current_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3
#define M3_A_Current_ADC_Buffer_Index 0
#define M3_B_Current_ADC_Buffer_Index M3_A_Current_ADC_Buffer_Index+3

//------------ADC采样缓存地址定义

#define CAP_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*2
#define BAT_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*3
#define TEMP1_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*4
#define TEMP2_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*5
#define TEMP3_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*6
#define MUX_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*7
#define POT_WIPER_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*8
#define HALL1_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*9
#define HALL2_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*10
#define HALL3_ADC_Buffer_Index M2_A_Current_ADC_Buffer_Index+3*11


typedef struct _MotorADC_IV_Handle_
{
	float MotorADC_Current;
	float MotorADC_Current_Filter;

	float MotorADC_A_Current;
	float MotorADC_A_Current_Filter;

	float MotorADC_B_Current;
	float MotorADC_B_Current_Filter;

	float MotorADC_Voltage_A;
	float MotorADC_Voltage_B;
	float MotorADC_Voltage;
} _MotorADC_IV_Handle_;

typedef struct _ADC_MotorBsp_IV_Handle_
{
	_MotorADC_IV_Handle_ TractionM_ADC_IV;
	_MotorADC_IV_Handle_ BrushM_ADC_IV;
	_MotorADC_IV_Handle_ VacuumM_ADC_IV;
	_MotorADC_IV_Handle_ BrushLiftM_ADC_IV;
	_MotorADC_IV_Handle_ SqueegeeLiftM_ADC_IV;
	_MotorADC_IV_Handle_ TurningM_ADC_IV;
	_MotorADC_IV_Handle_ SprayM_ADC_IV;
	_MotorADC_IV_Handle_ FilterM_ADC_IV;

	_MotorADC_IV_Handle_ TractionM_L_ADC_IV;
	_MotorADC_IV_Handle_ TractionM_R_ADC_IV;
} _ADC_MotorBsp_IV_Handle_;


//电机输出结构体
typedef struct
{
	float Current_Gain;			//电流增益
	uint8_t ADC_Offset;				//在ADC中的增益
	float filter_p1;			//滤波参数p1
	float filter_p2;			//滤波参数p2
	uint16_t *ZeroOffset;			//零点偏置
	float Linear_k;				//线性参数k
	float Linear_b;				//线性参数b
	uint8_t ZeroOffset_CalcOkFlag;	//零点校准成功标志
	uint8_t Linear_CalcOkFlag;		//线性校准成功标志
	float *Current_Value;		//计算出来的电流值
	float *Current_ValueFilter; //计算出来的 滤波后的电流值
	uint16_t ADC_Vaule;
} _ADC_MotorCurrent_Handle_;

void get_ADC123_Value(void);
void ADC_MUX_Param_Init(void);

#endif

