/*
 * File:   Guess_Which_LEDs.c
 * Author: Teddy
 *
 * Created on May 28, 2019, 4:58 AM
 * 
 *  DESCRIPTION
 * ------------------
 * The rand function returns a pseudo-random number between 0 and 32767
 * To generate a number between 1 and 15, we can divide the generated number by 2048
 * Finally we get the output in the 4 LEDS 
 */


#include <xc.h>
#include <stdlib.h>
#include "Config_Bits.h"

#define _XTAL_FREQ 8000000

void main(void) {
    int rand_num;
    
    ANSELB  = 0xF0; // Configure PORTB from RB0-RB3 as Digital
    TRISB   = 0xF0; // Configure PORTB from RB0-RB3 as output
    
    srand(10);    //random number seed is initialized 
     
      while(1)
    {   
        
        rand_num = rand();
        rand_num = rand_num/2048;
        PORTB = rand_num;
        __delay_ms(6000);
        
    }
}
