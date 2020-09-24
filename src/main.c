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

uint8_t ADC_enable = 0;
#define ARRAY_SIZE 100
#define TIMETASKNUMBER 1
uint32_t ADC_Vaule_Array[ARRAY_SIZE] = {0};
Functiontatus ADC_Sample(void)
{
	uint32_t ADC_Vaule;
	volatile static uint8_t Sample_Times = 0;
	volatile static uint8_t Start_enable = 0;

	if (!ADC_enable)
	{
		return FUNCTION_ERROR;
	}

	while(BSP_Get_ADC_Vaule(&ADC_Vaule));
//	if (2 != ADC_Vaule &&  0 == Start_enable)
//		return FUNCTION_ERROR;
//	else
//		Start_enable = 1;

	ADC_Vaule_Array[Sample_Times ++] = ADC_Vaule;

	if(Sample_Times == ARRAY_SIZE)
	{
		Sample_Times = 0;
		ADC_enable = 0;
		Start_enable = 0;
	}

	return FUNCTION_SUCCESS;
}
TimeTask TaskArray[TIMETASKNUMBER] = {
		{.Callback = ADC_Sample,.TaskTimeBase = 1},
};
int main(void)
{
	uint64_t Current_Vaule = 0;
	BSP_TIMER_Init(20000 / ARRAY_SIZE);
	BSP_UART_Init();
	BSP_LED_Init();
	BSP_ADC_Init(); //sample time 10us
	ADC_enable = 1;
	for(;;){
		BSP_LED_Write(LED_ON);
		HAL_Delay(500);
		BSP_LED_Write(LED_OFF);
		HAL_Delay(500);
		while (!ADC_enable){
			Current_Vaule = VoltageToCurrent(ADC_Vaule_Array,ARRAY_SIZE);
			ADC_enable = 1;
		}
		printf("The RMS current value is %d mA\n\r",(int)Current_Vaule);
	}
}

void TimerTask(void){
	static uint8_t TimeBase;
	TimeBase ++ ;
	for(uint8_t i = 0; i < sizeof(TaskArray)/sizeof(TimeTask) ; i++)
	{
		if (0 == (TimeBase % TaskArray[i].TaskTimeBase))
			TaskArray[i].Callback();
	}
}
