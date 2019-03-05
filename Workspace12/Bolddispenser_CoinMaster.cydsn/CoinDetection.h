#ifndef CoinDetection_h
#define CoinDetection_h

    
    
#include "Balldispenser.h"
#include "MotorControl.h"
#include "controller.h"
#include "project.h"


void rejectCoin();

void acceptCoin();

void handleCoinDetection();

void disableDispenser();

void enableDispenser();

void resetDetectorISR();

CY_ISR(ISR_detection_handler);

void initCoinDetector();

void resetDetectionISR();

#endif
