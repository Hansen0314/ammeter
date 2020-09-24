#include "Uart_bsp.h"
#ifdef UART_BSP_EN
 InitStatus BSP_UART_Init(void){
	 return HAL_UARTx_Init();
 }
 void BSP_UART_Write(uint8_t *pData, uint16_t Size)
 {
	 HAL_UARTx_Write_Raw_Data(pData,Size);
 }
#else
 InitStatus BSP_UART_Init(void){return INIT_SUCCESS;}
 void BSP_UART_Write(uint8_t *pData, uint16_t Size){}
#endif
