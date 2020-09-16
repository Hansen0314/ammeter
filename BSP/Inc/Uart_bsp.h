/**
  ******************************************************************************
  * @file    Uart_bsp.h
  * @author  MCD Application Team
  * @brief   Header file of ADC HAL extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_BSP_H
#define __UART_BSP_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32l0xx.h"
typedef struct __BSP_UART_InitTypeDef{
uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
                                         The baud rate register is computed using the following formula:
                                         LPUART:
                                         =======
                                            Baud Rate Register = ((256 * lpuart_ker_ck) / ((huart->Init.BaudRate)))
                                         where lpuart_ker_ck is the UART input clock
                                         UART:
                                         =====
                                         - If oversampling is 16 or in LIN mode,
                                            Baud Rate Register = ((uart_ker_ck) / ((huart->Init.BaudRate)))
                                         - If oversampling is 8,
                                            Baud Rate Register[15:4] = ((2 * uart_ker_ck) / ((huart->Init.BaudRate)))[15:4]
                                            Baud Rate Register[3] =  0
                                            Baud Rate Register[2:0] =  (((2 * uart_ker_ck) / ((huart->Init.BaudRate)))[3:0]) >> 1
                                         where uart_ker_ck is the UART input clock */

uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                         This parameter can be a value of @ref UARTEx_Word_Length. */

uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                         This parameter can be a value of @ref UART_Stop_Bits. */

uint32_t Parity;                    /*!< Specifies the parity mode.
                                         This parameter can be a value of @ref UART_Parity
                                         @note When parity is enabled, the computed parity is inserted
                                               at the MSB position of the transmitted data (9th bit when
                                               the word length is set to 9 data bits; 8th bit when the
                                               word length is set to 8 data bits). */

uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                         This parameter can be a value of @ref UART_Mode. */

uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled
                                         or disabled.
                                         This parameter can be a value of @ref UART_Hardware_Flow_Control. */

uint32_t OverSampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to f_PCLK/8).
                                         This parameter can be a value of @ref UART_Over_Sampling. */

uint32_t OneBitSampling;            /*!< Specifies whether a single sample or three samples' majority vote is selected.
                                         Selecting the single sample method increases the receiver tolerance to clock
                                         deviations. This parameter can be a value of @ref UART_OneBit_Sampling. */
}BSP_UART_InitTypeDef;
#ifdef UART_BSP_EN
ErrorStatus UART_Init(BSP_UART_InitTypeDef *BSP_UART);
#else
ErrorStatus UART_Init(BSP_UART_InitTypeDef *BSP_UART){return SUCCESS};
#endif
#ifdef __cplusplus
}
#endif /*  */
#endif
