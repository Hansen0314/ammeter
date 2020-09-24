/*
 * TIMER_bsp.h
 *
 *  Created on: 24 Sep 2020
 *      Author: C
 */

#ifndef INC_TIMER_BSP_H_
#define INC_TIMER_BSP_H_

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32l0xx_ammeter.h"
 InitStatus BSP_TIMER_Init(uint32_t Period);
#ifdef __cplusplus
}
#endif

#endif /* INC_TIMER_BSP_H_ */
