/*******************************************************************************
* File Name: WEIGHT_ADC_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "WEIGHT_ADC.h"


/***************************************
* Local data allocation
***************************************/

static WEIGHT_ADC_BACKUP_STRUCT  WEIGHT_ADC_backup =
{
    WEIGHT_ADC_DISABLED
};


/*******************************************************************************
* Function Name: WEIGHT_ADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void WEIGHT_ADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: WEIGHT_ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void WEIGHT_ADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: WEIGHT_ADC_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The WEIGHT_ADC_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  WEIGHT_ADC_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void WEIGHT_ADC_Sleep(void)
{
    if((WEIGHT_ADC_PWRMGR_SAR_REG  & WEIGHT_ADC_ACT_PWR_SAR_EN) != 0u)
    {
        if((WEIGHT_ADC_SAR_CSR0_REG & WEIGHT_ADC_SAR_SOF_START_CONV) != 0u)
        {
            WEIGHT_ADC_backup.enableState = WEIGHT_ADC_ENABLED | WEIGHT_ADC_STARTED;
        }
        else
        {
            WEIGHT_ADC_backup.enableState = WEIGHT_ADC_ENABLED;
        }
        WEIGHT_ADC_Stop();
    }
    else
    {
        WEIGHT_ADC_backup.enableState = WEIGHT_ADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: WEIGHT_ADC_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  WEIGHT_ADC_Sleep() was called. If the component was enabled before the
*  WEIGHT_ADC_Sleep() function was called, the
*  WEIGHT_ADC_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  WEIGHT_ADC_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void WEIGHT_ADC_Wakeup(void)
{
    if(WEIGHT_ADC_backup.enableState != WEIGHT_ADC_DISABLED)
    {
        WEIGHT_ADC_Enable();
        #if(WEIGHT_ADC_DEFAULT_CONV_MODE != WEIGHT_ADC__HARDWARE_TRIGGER)
            if((WEIGHT_ADC_backup.enableState & WEIGHT_ADC_STARTED) != 0u)
            {
                WEIGHT_ADC_StartConvert();
            }
        #endif /* End WEIGHT_ADC_DEFAULT_CONV_MODE != WEIGHT_ADC__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
