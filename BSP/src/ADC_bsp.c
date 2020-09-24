/*
 * ADC_bsp.c
 *
 *  Created on: 23 Sep 2020
 *      Author: C
 */
#include "ADC_bsp.h"
#include "math.h"
#ifdef ADC_BSP_EN
InitStatus BSP_ADC_Init(void)
{
	printf("Init ADC ...\n\r");
	while(HAL_ADCx_Init());
	printf("Init ADC successfully\n\r");
	return INIT_SUCCESS;
}
Functiontatus BSP_Get_ADC_Vaule(uint32_t *uwADCxConvertedValue)
{
	return HAL_Get_ADC_Vaule(uwADCxConvertedValue);
}
// return mA
uint64_t VoltageToCurrent(uint32_t *Voltage , uint8_t size)
{
	uint32_t Current = 0;
	uint64_t RMSCurrent = 0;
	for (uint8_t i=0; i < size ; i++)
	{
#ifdef DEBUG_EN
		printf("The adc value is %d \n\r",(int)Voltage[i]);
#endif
		Voltage[i] = Voltage[i] * 3300 / 4096.0 ; // convert to voltage (mV)
		Current = Voltage[i] * 1000 / 31.25; //convert to current (mA)
		RMSCurrent += Current * Current;
	}
	RMSCurrent = RMSCurrent / size;
	RMSCurrent = sqrt(RMSCurrent);
	return RMSCurrent;
}
#else
InitStatus BSP_ADC_Init(void) {return INIT_SUCCESS;}
Functiontatus BSP_Get_ADC_Vaule(uint32_t *uwADCxConvertedValue){return FUNCTION_SUCCESS;}
#endif

