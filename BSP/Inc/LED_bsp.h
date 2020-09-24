/*
 * LED_bsp.h
 *
 *  Created on: 23 Sep 2020
 *      Author: C
 */

#ifndef INC_LED_BSP_H_
#define INC_LED_BSP_H_
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32l0xx_ammeter.h"
InitStatus BSP_LED_Init(void);
void BSP_LED_Write(LEDStatus status);
#ifdef __cplusplus
}
#endif
#endif /* INC_LED_BSP_H_ */
