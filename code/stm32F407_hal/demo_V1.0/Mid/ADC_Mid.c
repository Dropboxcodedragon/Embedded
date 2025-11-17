#include "ADC_Mid.h"
#include "adc.h"


volatile uint8_t g_MuxChlSel = 0; // MUX当前选择的通道
volatile uint8_t ShutInputDetectFlag = 0; //关闭输入检测的标志



__IO float ADC_Compare_Threshold[3] = // ADC比较阈值
	{
		100,
		1200,
		2200 // 20K及1.5K分压电阻对应的低、断开、高阈值
};

volatile uint16_t g_M1_A_Current_ZeroOffsetV = 2048;			//M1  A电流采样中点
volatile uint16_t g_M1_B_Current_ZeroOffsetV = 2048;			//M1  B电流采样中点
volatile uint16_t g_M2_A_Current_ZeroOffsetV = 2048;			//M2  A电流采样中点
volatile uint16_t g_M2_B_Current_ZeroOffsetV = 2048;			//M2  B电流采样中点
volatile uint16_t g_M3_A_Current_ZeroOffsetV = 2048;			//M3  A电流采样中点
volatile uint16_t g_M3_B_Current_ZeroOffsetV = 2048;			//M3  B电流采样中点


_ADC_MotorBsp_IV_Handle_	ADC_MotorsBsp_IV_Data;
__InputStatus_List InputStatus_List;

__ADCVoltage_List ADCVoltage_List;
_Analog_Mux_Handle Analog_Mux_Data[MUX_NUM][MUX_CHANNEL_NUM] = {
// Channel_Index, ADC_Index, Channel_InState, Channel_Voltage, Channel_Gain, R1, R2, filter_p1, filter_p2,
{
	{0,0,(InputStatus *)&InputStatus_List.pot_low_InState,(float *)&ADCVoltage_List.pot_low_volt,1.0f,0,1,0.25f,0.75f,0,0},
	{1,0,(InputStatus *)&InputStatus_List.M3_A_InState,(float *)&ADCVoltage_List.M3_A_volt,1.0f,200000,10000,0.25f,0.75f,0,0},
	{2,0,(InputStatus *)&InputStatus_List.M3_B_InState,(float *)&ADCVoltage_List.M3_B_volt,1.0f,200000,10000,0.25f,0.75f,0,0},
	{3,0,(InputStatus *)&InputStatus_List.speed_pot_InState,(float *)&ADCVoltage_List.speed_pot_volt,1.0f,100000,49900,0.25f,0.75f,0,0},
	{4,0,(InputStatus *)&InputStatus_List.M1_A_InState,(float *)&ADCVoltage_List.M1_A_volt,1.0f,200000,10000,0.25f,0.75f,0,0},
	{5,0,(InputStatus *)&InputStatus_List.M2_B_InState,(float *)&ADCVoltage_List.M2_B_volt,1.0f,200000,10000,0.25f,0.75f,0,0},
	{6,0,(InputStatus *)&InputStatus_List.M1_B_InState,(float *)&ADCVoltage_List.M1_B_volt,1.0f,200000,10000,0.25f,0.75f,0,0},
	{7,0,(InputStatus *)&InputStatus_List.M2_A_InState,(float *)&ADCVoltage_List.M2_A_volt,1.0f,200000,10000,0.25f,0.75f,0,0},
}};

_Analog_Mux_Handle ADC_Data[ADC_NUM][ADC_CHANNEL_NUM] = {
// Channel_Index, ADC_Index, Channel_InState, Channel_Voltage, Channel_Gain, R1, R2, filter_p1, filter_p2,
{
	{0,0,(InputStatus *)&InputStatus_List.cap_InState,(float *)&ADCVoltage_List.cap_volt,1.0f,100000,4990,0.25f,0.75f,0,0},
	{1,0,(InputStatus *)&InputStatus_List.bat_volt_InState,(float *)&ADCVoltage_List.bat_volt,1.0f,100000,4990,0.25f,0.75f,0,0},
	{2,0,(InputStatus *)&InputStatus_List.temperature1_InState,(float *)&ADCVoltage_List.temperature1_volt,1.0f,0,1,0.25f,0.75f,0,0},
	{3,0,(InputStatus *)&InputStatus_List.temperature2_InState,(float *)&ADCVoltage_List.temperature2_volt,1.0f,0,1,0.25f,0.75f,0,0},
	{4,0,(InputStatus *)&InputStatus_List.temperature3_InState,(float *)&ADCVoltage_List.temperature3_volt,1.0f,0,1,0.25f,0.75f,0,0},
	{5,0,(InputStatus *)&InputStatus_List.pot_wiper_InState,(float *)&ADCVoltage_List.pot_wiper_volt,1.0f,100000,49900,0.25f,0.75f,0,0},
	{6,0,(InputStatus *)&InputStatus_List.hall1_InState,(float *)&ADCVoltage_List.hall1_volt,100.0f,0,1,0.25f,0.75f,0,0},
	{7,0,(InputStatus *)&InputStatus_List.hall2_InState,(float *)&ADCVoltage_List.hall2_volt,100.0f,0,1,0.25f,0.75f,0,0},
	{8,0,(InputStatus *)&InputStatus_List.hall3_InState,(float *)&ADCVoltage_List.hall3_volt,100.0f,0,1,0.25f,0.75f,0,0},
	{9,0,(InputStatus *)&InputStatus_List.M2_A_InState2,(float *)&ADCVoltage_List.M2_A_current_volt,49.9f,0,1,0.25f,0.75f,0,0},
	{10,0,(InputStatus *)&InputStatus_List.M2_B_InState2,(float *)&ADCVoltage_List.M2_B_current_volt,49.9f,0,1,0.25f,0.75f,0,0},
}};
  
