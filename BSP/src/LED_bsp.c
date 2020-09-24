/*
 * LED_bsp.c
 *
 *  Created on: 23 Sep 2020
 *      Author: C
 */
#include "LED_bsp.h"
#ifdef UART_BSP_EN
InitStatus BSP_LED_Init()
{
	printf("Init LED ...\n\r");
	while(HAL_LEDx_Init());
	printf("Init LED successfully\n\r");
	return INIT_SUCCESS;
}
void BSP_LED_Write(LEDStatus status)
{
	HAL_LEDx_Write(status);
}
#else
InitStatus BSP_LED_Init(){return INIT_SUCCESS;}
void BSP_LED_Write(LEDStatus status){}
#endif
