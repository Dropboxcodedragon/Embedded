/************************************* Copyright(C)******************************
**
**                 (C) Copyright 2025, @mayuxin,China, GCU.
**                            All Rights Reserved
**                     				By( @myx)
**-------------------------------------------------------------------------------
** @FileName   : uart_mid.c
** @Brief	     :
**
**-------------------------------------------------------------------------------
** @Author     : @zhaofeng
** @Version    : v1.0
** @Date       : 2025-05-08
**-------------------------------------------------------------------------------
** @Mender	   : Node
** @Version    : Node
** @Date       : Node
** @Brief      : Node
********************************************************************************/

#include "uart_mid.h"
#include "usart.h"

USART_TxCmd USART_TxMessage;
USART_RxCmd USART_RxMessage;
uint16_t rx_len = 0;
__USARTx_Manage USARTx_Manage;


//后续对其进行分层处理
void USART_Pakage_Recv(void)
{
	
}
void USART_Pakage_Send(void)
{
	USART_TxMessage.CrcData = 0xedcb;
	USART_TxMessage.Data = 0xa0987654;
	USART_TxMessage.Header = 0x3210;
	HAL_UART_Transmit(&huart2, (uint8_t *)&USART_TxMessage, USART_PakageSend_Num,10);
}
void UART_Poll(void)
{
	USART_Pakage_Send();

}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) 
{
    if (huart->Instance == USART2) 
		{
			USARTx_Manage.USARTx_TxBusy_Flag = false;
		}
}
uint8_t test = 0;
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART2)
	{
//		if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
//		{
//			HAL_UART_DMAStop(&huart2);                               //停止接收
//			 __HAL_UART_CLEAR_IDLEFLAG(&huart2); //清除IDLE标志
			
			USARTx_Manage.USARTx_RevData_Lenth = Size;
			
		//------------总线空闲，根据DMA接收到的数据长度 
			if(USARTx_Manage.USARTx_RevData_Lenth > 0)								//判断接收的包长度是否出错，如果没有异常则进行解包
			{
				USART_Pakage_Recv();
				if(USARTx_Manage.USARTx_TxBusy_Flag == false)
				{
//				memcpy((uint8_t*)USARTx_Manage.USARTx_RX_Buffer,(uint8_t*)&USARTx_DMA_RX_Buffer[0],USARTx_Manage.USARTx_RevData_Lenth);		//拷贝到缓存
					USARTx_Manage.USARTx_TxBusy_Flag = true;

//					USART2_TxStata.stata = 1;
					test = sizeof(USART_RxMessage);
					
//					USART_TxMessage.CrcData = USART_RxMessage.CrcData;
//					USART_TxMessage.Data = USART_RxMessage.Data;
//					USART_TxMessage.Header = USART_RxMessage.Header;
	//				memcpy(&USART_TxMessage, &USART_RxMessage,sizeof(USART_RxMessage));
	//				memcpy(&USART_TxMessage, &USART_RxMessage,test);
				//回传测试 测试后屏蔽
					HAL_UART_Transmit_DMA(&huart2, (uint8_t *)&USARTx_DMA_RX_Buffer, USARTx_Manage.USARTx_RevData_Lenth);
					HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *)&USARTx_DMA_RX_Buffer, USARTx_RX_BUFFERSIZE);
	//			__HAL_UART_CLEAR_IDLEFLAG(&huart2);
					
				}
			}
//		}
	}
}


