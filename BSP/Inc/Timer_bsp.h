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
typedef struct _TimeTask{
	 uint32_t TaskTimeBase; //Unit us  /* up to your timer*/
	__IO uint32_t *TaskInput;
	 uint8_t TaskInputSize;
	__IO uint32_t *TaskOutput;
	 uint8_t TaskOutputSize;
	 Functiontatus (* Callback)(void);
	 struct _TimeTask *NextTask;
} TimeTask;

#ifdef __cplusplus
}
#endif

#endif /* INC_TIMER_BSP_H_ */
