#include "lcd.h"
#include <pic1687x.h>


//-------------------------Reset LCD----------------------------------------
void reset()
{
TRISA=0;
//TRISC=0;
LCD_RESET =0;
delayMs(250);
LCD_RESET=1;

}

//------------------------Delay------------------------------------------------


void delay()
{
 int x;
    for(x=0;x<20;x++)
    {
    #asm
     nop
    #endasm
    } 
}   
//----------------------delay 1 -----------------------------

void delay1()
{
int x;
   for( x=0;x<3000;x++)
      {
      #asm
         nop
      #endasm
      }
}
//-----------------------Delay MS-------------------------------
void delayMs(int time)
{
 int x;
 int t;
 t=time*30;
 for(x=0;x<t;x++)
 {
   #asm 
     nop
    #endasm
 }
}
//-----------------SMALL DElay---------------------

void small_delay()
{
   int y;
   for(y=0;y<10000;y++)
   {
      #asm
       nop
      #endasm
      }
}
//-------------------------Writing a byte to the LCD----------------------------

void bytesender(char byte)
{

   int x;
   for( x=8;x>0;x--)
      {
         LCD_SCK=0;
         if((byte&0x80)==0x80)
            LCD_SDIN=1;
         else
            LCD_SDIN=0;
         LCD_SCK=1;
         byte=byte<<1;
      }
}

   

//----------------------------Writing Command byte---------------------------------


void writecommand(char byte )
{
LCD_DC=0;
bytesender(byte);

}

//--------------------------Writing character byte-------------------------------------
void writedata(char byte)
{
LCD_DC=1;
bytesender(byte);
}

//----------------------------write character------------------
void putchar(char character)
{
   int tablept, count, char_column;

   if ((character<0x20)||(character>0x7f)) {return;}      // Exit function if character is not found.
   tablept = ((5*character) - 160);                  // Point to the columns of the character in the table.

   for (count=5;count>0;count--)                     // Draw the columns to print the character.
   {
      char_column = pixel_table[tablept];
      writedata(char_column);
      tablept++;
   
   }
   writedata(0x00);                              // 1 pixel spacing per character.
}
//--------------------put char 2-----------------------

//------------------Put string--------------------------------

void putString(const char *s)
{
   while(*s) {putchar(*s++);}                        // Points to one ASCII to be written one at a time.
}
//-----------------put string 2--------------

//-------------------Clear RAM----------------------------
void clearram(void)
{
   int ddram;
   cursorxy(0,0);                                 // Cursor Home.
   for (ddram=504;ddram>0;ddram--)   {writedata(0x00);}      // 6*84 = 504 DDRAM addresses.
}
//------------------------go to Cursor XY--------------------

void cursorxy(char x, char y)
{
   writecommand(0x40|(y&0x07));   // Y axis
   writecommand(0x80|(x&0x7f));   // X axis
}

//----------------------------INITIALIZING---------------------------
void INIT()
{
   ADCON1=6;
   TRISA=0;
//TRISC=0;
//TRISB=0x00;
//PORTB=1;
reset();

//----------------------------control settings-------------------------
writecommand(0x21);
writecommand(0xC2);      // Set LCD Voltage to about 7V
writecommand(0x13);      // Adjust voltage bias.
writecommand(0x20);
writecommand(0x09);
delayMs(500);
writecommand(0x08);      // Clear display
delayMs(10);
writecommand(0x0C);
clearram();
cursorxy(0,0);

}

void switcher(int key)
{
   switch(key)
   {
      case 1:
         {
         putString("1");   
         break;
         }
      case 2:
         {
         putString("2");   
         break;
         }
      case 3:
         {
         putString("3");   
         break;
         }
      case 4:
         {
         putString("4");   
         break;
         }
      case 5:
         {
         putString("5");   
         break;
         }
      case 6:
         {
         putString("6");   
         break;
         }
      case 7:
         {
         putString("7");   
         break;
         }
      case 8:
         {
         putString("8");   
         break;
         }
      case 9:
         {
         putString("9");   
         break;
         }
      case 10:
         {
         putString("10");   
         break;
         }
      case 11:
         {
         putString("11");   
         break;
         }
      case 12:
         {
         putString("12");   
         break;
         }
      case 13:
         {
         putString("13");   
         break;
         }
      case 14:
         {
         putString("14");   
         break;
         }
      case 15:
         {
         putString("15");   
         break;
         }
      case 16:
         {
         putString("16");   
         break;
         }
      default:
         break;
      
   

   }
}

