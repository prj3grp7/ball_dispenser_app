#ifndef _RPi_IF
#define _RPi_IF
#pragma once
    
#include "UART_debug.h"
#include "project.h"
#include "CoinDetection.h"
#include "Balldispenser.h"    
    
#include <string.h>
#include <stdio.h>

void RPI_IF_init();

void coinInserted();

void resetReadBuffer();

void timer_update(int value);

void RPi_IF_handleData();

void SendToRPi(int message);

void dispenserStatus();

#endif
