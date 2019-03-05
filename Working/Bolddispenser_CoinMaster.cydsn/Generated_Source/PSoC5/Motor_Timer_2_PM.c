/*******************************************************************************
* File Name: Motor_Timer_2_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Motor_Timer_2.h"

static Motor_Timer_2_backupStruct Motor_Timer_2_backup;


/*******************************************************************************
* Function Name: Motor_Timer_2_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Motor_Timer_2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Motor_Timer_2_SaveConfig(void) 
{
    #if (!Motor_Timer_2_UsingFixedFunction)
        Motor_Timer_2_backup.TimerUdb = Motor_Timer_2_ReadCounter();
        Motor_Timer_2_backup.InterruptMaskValue = Motor_Timer_2_STATUS_MASK;
        #if (Motor_Timer_2_UsingHWCaptureCounter)
            Motor_Timer_2_backup.TimerCaptureCounter = Motor_Timer_2_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Motor_Timer_2_UDB_CONTROL_REG_REMOVED)
            Motor_Timer_2_backup.TimerControlRegister = Motor_Timer_2_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Motor_Timer_2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Motor_Timer_2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Motor_Timer_2_RestoreConfig(void) 
{   
    #if (!Motor_Timer_2_UsingFixedFunction)

        Motor_Timer_2_WriteCounter(Motor_Timer_2_backup.TimerUdb);
        Motor_Timer_2_STATUS_MASK =Motor_Timer_2_backup.InterruptMaskValue;
        #if (Motor_Timer_2_UsingHWCaptureCounter)
            Motor_Timer_2_SetCaptureCount(Motor_Timer_2_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Motor_Timer_2_UDB_CONTROL_REG_REMOVED)
            Motor_Timer_2_WriteControlRegister(Motor_Timer_2_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Motor_Timer_2_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Motor_Timer_2_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Motor_Timer_2_Sleep(void) 
{
    #if(!Motor_Timer_2_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Motor_Timer_2_CTRL_ENABLE == (Motor_Timer_2_CONTROL & Motor_Timer_2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Motor_Timer_2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Motor_Timer_2_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Motor_Timer_2_Stop();
    Motor_Timer_2_SaveConfig();
}


/*******************************************************************************
* Function Name: Motor_Timer_2_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Motor_Timer_2_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Motor_Timer_2_Wakeup(void) 
{
    Motor_Timer_2_RestoreConfig();
    #if(!Motor_Timer_2_UDB_CONTROL_REG_REMOVED)
        if(Motor_Timer_2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Motor_Timer_2_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
