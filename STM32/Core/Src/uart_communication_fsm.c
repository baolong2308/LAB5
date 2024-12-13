/*
 * uart_communication_fsm.c
 *
 *  Created on: Dec 11, 2024
 *      Author: admin
 */
#include <uart_communication_fsm.h>

int state = UART_INIT; //

uint32_t adc_value = 0;
uint8_t str[100];

void uart_communication_fsm() {
	switch (state) {
	case UART_INIT:
		state = UART_IDLE;
		break;
	case UART_IDLE:
		if (getReqFlag() == 1) {
			setReqFlag(0);
			state = SEND_ADC;

			adc_value = HAL_ADC_GetValue(&hadc1);
			HAL_UART_Transmit(&huart2, (void*) str,sprintf((char*) str, "!ADC=%d#\r\n", (int) adc_value),1000);
			setTimer(0, 300);
		}

		if (getOKFlag() == 1) {
			setOKFlag(0);
		}

		break;
	case SEND_ADC:
		if (getOKFlag() == 1) {
			setOKFlag(0);
			state = UART_IDLE;
		}

		if (isTimerExpired(0) == 1) {
			setTimer(0, 300);
			adc_value = HAL_ADC_GetValue(&hadc1);
			HAL_UART_Transmit(&huart2, (void*) str,sprintf((char*) str, "!ADC=%d#\r\n", (int) adc_value),1000);
			//HAL_UART_Transmit(&huart2, (void*) str, sizeof(str), 1000);
		}

		break;
	default:
		break;
	}
}

