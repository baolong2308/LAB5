/*
 * command_parser_fsm.h
 *
 *  Created on: Dec 11, 2024
 *      Author: admin
 */


#include <command_parser_fsm.h>
int status = IDLE;

uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;

uint8_t buffer_flag = 0;

uint8_t request_flag = 0;
uint8_t ok_flag = 0;

void command_parser_init() {
	HAL_UART_Receive_IT(&huart2, &temp, 1);
}

uint8_t getReqFlag() {
	return request_flag;
}

void setReqFlag(uint8_t value) {
	request_flag = value;
}

uint8_t getOKFlag() {
	return ok_flag;
}

void setOKFlag(uint8_t value) {
	ok_flag = value;
}

uint8_t getBufferFlag() {
	return buffer_flag;
}

void setBufferFlag(uint8_t value) {
	buffer_flag = value;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART2) {
		buffer[index_buffer++] = temp;
		if (index_buffer == 30)
			index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Transmit(&huart2, &temp, 1, 50);
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

void command_parser_fsm() {
	switch (status) {
	case INIT:
		status = IDLE;
		break;
	case IDLE:

		if (buffer[index_buffer] == '!') {
			status = STATE_FIRST;
			buffer_flag = 0;
			break;
		}

	case STATE_FIRST:

		if (buffer[index_buffer - 1] == '!') {
			status = STATE_FIRST;
			buffer_flag = 0;
			break;
		}

		if (buffer[index_buffer - 1] == 'R') {
			status = STATE_R;
			buffer_flag = 0;
			break;
		}

		if (buffer[index_buffer - 1] == 'O') {
			status = STATE_O;
			buffer_flag = 0;
			break;
		}

		status = IDLE;
		buffer_flag = 0;
		break;
	case STATE_R:

		if (buffer[index_buffer - 1] == '!') {
			status = STATE_FIRST;
			buffer_flag = 0;
			break;
		}

		if (buffer[index_buffer - 1] == 'S') {
			status = STATE_S;
			buffer_flag = 0;
			break;
		}

		status = IDLE;
		buffer_flag = 0;
		break;
	case STATE_S:

		if (buffer[index_buffer - 1] == '!') {
			status = STATE_FIRST;
			buffer_flag = 0;
			break;
		}

		if (buffer[index_buffer - 1] == 'T') {
			status = STATE_T;
			buffer_flag = 0;
			break;
		}

		status = IDLE;
		buffer_flag = 0;
		break;
	case STATE_T:

		if (buffer[index_buffer - 1] == '!') {
			status = STATE_FIRST;
			buffer_flag = 0;
			break;
		}

		if (buffer[index_buffer - 1] == '#') {
			status = IDLE;

			request_flag = 1;
			buffer_flag = 0;
			break;
		}

		status = IDLE;
		buffer_flag = 0;
		break;
	case STATE_O:

		if (buffer[index_buffer - 1] == '!') {
			status = STATE_FIRST;
			buffer_flag = 0;
			break;
		}

		if (buffer[index_buffer - 1] == 'K') {
			status = STATE_K;

			buffer_flag = 0;
			break;
		}

		status = IDLE;
		buffer_flag = 0;
		break;
	case STATE_K:

		if (buffer[index_buffer - 1] == '!') {
			status = STATE_FIRST;
			buffer_flag = 0;
			break;
		}

		if (buffer[index_buffer - 1] == '#') {
			status = IDLE;

			ok_flag = 1;
			buffer_flag = 0;
			break;
		}

		status = IDLE;
		buffer_flag = 0;
		break;
	case STATE_END:
		status = IDLE;
		break;
	default:
		break;
	}
}


