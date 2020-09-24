/*
 * Timer_bsp.c
 *
 *  Created on: 24 Sep 2020
 *      Author: C
 */
#include "Timer_bsp.h"
InitStatus BSP_TIMER_Init(uint32_t Period)
{

	HAL_SYSTICK_Init();
	return HAL_TIMERx_Init(Period);
}
