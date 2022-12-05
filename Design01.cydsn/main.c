/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

typedef unsigned char Bool;

#define False 0
#define True (!False)

Bool increment = True;
Bool interrupt = False;

CY_ISR(TC_ISR_Handler)
{
    /* Interrupt is cleared */ 

    interrupt = True;
    
    PWM_ClearInterrupt(PWM_INTR_MASK_TC);

    /* LED is toggled ON and OFF */
    //LED_RED_Write(~LED_RED_Read());
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
    char str[6];
    uint16 counter;
    
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    /* Enable interrupt component and set up handler */
    TC_ISR_StartEx(TC_ISR_Handler);
    
    /* Start the PWM Component */
    PWM_Start();
    UART_Start();
    
    UART_UartPutString("PWM Example written by Johann Schmid\x0d\x0a");
    UART_UartPutString("visit my channel youtube.com/@elektrotechnik2go\x0d\x0a");
    
    for(;;)
    {

    if (interrupt == True)
    {
        counter = PWM_ReadCompare();
        
        if (counter == 10000)
        {
            increment = False;
            
            sprintf(str, "%d", counter);
            strncat(str, "\x0d\x0a", 2);
            UART_UartPutString(str);
        }
        
        if (counter == 100)
        {
            increment = True;
            
            sprintf(str, "%d", counter);
            strncat(str, "\n", 2);
            UART_UartPutString(str);
        }
        
        if (increment == True)
        { 
            counter = counter + 100;
        }
        else
        {
            counter = counter - 100;
        }
        
        PWM_WriteCompare(counter);
        
        interrupt = False;
    }
    
    }
}

/* [] END OF FILE */
