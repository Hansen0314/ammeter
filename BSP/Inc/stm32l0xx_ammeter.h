#ifndef __STM32L0XX_AMMETER_H
#define __STM32L0XX_AMMETER_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32l0xx_hal.h"
#include "stdio.h"

typedef enum
{
INIT_SUCCESS = 0,
INIT_ERROR = !INIT_SUCCESS
} InitStatus;

typedef enum
{
LED_OFF = 1,
LED_ON = !LED_OFF
} LEDStatus;

typedef enum
{
FUNCTION_SUCCESS = 0,
FUNCTION_ERROR = !FUNCTION_SUCCESS
} Functiontatus;

//select module what you need
#define UART_BSP_EN
#define LED_BSP_EN
#define ADC_BSP_EN
#define DEBUG_EN
//#define SYSTICK_EN
#define TIMER_BSP_EN

#ifdef UART_BSP_EN

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_9 // GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF4_USART2
#define USARTx_RX_PIN                    GPIO_PIN_10 // GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF4_USART2

void HAL_UARTx_Write_Raw_Data(uint8_t *pData, uint16_t Size);
InitStatus HAL_UARTx_Init(void);
#endif /* UART_BSP_EN */
#ifdef __cplusplus
}
#endif /*  */
#ifdef LED_BSP_EN
#define LED_PIN                           	GPIO_PIN_1
#define LED_GPIO_PORT                     	GPIOB
#define LED_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOB_CLK_ENABLE()
InitStatus HAL_LEDx_Init(void);
void HAL_LEDx_Write(LEDStatus status);
#endif /* LED_BSP_EN */
#ifdef ADC_BSP_EN
#define ADCx                                 ADC1
#define ADCx_CLK_ENABLE()                  __HAL_RCC_ADC1_CLK_ENABLE()
#define ADCx_CLK_DISABLE()  			   __HAL_RCC_ADC1_CLK_DISABLE()
#define ADCx_CHANNEL                         ADC_CHANNEL_4
#define ADCx_GPIO_PORT                       GPIOA
#define ADCx_GPIO_PIN                        GPIO_PIN_4
#define ADCx_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADCx_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOA_CLK_DISABLE()
InitStatus HAL_ADCx_Init(void);
Functiontatus HAL_Get_ADC_Vaule(uint32_t *uwADCxConvertedValue);
#endif/* ADC_BSP_EN */
#ifdef TIMER_BSP_EN
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* User can use this section to tailor TIMx instance used and associated
   resources */
/* Definition for TIMx clock resources */
#define TIMx                           TIM2
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()

/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM2_IRQn
#define TIMx_IRQHandler                TIM2_IRQHandler
InitStatus HAL_SYSTICK_Init(void);
InitStatus HAL_TIMERx_Init(uint32_t Period);
//Functiontatus ADC_Sample(void);
void TimerTask(void);
#endif/* SYSTICK_EN */
#endif
