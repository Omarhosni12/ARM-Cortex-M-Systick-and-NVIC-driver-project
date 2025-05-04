/*
 * NVIC.c
 *
 *  Created on: Jul 29, 2024
 *      Author: CITY MALL
 */
#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
    /*check if the IRQ is between 0 and 31*/
    if((IRQ_Num >= 0) && (IRQ_Num <= 31))
    {
        NVIC_EN0_REG |= (1<<(IRQ_Num)); // set 1 on register EN0 to enable the intruppet
    }
    /*check if the IRQ is between 32 and 63*/
    else if ((IRQ_Num >= 32) && (IRQ_Num <= 63)){
        NVIC_EN1_REG |= (1 << (IRQ_Num-32)); // set 1 on register EN1 to enable the intruppet
    }
    /*check if the IRQ is between 64 and 95*/
    else if ((IRQ_Num >= 64) && (IRQ_Num <= 95)){
        NVIC_EN2_REG |= (1 << (IRQ_Num-64)); // set 1 on register EN2 to enable the intruppet
    }
    /*check if the IRQ is between 96 and 127*/
    else if ((IRQ_Num>=96) && (IRQ_Num<=127)){
        NVIC_EN3_REG |= (1<<(IRQ_Num-96));
    }
    /*check if the IRQ is between 128 and 138*/
    else if ((IRQ_Num>=128) && (IRQ_Num<=138)){
           NVIC_EN4_REG |= (1<<(IRQ_Num-128)); // set 1 on register EN3 to enable the intruppet
       }
}



void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
    /*check if the IRQ is between 0 and 31*/
    if((IRQ_Num >= 0) && (IRQ_Num <= 31))
    {
        NVIC_DIS0_REG |= (1<<(IRQ_Num)); // set 1 on register DIS0 to DISable the intruppet
    }
    /*check if the IRQ is between 32 and 63*/
    else if ((IRQ_Num >= 32) && (IRQ_Num <= 63)){
        NVIC_DIS1_REG |= (1 << (IRQ_Num-32)); // set 1 on register DIS1 to DISable the intruppet
    }
    /*check if the IRQ is between 64 and 95*/
    else if ((IRQ_Num >= 64) && (IRQ_Num <= 95)){
        NVIC_DIS2_REG |= (1 << (IRQ_Num-64)); // set 1 on register DIS2 to DISable the intruppet
    }
    /*check if the IRQ is between 96 and 127*/
    else if ((IRQ_Num>=96) && (IRQ_Num<=127)){
        NVIC_DIS3_REG |= (1<<(IRQ_Num-96)); // set 1 on register DIS2 to DISable the intruppet
    }
    /*check if the IRQ is between 128 and 138*/
    else if ((IRQ_Num>=128) && (IRQ_Num<=138)){
        NVIC_DIS4_REG |= (1<<(IRQ_Num-128)); // set 1 on register DIS3 to disable the intruppet
       }
}




void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){
    uint8 register_index = 0;
    uint8 IRQ_Pos_order_in_group,Priority_bits_position,Priority_mask;
    if ((IRQ_Priority>=0) && (IRQ_Priority<=7))
    {

        register_index=(IRQ_Num)/4;//find in which PRIN where the IRQ is in

        IRQ_Pos_order_in_group=(IRQ_Num%4);//find in which 3 bits in the register will we put the Priority number
        Priority_bits_position= 5+((IRQ_Pos_order_in_group)*8);//the shift needed to position the Priority Bits

        // Mask to clear the existing priority field
        Priority_mask = (0x7 << Priority_bits_position);

        // Access the corresponding IPR register and set the priority
        PRI( register_index ) = ( (PRI(register_index) & ~Priority_mask) | ((IRQ_Priority)<<Priority_bits_position ));
    }
}



/*************************exceptions***************************/



void NVIC_EnableException(NVIC_ExceptionType Exception_Num){
    switch(Exception_Num){
        case EXCEPTION_RESET_TYPE:
            //CANT BE ENABLED NOR DISABLED
        break;

        case EXCEPTION_NMI_TYPE:
            //CANT BE ENABLED NOR DISABLED
        break;

        case EXCEPTION_HARD_FAULT_TYPE:
            //ALWAYS ENABLED
        break;

        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
        break;

        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
        break;

        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
        break;

        case EXCEPTION_SVC_TYPE:
            //always enabled and cannot be disabled
        break;

        case EXCEPTION_DEBUG_MONITOR_TYPE:
            //always enabled and cannot be disabled
        break;

        case EXCEPTION_PEND_SV_TYPE:
            //always enabled and cannot be disabled
        break;

        case EXCEPTION_SYSTICK_TYPE:
            //NO NEED TO ENBALE it
        break;

        default:
            // Handle invalid exception number
        break;
    }
}




void NVIC_DisableException(NVIC_ExceptionType Exception_Num){
    switch(Exception_Num){
        case EXCEPTION_RESET_TYPE:
            //CANT BE ENABLED NOR DISABLED
        break;

        case EXCEPTION_NMI_TYPE:
            //CANT BE ENABLED NOR DISABLED
        break;

        case EXCEPTION_HARD_FAULT_TYPE:
            //ALWAYS ENABLED
        break;

        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
        break;

        case EXCEPTION_BUS_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
        break;

        case EXCEPTION_USAGE_FAULT_TYPE:
            NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
        break;

        case EXCEPTION_SVC_TYPE:
            //always enabled and cannot be disabled
        break;

        case EXCEPTION_DEBUG_MONITOR_TYPE:
            //always enabled and cannot be disabled
        break;

        case EXCEPTION_PEND_SV_TYPE:
            //always enabled and cannot be disabled
        break;

        case EXCEPTION_SYSTICK_TYPE:
            SYSTICK_CTRL_REG &= ~(1<<1); //Interrupt generation is disabled.
        break;

        default:
            // Handle invalid exception number
        break;
    }
}






void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){
    switch(Exception_Num){
        case EXCEPTION_RESET_TYPE:
            // Reset exception has a fixed priority and cannot be changed.
        break;

        case EXCEPTION_NMI_TYPE:
            // NMI has a fixed priority and cannot be changed.
        break;

        case EXCEPTION_HARD_FAULT_TYPE:
            // Hard Fault has a fixed priority and cannot be changed.
        break;

        case EXCEPTION_MEM_FAULT_TYPE:
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
        break;

        case EXCEPTION_BUS_FAULT_TYPE:
            /* Assign priority level  to the Bus Fault Exception */
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
        break;

        case EXCEPTION_USAGE_FAULT_TYPE:
            /* Assign priority level  to the Usage Fault Exception */
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
        break;

        case EXCEPTION_SVC_TYPE:
            /* Assign priority level  to the SVC Interrupt */
            NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
        break;

        case EXCEPTION_DEBUG_MONITOR_TYPE:
            /* Assign priority level  to the DEBUG_MONITOR  */
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
        break;

        case EXCEPTION_PEND_SV_TYPE:
            /* Assign priority level  to the PENDSV  */
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
        break;

        case EXCEPTION_SYSTICK_TYPE:
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
        break;

        default:
            // Handle invalid exception number
        break;
    }
}


