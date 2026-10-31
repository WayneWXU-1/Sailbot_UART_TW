/*
 * UARTMod.h
 *
 *  Created on: Oct 24, 2026
 *      Author: danielma
 */

#ifndef INC_UARTMOD_H_
#define INC_UARTMOD_H_

#include "main.h"
#include "stm32u5xx_hal.h"

void UARTMod_Init(void);
// void UARTMod_ErrorHandle(UART_HandleTypeDef *huart);
void UARTMod_RxCallback(UART_HandleTypeDef *huart);


#endif /* INC_UARTMOD_H_ */
