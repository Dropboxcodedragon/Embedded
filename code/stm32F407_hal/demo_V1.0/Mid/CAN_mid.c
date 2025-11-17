#include "CAN_mid.h"
#include "can.h"

CanTxMsg TxMessage;
CanRxMsg RxMessage;


CAN_RxHeaderTypeDef CAN_RxHeader;
CAN_TxHeaderTypeDef CAN_TxHeader;


//后续对其进行分层处理
void CAN_Pakage_Recv(CanRxMsg *CAN2_RxMessage)
{
	
}
void CAN_Pakage_Send(void)
{
}
void CAN_Poll(void)
{
	CAN_Pakage_Recv(&RxMessage);
}
void CAN_Send(void)
{
			uint32_t CAN_TX_BOX = 0;
			CAN_TxHeader.IDE = CAN_ID_STD;
			CAN_TxHeader.ExtId = 0x1c308100;
			CAN_TxHeader.StdId = 0x0107;
			CAN_TxHeader.RTR = CAN_RTR_DATA;
			CAN_TxHeader.DLC = 8;
			CAN_TxHeader.TransmitGlobalTime = DISABLE;
			
			RxMessage.Data[0] = 0x01;
			RxMessage.Data[1] = 0x02;
			RxMessage.Data[2] = 0x03;
			RxMessage.Data[3] = 0x04;
			RxMessage.Data[4] = 0x05;
			RxMessage.Data[5] = 0x06;
			RxMessage.Data[6] = 0x07;
			RxMessage.Data[7] = 0x08;
	
			HAL_CAN_AddTxMessage(&hcan2, &CAN_TxHeader, RxMessage.Data, &CAN_TX_BOX);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint32_t CAN_TX_BOX = 0;
	if(0 != HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0))
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &CAN_RxHeader, RxMessage.Data);
	//回传
		CAN_TxHeader.IDE = CAN_ID_EXT;
		CAN_TxHeader.ExtId = 0x1c308100;
		CAN_TxHeader.StdId = 0x0107;
		CAN_TxHeader.RTR = CAN_RTR_DATA;
		CAN_TxHeader.DLC = 4;
		CAN_TxHeader.TransmitGlobalTime = DISABLE;
		HAL_CAN_AddTxMessage(&hcan2, &CAN_TxHeader, RxMessage.Data, &CAN_TX_BOX);
	}
//	if(0 != HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO1))
//		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1, &CAN_RxHeader, RxMessage.Data);
	//协议解析

	//回传
//	HAL_CAN_AddTxMessage(&hcan2, &CAN_TxHeader, RxMessage.Data, uint32_t *pTxMailbox)
}

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
{
	uint32_t CAN_TX_BOX = 0;
	if(0 != HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO0))
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &CAN_RxHeader, RxMessage.Data);
	//回传
		CAN_TxHeader.IDE = CAN_ID_EXT;
		CAN_TxHeader.ExtId = 0x1c308100;
		CAN_TxHeader.StdId = 0x0107;
		CAN_TxHeader.RTR = CAN_RTR_DATA;
		CAN_TxHeader.DLC = 4;
		CAN_TxHeader.TransmitGlobalTime = DISABLE;
		HAL_CAN_AddTxMessage(&hcan2, &CAN_TxHeader, RxMessage.Data, &CAN_TX_BOX);
	}
//	if(0 != HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO1))
//		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1, &CAN_RxHeader, RxMessage.Data);
	//协议解析

	//回传
//	HAL_CAN_AddTxMessage(&hcan2, &CAN_TxHeader, RxMessage.Data, uint32_t *pTxMailbox)
}