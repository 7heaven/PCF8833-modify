// This library has been created by Markos Kyritsis. The stuff is all copyleft, so go ahead and do whatever you like
// with it. Please contribute to the community and upload all changes to the arduino playground for everyone else to 
// use. Enjoy!

#include "PCF8833.h"
// #include <wiring_digital.c>

extern "C" {
    // #include <wiring_private.h>
// #include <inttypes.h>
// #include <avr/pgmspace.h>
}

PCF8833::PCF8833(int8_t CS, int8_t SCLK, int8_t SDIN) {
    cs = CS;
	sclk = SCLK;
	sdin = SDIN;
}

void PCF8833::LCDClear(int color)	// Clear the whole screen with the specified colour
{

    LCDCommand(0x2B);
    LCDData(0);
    LCDData(132);
    LCDCommand(0x2A);
    LCDData(0);
    LCDData(132);
    LCDCommand(0x2C);
    for(int i=0; i < (132*132)/2; i++)
    {
        LCDData((color>>4)&0x00FF);
        LCDData(((color&0x0F)<<4)|(color>>8));
        LCDData(color&0x0FF);
    }
}



void PCF8833::LCDInit()	// Initialise the screen
{

    pinMode(cs, 0x1);
	pinMode(sclk, 0x1);
	pinMode(sdin, 0x1);
	
    csport      = portOutputRegister(digitalPinToPort(cs));
    cspinmask   = digitalPinToBitMask(cs);
	sclkport    = portOutputRegister(digitalPinToPort(sclk));
	sclkpinmask = digitalPinToBitMask(sclk);
	sdinport    = portOutputRegister(digitalPinToPort(sdin));
	sdinpinmask = digitalPinToBitMask(sdin);
	
    LCDCommand(0x11);   //Sleep_OUT
    LCDCommand(0x03);   //booster voltage on(BSTRON)
    LCDCommand(0x21);   //display inversion on(INVON)
    LCDCommand(0x36);   //memory data access control(MADCTL)
    LCDData(0xC8);      //
    LCDCommand(0x3A);   //interface pixel format(COLMOD)
    LCDCommand(0x25);   //set contrast(SETCON)
    LCDData(0x30);	    //
    LCDCommand(0x00);   //no operation(NOP) (for delay)

    LCDCommand(0x29);   //display on(DISPON)

}

void PCF8833::LCDCommand(unsigned char data) // Send a hex command through the serial port (SDATA 0 first)
{
    *csport &= ~cspinmask; //digitalWrite(CS,0); 	      // disable CS
    *sdinport &= ~sdinpinmask; //digitalWrite(SDATA,0);     // Disable Serial Data line, This means we are sending a command
    *sclkport &= ~sclkpinmask; //digitalWrite(SCLK,0);      // Disable Serial Clock
    *sclkport |= sclkpinmask; //digitalWrite(SCLK,1);	// Enable Serial Clock
    for (char j = 0; j < 8; j++)
    {
        if ((data & 0x80) == 0x80) 
            *sdinport |= sdinpinmask; //digitalWrite(SDATA,1);
        else 
            *sdinport &= ~sdinpinmask; //digitalWrite(SDATA,0);
        *sclkport &= ~sclkpinmask; //digitalWrite(SCLK,0);      // Disable Clock
        *sclkport |= sclkpinmask; //digitalWrite(SCLK,1);     // Enable Clock
        data <<= 1;
    }
    *sclkport &= ~sclkpinmask; //digitalWrite(SCLK,0);      // Disable Clock
    *sdinport &= ~sdinpinmask; //digitalWrite(SDATA,0);	   // Disable Serial Data	

    *csport |= cspinmask; //digitalWrite(CS,1);     // Enable CS
}

void PCF8833::LCDData(unsigned char data) // Send hex data through the serial port (SDATA 1 first)
{
    *csport &= ~cspinmask; //digitalWrite(CS,0); 	      // disable CS
    *sdinport |= sdinpinmask; //digitalWrite(SDATA,1);     // Enable Serial Data line, This means we are sending data
    *sclkport &= ~sclkpinmask; //digitalWrite(SCLK,0);      // Disable Serial Clock
    *sclkport |= sclkpinmask; //digitalWrite(SCLK,1);	// Enable Serial Clock

    for (char j = 0; j < 8; j++)
    {
        if ((data & 0x80) == 0x80)
            *sdinport |= sdinpinmask; //digitalWrite(SDATA,1);	// Enable Serial Data
        else 
            *sdinport &= ~sdinpinmask; //digitalWrite(SDATA,0); // Disable Serial Data line

        *sclkport &= ~sclkpinmask; //digitalWrite(SCLK,0);       // Disable Clock
        *sclkport |= sclkpinmask; //digitalWrite(SCLK,1);	// Enable Clock
        data <<= 1;
    }
    *sclkport &= ~sclkpinmask; //digitalWrite(SCLK,0);     // Disable Clock
    *sdinport &= ~sdinpinmask; //digitalWrite(SDATA,0);	// Disable Serial Data

    *csport |= ~cspinmask; //digitalWrite(CS,1);	 // Enable CS
}

void PCF8833::DrawPixel(int color, unsigned char x, unsigned char y) // 12bit pixel information FORMAT: RGB, four bits for each. MAX = FFF MIN = 000
{
	LCDCommand(0x2B);   // x start
	LCDData(x);
	LCDData(132);
    
	LCDCommand(0x2A);   // y start
	LCDData(y);
	LCDData(132);
    
	LCDCommand(0x2C);    // write
		
	LCDData((unsigned char)((color>>4)&0x00FF));
	LCDData((unsigned char)(((color&0x0F)<<4)|0x00));
}


