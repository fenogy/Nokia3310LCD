#include "nokia3310.h"



int countgloble;
    // 7f Left Arrow   <-

  
void reset();
void bytesender(int8 val);
void writecommand(int8 val);
void writedata(int8 val);
void putchara(char chr);
void putString(char *s);
void clearram(void);
void cursorxy(int8 x, int8 y);
void INIT();
void switcher(int8 key);



 char pixel_table[480] = {   
                           0x00,0x00,0x00,0x00,0x00,   // 20 space      ASCII table for NOKIA LCD: 96 rows * 5 bytes= 480 bytes
                       0x00,0x00,0x5f,0x00,0x00,   // 21 !         Note that this is the same set of codes for character you
                     0x00,0x07,0x00,0x07,0x00,   // 22 "         would find on a HD44780 based character LCD. :)
                     0x14,0x7f,0x14,0x7f,0x14,   // 23 #         Also, given the size of the LCD (84 pixels by 48 pixels),
                     0x24,0x2a,0x7f,0x2a,0x12,   // 24 $         the maximum number of characters per row is only 14. :)
                     0x23,0x13,0x08,0x64,0x62,   // 25 %
                     0x36,0x49,0x55,0x22,0x50,   // 26 &
                     0x00,0x05,0x03,0x00,0x00,   // 27 '
                     0x00,0x1c,0x22,0x41,0x00,   // 28 (
                     0x00,0x41,0x22,0x1c,0x00,   // 29 )
                     0x14,0x08,0x3e,0x08,0x14,   // 2a *
                     0x08,0x08,0x3e,0x08,0x08,   // 2b +
                     0x00,0x50,0x30,0x00,0x00,   // 2c ,
                     0x08,0x08,0x08,0x08,0x08,   // 2d -
                     0x00,0x60,0x60,0x00,0x00,   // 2e .
                     0x20,0x10,0x08,0x04,0x02,   // 2f /
                     0x3e,0x51,0x49,0x45,0x3e,   // 30 0
                     0x00,0x42,0x7f,0x40,0x00,   // 31 1
                     0x42,0x61,0x51,0x49,0x46,   // 32 2
                     0x21,0x41,0x45,0x4b,0x31,   // 33 3
                     0x18,0x14,0x12,0x7f,0x10,   // 34 4
                     0x27,0x45,0x45,0x45,0x39,   // 35 5
                     0x3c,0x4a,0x49,0x49,0x30,   // 36 6
                     0x01,0x71,0x09,0x05,0x03,   // 37 7
                     0x36,0x49,0x49,0x49,0x36,   // 38 8
                     0x06,0x49,0x49,0x29,0x1e,   // 39 9
                     0x00,0x36,0x36,0x00,0x00,   // 3a :
                     0x00,0x56,0x36,0x00,0x00,   // 3b ;
                     0x08,0x14,0x22,0x41,0x00,   // 3c <
                     0x14,0x14,0x14,0x14,0x14,   // 3d =
                     0x00,0x41,0x22,0x14,0x08,   // 3e >
                     0x02,0x01,0x51,0x09,0x06,   // 3f ?
                     0x32,0x49,0x79,0x41,0x3e,   // 40 @
                     0x7e,0x11,0x11,0x11,0x7e,   // 41 A
                     0x7f,0x49,0x49,0x49,0x36,   // 42 B
                     0x3e,0x41,0x41,0x41,0x22,   // 43 C
                     0x7f,0x41,0x41,0x22,0x1c,   // 44 D
                     0x7f,0x49,0x49,0x49,0x41,   // 45 E
                     0x7f,0x09,0x09,0x09,0x01,   // 46 F
                     0x3e,0x41,0x49,0x49,0x7a,   // 47 G
                     0x7f,0x08,0x08,0x08,0x7f,   // 48 H
                     0x00,0x41,0x7f,0x41,0x00,   // 49 I
                     0x20,0x40,0x41,0x3f,0x01,   // 4a J
                     0x7f,0x08,0x14,0x22,0x41,   // 4b K
                     0x7f,0x40,0x40,0x40,0x40,   // 4c L
                     0x7f,0x02,0x0c,0x02,0x7f,   // 4d M
                     0x7f,0x04,0x08,0x10,0x7f,   // 4e N
                     0x3e,0x41,0x41,0x41,0x3e,   // 4f O
                     0x7f,0x09,0x09,0x09,0x06,   // 50 P
                     0x3e,0x41,0x51,0x21,0x5e,   // 51 Q
                     0x7f,0x09,0x19,0x29,0x46,   // 52 R
                     0x46,0x49,0x49,0x49,0x31,   // 53 S
                     0x01,0x01,0x7f,0x01,0x01,   // 54 T
                     0x3f,0x40,0x40,0x40,0x3f,   // 55 U
                     0x1f,0x20,0x40,0x20,0x1f,   // 56 V
                     0x3f,0x40,0x38,0x40,0x3f,   // 57 W
                     0x63,0x14,0x08,0x14,0x63,   // 58 X
                     0x07,0x08,0x70,0x08,0x07,   // 59 Y
                     0x61,0x51,0x49,0x45,0x43,   // 5a Z
                     0x00,0x7f,0x41,0x41,0x00,   // 5b [
                     0x02,0x04,0x08,0x10,0x20,   // 5c Yen Currency Sign
                     0x00,0x41,0x41,0x7f,0x00,   // 5d ]
                     0x04,0x02,0x01,0x02,0x04,   // 5e ^
                     0x40,0x40,0x40,0x40,0x40,   // 5f _
                     0x00,0x01,0x02,0x04,0x00,   // 60 `
                     0x20,0x54,0x54,0x54,0x78,   // 61 a
                     0x7f,0x48,0x44,0x44,0x38,   // 62 b
                     0x38,0x44,0x44,0x44,0x20,   // 63 c
                     0x38,0x44,0x44,0x48,0x7f,   // 64 d
                     0x38,0x54,0x54,0x54,0x18,   // 65 e
                     0x08,0x7e,0x09,0x01,0x02,   // 66 f
                     0x0c,0x52,0x52,0x52,0x3e,   // 67 g
                     0x7f,0x08,0x04,0x04,0x78,   // 68 h
                     0x00,0x44,0x7d,0x40,0x00,   // 69 i
                     0x20,0x40,0x44,0x3d,0x00,   // 6a j 
                     0x7f,0x10,0x28,0x44,0x00,   // 6b k
                     0x00,0x41,0x7f,0x40,0x00,   // 6c l
                     0x7c,0x04,0x18,0x04,0x78,   // 6d m
                     0x7c,0x08,0x04,0x04,0x78,   // 6e n
                     0x38,0x44,0x44,0x44,0x38,   // 6f o
                     0x7c,0x14,0x14,0x14,0x08,   // 70 p
                     0x08,0x14,0x14,0x18,0x7c,   // 71 q
                     0x7c,0x08,0x04,0x04,0x08,   // 72 r
                     0x48,0x54,0x54,0x54,0x20,   // 73 s
                     0x04,0x3f,0x44,0x40,0x20,   // 74 t
                     0x3c,0x40,0x40,0x20,0x7c,   // 75 u
                     0x1c,0x20,0x40,0x20,0x1c,   // 76 v
                     0x3c,0x40,0x30,0x40,0x3c,   // 77 w
                     0x44,0x28,0x10,0x28,0x44,   // 78 x
                     0x0c,0x50,0x50,0x50,0x3c,   // 79 y
                     0x44,0x64,0x54,0x4c,0x44,   // 7a z
                     0x00,0x08,0x36,0x41,0x00,   // 7b <
                     0x00,0x00,0x7f,0x00,0x00,   // 7c |
                     0x00,0x41,0x36,0x08,0x00,   // 7d >
                     0x10,0x08,0x08,0x10,0x08,   // 7e Right Arrow    ->
                     0x78,0x46,0x41,0x46,0x78
                     };




