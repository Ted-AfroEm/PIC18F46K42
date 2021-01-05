/*
 * File:   Binary_CounterLED.c
 * Author: Teddy
 *
 * Created on May 28, 2019, 7:24 AM
 * 
 *  DESCRIPTION
 * ------------------
 * Binary counts every 500ms until 1111
 */

#include <xc.h>
#include "Config_Bits.h"

#define _XTAL_FREQ 8000000


void main(void) {
    unsigned char num = 1;
    unsigned char Pattern;
    unsigned char COUNTER[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    
    ANSELB  = 0xF0; // Configure PORTB from RB0-RB3 as Digital
    TRISB   = 0xF0; // Configure PORTB from RB0-RB3 as output
  
         
    for(;;)
          {
              Pattern = COUNTER[num];
              PORTB = Pattern;
              __delay_ms(500);   // Delay 1s
              if(num ==16) num = 1;
              else num++;
          }
          
    
}