_ADC_MotorCurrent_Handle_ ADC_MotorCurrent_Params[ADC_Current_NUM] = { // ADC电流采样结构体
// Current_Gain, ADC_Offset, filter_p1, filter_p2, ZeroOffset, Linear_k, Linear_b, ZeroOffset_CalcOkFlag, Linear_CalcOkFlag, *Current_Value, *Current_ValueFilter
// 0、M1_A Current
{0.161132813f, M1_A_Current_ADC_Buffer_Index, 0.0625f, 0.9375f, (uint16_t *)&g_M1_A_Current_ZeroOffsetV, 1.0f, 0, 0, 0, &ADC_MotorsBsp_IV_Data.TractionM_R_ADC_IV.MotorADC_A_Current, &ADC_MotorsBsp_IV_Data.TractionM_R_ADC_IV.MotorADC_A_Current_Filter},
// 1、M1_B Current
{0.161132813f, M1_B_Current_ADC_Buffer_Index, 0.0625f, 0.9375f, (uint16_t *)&g_M1_B_Current_ZeroOffsetV, 1.0f, 0, 0, 0, &ADC_MotorsBsp_IV_Data.TractionM_R_ADC_IV.MotorADC_B_Current, &ADC_MotorsBsp_IV_Data.TractionM_R_ADC_IV.MotorADC_B_Current_Filter},
// 2、M2_A Current
{0.161132813f, M2_A_Current_ADC_Buffer_Index, 0.0625f, 0.9375f, (uint16_t *)&g_M2_A_Current_ZeroOffsetV, 1.0f, 0, 0, 0, &ADC_MotorsBsp_IV_Data.TractionM_L_ADC_IV.MotorADC_A_Current, &ADC_MotorsBsp_IV_Data.TractionM_L_ADC_IV.MotorADC_A_Current_Filter},
// 3、M2_B Current
{0.161132813f, M2_B_Current_ADC_Buffer_Index, 0.0625f, 0.9375f, (uint16_t *)&g_M2_B_Current_ZeroOffsetV, 1.0f, 0, 0, 0, &ADC_MotorsBsp_IV_Data.TractionM_L_ADC_IV.MotorADC_B_Current, &ADC_MotorsBsp_IV_Data.TractionM_L_ADC_IV.MotorADC_B_Current_Filter},
// 4、M3_A Current
{0.161132813f, M3_A_Current_ADC_Buffer_Index, 0.0625f, 0.9375f, (uint16_t *)&g_M3_A_Current_ZeroOffsetV, 1.0f, 0, 0, 0, &ADC_MotorsBsp_IV_Data.BrushM_ADC_IV.MotorADC_Current, &ADC_MotorsBsp_IV_Data.BrushM_ADC_IV.MotorADC_Current_Filter},
// 5、M3_B Current
{0.067988528f, M3_B_Current_ADC_Buffer_Index, 0.0625f, 0.9375f, (uint16_t *)&g_M3_B_Current_ZeroOffsetV, 1.0f, 0, 0, 0, &ADC_MotorsBsp_IV_Data.VacuumM_ADC_IV.MotorADC_Current, &ADC_MotorsBsp_IV_Data.VacuumM_ADC_IV.MotorADC_Current_Filter},
};



