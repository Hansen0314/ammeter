#include "stm32l0xx_ammeter.h"
//set privacy function
static void SystemClock_Config(void);
#ifdef UART_BSP_EN
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
UART_HandleTypeDef UartHandle;
// UARTx Init
InitStatus HAL_UARTx_Init(void)
{
	/* UART handler declaration */
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	  - Word Length = 8 Bits (7 data bit + 1 parity bit) :
					  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	  - Stop Bit    = One Stop bit
	  - Parity      = ODD parity
	  - BaudRate    = 256000 baud
	  - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance        = USARTx;

	UartHandle.Init.BaudRate   = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE; //UART_PARITY_ODD
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		/* Initialization Error */
		return INIT_ERROR;
	}
	return INIT_SUCCESS;

}

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;


  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();


  /* Enable USARTx clock */
  USARTx_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

}
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART2 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
void HAL_UARTx_Write_Raw_Data(uint8_t *pData, uint16_t Size)
{
	HAL_UART_Transmit(&UartHandle, pData, Size, 0xFFFF);
}
#endif  /* UART_BSP_EN */
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = MSI
  *            SYSCLK(Hz)                     = 2000000
  *            HCLK(Hz)                       = 2000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            Flash Latency(WS)              = 0
  *            Main regulator output voltage  = Scale3 mode
  * @retval None
  */
// HAL LED

