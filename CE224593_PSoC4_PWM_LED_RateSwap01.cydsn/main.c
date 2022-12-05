/******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description: This example demonstrates how to drive an LED with PWM output
* with the ability to swap the blinking rates between slow and fast.
*
* Related Document: CE224593_PSoC4_TCPWM_PWM.pdf 
*
* Hardware Dependency: CY8CKIT-042 PSoC 4 PIONEER KIT
*
******************************************************************************
* Copyright (2018-2019), Cypress Semiconductor Corporation.
******************************************************************************
* This software, including source code, documentation and related materials
* ("Software") is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the 
* Cypress source code and derivative works for the sole purpose of creating 
* custom software in support of licensee product, such licensee product to be
* used only in conjunction with Cypress's integrated circuit as specified in the
* applicable agreement. Any reproduction, modification, translation, compilation,
* or representation of this Software except as specified above is prohibited 
* without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes to the Software without notice. 
* Cypress does not assume any liability arising out of the application or use
* of Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use as critical components in any products 
* where a malfunction or failure may reasonably be expected to result in 
* significant injury or death ("ACTIVE Risk Product"). By including Cypress's 
* product in a ACTIVE Risk Product, the manufacturer of such system or application
* assumes all risk of such use and in doing so indemnifies Cypress against all
* liability. Use of this Software may be limited by and subject to the applicable
* Cypress software license agreement.
*****************************************************************************/

#include <project.h>

/***************************************************************************//**
* Function Name: ISR_TC
********************************************************************************
*
* Summary:
* This function is executed when interrupt for terminal count occurs.
* This ISR:
*   1. Clears the interrupt
*   2. Toggles the state of LED
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(TC_ISR_Handler)
{
    /* Interrupt is cleared */ 
    PWM_ClearInterrupt(PWM_INTR_MASK_TC);

    /* LED is toggled ON and OFF */
    LED_RED_Write(~LED_RED_Read());
}

/*******************************************************************************
* Function Name: main
********************************************************************************
*
*  The main function performs the following actions:
*   1. Sets up and enables the PWM and its interrupt.
*   2. Starts the PWM Component
*
*******************************************************************************/
int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    /* Enable interrupt component and set up handler */
    TC_ISR_StartEx(TC_ISR_Handler);
    
    /* Start the PWM Component */
    PWM_Start();
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