void PCF8833::DrawCircle(int colour, uint8_t x0, uint8_t y0, uint8_t radius)  //Midpoint circle algorithm
{
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
  
    DrawPixel(colour,x0, y0 + radius);
    DrawPixel(colour,x0, y0 - radius);
    DrawPixel(colour,x0 + radius, y0);
    DrawPixel(colour,x0 - radius, y0);
  
    while(x < y)
    {
        if(f >= 0) 
        {
            y--;
          ddF_y += 2;
          f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;    
        DrawPixel(colour,x0 + x, y0 + y);
        DrawPixel(colour,x0 - x, y0 + y);
        DrawPixel(colour,x0 + x, y0 - y);
        DrawPixel(colour,x0 - x, y0 - y);
        DrawPixel(colour,x0 + y, y0 + x);
        DrawPixel(colour,x0 - y, y0 + x);
        DrawPixel(colour,x0 + y, y0 - x);
        DrawPixel(colour,x0 - y, y0 - x);
    }
}


// void  PCF8833::DrawWuLine(int colour, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) { // Wu's Anti-alias Line Algorithm
//     int Dx = x1 - x0; 
//     int Dy = y1 - y0;
//     int steep = (abs(Dy) >= abs(Dx));
//     if (steep) {

//         /*
// 		int a = x0;
//         int b = y0;
//         x0=b;
//         y0=a;

//         a = x1;
//         b = y1;
//         x1=b;
//         y1=a;
// 		*/
		
// 		x0 ^= x1;
// 		x1 ^= x0;
// 		x0 ^= x1;
		
// 		y0 ^= y1;
// 		y1 ^= y0;
// 		y0 ^= y1;

//         // recompute Dx, Dy after swap
//         Dx = x1 - x0;
//         Dy = y1 - y0;
//     }
//     int xstep = 1;
//     if (Dx < 0) {
//         xstep = -1;
//         Dx = -Dx;
//     }
//     int ystep = 1;
//     if (Dy < 0) {
//         ystep = -1;		
//         Dy = -Dy; 
//     }
//     int TwoDy = 2*Dy; 
//     int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
//     int E = TwoDy - Dx; //2*Dy - Dx
//     int y = y0;
//     int xDraw, yDraw;	
//     for (int x = x0; x != x1; x += xstep) {		
//         if (steep) {			
//             xDraw = y;
//             yDraw = x;
//         } else {			
//            xDraw = x;
//            yDraw = y;
//         }
//         // plot
//         DrawPixel(colour,xDraw, yDraw);
//         // next
//         if (E > 0) {
//             E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
//             y = y + ystep;
//         } else {
//             E += TwoDy; //E += 2*Dy;
//         }
//     }
// }


void  PCF8833::DrawBrLine(int colour, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) { // Bresenham Line Algorithm
    int Dx = x1 - x0; 
    int Dy = y1 - y0;
    int steep = (abs(Dy) >= abs(Dx));
    if (steep) {

        int a = x0;
        int b = y0;
        x0=b;
        y0=a;

        a = x1;
        b = y1;
        x1=b;
        y1=a;

        // recompute Dx, Dy after swap
        Dx = x1 - x0;
        Dy = y1 - y0;
    }
    int xstep = 1;
    if (Dx < 0) {
        xstep = -1;
        Dx = -Dx;
    }
    int ystep = 1;
    if (Dy < 0) {
        ystep = -1;		
        Dy = -Dy; 
    }
    int TwoDy = 2*Dy; 
    int TwoDyTwoDx = TwoDy - 2*Dx; // 2*Dy - 2*Dx
    int E = TwoDy - Dx; //2*Dy - Dx
    int y = y0;
    int xDraw, yDraw;	
    for (int x = x0; x != x1; x += xstep) {		
        if (steep) {			
            xDraw = y;
            yDraw = x;
        } else {			
            xDraw = x;
            yDraw = y;
        }
        // plot
        DrawPixel(colour,xDraw, yDraw);
        // next
        if (E > 0) {
            E += TwoDyTwoDx; //E += 2*Dy - 2*Dx;
            y = y + ystep;
        } else {
            E += TwoDy; //E += 2*Dy;
        }
    }
}

void PCF8833::FillRectangle(int colour, uint8_t x0, uint8_t y0, uint8_t width, uint8_t height)
{
    for (uint8_t i = y0+1; i < y0+height; i++) {
        DrawBrLine(colour, x0, i, x0+width, i);
    }

}

void PCF8833::DrawRectangle(int colour, uint8_t x0, uint8_t y0, uint8_t width, uint8_t height)
{
// Draw Top side
    DrawBrLine(colour,x0, y0, x0+width+1, y0);

// Draw Bottom side 
    DrawBrLine(colour,x0, y0+height, x0+width+1, y0+height);

// Now the sides
    for (uint8_t i = y0+1; i < y0+height; i++) {
        DrawPixel(colour,x0,i);
        DrawPixel(colour,x0+width,i);
    }
}

// void PCF8833::DrawBitmap(int xpos, int ypos) {
//     int count = 0;
//     for (int j = 0; j < sheight; j++) {
//         for (int i = 0; i < swidth; i++) {
//             DrawPixel(pgm_read_word_near(header_data + count),xpos+i,ypos+j);
//             count++;
//         }
//     }

// }


// PCF8833 LCDP = PCF8833();

