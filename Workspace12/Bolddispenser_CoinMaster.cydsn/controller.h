#ifndef _RPi_IF
#define _RPi_IF
#pragma once
    
#include "UART_debug.h"
#include "project.h"
#include "CoinDetection.h"
#include "Balldispenser.h"    
    
#include <string.h>
#include <stdio.h>

void initI2C();

void coinInserted();

void resetReadBuffer();

void timer_update(int value);

void handleI2CData();

void SendToRPi(uint8_t message);

void sendDispenserStatus();

void dispenserEmpty();

void sendCoinDetected();

#endif
