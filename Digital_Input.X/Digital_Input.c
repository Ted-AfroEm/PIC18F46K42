/*
 * File:   Digital_Input.c
 * Author: Teddy
 *
 * Created on May 27, 2019, 8:49 PM
 * 
 DESCRIPTION
 * ------------------
 * LED at RB3 is on when Button at RC5 is pressed
 */

#include <xc.h>
#include "Config_Bits.h"

#define _XTAL_FREQ 8000000

#define LED_1_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define LED_1_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define SWITCH_GetValue()           PORTCbits.RC5

void main(void) {
//    ANSELBbits.ANSELB3 = 0; //Set RB3 Digital
//    ANSELCbits.ANSELC5 = 0; //set RC5 Digital
//    
//    TRISBbits.TRISB3 = 0;   //set RB3 as output
//    TRISCbits.TRISC5 = 1;   //set RC5 as input

    ANSELB = 0xF7; //Set RB3 Digital
    ANSELC = 0xDF; //set RC5 Digital
    
    TRISB = 0xF7;   //set RB3 as output
    TRISC = 0xFF;   //set RC5 as input
    

    while(1)
    {
        if(SWITCH_GetValue()==0)
        {
            LED_1_SetHigh();
        }
        else
        {
            LED_1_SetLow();
        }
    }

}
