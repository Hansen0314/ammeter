/*
 * ADC_bsp.h
 *
 *  Created on: 23 Sep 2020
 *      Author: C
 */

#ifndef INC_ADC_BSP_H_
#define INC_ADC_BSP_H_
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32l0xx_ammeter.h"
InitStatus BSP_ADC_Init(void);
Functiontatus BSP_Get_ADC_Vaule(uint32_t *uwADCxConvertedValue);
uint64_t VoltageToCurrent(uint32_t *Voltage , uint8_t size);
#ifdef __cplusplus
}
#endif
#endif /* INC_ADC_BSP_H_ */
