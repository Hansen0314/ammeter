/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32l0xx.h"
#include "bsp_header.h"
int main(void)
{
	BSP_UART_InitTypeDef  BSP_UART;
	BSP_UART.BaudRate = 9600;
	UART_Init(&BSP_UART);
	for(;;);
}
