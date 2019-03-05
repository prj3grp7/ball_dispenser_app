#ifndef _UART_debug_H
#define _UART_debug_H
#pragma once
#include "CoinDetection.h"
#include "controller.h"
#include "Balldispenser.h"

void initUART();

void handleCommand(char cmd);

void handleUART();

CY_ISR(ISR_UART_rx_handler);

#endif