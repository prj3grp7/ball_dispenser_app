#ifndef MotorControl_h
#define MotorControl_h
#pragma once
#include "project.h"
#include "stdbool.h"

#define Forward 1
#define Backward -1
#define Forward2 1
#define Backward2 -1

void step(int mode);

void Rotate90();

void Rotate180();

void revRotate90();

void revRotate180();

CY_ISR(Motor_Timer_I_handler);

void initMotorControl();

//---------------------------------//

void step2(int mode);

void Rotate902();

void Rotate360();

void revRotate902();

void revRotate1802();


#endif