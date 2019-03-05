/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "Balldispenser.h"
#include "CoinDetection.h"
#include "controller.h"
#include "UART_debug.h"




int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    
    initCoinDetector();
    initMotorControl();
    initUART();
    initI2C();
    initBallDispenser();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        handleI2CData();
        countBalls();
    }
}

/* [] END OF FILE */
