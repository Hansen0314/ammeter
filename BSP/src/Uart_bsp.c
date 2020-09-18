#include "Uart_bsp.h"
#ifdef UART_BSP_EN
 InitStatus BSP_UART_Init(void){
	 return HAL_UARTx_Init();
 }
#else
 InitStatus BSP_UART_Init(void){return INIT_SUCCESS;}
#endif
