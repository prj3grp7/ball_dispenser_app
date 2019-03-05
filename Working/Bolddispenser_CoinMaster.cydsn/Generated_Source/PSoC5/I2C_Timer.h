/*******************************************************************************
* File Name: I2C_Timer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_I2C_Timer_H)
#define CY_TIMER_I2C_Timer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 I2C_Timer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define I2C_Timer_Resolution                 16u
#define I2C_Timer_UsingFixedFunction         1u
#define I2C_Timer_UsingHWCaptureCounter      0u
#define I2C_Timer_SoftwareCaptureMode        0u
#define I2C_Timer_SoftwareTriggerMode        0u
#define I2C_Timer_UsingHWEnable              0u
#define I2C_Timer_EnableTriggerMode          0u
#define I2C_Timer_InterruptOnCaptureCount    0u
#define I2C_Timer_RunModeUsed                0u
#define I2C_Timer_ControlRegRemoved          0u

#if defined(I2C_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define I2C_Timer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (I2C_Timer_UsingFixedFunction)
    #define I2C_Timer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define I2C_Timer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End I2C_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!I2C_Timer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (I2C_Timer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!I2C_Timer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}I2C_Timer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    I2C_Timer_Start(void) ;
void    I2C_Timer_Stop(void) ;

void    I2C_Timer_SetInterruptMode(uint8 interruptMode) ;
uint8   I2C_Timer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define I2C_Timer_GetInterruptSource() I2C_Timer_ReadStatusRegister()

#if(!I2C_Timer_UDB_CONTROL_REG_REMOVED)
    uint8   I2C_Timer_ReadControlRegister(void) ;
    void    I2C_Timer_WriteControlRegister(uint8 control) ;
#endif /* (!I2C_Timer_UDB_CONTROL_REG_REMOVED) */

uint16  I2C_Timer_ReadPeriod(void) ;
void    I2C_Timer_WritePeriod(uint16 period) ;
uint16  I2C_Timer_ReadCounter(void) ;
void    I2C_Timer_WriteCounter(uint16 counter) ;
uint16  I2C_Timer_ReadCapture(void) ;
void    I2C_Timer_SoftwareCapture(void) ;

#if(!I2C_Timer_UsingFixedFunction) /* UDB Prototypes */
    #if (I2C_Timer_SoftwareCaptureMode)
        void    I2C_Timer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!I2C_Timer_UsingFixedFunction) */

    #if (I2C_Timer_SoftwareTriggerMode)
        void    I2C_Timer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (I2C_Timer_SoftwareTriggerMode) */

    #if (I2C_Timer_EnableTriggerMode)
        void    I2C_Timer_EnableTrigger(void) ;
        void    I2C_Timer_DisableTrigger(void) ;
    #endif /* (I2C_Timer_EnableTriggerMode) */


    #if(I2C_Timer_InterruptOnCaptureCount)
        void    I2C_Timer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (I2C_Timer_InterruptOnCaptureCount) */

    #if (I2C_Timer_UsingHWCaptureCounter)
        void    I2C_Timer_SetCaptureCount(uint8 captureCount) ;
        uint8   I2C_Timer_ReadCaptureCount(void) ;
    #endif /* (I2C_Timer_UsingHWCaptureCounter) */

    void I2C_Timer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void I2C_Timer_Init(void)          ;
void I2C_Timer_Enable(void)        ;
void I2C_Timer_SaveConfig(void)    ;
void I2C_Timer_RestoreConfig(void) ;
void I2C_Timer_Sleep(void)         ;
void I2C_Timer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define I2C_Timer__B_TIMER__CM_NONE 0
#define I2C_Timer__B_TIMER__CM_RISINGEDGE 1
#define I2C_Timer__B_TIMER__CM_FALLINGEDGE 2
#define I2C_Timer__B_TIMER__CM_EITHEREDGE 3
#define I2C_Timer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define I2C_Timer__B_TIMER__TM_NONE 0x00u
#define I2C_Timer__B_TIMER__TM_RISINGEDGE 0x04u
#define I2C_Timer__B_TIMER__TM_FALLINGEDGE 0x08u
#define I2C_Timer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define I2C_Timer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define I2C_Timer_INIT_PERIOD             1999u
#define I2C_Timer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << I2C_Timer_CTRL_CAP_MODE_SHIFT))
#define I2C_Timer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << I2C_Timer_CTRL_TRIG_MODE_SHIFT))
#if (I2C_Timer_UsingFixedFunction)
    #define I2C_Timer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << I2C_Timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << I2C_Timer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define I2C_Timer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << I2C_Timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << I2C_Timer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << I2C_Timer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (I2C_Timer_UsingFixedFunction) */
