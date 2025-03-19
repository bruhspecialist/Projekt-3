/*******************************************************************************
* File Name: STEP_2b.h  
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

#if !defined(CY_PINS_STEP_2b_H) /* Pins STEP_2b_H */
#define CY_PINS_STEP_2b_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "STEP_2b_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 STEP_2b__PORT == 15 && ((STEP_2b__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    STEP_2b_Write(uint8 value);
void    STEP_2b_SetDriveMode(uint8 mode);
uint8   STEP_2b_ReadDataReg(void);
uint8   STEP_2b_Read(void);
void    STEP_2b_SetInterruptMode(uint16 position, uint16 mode);
uint8   STEP_2b_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the STEP_2b_SetDriveMode() function.
     *  @{
     */
        #define STEP_2b_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define STEP_2b_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define STEP_2b_DM_RES_UP          PIN_DM_RES_UP
        #define STEP_2b_DM_RES_DWN         PIN_DM_RES_DWN
        #define STEP_2b_DM_OD_LO           PIN_DM_OD_LO
        #define STEP_2b_DM_OD_HI           PIN_DM_OD_HI
        #define STEP_2b_DM_STRONG          PIN_DM_STRONG
        #define STEP_2b_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define STEP_2b_MASK               STEP_2b__MASK
#define STEP_2b_SHIFT              STEP_2b__SHIFT
#define STEP_2b_WIDTH              1u

/* Interrupt constants */
#if defined(STEP_2b__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in STEP_2b_SetInterruptMode() function.
     *  @{
     */
        #define STEP_2b_INTR_NONE      (uint16)(0x0000u)
        #define STEP_2b_INTR_RISING    (uint16)(0x0001u)
        #define STEP_2b_INTR_FALLING   (uint16)(0x0002u)
        #define STEP_2b_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define STEP_2b_INTR_MASK      (0x01u) 
#endif /* (STEP_2b__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define STEP_2b_PS                     (* (reg8 *) STEP_2b__PS)
/* Data Register */
#define STEP_2b_DR                     (* (reg8 *) STEP_2b__DR)
/* Port Number */
#define STEP_2b_PRT_NUM                (* (reg8 *) STEP_2b__PRT) 
/* Connect to Analog Globals */                                                  
#define STEP_2b_AG                     (* (reg8 *) STEP_2b__AG)                       
/* Analog MUX bux enable */
#define STEP_2b_AMUX                   (* (reg8 *) STEP_2b__AMUX) 
/* Bidirectional Enable */                                                        
#define STEP_2b_BIE                    (* (reg8 *) STEP_2b__BIE)
/* Bit-mask for Aliased Register Access */
#define STEP_2b_BIT_MASK               (* (reg8 *) STEP_2b__BIT_MASK)
/* Bypass Enable */
#define STEP_2b_BYP                    (* (reg8 *) STEP_2b__BYP)
/* Port wide control signals */                                                   
#define STEP_2b_CTL                    (* (reg8 *) STEP_2b__CTL)
/* Drive Modes */
#define STEP_2b_DM0                    (* (reg8 *) STEP_2b__DM0) 
#define STEP_2b_DM1                    (* (reg8 *) STEP_2b__DM1)
#define STEP_2b_DM2                    (* (reg8 *) STEP_2b__DM2) 
/* Input Buffer Disable Override */
#define STEP_2b_INP_DIS                (* (reg8 *) STEP_2b__INP_DIS)
/* LCD Common or Segment Drive */
#define STEP_2b_LCD_COM_SEG            (* (reg8 *) STEP_2b__LCD_COM_SEG)
/* Enable Segment LCD */
#define STEP_2b_LCD_EN                 (* (reg8 *) STEP_2b__LCD_EN)
/* Slew Rate Control */
#define STEP_2b_SLW                    (* (reg8 *) STEP_2b__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define STEP_2b_PRTDSI__CAPS_SEL       (* (reg8 *) STEP_2b__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define STEP_2b_PRTDSI__DBL_SYNC_IN    (* (reg8 *) STEP_2b__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define STEP_2b_PRTDSI__OE_SEL0        (* (reg8 *) STEP_2b__PRTDSI__OE_SEL0) 
#define STEP_2b_PRTDSI__OE_SEL1        (* (reg8 *) STEP_2b__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define STEP_2b_PRTDSI__OUT_SEL0       (* (reg8 *) STEP_2b__PRTDSI__OUT_SEL0) 
#define STEP_2b_PRTDSI__OUT_SEL1       (* (reg8 *) STEP_2b__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define STEP_2b_PRTDSI__SYNC_OUT       (* (reg8 *) STEP_2b__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(STEP_2b__SIO_CFG)
    #define STEP_2b_SIO_HYST_EN        (* (reg8 *) STEP_2b__SIO_HYST_EN)
    #define STEP_2b_SIO_REG_HIFREQ     (* (reg8 *) STEP_2b__SIO_REG_HIFREQ)
    #define STEP_2b_SIO_CFG            (* (reg8 *) STEP_2b__SIO_CFG)
    #define STEP_2b_SIO_DIFF           (* (reg8 *) STEP_2b__SIO_DIFF)
#endif /* (STEP_2b__SIO_CFG) */

/* Interrupt Registers */
#if defined(STEP_2b__INTSTAT)
    #define STEP_2b_INTSTAT            (* (reg8 *) STEP_2b__INTSTAT)
    #define STEP_2b_SNAP               (* (reg8 *) STEP_2b__SNAP)
    
	#define STEP_2b_0_INTTYPE_REG 		(* (reg8 *) STEP_2b__0__INTTYPE)
#endif /* (STEP_2b__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_STEP_2b_H */


/* [] END OF FILE */
