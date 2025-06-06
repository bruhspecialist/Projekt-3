/*******************************************************************************
* File Name: WEIGHT_ADC_ExtVref.h  
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

#if !defined(CY_PINS_WEIGHT_ADC_ExtVref_H) /* Pins WEIGHT_ADC_ExtVref_H */
#define CY_PINS_WEIGHT_ADC_ExtVref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WEIGHT_ADC_ExtVref_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WEIGHT_ADC_ExtVref__PORT == 15 && ((WEIGHT_ADC_ExtVref__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WEIGHT_ADC_ExtVref_Write(uint8 value);
void    WEIGHT_ADC_ExtVref_SetDriveMode(uint8 mode);
uint8   WEIGHT_ADC_ExtVref_ReadDataReg(void);
uint8   WEIGHT_ADC_ExtVref_Read(void);
void    WEIGHT_ADC_ExtVref_SetInterruptMode(uint16 position, uint16 mode);
uint8   WEIGHT_ADC_ExtVref_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WEIGHT_ADC_ExtVref_SetDriveMode() function.
     *  @{
     */
        #define WEIGHT_ADC_ExtVref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WEIGHT_ADC_ExtVref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WEIGHT_ADC_ExtVref_DM_RES_UP          PIN_DM_RES_UP
        #define WEIGHT_ADC_ExtVref_DM_RES_DWN         PIN_DM_RES_DWN
        #define WEIGHT_ADC_ExtVref_DM_OD_LO           PIN_DM_OD_LO
        #define WEIGHT_ADC_ExtVref_DM_OD_HI           PIN_DM_OD_HI
        #define WEIGHT_ADC_ExtVref_DM_STRONG          PIN_DM_STRONG
        #define WEIGHT_ADC_ExtVref_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WEIGHT_ADC_ExtVref_MASK               WEIGHT_ADC_ExtVref__MASK
#define WEIGHT_ADC_ExtVref_SHIFT              WEIGHT_ADC_ExtVref__SHIFT
#define WEIGHT_ADC_ExtVref_WIDTH              1u

/* Interrupt constants */
#if defined(WEIGHT_ADC_ExtVref__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WEIGHT_ADC_ExtVref_SetInterruptMode() function.
     *  @{
     */
        #define WEIGHT_ADC_ExtVref_INTR_NONE      (uint16)(0x0000u)
        #define WEIGHT_ADC_ExtVref_INTR_RISING    (uint16)(0x0001u)
        #define WEIGHT_ADC_ExtVref_INTR_FALLING   (uint16)(0x0002u)
        #define WEIGHT_ADC_ExtVref_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WEIGHT_ADC_ExtVref_INTR_MASK      (0x01u) 
#endif /* (WEIGHT_ADC_ExtVref__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WEIGHT_ADC_ExtVref_PS                     (* (reg8 *) WEIGHT_ADC_ExtVref__PS)
/* Data Register */
#define WEIGHT_ADC_ExtVref_DR                     (* (reg8 *) WEIGHT_ADC_ExtVref__DR)
/* Port Number */
#define WEIGHT_ADC_ExtVref_PRT_NUM                (* (reg8 *) WEIGHT_ADC_ExtVref__PRT) 
/* Connect to Analog Globals */                                                  
#define WEIGHT_ADC_ExtVref_AG                     (* (reg8 *) WEIGHT_ADC_ExtVref__AG)                       
/* Analog MUX bux enable */
#define WEIGHT_ADC_ExtVref_AMUX                   (* (reg8 *) WEIGHT_ADC_ExtVref__AMUX) 
/* Bidirectional Enable */                                                        
#define WEIGHT_ADC_ExtVref_BIE                    (* (reg8 *) WEIGHT_ADC_ExtVref__BIE)
/* Bit-mask for Aliased Register Access */
#define WEIGHT_ADC_ExtVref_BIT_MASK               (* (reg8 *) WEIGHT_ADC_ExtVref__BIT_MASK)
/* Bypass Enable */
#define WEIGHT_ADC_ExtVref_BYP                    (* (reg8 *) WEIGHT_ADC_ExtVref__BYP)
/* Port wide control signals */                                                   
#define WEIGHT_ADC_ExtVref_CTL                    (* (reg8 *) WEIGHT_ADC_ExtVref__CTL)
/* Drive Modes */
#define WEIGHT_ADC_ExtVref_DM0                    (* (reg8 *) WEIGHT_ADC_ExtVref__DM0) 
#define WEIGHT_ADC_ExtVref_DM1                    (* (reg8 *) WEIGHT_ADC_ExtVref__DM1)
#define WEIGHT_ADC_ExtVref_DM2                    (* (reg8 *) WEIGHT_ADC_ExtVref__DM2) 
/* Input Buffer Disable Override */
#define WEIGHT_ADC_ExtVref_INP_DIS                (* (reg8 *) WEIGHT_ADC_ExtVref__INP_DIS)
/* LCD Common or Segment Drive */
#define WEIGHT_ADC_ExtVref_LCD_COM_SEG            (* (reg8 *) WEIGHT_ADC_ExtVref__LCD_COM_SEG)
/* Enable Segment LCD */
#define WEIGHT_ADC_ExtVref_LCD_EN                 (* (reg8 *) WEIGHT_ADC_ExtVref__LCD_EN)
/* Slew Rate Control */
#define WEIGHT_ADC_ExtVref_SLW                    (* (reg8 *) WEIGHT_ADC_ExtVref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WEIGHT_ADC_ExtVref_PRTDSI__CAPS_SEL       (* (reg8 *) WEIGHT_ADC_ExtVref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WEIGHT_ADC_ExtVref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WEIGHT_ADC_ExtVref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WEIGHT_ADC_ExtVref_PRTDSI__OE_SEL0        (* (reg8 *) WEIGHT_ADC_ExtVref__PRTDSI__OE_SEL0) 
#define WEIGHT_ADC_ExtVref_PRTDSI__OE_SEL1        (* (reg8 *) WEIGHT_ADC_ExtVref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WEIGHT_ADC_ExtVref_PRTDSI__OUT_SEL0       (* (reg8 *) WEIGHT_ADC_ExtVref__PRTDSI__OUT_SEL0) 
#define WEIGHT_ADC_ExtVref_PRTDSI__OUT_SEL1       (* (reg8 *) WEIGHT_ADC_ExtVref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WEIGHT_ADC_ExtVref_PRTDSI__SYNC_OUT       (* (reg8 *) WEIGHT_ADC_ExtVref__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WEIGHT_ADC_ExtVref__SIO_CFG)
    #define WEIGHT_ADC_ExtVref_SIO_HYST_EN        (* (reg8 *) WEIGHT_ADC_ExtVref__SIO_HYST_EN)
    #define WEIGHT_ADC_ExtVref_SIO_REG_HIFREQ     (* (reg8 *) WEIGHT_ADC_ExtVref__SIO_REG_HIFREQ)
    #define WEIGHT_ADC_ExtVref_SIO_CFG            (* (reg8 *) WEIGHT_ADC_ExtVref__SIO_CFG)
    #define WEIGHT_ADC_ExtVref_SIO_DIFF           (* (reg8 *) WEIGHT_ADC_ExtVref__SIO_DIFF)
#endif /* (WEIGHT_ADC_ExtVref__SIO_CFG) */

/* Interrupt Registers */
#if defined(WEIGHT_ADC_ExtVref__INTSTAT)
    #define WEIGHT_ADC_ExtVref_INTSTAT            (* (reg8 *) WEIGHT_ADC_ExtVref__INTSTAT)
    #define WEIGHT_ADC_ExtVref_SNAP               (* (reg8 *) WEIGHT_ADC_ExtVref__SNAP)
    
	#define WEIGHT_ADC_ExtVref_0_INTTYPE_REG 		(* (reg8 *) WEIGHT_ADC_ExtVref__0__INTTYPE)
#endif /* (WEIGHT_ADC_ExtVref__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WEIGHT_ADC_ExtVref_H */


/* [] END OF FILE */
