/*
 * File:   LCD_test.c
 * Author: Teddy
 *
 * Created on June 4, 2019, 11:09 AM

DESCRIPTION
 * ------------------
	This is LCD that display string out.
 * 	
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
#include "lcd.h"
#include "Config_Bits.h"


int main()
{
  unsigned int a;
  ANSELD  = 0x00;         // Configure PORTD as Digital
  TRISD   = 0x00;         // Configure PORTD as output
 // TRISD = 0x00;
  Lcd_Init();
  while(1)
  {
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("  AASTU 2019  ");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("BlueMoon Intern");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Developed_by:");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("TEDROS");
    __delay_ms(2000);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Afro Embedded Solutions");

    for(a=0;a<15;a++)
    {
        __delay_ms(600);
        Lcd_Shift_Left();
    }

    for(a=0;a<15;a++)
    {
        __delay_ms(600);
        Lcd_Shift_Right();
    }

    Lcd_Clear();
    Lcd_Set_Cursor(2,1);
    Lcd_Write_Char('A');
    Lcd_Write_Char('A');
    Lcd_Write_Char('S');
    Lcd_Write_Char('T');
    Lcd_Write_Char('U');
    __delay_ms(2000);
  }
  return 0;
}