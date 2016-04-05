/*
=================================================================================
 Name        : PCD8544.c
 Version     : 0.1

 Copyright (C) 2016 Volkan UGUR NeuralKey

================================================================================
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
 */
#include <stdint.h>

#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define __DISPLAY_ON           0xaf   //  Display on
#define __DISPLAY_OFF          0xae   //  Display off
#define __SET_ADC              0xa1   //  Reverse disrect (SEG131-SEG0)
#define __CLEAR_ADC            0xa0   //  Normal disrect (SEG0-SEG131)
#define __REVERSE_DISPLAY_ON   0xa7   //  Reverse display : 0 illuminated
#define __REVERSE_DISPLAY_OFF  0xa6   //  Normal display : 1 illuminated
#define __ENTIRE_DISPLAY_ON    0xa5   //  Entire dislay   Force whole LCD point
#define __ENTIRE_DISPLAY_OFF   0xa4   //  Normal display
#define __SET_BIAS             0xa3   //  bias 1   1/7 bais
#define __CLEAR_BIAS           0xa2   //  bias 0   1/9 bais
#define __RESET                0xe2 	//   system reset
#define __SET_SHL              0xc8   // SHL 1,COM63-COM0
#define __CLEAR_SHL            0xc0   // SHL 0,COM0-COM63

#define Start_column	0x00
#define Start_page		0x00
#define	StartLine_set	0x00

#define swap(a, b) { uint8_t t = a; a = b; b = t; }

 // calibrate clock constants
#define CLKCONST_1  8000
#define CLKCONST_2  400  // 400 is a good tested value for Raspberry Pi

// keywords
#define LSBFIRST  0
#define MSBFIRST  1

 void LCDInit(uint8_t SCLK, uint8_t DIN, uint8_t DC, uint8_t CS, uint8_t RST, uint8_t contrast);
 void LCDcommand(uint8_t c);
 void LCDdata(uint8_t c);
 void LCDsetContrast(uint8_t val);
 void LCDclear();
 void LCDdisplay();
 void LCDsetPixel(uint8_t x, uint8_t y, uint8_t color);
 uint8_t LCDgetPixel(uint8_t x, uint8_t y);
 void LCDfillcircle(uint8_t x0, uint8_t y0, uint8_t r,uint8_t color);
 void LCDdrawcircle(uint8_t x0, uint8_t y0, uint8_t r,uint8_t color);
 void LCDdrawrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint8_t color);
 void LCDfillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,uint8_t color);
 void LCDdrawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
 void LCDsetCursor(uint8_t x, uint8_t y);
 void LCDsetTextSize(uint8_t s);
 void LCDsetTextColor(uint8_t c);
 void LCDwrite(uint8_t c);
 void LCDshowLogo();
 void LCDdrawchar(uint8_t x, uint8_t line, char c);
 void LCDdrawstring(uint8_t x, uint8_t line, char *c);
 void LCDdrawstring_P(uint8_t x, uint8_t line, const char *c);
 void LCDdrawbitmap(uint8_t x, uint8_t y,  const uint8_t *bitmap, uint8_t w, uint8_t h,  uint8_t color);
 void LCDspiwrite(uint8_t c);
 void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
 void _delay_ms(uint32_t t);
