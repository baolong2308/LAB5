/*
 * uart_communication_fsm.h
 *
 *  Created on: Dec 11, 2024
 *      Author: admin
 */
#ifndef _UART_COMMUNICATION_FSM_H
#define _UART_COMMUNICATION_FSM_H

#include <main.h>
#include <command_parser_fsm.h>
#include <stdio.h>
#include <timer.h>

#define UART_INIT 0
#define UART_IDLE 1
#define READ_AND_SEND 2
#define SEND_ADC 3
void uart_communication_fsm();

#endif
