/*******************************************************************************
* File Name: WEIGHT_ADC_theACLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_WEIGHT_ADC_theACLK_H)
#define CY_CLOCK_WEIGHT_ADC_theACLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void WEIGHT_ADC_theACLK_Start(void) ;
void WEIGHT_ADC_theACLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void WEIGHT_ADC_theACLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void WEIGHT_ADC_theACLK_StandbyPower(uint8 state) ;
void WEIGHT_ADC_theACLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 WEIGHT_ADC_theACLK_GetDividerRegister(void) ;
void WEIGHT_ADC_theACLK_SetModeRegister(uint8 modeBitMask) ;
void WEIGHT_ADC_theACLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 WEIGHT_ADC_theACLK_GetModeRegister(void) ;
void WEIGHT_ADC_theACLK_SetSourceRegister(uint8 clkSource) ;
uint8 WEIGHT_ADC_theACLK_GetSourceRegister(void) ;
#if defined(WEIGHT_ADC_theACLK__CFG3)
void WEIGHT_ADC_theACLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 WEIGHT_ADC_theACLK_GetPhaseRegister(void) ;
#endif /* defined(WEIGHT_ADC_theACLK__CFG3) */

#define WEIGHT_ADC_theACLK_Enable()                       WEIGHT_ADC_theACLK_Start()
#define WEIGHT_ADC_theACLK_Disable()                      WEIGHT_ADC_theACLK_Stop()
#define WEIGHT_ADC_theACLK_SetDivider(clkDivider)         WEIGHT_ADC_theACLK_SetDividerRegister(clkDivider, 1u)
#define WEIGHT_ADC_theACLK_SetDividerValue(clkDivider)    WEIGHT_ADC_theACLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define WEIGHT_ADC_theACLK_SetMode(clkMode)               WEIGHT_ADC_theACLK_SetModeRegister(clkMode)
#define WEIGHT_ADC_theACLK_SetSource(clkSource)           WEIGHT_ADC_theACLK_SetSourceRegister(clkSource)
#if defined(WEIGHT_ADC_theACLK__CFG3)
#define WEIGHT_ADC_theACLK_SetPhase(clkPhase)             WEIGHT_ADC_theACLK_SetPhaseRegister(clkPhase)
#define WEIGHT_ADC_theACLK_SetPhaseValue(clkPhase)        WEIGHT_ADC_theACLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(WEIGHT_ADC_theACLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define WEIGHT_ADC_theACLK_CLKEN              (* (reg8 *) WEIGHT_ADC_theACLK__PM_ACT_CFG)
#define WEIGHT_ADC_theACLK_CLKEN_PTR          ((reg8 *) WEIGHT_ADC_theACLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define WEIGHT_ADC_theACLK_CLKSTBY            (* (reg8 *) WEIGHT_ADC_theACLK__PM_STBY_CFG)
#define WEIGHT_ADC_theACLK_CLKSTBY_PTR        ((reg8 *) WEIGHT_ADC_theACLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define WEIGHT_ADC_theACLK_DIV_LSB            (* (reg8 *) WEIGHT_ADC_theACLK__CFG0)
#define WEIGHT_ADC_theACLK_DIV_LSB_PTR        ((reg8 *) WEIGHT_ADC_theACLK__CFG0)
#define WEIGHT_ADC_theACLK_DIV_PTR            ((reg16 *) WEIGHT_ADC_theACLK__CFG0)

/* Clock MSB divider configuration register. */
#define WEIGHT_ADC_theACLK_DIV_MSB            (* (reg8 *) WEIGHT_ADC_theACLK__CFG1)
#define WEIGHT_ADC_theACLK_DIV_MSB_PTR        ((reg8 *) WEIGHT_ADC_theACLK__CFG1)

/* Mode and source configuration register */
#define WEIGHT_ADC_theACLK_MOD_SRC            (* (reg8 *) WEIGHT_ADC_theACLK__CFG2)
#define WEIGHT_ADC_theACLK_MOD_SRC_PTR        ((reg8 *) WEIGHT_ADC_theACLK__CFG2)

#if defined(WEIGHT_ADC_theACLK__CFG3)
/* Analog clock phase configuration register */
#define WEIGHT_ADC_theACLK_PHASE              (* (reg8 *) WEIGHT_ADC_theACLK__CFG3)
#define WEIGHT_ADC_theACLK_PHASE_PTR          ((reg8 *) WEIGHT_ADC_theACLK__CFG3)
#endif /* defined(WEIGHT_ADC_theACLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define WEIGHT_ADC_theACLK_CLKEN_MASK         WEIGHT_ADC_theACLK__PM_ACT_MSK
#define WEIGHT_ADC_theACLK_CLKSTBY_MASK       WEIGHT_ADC_theACLK__PM_STBY_MSK

/* CFG2 field masks */
#define WEIGHT_ADC_theACLK_SRC_SEL_MSK        WEIGHT_ADC_theACLK__CFG2_SRC_SEL_MASK
#define WEIGHT_ADC_theACLK_MODE_MASK          (~(WEIGHT_ADC_theACLK_SRC_SEL_MSK))

#if defined(WEIGHT_ADC_theACLK__CFG3)
/* CFG3 phase mask */
#define WEIGHT_ADC_theACLK_PHASE_MASK         WEIGHT_ADC_theACLK__CFG3_PHASE_DLY_MASK
#endif /* defined(WEIGHT_ADC_theACLK__CFG3) */

#endif /* CY_CLOCK_WEIGHT_ADC_theACLK_H */


/* [] END OF FILE */
