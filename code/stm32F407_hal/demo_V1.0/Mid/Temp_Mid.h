#ifndef __UART_MID_H__
#define __UART_MID_H__

#include "main.h"
#include "usart.h"

/*----------------------串口数据结构体定义---------------------*/
#pragma pack (1)
typedef struct _USART_TxCmd_
{
	uint16_t Header;								//数据头 
	uint32_t Data;									//高16位是索引地址，低16位是数据
	uint16_t CrcData;								//16位CRC校验值
}USART_TxCmd;
#pragma pack()


/************************** 串口发送接收管理 **************************/
typedef volatile struct __USARTx_Manage_
{
	bool 			USARTx_Sending_Flag;						//串口正在发送数据标志
	bool 			USARTx_TxBusy_Flag;						//串口正在发送数据标志
	bool 			USARTx_RevDataAvailable_Flag;		//串口数据有效标志
	bool 			USARTx_TxMode_EnableStatus;		//串口发送引脚使能状态
	
	uint8_t 	USARTx_RX_Buffer[USARTx_RX_BUFFERSIZE];
	uint8_t 	USARTx_TX_Buffer[USARTx_TX_BUFFERSIZE]; 
	uint8_t 	USARTx_RevData_Lenth;						//串口接收数据长度
	uint8_t 	USARTx_SendData_Lenth;					//串口发送数据长度
	uint16_t 	USARTx_SendData_TimeOut;				//串口发送数据超时，开始发送数据，超时后复位串口
	uint8_t 	USARTx_SendData_Lenth_Buffer;	//串口发送长度缓存
}__USARTx_Manage;

#pragma pack (1)
typedef struct _USART_RxCmd_
{
	uint16_t Header;								//数据头 
	uint32_t Data;									//高16位是索引地址，低16位是数据
	uint16_t CrcData;								//16位CRC校验值
}USART_RxCmd;
#pragma pack()

extern __USARTx_Manage USARTx_Manage;


#endif

