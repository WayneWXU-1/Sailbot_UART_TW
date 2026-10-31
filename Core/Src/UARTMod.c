/*
 * UARTMod.c
 *
 *  Created on: Oct 24, 2026
 *      Author: danielma
 */

#include "UARTMod.h"
#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

static uint8_t rx1_data;
static uint8_t rx2_data;
static uint8_t rx3_data;

void UARTMod_Init(void) {
	HAL_UART_Receive_IT(&huart1, &rx1_data, 1);
	HAL_UART_Receive_IT(&huart2, &rx2_data, 1);
	HAL_UART_Receive_IT(&huart3, &rx3_data, 1);
}

void UARTMod_RxCallback(UART_HandleTypeDef *huart) {

	const uint32_t TX_TIMEOUT_MS = 5;

	// UART for USB connection
	if (huart->Instance == USART1) {
		HAL_UART_Transmit(&huart2, &rx1_data, 1, TX_TIMEOUT_MS);
		HAL_UART_Transmit(&huart3, &rx1_data, 1, TX_TIMEOUT_MS);

		HAL_UART_Receive_IT(&huart1, &rx1_data, 1);
	}

	// UART for other NUCLEO connection
	else if (huart->Instance == USART2 || huart->Instance == USART3) {

		// Grab the correct byte depending on which UART triggered
		uint8_t current_data = (huart->Instance == USART2) ? rx2_data : rx3_data;

		// Control the green LED using BSP commands
		if (current_data == 'g') {
			BSP_LED_On(LED_GREEN);
		} else {
			BSP_LED_Off(LED_GREEN);
		}
		if (current_data == 'r') {
			BSP_LED_On(LED_RED);
		} else {
			BSP_LED_Off(LED_RED);
		}
		if (current_data == 'b') {
			BSP_LED_On(LED_BLUE);
		} else {
			BSP_LED_Off(LED_BLUE);
		}

		// Send the raw character straight to USB/PuTTY through USART1
		HAL_UART_Transmit(&huart1, &current_data, 1, TX_TIMEOUT_MS);

		// Re-enable the specific interrupt that just fired
		if (huart->Instance == USART2) {
			HAL_UART_Receive_IT(&huart2, &rx2_data, 1);
		} else {
			HAL_UART_Receive_IT(&huart3, &rx3_data, 1);
		}
	}
}
