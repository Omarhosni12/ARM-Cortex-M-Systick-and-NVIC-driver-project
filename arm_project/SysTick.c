/*
 * SysTick.c
 *
 *  Created on: Jul 29, 2024
 *      Author: CITY MALL
 */
#include "SysTick.h"


void SysTick_Init(uint16 a_TimeInMilliSeconds){
    SYSTICK_CTRL_REG    = 0;               /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = ((a_TimeInMilliSeconds/1000) * (SysClock_Freq))-1;         /* Set the Reload value */
    SYSTICK_CURRENT_REG = 0;               /* Clear the Current Register value */

/* Configure the SysTick Control Register
 * Enable the SysTick Timer (ENABLE = 1)
 * Enable SysTick Interrupt (INTEN = 1)
 * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SysTick_Start();
    SYSTICK_CTRL_REG |= 0x06;
}


void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){

    SYSTICK_CTRL_REG    = 0;              /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = ((a_TimeInMilliSeconds/1000) * (SysClock_Freq))-1;        /* Set the Reload value */
    SYSTICK_CURRENT_REG = 0;              /* Clear the Current Register value */

    /* Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SysTick_Start();
    SYSTICK_CTRL_REG |= 0x04;

    /*wait until the time is elapsed*/
    while(!(SYSTICK_CTRL_REG & (1<<16))); /* wait until the COUNT flag = 1 which mean SysTick Timer reaches ZERO value ... COUNT flag is cleared after read the CTRL register value */

    /*stops the timer*/
    SysTick_Stop();

}



void SysTick_Hander(void){
    if(g_CallBackPtr != NULL_PTR){
        (*g_CallBackPtr)(); //calls the callback function.
    }
}




void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
    g_CallBackPtr = Ptr2Func; //the pointer now has the address of the callback function
}


void SysTick_Stop(void){
    /*stops the timer*/
    SYSTICK_CTRL_REG   &= ~(1<<0);//Disable SysTick
}


void SysTick_Start(void)
{
    /*enable SysTick timer*/
    SYSTICK_CTRL_REG   |= (1<<0);

}


void SysTick_DeInit(void){
    SysTick_Stop();
    SYSTICK_RELOAD_REG  = 0;    /* Clear the Reload register */
    SYSTICK_CURRENT_REG = 0;    /* Clear the Current Register value */
}
