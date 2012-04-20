/*
 * Graphics.c
 *
 *  Created on: Apr 6, 2012
 *      Author: nb418308
 *
 *  Edited on: Apr 13. 2012
 *  	Editor: jr454918
 */

#include "Graphics.h"


void putPixel(int x, int y, u8 color)
{
	if (x < MAX_WIDTH && x>=0 && y < MAX_HEIGHT && y>=0)
		Xil_Out32(VGA_BASEADDR, ((y*MAX_WIDTH + x)<<3)| color);
}

void drawLine(int x0, int y0, int x1, int y1, u8 color)
{
    //optimized bresenham algorithm
    int dx = x1 >= x0 ? (x1 - x0): (x0 - x1);
    int dy = y1 >= y0 ? (y1 - y0): (y0 - y1);

    int sx = (x0 < x1) ? 1: -1;
    int sy = (y0 < y1) ? 1: -1;

    int e = (dx - dy);

    while( (x0 != x1) || (y0 != y1) )
    {
 	   putPixel(x0, y0, color);

	   int e2 = 2*e;

	   if(e2 > -dy)
	   {
		  e      -= dy;
		  x0     += sx;
	   }

	   if(e2 < dx)
	   {
		  e      += dx;
		  y0     += sy;
	   }
    }

    putPixel(x0, y0, color);
}

void drawRectangle(int x1, int y1, int x2, int y2, u8 color, u8 filled)
{
	if (filled == 0)
	{
		drawLine(x1,y1,x2,y1,color);
		drawLine(x1,y1,x1,y2,color);
		drawLine(x2,y2,x1,y2,color);
		drawLine(x2,y2,x2,y1,color);
	}
	else
	{
		if (y1>y2)	y1 ^= y2 ^= y1 ^= y2;
		if (x1>x2)	x1 ^= x2 ^= x1 ^= x2;

		int i, j;
		for (i = y1; i<=y2; ++i){
			for (j = x1; j<=x2; ++j){
			    putPixel(j, i, color);
			}
		}
	}
}


void drawCircle(int x0, int y0, int radius, u8 color, u8 filled)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	if (filled==0)
	{
		putPixel(x0, y0 + radius,color);
		putPixel(x0, y0 - radius,color);
		putPixel(x0 + radius, y0,color);
		putPixel(x0 - radius, y0,color);
	}
	else
	{
		drawLine(x0, y0 + radius,x0, y0 - radius,color);
		drawLine(x0 + radius, y0 ,x0 - radius, y0,color);
	}



	while(x < y)
	{
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if(f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (filled==0)
		{
			putPixel(x0 + x, y0 + y,color);
			putPixel(x0 - x, y0 + y,color);

			putPixel(x0 + x, y0 - y,color);
			putPixel(x0 - x, y0 - y,color);

			putPixel(x0 + y, y0 + x,color);
			putPixel(x0 - y, y0 + x,color);

			putPixel(x0 + y, y0 - x,color);
			putPixel(x0 - y, y0 - x,color);
		}
		else
		{
			drawLine(x0 + x, y0 + y,x0 - x, y0 + y,color);
			drawLine(x0 + y, y0 - x,x0 - y, y0 - x,color);
			drawLine(x0 + y, y0 + x,x0 - y, y0 + x,color);
			drawLine(x0 + x, y0 - y,x0 - x, y0 - y,color);

		}

	}
}

void fanFromPointToLine(int x1, int y1, int x2, int y2, int vX, int vY, u8 color)
{

	int n, deltax, deltay, sgndeltax, sgndeltay, deltaxabs, deltayabs, x, y, drawx, drawy;

	deltax = x2 - x1;
	deltay = y2 - y1;
	deltaxabs = (deltax<0)?(deltax*-1):deltax;//abs(deltax);
	deltayabs = (deltay<0)?(deltay*-1):deltay;//abs(deltay);
	sgndeltax = (deltax>0)?1:(deltax==0)?0:-1;//sgn(deltax);
	sgndeltay = (deltay>0)?1:(deltay==0)?0:-1;//sgn(deltay);
	x = deltayabs >> 1;
	y = deltaxabs >> 1;
	drawx = x1;
	drawy = y1;

	drawLine(drawx,drawy,vX,vY,color);

	if(deltaxabs >= deltayabs)
	{
		for(n = 0; n < deltaxabs; n++)
		{
			y += deltayabs;
			if(y >= deltaxabs)
			{
				y -= deltaxabs;
				drawy += sgndeltay;
			}
			drawx += sgndeltax;
			drawLine(drawx,drawy,vX,vY,color);
		}
	}
	else
	{
		for(n = 0; n < deltayabs; n++)
		{
			x += deltaxabs;
			if(x >= deltayabs)
			{
				x -= deltayabs;
				drawx += sgndeltax;
			}
			drawy += sgndeltay;
			drawLine(drawx,drawy,vX,vY,color);
		}
	}
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, u8 color, u8 filled)
{
	if (filled == 0)
	{
		drawLine(x1,y1,x2,y2,color);
		drawLine(x3,y3,x2,y2,color);
		drawLine(x1,y1,x3,y3,color);
	}
	else
	{
		fanFromPointToLine(x1,y1,x2,y2,x3,y3,color);
		fanFromPointToLine(x3,y3,x1,y1,x2,y2,color);
		fanFromPointToLine(x2,y2,x3,y3,x1,y1,color);
	}
}



