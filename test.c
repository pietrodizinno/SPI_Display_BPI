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
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "PCD8544.h"

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;

// lcd contrast
int contrast = 50;

int main (void)
{
  // print infos
  printf("Raspberry Pi PCD8544 test\n");
  printf("========================================\n");

  printf("CLK on Port %i \n", _sclk);
  printf("DIN on Port %i \n", _din);
  printf("DC on Port %i \n", _dc);
  printf("CS on Port %i \n", _cs);
  printf("RST on Port %i \n", _rst);
  printf("========================================\n");

  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }

  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDclear();

  // turn all the pixels on (a handy test)
  printf("Test: All pixels on.\n");
  LCDcommand(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYALLON);
  delay(1000);
  // back to normal
  printf("Test: All pixels off.\n");
  LCDcommand(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
  LCDclear();

  // display logo
  printf("Test: Display logo.\n");
  LCDshowLogo();
  delay(2000);
  LCDclear();

  // draw a single pixel
  printf("Test: Display single pixel.\n");
  LCDsetPixel(10, 10, BLACK);
  LCDdisplay();
  delay(2000);
  LCDclear();

  // draw many lines
  printf("Test: Draw many lines.\n");
  int i;
  for (i=0; i<84; i+=4) {
    LCDdrawline(0, 0, i, 47, BLACK);
  }
  for (i=0; i<48; i+=4) {
    LCDdrawline(0, 0, 83, i, BLACK);
  }
  LCDdisplay();
  delay(2000);
  LCDclear();

  // draw rectangles
  printf("Test: Draw rectangles.\n");
  for (i=0; i<48; i+=2) {
    LCDdrawrect(i, i, 96-i, 48-i, BLACK);
  }
  LCDdisplay();
  delay(2000);
  LCDclear();

  // draw multiple rectangles
  printf("Test: Draw multiple rectangles.\n");
  for (i=0; i<48; i++) {
    // alternate colors for moire effect
    LCDfillrect(i, i, 84-i, 48-i, i%2);
  }
  LCDdisplay();
  delay(2000);
  LCDclear();

  // draw mulitple circles
  printf("Test: Draw multiple circles.\n");
  for (i=0; i<48; i+=2) {
    LCDdrawcircle(41, 23, i, BLACK);
  }
  LCDdisplay();
  delay(2000);
  LCDclear();

  // draw the first ~120 characters in the font
  printf("Test: Draw the first ~120 chars.\n");
  for (i=0; i < 64; i++) {
    LCDdrawchar((i % 14) * 6, (i/14) * 8, i);
  }
  LCDdisplay();
  delay(2000);
  for (i=0; i < 64; i++) {
    LCDdrawchar((i % 14) * 6, (i/14) * 8, i + 64);
  }
  LCDdisplay();
  delay(2000);
  LCDclear();

  return 0;
}
