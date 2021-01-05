/*
 * File:   Calculator_with_LCD.c
 * Author: afroe
 *
 * Created on June 25, 2019, 9:39 AM
 * Description
 * --------------------
 * CALCULATOR WITH KEYPAD AND LCD
 * 
 *  The keys are organised as follows:
            0 1 2 3
            4 5 6 7
            8 9 10 11
            12 13 14 15
    
 * The keys are labeled as follows:
            1   2     3       +
            4   5     6       -
            7   8     9       *
                0     Entter  /
 */

#define _XTAL_FREQ 8000000
//LATCbits.LATC6

#define RS RD2   
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include <xc.h>
#include <stdlib.h>
#include "lcd.h"
#include "Config_Bits.h"

#define MASK        0xF0
#define Enter       14
#define Plus        3
#define Minus       7
#define Multiply    11
#define Divide      15


// This funcƟon gets a key from the keypad and returns it to calling program
//
unsigned char getkeypad()
{
    unsigned char i, Key = 0;
    PORTC = 0x01; // Start with column 1
    while((PORTC & MASK) == 0) // While no key pressed
    {
        PORTC = (PORTC << 1); // next column
        Key++; // column number
        
        if(Key == 4)
           {
            PORTC = 0x01; // Back to column 1
            Key = 0;
            }   
    }

    __delay_ms(20); // Switch debounce
    
    for(i = 0x10; i !=0; i <<=1) // Find the key pressed
    {
        if((PORTC & i) != 0)break;
        Key = Key + 4;
    }

    PORTC = 0x0F;

    while((PORTC & MASK) != 0); // Wait unƟl key released
    
    __delay_ms(20); // Switch debounce
    
    return (Key); // Return key number
}




int main()
{
  unsigned char MyKey,i,j,Op[10];
  unsigned char Calc, Op1, Op2;
  
  ANSELD  = 0x00;         // Configure PORTD as Digital
  TRISD   = 0x00;         // Configure PORTD as output
 
  ANSELC = 0;
  TRISC  = 0xF0;
  // TRISD = 0x00;
  Lcd_Init();
  while(1)
  {
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Ethio_CALCULATOR");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("^Inside-Out^");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Developed_by:");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("TEDROS");
    __delay_ms(2000);
    Lcd_Clear();
    
    
//    Lcd_Set_Cursor(1,1);
//    Lcd_Write_String("Afro Embedded Solutions");
//
//    for(a=0;a<15;a++)
//    {
//        __delay_ms(600);
//        Lcd_Shift_Left();
//    }
//
//    for(a=0;a<15;a++)
//    {
//        __delay_ms(600);
//        Lcd_Shift_Right();
//    }
//
//    Lcd_Clear();
//    Lcd_Set_Cursor(2,1);
//    Lcd_Write_Char('A');
//    Lcd_Write_Char('A');
//    Lcd_Write_Char('S');
//    Lcd_Write_Char('T');
//    Lcd_Write_Char('U');
//    __delay_ms(2000);
//  }
  
 //Program Loop
    
    for(;;)
    {
        MyKey = 0;
        Op1 = 0;
        Op2 = 0;
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("No1:");
        
		while(1)
        {
            MyKey = getkeypad();
			if(MyKey == Enter)break;
			MyKey++;
			if(MyKey == 10)MyKey = 0;
			Lcd_Write_String(MyKey + '0'); 
			Op1 = 10 * Op1 + MyKey;
			
        }
		
		Lcd_Set_Cursor(2,1);
		Lcd_Write_String("No2:");
		
		while(1)
		{
			MyKey = getkeypad();
			if(MyKey == Enter)break;
			MyKey++;
			
			if(MyKey == 10) MyKey = 0;
			Lcd_Write_String(MyKey + '0');
			Op2 = 10 * Op2 + MyKey;
    }
			
			Lcd_Clear();
			Lcd_Set_Cursor(1,1);
			Lcd_Write_String("Op:");
			
			MyKey = getkeypad();
			Lcd_Clear();
			Lcd_Set_Cursor(1,1);
			Lcd_Write_String("Result=");
			
			switch(MyKey)
			{
				case Plus:
					Calc = Op1 + Op2;
					break;
				case Minus:
					Calc = Op1 - Op2;
					break;
				case Multiply:
					Calc = Op1 * Op2;
					break;
				case Divide:
					break;
					Calc = Op1/Op2;
			}		
	
				Itoa(op,Calc,10);
				Lcd_Write_String(op);
				__delay_ms(5000);
				Lcd_Clear();
	}
  return 0;
}