u8 digits[10][8] = {
		{0x38, 0x4C, 0xC6, 0xC6, 0xC6, 0x64, 0x38, 0x00},
		//{0b00111000,0b01001100,0b11000110,0b11000110,0b11000110,0b01100100,0b00111000,0b00000000},
		{0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00},
		//{0b00110000,0b01110000,0b00110000,0b00110000,0b00110000,0b00110000,0b11111100,0b00000000},
		{0x7C, 0xC6, 0x0E, 0x3C, 0x78, 0xE0, 0xFE, 0x00},
		//{0b01111100,0b11000110,0b00001110,0b00111100,0b01111000,0b11100000,0b11111110,0b00000000},
		{0x7E, 0x0C, 0x18, 0x3C, 0x06, 0xC6, 0x7C, 0x00},
		//{0b01111110,0b00001100,0b00011000,0b00111100,0b00000110,0b11000110,0b01111100,0b00000000},
		{0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x00},
		//{0b00011100,0b00111100,0b01101100,0b11001100,0b11111110,0b00001100,0b00001100,0b00000000},
		{0xFC, 0xC0, 0xFC, 0x06, 0x06, 0xC6, 0x7C, 0x00},
		//{0b11111100,0b11000000,0b11111100,0b00000110,0b00000110,0b11000110,0b01111100,0b00000000},
		{0x3C, 0x60, 0xC0, 0xFC, 0xC6, 0xC6, 0x7C, 0x00},
		//{0b00111100,0b01100000,0b11000000,0b11111100,0b11000110,0b11000110,0b01111100,0b00000000},
		{0xFE, 0xC6, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00},
		//{0b11111110,0b11000110,0b00001100,0b00011000,0b00110000,0b00110000,0b00110000,0b00000000},
		{0x78, 0xC4, 0xE4, 0x78, 0x9E, 0x86, 0x7C, 0x00},
		//{0b01111000,0b11000100,0b11100100,0b01111000,0b10011110,0b10000110,0b01111100,0b00000000},
		{0x7C, 0xC6, 0xC6, 0x7E, 0x06, 0x06, 0x78, 0x00}};
		//{0b01111100,0b11000110,0b11000110,0b01111110,0b00000110,0b00001100,0b01111000,0b00000000}};

u8 letters[26][8] = {

		{0x1c, 0x36, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x0},
		{0x7e, 0x63, 0x63, 0x7e, 0x63, 0x63, 0x7e, 0x0},
		{0x1e, 0x33, 0x60, 0x60, 0x60, 0x33, 0x1e, 0x0},
		{0x7c, 0x66, 0x63, 0x63, 0x63, 0x66, 0x7c, 0x0},
		{0x3f, 0x30, 0x30, 0x3e, 0x30, 0x30, 0x3f, 0x0},
		{0x7f, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x60, 0x0},
		{0x1f, 0x30, 0x60, 0x67, 0x63, 0x33, 0x1f, 0x0},
		{0x63, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x63, 0x0},
		{0x3f, 0xc,	 0xc,  0xc,  0xc,  0xc,  0x3f, 0x0},
		{0x3,  0x3,  0x3,  0x3,  0x3,  0x63, 0x3e, 0x0},
		{0x63, 0x66, 0x6c, 0x78, 0x7c, 0x6e, 0x67, 0x0},
		{0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3f, 0x0},
		{0x63, 0x77, 0x7f, 0x7f, 0x6b, 0x63, 0x63, 0x0},
		{0x63, 0x73, 0x7b, 0x7f, 0x6f, 0x67, 0x63, 0x0},
		{0x3e, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x0},
		{0x7e, 0x63, 0x63, 0x63, 0x7e, 0x60, 0x60, 0x0},
		{0x3e, 0x63, 0x63, 0x63, 0x6f, 0x66, 0x3d, 0x0},
		{0x7e, 0x63, 0x63, 0x67, 0x7c, 0x6e, 0x67, 0x0},
		{0x3c, 0x66, 0x60, 0x3e, 0x3,  0x63, 0x3e, 0x0},
		{0x3f, 0xc,  0xc,  0xc,  0xc,  0xc,  0xc,  0x0},
		{0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x0},
		{0x63, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x8,  0x0},
		{0x63, 0x63, 0x6b, 0x7f, 0x7f, 0x36, 0x22, 0x0},
		{0x63, 0x77, 0x3e, 0x1c, 0x3e, 0x77, 0x63, 0x0},
		{0x33, 0x33, 0x12, 0x1e, 0xc,  0xc,  0xc,  0x0},
		{0x7f, 0x7,  0xe,  0x1c, 0x38, 0x70, 0x7f, 0x0}
};

void drawLetter(int x, int y, char letter, u8 color)
{
	drawCharacter(x, y, (letter | 0x20) - 97, color, letters);
}

void drawDigit(int x, int y, u8 digit, u8 color)
{
	drawCharacter(x, y, digit, color, digits);
}

void drawCharacter(int x, int y, u8 digit, u8 color, u8 char_map[][8])
{
	int xi = 0, yi = 0;
	for (yi = 0; yi<8; ++yi)
		for (xi = 0; xi<8; ++xi)
			if ((char_map[digit][yi] & (128 >> xi))>0)
				putPixel(x+xi,y+yi,color);
			else
				putPixel(x+xi,y+yi,WHITE);
}

void drawNumber(int x, int y, u32 digit, u8 color)
{
	int magnitude = 1;

	//determine the magnitude of the number
	while ((digit/(magnitude*10))>0)
		magnitude*=10;

	//draw each digit in the number from left to right in terms of decreasing order of magnitude
	while (magnitude>0)
	{
		drawDigit(x,y,(digit/magnitude),color);
		digit = digit%magnitude;
		magnitude /= 10;
		x+=8;
	}
}

