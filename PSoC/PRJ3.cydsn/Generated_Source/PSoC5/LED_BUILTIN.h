/*******************************************************************************
* File Name: LED_BUILTIN.h  
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

#if !defined(CY_PINS_LED_BUILTIN_H) /* Pins LED_BUILTIN_H */
#define CY_PINS_LED_BUILTIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_BUILTIN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_BUILTIN__PORT == 15 && ((LED_BUILTIN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED_BUILTIN_Write(uint8 value);
void    LED_BUILTIN_SetDriveMode(uint8 mode);
uint8   LED_BUILTIN_ReadDataReg(void);
uint8   LED_BUILTIN_Read(void);
void    LED_BUILTIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED_BUILTIN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED_BUILTIN_SetDriveMode() function.
     *  @{
     */
        #define LED_BUILTIN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED_BUILTIN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED_BUILTIN_DM_RES_UP          PIN_DM_RES_UP
        #define LED_BUILTIN_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED_BUILTIN_DM_OD_LO           PIN_DM_OD_LO
        #define LED_BUILTIN_DM_OD_HI           PIN_DM_OD_HI
        #define LED_BUILTIN_DM_STRONG          PIN_DM_STRONG
        #define LED_BUILTIN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED_BUILTIN_MASK               LED_BUILTIN__MASK
#define LED_BUILTIN_SHIFT              LED_BUILTIN__SHIFT
#define LED_BUILTIN_WIDTH              1u

/* Interrupt constants */
#if defined(LED_BUILTIN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED_BUILTIN_SetInterruptMode() function.
     *  @{
     */
        #define LED_BUILTIN_INTR_NONE      (uint16)(0x0000u)
        #define LED_BUILTIN_INTR_RISING    (uint16)(0x0001u)
        #define LED_BUILTIN_INTR_FALLING   (uint16)(0x0002u)
        #define LED_BUILTIN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED_BUILTIN_INTR_MASK      (0x01u) 
#endif /* (LED_BUILTIN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_BUILTIN_PS                     (* (reg8 *) LED_BUILTIN__PS)
/* Data Register */
#define LED_BUILTIN_DR                     (* (reg8 *) LED_BUILTIN__DR)
/* Port Number */
#define LED_BUILTIN_PRT_NUM                (* (reg8 *) LED_BUILTIN__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_BUILTIN_AG                     (* (reg8 *) LED_BUILTIN__AG)                       
/* Analog MUX bux enable */
#define LED_BUILTIN_AMUX                   (* (reg8 *) LED_BUILTIN__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_BUILTIN_BIE                    (* (reg8 *) LED_BUILTIN__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_BUILTIN_BIT_MASK               (* (reg8 *) LED_BUILTIN__BIT_MASK)
/* Bypass Enable */
#define LED_BUILTIN_BYP                    (* (reg8 *) LED_BUILTIN__BYP)
/* Port wide control signals */                                                   
#define LED_BUILTIN_CTL                    (* (reg8 *) LED_BUILTIN__CTL)
/* Drive Modes */
#define LED_BUILTIN_DM0                    (* (reg8 *) LED_BUILTIN__DM0) 
#define LED_BUILTIN_DM1                    (* (reg8 *) LED_BUILTIN__DM1)
#define LED_BUILTIN_DM2                    (* (reg8 *) LED_BUILTIN__DM2) 
/* Input Buffer Disable Override */
#define LED_BUILTIN_INP_DIS                (* (reg8 *) LED_BUILTIN__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_BUILTIN_LCD_COM_SEG            (* (reg8 *) LED_BUILTIN__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_BUILTIN_LCD_EN                 (* (reg8 *) LED_BUILTIN__LCD_EN)
/* Slew Rate Control */
#define LED_BUILTIN_SLW                    (* (reg8 *) LED_BUILTIN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_BUILTIN_PRTDSI__CAPS_SEL       (* (reg8 *) LED_BUILTIN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_BUILTIN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_BUILTIN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_BUILTIN_PRTDSI__OE_SEL0        (* (reg8 *) LED_BUILTIN__PRTDSI__OE_SEL0) 
#define LED_BUILTIN_PRTDSI__OE_SEL1        (* (reg8 *) LED_BUILTIN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_BUILTIN_PRTDSI__OUT_SEL0       (* (reg8 *) LED_BUILTIN__PRTDSI__OUT_SEL0) 
#define LED_BUILTIN_PRTDSI__OUT_SEL1       (* (reg8 *) LED_BUILTIN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_BUILTIN_PRTDSI__SYNC_OUT       (* (reg8 *) LED_BUILTIN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED_BUILTIN__SIO_CFG)
    #define LED_BUILTIN_SIO_HYST_EN        (* (reg8 *) LED_BUILTIN__SIO_HYST_EN)
    #define LED_BUILTIN_SIO_REG_HIFREQ     (* (reg8 *) LED_BUILTIN__SIO_REG_HIFREQ)
    #define LED_BUILTIN_SIO_CFG            (* (reg8 *) LED_BUILTIN__SIO_CFG)
    #define LED_BUILTIN_SIO_DIFF           (* (reg8 *) LED_BUILTIN__SIO_DIFF)
#endif /* (LED_BUILTIN__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED_BUILTIN__INTSTAT)
    #define LED_BUILTIN_INTSTAT            (* (reg8 *) LED_BUILTIN__INTSTAT)
    #define LED_BUILTIN_SNAP               (* (reg8 *) LED_BUILTIN__SNAP)
    
	#define LED_BUILTIN_0_INTTYPE_REG 		(* (reg8 *) LED_BUILTIN__0__INTTYPE)
#endif /* (LED_BUILTIN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED_BUILTIN_H */


/* [] END OF FILE */
