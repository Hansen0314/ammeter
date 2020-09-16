#include "Uart_bsp.h"
#ifdef UART_BSP_EN
ErrorStatus UART_Init(BSP_UART_InitTypeDef *BSP_UART)
{
	/* UART handler declaration */
	UART_HandleTypeDef UartHandle;
	UartHandle.Instance        = USARTx;
	UartHandle.Init.BaudRate   = BSP_UART->BaudRate;;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	if(HAL_UART_Init(&UartHandle) != HAL_OK)
		return ERROR;
	return SUCCESS;
}
#endif
