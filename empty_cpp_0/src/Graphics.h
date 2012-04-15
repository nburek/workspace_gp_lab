/*
 * Graphics.h
 *
 *  Created on: Apr 6, 2012
 *      Author: nb418308
 */


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <stdio.h>
#include "xparameters.h"
#include "xbasic_types.h"
#include "xil_io.h"	//Contains the Xil_Out32 and Xil_In32 functions

#define VGA_BASEADDR XPAR_VGA_0_BASEADDR

#define MAX_WIDTH 384
#define MAX_HEIGHT 216

//Colors
#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define PURPLE 0x05
#define YELLOW 0x06
#define WHITE 0x07


void putPixel(int x, int y, u8 color);
void drawLine(int x1, int y1, int x2, int y2, u8 color);
void drawCircle(int x0, int y0, int radius, u8 color, u8 filled);
void fanFromPointToLine(int x1, int y1, int x2, int y2, int vX, int vY, u8 color);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, u8 color, u8 filled);
double sin(double angle);
double cos(double angle);
uint randNum();

#endif /* GRAPHICS_H_