char str[12] = {'V','O','L','T','S','\0'};
int i = 0;
void main()
{

   //setup_adc_ports(NO_ANALOGS|VSS_VDD);
   //setup_adc(ADC_OFF|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   //setup_comparator(NC_NC_NC_NC);
   //setup_vref(FALSE);
   setup_oscillator(False);

   // TODO: USER CODE!!
   
   INIT();
   
  // INIT();
  
  
   clearram();
   
         cursorxy(40,30);
         i=61;
      while(i<90){
     putchara(i);
     i++;
     //if((i%72) == 0){
     //clearram();
     ///}
      }
      while(1){


                              
//!      delay_ms(100);
//
//!      cursorxy(0,1);
//!     // putString("1.Security Settings");
//!      putchar('M');
//!      delay_ms(100);
//!      cursorxy(0,2);
//!     // putString("2.IP setting");
//!      putchar('M');
//!      cursorxy(0,3);
//!      delay_ms(100);
//!     // putString("3.Registration");
//!      putchar('M');
//!      cursorxy(0,4);
//!      //putString("4.Factory Reset");
//!       putchar('M');
//!      cursorxy(50,5);
//!      delay_ms(100);
//!      //putString("Back");
//!       putchar('M');

//writedata(0xFF);
      

   
      output_high(PIN_E0);
      delay_ms(2000);
      putc('A');
      output_low(PIN_E0);
      delay_ms(2000);
      
      putc('B');
   }

}

