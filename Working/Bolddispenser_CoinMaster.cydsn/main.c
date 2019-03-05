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
#include "RPi_IF.h"
#include "UART_debug.h"




int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    initBallDispenser();
    initCoinDetector();
    initMotorControl();
    initUART();
    RPI_IF_init();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        RPi_IF_handleData();
    }
}

/* [] END OF FILE */
