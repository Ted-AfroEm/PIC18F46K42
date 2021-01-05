/*
 * File:   Blink_Led.c
 * Author: Teddy
 *
 * Created on May 27, 2019, 8:33 AM
 * 
          LED       PORT    J       Binary
        BlueLED     RBO:    1       0001
        RedLED-     RB1:    2       0010
        YelloLED-   RB2:    4       0100
        GreenLEd-   RB3:    8       1000
        Reset              16      10000     
     */

#include <xc.h>
#include "Config_Bits.h"

#define _XTAL_FREQ 8000000

void main()
{
  
    unsigned char J = 1;
    
    ANSELB  = 0xF0; // Configure PORTB from RB0-RB3 as Digital
    TRISB   = 0xF0; // Configure PORTB from RB0-RB3 as output
    
    for(;;) // Endless loop
    {
        PORTB = J;          // Send J to PORTB
        __delay_ms(500);   // Delay 1s
        J = J << 1;         // Shift left J
    
        if(J == 16) J = 1;  // If last LED 10000, move to first one
}
}
   
