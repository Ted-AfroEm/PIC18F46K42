/*
 * File:   Interrupt_on_Change.c
 * Author: Teddy
 *
 * Created on May 31, 2019, 11:30 AM
 * 
 * DESCRIPTION
 * ------------------
 * 	Potentiometer is used to read by RA0 then display in 4LEDs 
	based on voltage value:
	Voltage Level		LED
	  >1 volt		LED1_Blue_LED
	  >2 volt		LED2_Red_LED
	  >3 volt		LED3_Yellow_LED
	  >4 volt		LED4_Green_LED
 
 */


#include <xc.h>
#include "Config_Bits.h"
#include <stdint.h>

typedef uint16_t adc_result_t;

#define LED_4_LAT                  LATBbits.LATB0
#define LED_3_LAT                  LATBbits.LATB1
#define LED_2_LAT                  LATBbits.LATB2
#define LED_1_LAT                  LATBbits.LATB3

#define _XTAL_FREQ 4000000

adc_result_t ADCC_GetConversionResult(void)
{
    // Return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

void __interrupt() InterruptManager (void)
{
     // interrupt handler
    if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
    {
        adc_result_t adval = ADCC_GetConversionResult();
        LED_4_LAT = (adval > (1024*4.882)/5); 	// LED4 on if adval > 1volt
        LED_3_LAT = (adval > (1024*9.766)/5); 	// LED3 on if adval > 2volt
        LED_2_LAT = (adval > (1024*14.648)/5); 	// LED2 on if adval > 3volt
        LED_1_LAT = (adval > (1024*19.5312)/5); // LED1 on if adval > 4volt

        // Clear the ADCC interrupt flag
        PIR1bits.ADIF = 0;
    }
    else
    {
        //Unhandled Interrupt
    }
}
void ADCC_Initialize(void)
{   
   
    
    ADREF = 0x00;       //voltage reference to VSS and VDD
    ADPCH = 0x00;       //Select port A0 as input for ADCC
   
    ADPREL = 0x00;
  //8000 clocks of the selected ADC Clock 13.6ms
    ADACQL = 0x40;
    ADACQH = 0x1F;
   
    ADACT = 0x08;       //Auto conversion trigger Timer6
    ADCLK = 0x07;       //ADC conversion Clock FOSC/16
    ADCON0 = 0x94;      // ADGO stop; ADFM right; ADON enabled; ADCS Frc; ADCONT disabled; 
    
    PIE1bits.ADIE = 1;  // Enabling ADCC interrupt.
    PIR1bits.ADIF = 0; // Clear the ADC interrupt flag
    
           
}

void TMR6_Initialize(void)
{
    // Setting of Timer6
    T6CLKbits.CS = 0x04;    // Timer6 clock source LFINTOSC;  
    T6HLT = 0x00;           //Not Synchronized; Rising Edge; T6CKSYNC Not Synchronized; T6MODE Software control;  
    T6RST = 0x00;           // pin selected by T6INPPS
    T6PR = 0x60;            // period register; 
    T6TMR = 0x00;           // counter bits; 
    PIR9bits.TMR6IF = 0;    // Clearing IF flag.
    T6CON = 0xD0;           // timer is on; 1:32 prescaler; 1:1 postscaler;
}
void pin_manager(void)
{
    
    ANSELB  = 0xF0;         // Configure PORTB from RB0-RB3 as Digital
    TRISB   = 0xF0;         // Configure PORTB from RB0-RB3 as output
    
    ANSELAbits.ANSELA0 = 1;  // Configure PORTA from RA0 as Analog
    TRISAbits.TRISA0   = 1; // Configure PORTA from RA0 as input
    
}
void main(void) {
    
    INTCON0bits.GIE = 1;    //Enable the Global Interrupt
    
    pin_manager();
    TMR6_Initialize();
    ADCC_Initialize();
    
    ADCON0bits.ADGO = 1;    // Start the conversion
    
    //while loop is must for the continues working else it will
    //or ADC will only work once
    while(1)
    {
        
    }
    
}
