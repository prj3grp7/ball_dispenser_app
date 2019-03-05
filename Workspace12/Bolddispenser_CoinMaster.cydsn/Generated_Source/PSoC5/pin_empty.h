/*******************************************************************************
* File Name: pin_empty.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pin_empty_H) /* Pins pin_empty_H */
#define CY_PINS_pin_empty_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_empty_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pin_empty__PORT == 15 && ((pin_empty__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pin_empty_Write(uint8 value);
void    pin_empty_SetDriveMode(uint8 mode);
uint8   pin_empty_ReadDataReg(void);
uint8   pin_empty_Read(void);
void    pin_empty_SetInterruptMode(uint16 position, uint16 mode);
uint8   pin_empty_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pin_empty_SetDriveMode() function.
     *  @{
     */
        #define pin_empty_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pin_empty_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pin_empty_DM_RES_UP          PIN_DM_RES_UP
        #define pin_empty_DM_RES_DWN         PIN_DM_RES_DWN
        #define pin_empty_DM_OD_LO           PIN_DM_OD_LO
        #define pin_empty_DM_OD_HI           PIN_DM_OD_HI
        #define pin_empty_DM_STRONG          PIN_DM_STRONG
        #define pin_empty_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pin_empty_MASK               pin_empty__MASK
#define pin_empty_SHIFT              pin_empty__SHIFT
#define pin_empty_WIDTH              1u

/* Interrupt constants */
#if defined(pin_empty__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pin_empty_SetInterruptMode() function.
     *  @{
     */
        #define pin_empty_INTR_NONE      (uint16)(0x0000u)
        #define pin_empty_INTR_RISING    (uint16)(0x0001u)
        #define pin_empty_INTR_FALLING   (uint16)(0x0002u)
        #define pin_empty_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pin_empty_INTR_MASK      (0x01u) 
#endif /* (pin_empty__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_empty_PS                     (* (reg8 *) pin_empty__PS)
/* Data Register */
#define pin_empty_DR                     (* (reg8 *) pin_empty__DR)
/* Port Number */
#define pin_empty_PRT_NUM                (* (reg8 *) pin_empty__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_empty_AG                     (* (reg8 *) pin_empty__AG)                       
/* Analog MUX bux enable */
#define pin_empty_AMUX                   (* (reg8 *) pin_empty__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_empty_BIE                    (* (reg8 *) pin_empty__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_empty_BIT_MASK               (* (reg8 *) pin_empty__BIT_MASK)
/* Bypass Enable */
#define pin_empty_BYP                    (* (reg8 *) pin_empty__BYP)
/* Port wide control signals */                                                   
#define pin_empty_CTL                    (* (reg8 *) pin_empty__CTL)
/* Drive Modes */
#define pin_empty_DM0                    (* (reg8 *) pin_empty__DM0) 
#define pin_empty_DM1                    (* (reg8 *) pin_empty__DM1)
#define pin_empty_DM2                    (* (reg8 *) pin_empty__DM2) 
/* Input Buffer Disable Override */
#define pin_empty_INP_DIS                (* (reg8 *) pin_empty__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_empty_LCD_COM_SEG            (* (reg8 *) pin_empty__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_empty_LCD_EN                 (* (reg8 *) pin_empty__LCD_EN)
/* Slew Rate Control */
#define pin_empty_SLW                    (* (reg8 *) pin_empty__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_empty_PRTDSI__CAPS_SEL       (* (reg8 *) pin_empty__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_empty_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_empty__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_empty_PRTDSI__OE_SEL0        (* (reg8 *) pin_empty__PRTDSI__OE_SEL0) 
#define pin_empty_PRTDSI__OE_SEL1        (* (reg8 *) pin_empty__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_empty_PRTDSI__OUT_SEL0       (* (reg8 *) pin_empty__PRTDSI__OUT_SEL0) 
#define pin_empty_PRTDSI__OUT_SEL1       (* (reg8 *) pin_empty__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_empty_PRTDSI__SYNC_OUT       (* (reg8 *) pin_empty__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pin_empty__SIO_CFG)
    #define pin_empty_SIO_HYST_EN        (* (reg8 *) pin_empty__SIO_HYST_EN)
    #define pin_empty_SIO_REG_HIFREQ     (* (reg8 *) pin_empty__SIO_REG_HIFREQ)
    #define pin_empty_SIO_CFG            (* (reg8 *) pin_empty__SIO_CFG)
    #define pin_empty_SIO_DIFF           (* (reg8 *) pin_empty__SIO_DIFF)
#endif /* (pin_empty__SIO_CFG) */

/* Interrupt Registers */
#if defined(pin_empty__INTSTAT)
    #define pin_empty_INTSTAT            (* (reg8 *) pin_empty__INTSTAT)
    #define pin_empty_SNAP               (* (reg8 *) pin_empty__SNAP)
    
	#define pin_empty_0_INTTYPE_REG 		(* (reg8 *) pin_empty__0__INTTYPE)
#endif /* (pin_empty__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pin_empty_H */


/* [] END OF FILE */