void ADC_Mux12_Channel_Poll(void)
{
	static uint8_t read_highspd_poll = 0;
	static uint8_t read_lowspd_poll = 0;
	switch (read_highspd_poll)
	{
		/*----------------高频率读取 0---------------------*/
		case 0:
			HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_SET);
			g_MuxChlSel = MUX_Sel_000; 
			read_highspd_poll++;
			break;
		
		/*----------------低频率读取---------------------*/
		case 1: //
			switch (read_lowspd_poll)
			{
				case 0:
					HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_RESET);
					g_MuxChlSel = MUX_Sel_001;
					read_lowspd_poll++;
					break;
				case 1: //低频率读取通道0
					HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_SET);
					g_MuxChlSel = MUX_Sel_010;
					read_lowspd_poll++;
					break;
				case 2: //低频率读取通道1
					HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_RESET);
					g_MuxChlSel = MUX_Sel_011;
					read_lowspd_poll++;
					break;
				case 3: //低频率读取通道2
				  HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_SET);
				  HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_SET);
					g_MuxChlSel = MUX_Sel_100;
					read_lowspd_poll++;
					break;
				case 4: //低频率读取通道3
					HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_SET);
					HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_RESET);
					g_MuxChlSel = MUX_Sel_101;
					read_lowspd_poll++;
					break;
				case 5: //低频率读取通道4
				  HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_RESET);
				  HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_SET);
					g_MuxChlSel = MUX_Sel_110;
					read_lowspd_poll++;
					break;
				case 6: //低频率读取通道5
					HAL_GPIO_WritePin(ADC_MUX_S2_GPIO_Port, ADC_MUX_S2_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(ADC_MUX_S1_GPIO_Port, ADC_MUX_S1_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(ADC_MUX_S0_GPIO_Port, ADC_MUX_S0_Pin, GPIO_PIN_RESET);
					g_MuxChlSel = MUX_Sel_111;
					read_lowspd_poll = 0;
					break;
				default:
					break;
			}
			read_highspd_poll = 0;
			break;
		default:
			read_highspd_poll = 0;
			break;
	}
}
void read_MUX12_Status(uint8_t chl, uint16_t data1)
{
	float data_float_t = 0.0f;
	
	Analog_Mux_Data[0][chl].Channel_ADCVaule = data1;
	data_float_t = data1 * Analog_Mux_Data[0][chl].Channel_Gain;
	Analog_Mux_Data[0][chl].Channel_Voltage = data_float_t;
	*Analog_Mux_Data[0][chl].Channel_VoltageFilter = (data_float_t * Analog_Mux_Data[0][chl].filter_p1 + (*Analog_Mux_Data[0][chl].Channel_VoltageFilter) * Analog_Mux_Data[0][chl].filter_p2);

	//输入状态更新
	if (ShutInputDetectFlag == 0x00)
	{
		// ch0
		if (*Analog_Mux_Data[0][chl].Channel_VoltageFilter < ADC_Compare_Threshold[LowThreshold_Index])
		{
			*Analog_Mux_Data[0][chl].Channel_InState = Input_Low;
		}
		else if (*Analog_Mux_Data[0][chl].Channel_VoltageFilter < ADC_Compare_Threshold[OpenThreshold_Index])
		{
			*Analog_Mux_Data[0][chl].Channel_InState = Input_Open;
		}
		else
		{
			*Analog_Mux_Data[0][chl].Channel_InState = Input_High;
		}

		// ch1
		if (*Analog_Mux_Data[1][chl].Channel_VoltageFilter < ADC_Compare_Threshold[LowThreshold_Index])
		{
			*Analog_Mux_Data[1][chl].Channel_InState = Input_Low;
		}
		else if (*Analog_Mux_Data[1][chl].Channel_VoltageFilter < ADC_Compare_Threshold[OpenThreshold_Index])
		{
			*Analog_Mux_Data[1][chl].Channel_InState = Input_Open;
		}
		else
		{
			*Analog_Mux_Data[1][chl].Channel_InState = Input_High;
		}
	}
}

void read_MUX_Poll(uint16_t data1)
{
	static uint8_t g_Sel_Step = 0;

	//-------------模拟复用器2读取时序
	switch (g_Sel_Step)
	{
		case 0:
			ADC_Mux12_Channel_Poll();
			g_Sel_Step++;
			break;
		case 1:
			g_Sel_Step++;
			break;
		case 2:
			g_Sel_Step = 0;
			read_MUX12_Status(g_MuxChlSel, data1);
			break;
		default:
			g_Sel_Step = 0;
			break;
	}
}

