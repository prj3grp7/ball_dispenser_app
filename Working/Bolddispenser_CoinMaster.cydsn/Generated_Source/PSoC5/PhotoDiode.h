/*******************************************************************************
* File Name: PhotoDiode.h  
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

#if !defined(CY_PINS_PhotoDiode_H) /* Pins PhotoDiode_H */
#define CY_PINS_PhotoDiode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PhotoDiode_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PhotoDiode__PORT == 15 && ((PhotoDiode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PhotoDiode_Write(uint8 value);
void    PhotoDiode_SetDriveMode(uint8 mode);
uint8   PhotoDiode_ReadDataReg(void);
uint8   PhotoDiode_Read(void);
void    PhotoDiode_SetInterruptMode(uint16 position, uint16 mode);
uint8   PhotoDiode_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PhotoDiode_SetDriveMode() function.
     *  @{
     */
        #define PhotoDiode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PhotoDiode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PhotoDiode_DM_RES_UP          PIN_DM_RES_UP
        #define PhotoDiode_DM_RES_DWN         PIN_DM_RES_DWN
        #define PhotoDiode_DM_OD_LO           PIN_DM_OD_LO
        #define PhotoDiode_DM_OD_HI           PIN_DM_OD_HI
        #define PhotoDiode_DM_STRONG          PIN_DM_STRONG
        #define PhotoDiode_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PhotoDiode_MASK               PhotoDiode__MASK
#define PhotoDiode_SHIFT              PhotoDiode__SHIFT
#define PhotoDiode_WIDTH              1u

/* Interrupt constants */
#if defined(PhotoDiode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PhotoDiode_SetInterruptMode() function.
     *  @{
     */
        #define PhotoDiode_INTR_NONE      (uint16)(0x0000u)
        #define PhotoDiode_INTR_RISING    (uint16)(0x0001u)
        #define PhotoDiode_INTR_FALLING   (uint16)(0x0002u)
        #define PhotoDiode_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PhotoDiode_INTR_MASK      (0x01u) 
#endif /* (PhotoDiode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PhotoDiode_PS                     (* (reg8 *) PhotoDiode__PS)
/* Data Register */
#define PhotoDiode_DR                     (* (reg8 *) PhotoDiode__DR)
/* Port Number */
#define PhotoDiode_PRT_NUM                (* (reg8 *) PhotoDiode__PRT) 
/* Connect to Analog Globals */                                                  
#define PhotoDiode_AG                     (* (reg8 *) PhotoDiode__AG)                       
/* Analog MUX bux enable */
#define PhotoDiode_AMUX                   (* (reg8 *) PhotoDiode__AMUX) 
/* Bidirectional Enable */                                                        
#define PhotoDiode_BIE                    (* (reg8 *) PhotoDiode__BIE)
/* Bit-mask for Aliased Register Access */
#define PhotoDiode_BIT_MASK               (* (reg8 *) PhotoDiode__BIT_MASK)
/* Bypass Enable */
#define PhotoDiode_BYP                    (* (reg8 *) PhotoDiode__BYP)
/* Port wide control signals */                                                   
#define PhotoDiode_CTL                    (* (reg8 *) PhotoDiode__CTL)
/* Drive Modes */
#define PhotoDiode_DM0                    (* (reg8 *) PhotoDiode__DM0) 
#define PhotoDiode_DM1                    (* (reg8 *) PhotoDiode__DM1)
#define PhotoDiode_DM2                    (* (reg8 *) PhotoDiode__DM2) 
/* Input Buffer Disable Override */
#define PhotoDiode_INP_DIS                (* (reg8 *) PhotoDiode__INP_DIS)
/* LCD Common or Segment Drive */
#define PhotoDiode_LCD_COM_SEG            (* (reg8 *) PhotoDiode__LCD_COM_SEG)
/* Enable Segment LCD */
#define PhotoDiode_LCD_EN                 (* (reg8 *) PhotoDiode__LCD_EN)
/* Slew Rate Control */
#define PhotoDiode_SLW                    (* (reg8 *) PhotoDiode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PhotoDiode_PRTDSI__CAPS_SEL       (* (reg8 *) PhotoDiode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PhotoDiode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PhotoDiode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PhotoDiode_PRTDSI__OE_SEL0        (* (reg8 *) PhotoDiode__PRTDSI__OE_SEL0) 
#define PhotoDiode_PRTDSI__OE_SEL1        (* (reg8 *) PhotoDiode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PhotoDiode_PRTDSI__OUT_SEL0       (* (reg8 *) PhotoDiode__PRTDSI__OUT_SEL0) 
#define PhotoDiode_PRTDSI__OUT_SEL1       (* (reg8 *) PhotoDiode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PhotoDiode_PRTDSI__SYNC_OUT       (* (reg8 *) PhotoDiode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PhotoDiode__SIO_CFG)
    #define PhotoDiode_SIO_HYST_EN        (* (reg8 *) PhotoDiode__SIO_HYST_EN)
    #define PhotoDiode_SIO_REG_HIFREQ     (* (reg8 *) PhotoDiode__SIO_REG_HIFREQ)
    #define PhotoDiode_SIO_CFG            (* (reg8 *) PhotoDiode__SIO_CFG)
    #define PhotoDiode_SIO_DIFF           (* (reg8 *) PhotoDiode__SIO_DIFF)
#endif /* (PhotoDiode__SIO_CFG) */

/* Interrupt Registers */
#if defined(PhotoDiode__INTSTAT)
    #define PhotoDiode_INTSTAT            (* (reg8 *) PhotoDiode__INTSTAT)
    #define PhotoDiode_SNAP               (* (reg8 *) PhotoDiode__SNAP)
    
	#define PhotoDiode_0_INTTYPE_REG 		(* (reg8 *) PhotoDiode__0__INTTYPE)
#endif /* (PhotoDiode__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PhotoDiode_H */


/* [] END OF FILE */
