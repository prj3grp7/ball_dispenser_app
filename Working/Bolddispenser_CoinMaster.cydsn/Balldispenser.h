#ifndef Balldispenser_h
#define Balldispenser_h


#pragma once
    
#include "MotorControl.h"
#include "RPi_IF.h"
#include "project.h"


void initBallDispenser();
void DispenseBalls();
int countBalls();
void UpdateStatusLEDS();

#endif

