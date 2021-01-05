/*
 * File:   Interrupt_on_Change.c
 * Author: Teddy
 *
 * Created on May 30, 2019, 9:30 AM
 * 
 * DESCRIPTION
 * ------------------
 * This project uses interrupt on change on pins in rising edge or falling edge
 * Pin RC5 is connected with button to act as IOC on negative-going edge
 * then led green, yellow and red toggle when this interrupt is detected
 */


//#include <xc.h>
#include <pic18f46k42.h>
#include "Config_Bits.h"

#define LED_1_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define LED_2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define LED_3_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)

#define _XTAL_FREQ 8000000

void __interrupt() InterruptManager (void)
{
    // interrupt handler
    if(PIE0bits.IOCIE == 1 && IOCCFbits.IOCCF5 ==1)
    {
        LED_1_Toggle();
        LED_2_Toggle();
        LED_3_Toggle();
        
        IOCCFbits.IOCCF5 = 0;
        
    }
    else
    {
        //Unhandled Interrupt
    }
}

void main(void) {
    
    ANSELB  = 0xF1;         // Configure PORTB from RB1-RB3 as Digital
    TRISB   = 0xF1;         // Configure PORTB from RB1-RB3 as output
    ANSELCbits.ANSELC5 = 0; // Configure PORTC from RC5 as Digital
    TRISCbits.TRISC5   = 1; // Configure PORTc from RC5 as input
    WPUC = 0x20;            // weak pull-ups for RC5

    INTCON0bits.GIE = 1;    //Enable the Global Interrupts
    PIE0bits.IOCIE   = 1;   //interrupt_on_change enable bit
    
    IOCCFbits.IOCCF5 = 0;   //interrupt on change for group IOCCF - flag
    IOCCPbits.IOCCP5 = 0;   //interrupt on change for group IOCCP - positive
    IOCCNbits.IOCCN5 = 1;   //IOC on RC5 for a negative-going edge
}
