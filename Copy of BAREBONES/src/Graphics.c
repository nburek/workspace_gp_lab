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


double sin(double angle)
{
	while (angle>=6.28318)
		angle-=6.28318;
	double xSquared = angle*angle;
	double x = angle;
	double ans = x;
	u8 posOrNeg = 0;
	u16 lcv = 0;
	double fact = 1;
	for (lcv = 3;lcv<26;lcv=lcv+2)
	{
		fact *= (lcv*(lcv-1));
		x *= ((xSquared)/(lcv*(lcv-1)));

		if (posOrNeg == 0)
			ans -= x;
		else
			ans += x;

		posOrNeg = 1-posOrNeg;
	}
	return (ans);
}

//double sin(int angle)
//{
//	double lTable[] = {0,0.17364817766693,0.342020143325669,0.5,0.642787609686539,0.766044443118978,0.866025403784439,0.939692620785908,0.984807753012208,1,0.984807753012208,0.939692620785908,0.866025403784439,0.766044443118978,0.642787609686539,0.5,0.342020143325669,0.17364817766693,0};
//
//	while (angle>=360)
//		angle-=360;
//
//	if (angle<180)
//		return lTable[(angle/10)];
//	else
//		return -1*lTable[(angle/10)];
//}

double cos(double angle)
{
	return sin(angle+3.14159/2);
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
		if (y1>y2)
			y1 ^= y2 ^= y1 ^= y2;

		int i;
		for (i = y1; i<=y2; ++i)
			drawLine(x1,i,x2,i,color);
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

void drawDigit(int x, int y, u8 digit, u8 color)
{
	int xi = 0, yi = 0;
	for (yi = 0; yi<8; ++yi)
		for (xi = 0; xi<8; ++xi)
			if ((digits[digit][yi] & (128 >> xi))>0)
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