//-------------------------Reset LCD----------------------------------------


void reset()
{
set_tris_d(0x00);
//TRISC=0;
//LCD_RESET = FALSE;
output_low(PIN_D3);
delay_ms(250);
output_high(PIN_D3);

}

//-------------------------Writing a byte to the LCD----------------------------

void bytesender(int8 val){

   int x;
   
   for(x=8;x>0;x--)
      {
         //LCD_SCK=0;
         output_low(PIN_D0);
         if((val&0x80)==0x80)
            //LCD_SDIN=1;
            output_high(PIN_D1);
         else
            //LCD_SDIN=0;
            output_low(PIN_D1);
         //LCD_SCK=1;
         output_high(PIN_D0);
         val=val<<1;
      }
}

   

//----------------------------Writing Command byte---------------------------------


void writecommand(int8 val){
   //LCD_DC=0;
   output_low(PIN_D2);
   bytesender(val);

}

//--------------------------Writing character byte-------------------------------------
void writedata(int8 val){
   //LCD_DC=1;
   output_high(PIN_D2);
   bytesender(val);
}


void putchara(char chr){

   int16 tablept, count, char_column;

   if ((chr<0x20)||(chr>0x7f)) {
   
      return;                           // Exit function if character is not found.
   }  
   
   tablept = ((5*chr) - 160);                  // Point to the columns of the character in the table.

   for (count=5;count>0;count--)                     // Draw the columns to print the character.
   {
      char_column = pixel_table[tablept];
    //char_column = 0x15;
      writedata(char_column);
      tablept++;
   
   }
   writedata(0x00);                              // 1 pixel spacing per character.
}


void putString(char *s)
{
   while(*s) {putchar(*s++);}                        // Points to one ASCII to be written one at a time.
}


//-------------------Clear RAM----------------------------
void clearram(void){

   int16 ddram;
   cursorxy(0,0);                                 // Cursor Home.
   for (ddram=504;ddram>0;ddram--){
   
    writedata(0x00);                               // 6*84 = 504 DDRAM addresses
   
   }      
}
//------------------------go to Cursor XY--------------------

void cursorxy(int8 x, int8 y){

   writecommand(0x40|(y&0x07));   // Y axis
   writecommand(0x80|(x&0x7f));   // X axis

}

//----------------------------INITIALIZING---------------------------
void INIT(){

  // ADCON1=6;// Idid this
   set_tris_d(0x00);
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
delay_ms(500);
writecommand(0x08);      // Clear display
delay_ms(10);
writecommand(0x0C);
clearram();
cursorxy(0,0);

//while(1){
///writedata(0x01);
//putchara('P');
//putchara('R');
//putchara('A');
//putchara('B');
//putchara('A');
//putchara('S');
//putchara('H');

//}

//while(1){

//   delay_ms(100);
//   writedata(0xFF);
//   writedata(0x0F);
//   writedata(0xF0);
//}

}