#define I2C_Timer_INIT_CAPTURE_COUNT      (2u)
#define I2C_Timer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << I2C_Timer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (I2C_Timer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define I2C_Timer_STATUS         (*(reg8 *) I2C_Timer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define I2C_Timer_STATUS_MASK    (*(reg8 *) I2C_Timer_TimerHW__SR0 )
    #define I2C_Timer_CONTROL        (*(reg8 *) I2C_Timer_TimerHW__CFG0)
    #define I2C_Timer_CONTROL2       (*(reg8 *) I2C_Timer_TimerHW__CFG1)
    #define I2C_Timer_CONTROL2_PTR   ( (reg8 *) I2C_Timer_TimerHW__CFG1)
    #define I2C_Timer_RT1            (*(reg8 *) I2C_Timer_TimerHW__RT1)
    #define I2C_Timer_RT1_PTR        ( (reg8 *) I2C_Timer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define I2C_Timer_CONTROL3       (*(reg8 *) I2C_Timer_TimerHW__CFG2)
        #define I2C_Timer_CONTROL3_PTR   ( (reg8 *) I2C_Timer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define I2C_Timer_GLOBAL_ENABLE  (*(reg8 *) I2C_Timer_TimerHW__PM_ACT_CFG)
    #define I2C_Timer_GLOBAL_STBY_ENABLE  (*(reg8 *) I2C_Timer_TimerHW__PM_STBY_CFG)

    #define I2C_Timer_CAPTURE_LSB         (* (reg16 *) I2C_Timer_TimerHW__CAP0 )
    #define I2C_Timer_CAPTURE_LSB_PTR       ((reg16 *) I2C_Timer_TimerHW__CAP0 )
    #define I2C_Timer_PERIOD_LSB          (* (reg16 *) I2C_Timer_TimerHW__PER0 )
    #define I2C_Timer_PERIOD_LSB_PTR        ((reg16 *) I2C_Timer_TimerHW__PER0 )
    #define I2C_Timer_COUNTER_LSB         (* (reg16 *) I2C_Timer_TimerHW__CNT_CMP0 )
    #define I2C_Timer_COUNTER_LSB_PTR       ((reg16 *) I2C_Timer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define I2C_Timer_BLOCK_EN_MASK                     I2C_Timer_TimerHW__PM_ACT_MSK
    #define I2C_Timer_BLOCK_STBY_EN_MASK                I2C_Timer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define I2C_Timer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define I2C_Timer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define I2C_Timer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define I2C_Timer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define I2C_Timer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define I2C_Timer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << I2C_Timer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define I2C_Timer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define I2C_Timer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << I2C_Timer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define I2C_Timer_CTRL_MODE_SHIFT                 0x01u
        #define I2C_Timer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << I2C_Timer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define I2C_Timer_CTRL_RCOD_SHIFT        0x02u
        #define I2C_Timer_CTRL_ENBL_SHIFT        0x00u
        #define I2C_Timer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define I2C_Timer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << I2C_Timer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define I2C_Timer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << I2C_Timer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define I2C_Timer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << I2C_Timer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define I2C_Timer_CTRL_RCOD       ((uint8)((uint8)0x03u << I2C_Timer_CTRL_RCOD_SHIFT))
        #define I2C_Timer_CTRL_ENBL       ((uint8)((uint8)0x80u << I2C_Timer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define I2C_Timer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define I2C_Timer_RT1_MASK                        ((uint8)((uint8)0x03u << I2C_Timer_RT1_SHIFT))
    #define I2C_Timer_SYNC                            ((uint8)((uint8)0x03u << I2C_Timer_RT1_SHIFT))
    #define I2C_Timer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define I2C_Timer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << I2C_Timer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define I2C_Timer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << I2C_Timer_SYNCDSI_SHIFT))

    #define I2C_Timer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << I2C_Timer_CTRL_MODE_SHIFT))
    #define I2C_Timer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << I2C_Timer_CTRL_MODE_SHIFT))
    #define I2C_Timer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << I2C_Timer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define I2C_Timer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define I2C_Timer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define I2C_Timer_STATUS_TC_INT_MASK_SHIFT        (I2C_Timer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define I2C_Timer_STATUS_CAPTURE_INT_MASK_SHIFT   (I2C_Timer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define I2C_Timer_STATUS_TC                       ((uint8)((uint8)0x01u << I2C_Timer_STATUS_TC_SHIFT))
    #define I2C_Timer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << I2C_Timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define I2C_Timer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << I2C_Timer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define I2C_Timer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << I2C_Timer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define I2C_Timer_STATUS              (* (reg8 *) I2C_Timer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define I2C_Timer_STATUS_MASK         (* (reg8 *) I2C_Timer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define I2C_Timer_STATUS_AUX_CTRL     (* (reg8 *) I2C_Timer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define I2C_Timer_CONTROL             (* (reg8 *) I2C_Timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(I2C_Timer_Resolution <= 8u) /* 8-bit Timer */
        #define I2C_Timer_CAPTURE_LSB         (* (reg8 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define I2C_Timer_CAPTURE_LSB_PTR       ((reg8 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define I2C_Timer_PERIOD_LSB          (* (reg8 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define I2C_Timer_PERIOD_LSB_PTR        ((reg8 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define I2C_Timer_COUNTER_LSB         (* (reg8 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define I2C_Timer_COUNTER_LSB_PTR       ((reg8 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(I2C_Timer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define I2C_Timer_CAPTURE_LSB         (* (reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define I2C_Timer_CAPTURE_LSB_PTR       ((reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define I2C_Timer_PERIOD_LSB          (* (reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define I2C_Timer_PERIOD_LSB_PTR        ((reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define I2C_Timer_COUNTER_LSB         (* (reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define I2C_Timer_COUNTER_LSB_PTR       ((reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define I2C_Timer_CAPTURE_LSB         (* (reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define I2C_Timer_CAPTURE_LSB_PTR       ((reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define I2C_Timer_PERIOD_LSB          (* (reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define I2C_Timer_PERIOD_LSB_PTR        ((reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define I2C_Timer_COUNTER_LSB         (* (reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define I2C_Timer_COUNTER_LSB_PTR       ((reg16 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(I2C_Timer_Resolution <= 24u)/* 24-bit Timer */
        #define I2C_Timer_CAPTURE_LSB         (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define I2C_Timer_CAPTURE_LSB_PTR       ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define I2C_Timer_PERIOD_LSB          (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define I2C_Timer_PERIOD_LSB_PTR        ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define I2C_Timer_COUNTER_LSB         (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define I2C_Timer_COUNTER_LSB_PTR       ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define I2C_Timer_CAPTURE_LSB         (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define I2C_Timer_CAPTURE_LSB_PTR       ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define I2C_Timer_PERIOD_LSB          (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define I2C_Timer_PERIOD_LSB_PTR        ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define I2C_Timer_COUNTER_LSB         (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define I2C_Timer_COUNTER_LSB_PTR       ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define I2C_Timer_CAPTURE_LSB         (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define I2C_Timer_CAPTURE_LSB_PTR       ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define I2C_Timer_PERIOD_LSB          (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define I2C_Timer_PERIOD_LSB_PTR        ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define I2C_Timer_COUNTER_LSB         (* (reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define I2C_Timer_COUNTER_LSB_PTR       ((reg32 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define I2C_Timer_COUNTER_LSB_PTR_8BIT       ((reg8 *) I2C_Timer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (I2C_Timer_UsingHWCaptureCounter)
        #define I2C_Timer_CAP_COUNT              (*(reg8 *) I2C_Timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define I2C_Timer_CAP_COUNT_PTR          ( (reg8 *) I2C_Timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define I2C_Timer_CAPTURE_COUNT_CTRL     (*(reg8 *) I2C_Timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define I2C_Timer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) I2C_Timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (I2C_Timer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define I2C_Timer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define I2C_Timer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define I2C_Timer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define I2C_Timer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define I2C_Timer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define I2C_Timer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << I2C_Timer_CTRL_INTCNT_SHIFT))
    #define I2C_Timer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << I2C_Timer_CTRL_TRIG_MODE_SHIFT))
    #define I2C_Timer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << I2C_Timer_CTRL_TRIG_EN_SHIFT))
    #define I2C_Timer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << I2C_Timer_CTRL_CAP_MODE_SHIFT))
    #define I2C_Timer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << I2C_Timer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define I2C_Timer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define I2C_Timer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define I2C_Timer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define I2C_Timer_STATUS_TC_INT_MASK_SHIFT       I2C_Timer_STATUS_TC_SHIFT
    #define I2C_Timer_STATUS_CAPTURE_INT_MASK_SHIFT  I2C_Timer_STATUS_CAPTURE_SHIFT
    #define I2C_Timer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define I2C_Timer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define I2C_Timer_STATUS_FIFOFULL_INT_MASK_SHIFT I2C_Timer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define I2C_Timer_STATUS_TC                      ((uint8)((uint8)0x01u << I2C_Timer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define I2C_Timer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << I2C_Timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define I2C_Timer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << I2C_Timer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define I2C_Timer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << I2C_Timer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define I2C_Timer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << I2C_Timer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define I2C_Timer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << I2C_Timer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define I2C_Timer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << I2C_Timer_STATUS_FIFOFULL_SHIFT))

    #define I2C_Timer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define I2C_Timer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define I2C_Timer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define I2C_Timer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define I2C_Timer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define I2C_Timer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_I2C_Timer_H */


/* [] END OF FILE */
