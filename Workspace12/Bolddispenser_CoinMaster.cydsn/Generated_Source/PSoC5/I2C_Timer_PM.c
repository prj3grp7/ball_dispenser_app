/*******************************************************************************
* File Name: I2C_Timer_PM.c
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

#include "I2C_Timer.h"

static I2C_Timer_backupStruct I2C_Timer_backup;


/*******************************************************************************
* Function Name: I2C_Timer_SaveConfig
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
*  I2C_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void I2C_Timer_SaveConfig(void) 
{
    #if (!I2C_Timer_UsingFixedFunction)
        I2C_Timer_backup.TimerUdb = I2C_Timer_ReadCounter();
        I2C_Timer_backup.InterruptMaskValue = I2C_Timer_STATUS_MASK;
        #if (I2C_Timer_UsingHWCaptureCounter)
            I2C_Timer_backup.TimerCaptureCounter = I2C_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!I2C_Timer_UDB_CONTROL_REG_REMOVED)
            I2C_Timer_backup.TimerControlRegister = I2C_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: I2C_Timer_RestoreConfig
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
*  I2C_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void I2C_Timer_RestoreConfig(void) 
{   
    #if (!I2C_Timer_UsingFixedFunction)

        I2C_Timer_WriteCounter(I2C_Timer_backup.TimerUdb);
        I2C_Timer_STATUS_MASK =I2C_Timer_backup.InterruptMaskValue;
        #if (I2C_Timer_UsingHWCaptureCounter)
            I2C_Timer_SetCaptureCount(I2C_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!I2C_Timer_UDB_CONTROL_REG_REMOVED)
            I2C_Timer_WriteControlRegister(I2C_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: I2C_Timer_Sleep
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
*  I2C_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void I2C_Timer_Sleep(void) 
{
    #if(!I2C_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(I2C_Timer_CTRL_ENABLE == (I2C_Timer_CONTROL & I2C_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            I2C_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            I2C_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    I2C_Timer_Stop();
    I2C_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: I2C_Timer_Wakeup
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
*  I2C_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void I2C_Timer_Wakeup(void) 
{
    I2C_Timer_RestoreConfig();
    #if(!I2C_Timer_UDB_CONTROL_REG_REMOVED)
        if(I2C_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                I2C_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