/********************************************************************************************
**函数名:	ADC_MUX_Param_Init
**功能:		模拟复用器 参数初始化
**返回值:	None
**参数:	  None
**备注:
*********************************************************************************************/
void ADC_MUX_Param_Init(void)
{
	uint8_t i, j = 0;

	//初始化模拟复用器通道增益
	for (i = 0; i < ADC_NUM; i++)
	{
		for (j = 0; j < ADC_CHANNEL_NUM; j++)
		{
			ADC_Data[i][j].Channel_Gain = (3.3f * (float)(ADC_Data[i][j].R1 + ADC_Data[i][j].R2) / (ADC_Data[i][j].R2 * 4096));
		}
	}

	for (i = 0; i < MUX_NUM; i++)
	{
		for (j = 0; j < MUX_CHANNEL_NUM; j++)
		{
			Analog_Mux_Data[i][j].Channel_Gain = (3.3f * (float)(Analog_Mux_Data[i][j].R1 + Analog_Mux_Data[i][j].R2) / (Analog_Mux_Data[i][j].R2 * 4096));
		}
	}
	

}
void ADC_to_voltage(uint8_t chl,uint32_t data1)
{
	float data_float_t = 0.0f;
	
	ADC_Data[0][chl].Channel_ADCVaule = data1;
	data_float_t = data1 * ADC_Data[0][chl].Channel_Gain;
	ADC_Data[0][chl].Channel_Voltage = data_float_t;
	*ADC_Data[0][chl].Channel_VoltageFilter = (data_float_t * ADC_Data[0][chl].filter_p1 + (*ADC_Data[0][chl].Channel_VoltageFilter) * ADC_Data[0][chl].filter_p2);

	//输入状态更新
//	if (ShutInputDetectFlag == 0x00)
	{
		// ch0
		if (*ADC_Data[0][chl].Channel_VoltageFilter < ADC_Compare_Threshold[LowThreshold_Index])
		{
			*ADC_Data[0][chl].Channel_InState = Input_Low;
		}
		else if (*ADC_Data[0][chl].Channel_VoltageFilter < ADC_Compare_Threshold[OpenThreshold_Index])
		{
			*ADC_Data[0][chl].Channel_InState = Input_Open;
		}
		else
		{
			*ADC_Data[0][chl].Channel_InState = Input_High;
		}
	}
}

void get_ADC123_Value(void)
{
	uint8_t i = 0;
	uint8_t offset = 0;
//	float tmp = 0;
	
	//-----------------拖动电机
	if(0x00 == CurrentZeroOffsetReadFlg)
	{
		g_M1_A_Current_ZeroOffsetV = (aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+M1_A_Current_ADC_Buffer_Index] + g_M1_A_Current_ZeroOffsetV*15)/16;
		g_M1_B_Current_ZeroOffsetV = (aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+M1_B_Current_ADC_Buffer_Index] + g_M1_B_Current_ZeroOffsetV*15)/16;
		g_M2_A_Current_ZeroOffsetV  = (aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+M2_A_Current_ADC_Buffer_Index] + g_M2_A_Current_ZeroOffsetV*15)/16;
		g_M2_B_Current_ZeroOffsetV  = (aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+M2_B_Current_ADC_Buffer_Index] + g_M2_B_Current_ZeroOffsetV*15)/16;

		g_M3_A_Current_ZeroOffsetV = (aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+M3_B_Current_ADC_Buffer_Index] + g_M3_A_Current_ZeroOffsetV*15)/16;
		g_M3_B_Current_ZeroOffsetV = (aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+M3_B_Current_ADC_Buffer_Index] + g_M3_B_Current_ZeroOffsetV*15)/16;
	}
	else
	{
		for(i=0;i<ADC_Current_NUM;i++)
		{
			//得到ADC偏置offset
			offset = ADC_MotorCurrent_Params[i].ADC_Offset;
			ADC_MotorCurrent_Params[i].ADC_Vaule = aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+offset];
			//计算电流值
			*ADC_MotorCurrent_Params[i].Current_Value = (ADC_MotorCurrent_Params[i].Current_Gain * 
							(aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart+offset] - (*ADC_MotorCurrent_Params[i].ZeroOffset)));
			//计算电流值滤波
			*ADC_MotorCurrent_Params[i].Current_ValueFilter = ((*ADC_MotorCurrent_Params[i].Current_Value) * ADC_MotorCurrent_Params[i].filter_p1 + (*ADC_MotorCurrent_Params[i].Current_ValueFilter) * ADC_MotorCurrent_Params[i].filter_p2);

			//注意电流反向  请在电机控制库BSP底层进行  根据运行方向来重新设定电流符号
		}
	}
	ADC_to_voltage(0,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +CAP_ADC_Buffer_Index]);
	ADC_to_voltage(1,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +BAT_ADC_Buffer_Index]);
	ADC_to_voltage(2,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +TEMP1_ADC_Buffer_Index]);
	ADC_to_voltage(3,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +TEMP2_ADC_Buffer_Index]);
	ADC_to_voltage(4,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +TEMP3_ADC_Buffer_Index]);
	ADC_to_voltage(5,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +POT_WIPER_ADC_Buffer_Index]);
	ADC_to_voltage(6,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +HALL1_ADC_Buffer_Index]);
	ADC_to_voltage(7,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +HALL2_ADC_Buffer_Index]);
	ADC_to_voltage(8,aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +HALL3_ADC_Buffer_Index]);
	read_MUX_Poll(aADCTripleConvertedValue[ADC_ActiveBuffer_AddressStart +MUX_ADC_Buffer_Index]);

}
