/*
 * Graphics.c
 *
 *  Created on: Apr 6, 2012
 *      Author: nb418308
 */

#include "Graphics.h"

double sin(int angle)
{
	double lTable[] = {0,0.17364817766693,0.342020143325669,0.5,0.642787609686539,0.766044443118978,0.866025403784439,0.939692620785908,0.984807753012208,1,0.984807753012208,0.939692620785908,0.866025403784439,0.766044443118978,0.642787609686539,0.5,0.342020143325669,0.17364817766693,0};

	while (angle>=360)
		angle-=360;

	if (angle<180)
		return lTable[(angle/10)];
	else
		return -1*lTable[(angle/10)];
}

double cos(int angle)
{
	return sin(angle+90);
}

void putPixel(int x, int y, u8 color)
{
	if (x < MAX_WIDTH && x>=0 && y < MAX_HEIGHT && y>=0)
		Xil_Out32(VGA_BASEADDR, ((y*MAX_WIDTH + x)<<3)| color);
}

void drawLine(int x1, int y1, int x2, int y2, u8 color)
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

	putPixel(drawx, drawy, color);

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
			putPixel(drawx, drawy,color);
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
			putPixel(drawx, drawy,color);
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





uint m_w = 25;    /* must not be zero */
uint m_z = 683;    /* must not be zero */

uint randNum()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}


u8 digits[10][8] = {
		{0b00111000,0b01001100,0b11000110,0b11000110,0b11000110,0b01100100,0b00111000,0b00000000},
		{0b00110000,0b01110000,0b00110000,0b00110000,0b00110000,0b00110000,0b11111100,0b00000000},
		{0b01111100,0b11000110,0b00001110,0b00111100,0b01111000,0b11100000,0b11111110,0b00000000},
		{0b01111110,0b00001100,0b00011000,0b00111100,0b00000110,0b11000110,0b01111100,0b00000000},
		{0b00011100,0b00111100,0b01101100,0b11001100,0b11111110,0b00001100,0b00001100,0b00000000},
		{0b11111100,0b11000000,0b11111100,0b00000110,0b00000110,0b11000110,0b01111100,0b00000000},
		{0b00111100,0b01100000,0b11000000,0b11111100,0b11000110,0b11000110,0b01111100,0b00000000},
		{0b11111110,0b11000110,0b00001100,0b00011000,0b00110000,0b00110000,0b00110000,0b00000000},
		{0b01111000,0b11000100,0b11100100,0b01111000,0b10011110,0b10000110,0b01111100,0b00000000},
		{0b01111100,0b11000110,0b11000110,0b01111110,0b00000110,0b00001100,0b01111000,0b00000000}};

void drawDigit(int x, int y, u8 digit, u8 color)
{
	int xi = 0, yi = 0;
	for (xi = 0; xi<8; ++xi)
		for (yi = 0; yi<8; ++yi)
			if (digits[digit][xi+yi*8]==1)
				putPixel(x+xi,y+yi,color);
}