#ifdef LED_BSP_EN
InitStatus HAL_LEDx_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	LED_GPIO_CLK_ENABLE();
	/* -2- Configure IO in output push-pull mode to drive external LEDs */
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = LED_PIN;
	HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(LED_GPIO_PORT,LED_PIN,GPIO_PIN_RESET);
	return INIT_SUCCESS;
}
void HAL_LEDx_Write(LEDStatus status)
{
	HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN ,status);
}
#endif
#ifdef ADC_BSP_EN
/* ADC handler declaration */
ADC_HandleTypeDef    AdcHandle;
InitStatus HAL_ADCx_Init(void){
	/* ADC channel configuration structure declaration */
	ADC_ChannelConfTypeDef        sConfig;
	/* ### - 1 - Initialize ADC peripheral #################################### */
	/*
	*  Instance                  = ADC1.
	*  OversamplingMode          = Disabled
	*  ClockPrescaler            = PCLK clock with no division.
	*  LowPowerAutoPowerOff      = Disabled (For this exemple continuous mode is enabled with software start)
	*  LowPowerFrequencyMode     = Enabled (To be enabled only if ADC clock is lower than 2.8MHz)
	*  LowPowerAutoWait          = Disabled (New conversion starts only when the previous conversion is completed)
	*  Resolution                = 12 bit (increased to 16 bit with oversampler)
	*  SamplingTime              = 7.5 cycles od ADC clock.
	*  ScanConvMode              = Forward
	*  DataAlign                 = Right
	*  ContinuousConvMode        = Enabled
	*  DiscontinuousConvMode     = Disabled
	*  ExternalTrigConvEdge      = None (Software start)
	*  EOCSelection              = End Of Conversion event
	*  DMAContinuousRequests     = DISABLE
	*/

	AdcHandle.Instance = ADCx;

	AdcHandle.Init.OversamplingMode      = DISABLE;

	AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;
	AdcHandle.Init.LowPowerAutoPowerOff  = DISABLE;
	AdcHandle.Init.LowPowerFrequencyMode = ENABLE;
	AdcHandle.Init.LowPowerAutoWait      = DISABLE;

	AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
	AdcHandle.Init.SamplingTime          = ADC_SAMPLETIME_7CYCLES_5;
	AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;
	AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
	AdcHandle.Init.ContinuousConvMode    = ENABLE;
	AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
	AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
	AdcHandle.Init.DMAContinuousRequests = DISABLE;
	AdcHandle.State = HAL_ADC_STATE_RESET;
	/* Initialize ADC peripheral according to the passed parameters */
	if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
	{
#ifdef DEBUG_EN
		printf("HAL_ADC_Init failed\n\r");
#endif
		return INIT_ERROR;
	}

	/* ### - 2 - Start calibration ############################################ */
	if (HAL_ADCEx_Calibration_Start(&AdcHandle, ADC_SINGLE_ENDED) != HAL_OK)
	{
#ifdef DEBUG_EN
		printf("HAL_ADCEx_Calibration_Start failed\n\r");
#endif
		return INIT_ERROR;
	}

	/* ### - 3 - Channel configuration ######################################## */
	/* Select Channel x to be converted */
	sConfig.Channel = ADCx_CHANNEL;
	if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
	{
#ifdef DEBUG_EN
		printf("HAL_ADC_ConfigChannel failed\n\r");
#endif
		return INIT_ERROR;
	}

	/*##- 4- Start the conversion process #######################################*/
	if ( HAL_ADC_Start(&AdcHandle)  != HAL_OK)
	{
	/* Start Conversation Error */
#ifdef DEBUG_EN
		uint8_t status;
		printf("HAL_ADC_Start failed\n\r");
		status = HAL_ADC_Start(&AdcHandle);
		printf("The status is %d\n\r",status);
#endif
		return INIT_ERROR;
	}
	return INIT_SUCCESS;
}
Functiontatus HAL_Get_ADC_Vaule(uint32_t *uwADCxConvertedValue)
{
    if (HAL_ADC_PollForConversion(&AdcHandle, 10) != HAL_OK)
    {
      /* End Of Conversion flag not set on time */
    	return FUNCTION_ERROR;
    }
    /* Check if the continuous conversion of regular channel is finished */
    if ((HAL_ADC_GetState(&AdcHandle) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC)
    {
        /*##-6- Get the converted value of regular channel  ########################*/
        *uwADCxConvertedValue = HAL_ADC_GetValue(&AdcHandle);
    }
    return FUNCTION_SUCCESS;
}
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};

  /*** Configure the GPIOs ***/
  /* Enable GPIO clock */
  ADCx_GPIO_CLK_ENABLE();

  /* Configure ADC1 Channel8 as analog input */
  gpioinitstruct.Pin = ADCx_GPIO_PIN ;
  gpioinitstruct.Mode = GPIO_MODE_ANALOG;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  HAL_GPIO_Init(ADCx_GPIO_PORT, &gpioinitstruct);

  /*** Configure the ADC peripheral ***/
  /* Enable ADC clock */
  ADCx_CLK_ENABLE();
}
/**
  * @brief  DeInitializes ADC MSP.
  * @param  hadc: ADC peripheral
  * @note ADC DeInit does not disable the GPIO clock
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  GPIO_InitTypeDef  gpioinitstruct;

  /*** DeInit the ADC peripheral ***/
  /* Disable ADC clock */
  ADCx_CLK_DISABLE();

  /* Configure the selected ADC Channel as analog input */
  gpioinitstruct.Pin = ADCx_GPIO_PIN ;
  HAL_GPIO_DeInit(ADCx_GPIO_PORT, gpioinitstruct.Pin);

  /* Disable GPIO clock has to be done by the application*/
  /* NUCLEO_ADCx_GPIO_CLK_DISABLE(); */
}
#endif
#ifdef TIMER_BSP_EN
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* TIM handle declaration */
TIM_HandleTypeDef    TimHandle;
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable MSI Oscillator */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.MSICalibrationValue=0x00;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0)!= HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

}
InitStatus HAL_SYSTICK_Init(void)
{
	HAL_Init();
	/* Configure the system clock to 2 MHz */
	SystemClock_Config();
	return INIT_SUCCESS;
}
InitStatus HAL_TIMERx_Init(uint32_t Period)
{
	/* Prescaler declaration */
	uint32_t uwPrescalerValue = 0;
	/*##-1- Configure the TIM peripheral #######################################*/
	  /* -----------------------------------------------------------------------
	    In this example TIM2 input clock (TIM2CLK) is set to APB1 clock (PCLK1),
	    since APB1 prescaler is equal to 1, TIM2CLK = PCLK1 = HCLK = SystemCoreClock

	    To get TIM2 counter clock at 10 KHz, the timer Prescaler is computed as follow :
	    Prescaler = (TIM2CLK / TIM2 counter clock) - 1
	    Prescaler = (SystemCoreClock/10 KHz) - 1

	    Note:
	     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32l0xx.c file.
	     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
	     variable value. Otherwise, any configuration based on this variable will be incorrect.
	     This variable is updated in three ways:
	      1) by calling CMSIS function SystemCoreClockUpdate()
	      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
	      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
	  ----------------------------------------------------------------------- */

	  /* Compute the prescaler value to have TIMx counter clock equal to 1M Hz */
	  uwPrescalerValue = (uint32_t)(SystemCoreClock / 1000000) - 1;

	  /* Set TIMx instance */
	  TimHandle.Instance = TIMx;

	  /* Initialize TIMx peripheral as follows:
	       + Period = 2500 - 1
	       + Prescaler = (SystemCoreClock/2500) - 1
	       + ClockDivision = 0
	       + Counter direction = Up
	  */
	  TimHandle.Init.Period            = Period - 1;
	  TimHandle.Init.Prescaler         = uwPrescalerValue;
	  TimHandle.Init.ClockDivision     = 0;
	  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;

	  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    return INIT_ERROR;
	  }

	  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
	  /* Start Channel1 */
	  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
	  {
	    /* Starting Error */
	    return INIT_ERROR;
	  }
	return 	INIT_SUCCESS;
}
/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /*##-1- Enable peripheral clock #################################*/
  /* TIMx Peripheral clock enable */
  TIMx_CLK_ENABLE();

  /*##-2- Configure the NVIC for TIMx ########################################*/
  /* Set the TIMx priority */
  HAL_NVIC_SetPriority(TIMx_IRQn, 3, 0);

  /* Enable the TIMx global Interrupt */
  HAL_NVIC_EnableIRQ(TIMx_IRQn);
}
void TIMx_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle);
}
__weak Functiontatus ADC_Sample(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */
	return FUNCTION_SUCCESS;
}
__weak void TimerTask(void)
{
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	ADC_Sample();
	TimerTask();
}

#endif /* TIMER_BSP_EN */

