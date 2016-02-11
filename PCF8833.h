// This library has been created by Markos Kyritsis. The stuff is all copyleft, so go ahead and do whatever you like
// with it. Please contribute to the community and upload all changes to the arduino playground for everyone else to 
// use. Enjoy!

#ifndef	PCF8833_h
#define PCF8833_h
#include <avr/pgmspace.h>
#include <inttypes.h>


class PCF8833 {
	typedef unsigned char byte;



public:

	PCF8833(int8_t CS, int8_t SCLK, int8_t SDIN, int8_t RST);

	void LCDCommand(unsigned char data);
	void LCDData(unsigned char data);
	void LCDInit(void);
	void LCDClear(int color);
	void DrawPixel(int color, unsigned char x, unsigned char y);
	void DrawCircle(int colour, uint8_t x0, uint8_t y0, uint8_t radius);
	void DrawBrLine(int colour, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1); 
	void FillRectangle(int colour, uint8_t x0, uint8_t y0, uint8_t width, uint8_t height);
	void DrawRectangle(int colour, uint8_t x0, uint8_t y0, uint8_t width, uint8_t height);
	void DrawBitmap(int xpos, int ypos);



	/*
	static const byte CS = 9; 
	static const byte SCLK = 7;  
	static const byte SDATA = 5;  
	*/
	
	int8_t cs, sclk, sdin, rst;
	
	volatile uint8_t *csport, *sclkport, *sdinport;
    uint8_t cspinmask, sclkpinmask, sdinpinmask;
};
extern PCF8833 LCDP;    
#endif
