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
	BSP_UART_Init();
	/* Output a message on Hyperterminal using printf function */
	printf("\n\r UART Printf Example: retarget the C library printf function to the UART\n\r");
	printf("** Test finished successfully. ** \n\r");
	for(;;){
	}
}
