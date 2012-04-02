/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */


#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
#include "xparameters.h"
#include "xbasic_types.h"
//#include "xgpio.h"
//#include "gpio_header.h"
#include "uartlite_header.h"
#include "xil_io.h"	//Contains the Xil_Out32 and Xil_In32 functions
#include "mb_interface.h" //Contains the functions for registering the
						  //interrupt controller with the microblaze MP
#include <math.h>

#define SS_BASEADDR XPAR_DIGILENT_SEVSEG_DISP_BASEADDR
#define VGA_BASEADDR XPAR_VGA_0_BASEADDR

/*
 * The following constants are used to mask the contents of the seven-
 * segment output register
 */
#define mskCathodes 0x000000FF
#define mskAnodes 0x00000F00
#define bnAnodes 8

volatile u32 ssBuf;
volatile int ssVal;

#define MAX_WIDTH 384
#define MAX_HEIGHT 216

/*
 * This array maps a number from 0-9 to the appropriate cathode values
 * necessary to display that number on a seven segment display
 */
static const u32 rgfsNumMap[10] = {0x000000C0, 0x000000F9, 0x000000A4,
								0x000000B0, 0x00000099, 0x00000092,
								0x00000082, 0x000000F8, 0x00000080,
								0x00000090};

void putPixel(int x, int y, u8 color);

void drawLine(int x1, int y1, int x2, int y2, u8 color);
void drawCircle(int x0, int y0, int radius, u8 color);
void fillCircle(int x0, int y0, int radius, u8 color);
void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, u8 color);
void fanFromPointToLine(int x1, int y1, int x2, int y2, int vX, int vY, u8 color);
uint randNum();

int main() 
{



   print("---Entering main---\n\r");

   {
	    ssVal = 2;
	    ssBuf = rgfsNumMap[0];
	    Xil_Out32(SS_BASEADDR, ssBuf);
	    ssBuf = (ssBuf & mskAnodes) | rgfsNumMap[ssVal];
	    Xil_Out32(SS_BASEADDR, ssBuf);

	    int x = 0;
	    int y = 215;
	    u8 color = 1;
	    volatile int delayCounter = 0;

	    for (x = 0; x<MAX_WIDTH; ++x)
	    	for (y = 0; y<MAX_HEIGHT; ++y)
	    		Xil_Out32(VGA_BASEADDR, ((y*384 + x)<<3)| (7));
	    //drawLine(10,10,300,60,0x02);
	    //drawLine(350,160,10,10,0x02);
	    while (1==1)
	    {
	    	int shape = randNum()%4;

	    	if (shape == 0)
	    		drawLine(randNum()%MAX_WIDTH,randNum()%MAX_HEIGHT,randNum()%MAX_WIDTH,randNum()%MAX_HEIGHT,randNum()%8);
	    	else if (shape == 1)
	    		drawCircle(randNum()%MAX_WIDTH,randNum()%MAX_HEIGHT,randNum()%50,randNum()%8);
	    	else if (shape == 2)
	    		fillCircle(randNum()%MAX_WIDTH,randNum()%MAX_HEIGHT,randNum()%50,randNum()%8);
	    	else if (shape == 3)
	    		fillTriangle(randNum()%MAX_WIDTH,randNum()%MAX_HEIGHT,randNum()%MAX_WIDTH,randNum()%MAX_HEIGHT,randNum()%MAX_WIDTH,randNum()%MAX_HEIGHT,randNum()%8);
	    	delayCounter = 0;
		    //while (delayCounter < 999999)
		    	//delayCounter++;
	    }

	    /*while (1==1)
	    {
	    	for (color = 0; color<8; ++color)
	    	{
	    		for (x = 0; x<MAX_WIDTH; ++x)
	    			for (y = 0; y<MAX_HEIGHT; ++y)
	    				if ((x-(MAX_WIDTH/2))*(x-(MAX_WIDTH/2)) + (y-(MAX_HEIGHT/2))*(y-(MAX_HEIGHT/2)) < 10000)
	    					Xil_Out32(VGA_BASEADDR, ((y*384 + x)<<3)| (color^0x7));
	    				else
	    					Xil_Out32(VGA_BASEADDR, ((y*384 + x)<<3)| color);
		    	delayCounter = 0;
		    	while (delayCounter < 9999999)
		    		delayCounter++;
	    	}
	    }*/
	    //Xil_Out32(VGA_BASEADDR, (383<<3)|0x00000002);
   }
/*
   {
      u32 status;
      
      print("\r\nRunning GpioInputExample() for DIP_Switches_8Bits...\r\n");

      u32 DataRead;
      
      status = GpioInputExample(XPAR_DIP_SWITCHES_8BITS_DEVICE_ID, &DataRead);
      
      if (status == 0) {
         xil_printf("GpioInputExample PASSED. Read data:0x%X\r\n", DataRead);
      }
      else {
         print("GpioInputExample FAILED.\r\n");
      }
   }
   

   {
      u32 status;
      
      print("\r\nRunning GpioOutputExample() for LEDs_8Bits...\r\n");

      status = GpioOutputExample(XPAR_LEDS_8BITS_DEVICE_ID,8);
      
      if (status == 0) {
         print("GpioOutputExample PASSED.\r\n");
      }
      else {
         print("GpioOutputExample FAILED.\r\n");
      }
   }
   

   {
      u32 status;
      
      print("\r\nRunning GpioInputExample() for Push_Buttons_4Bits...\r\n");

      u32 DataRead;
      
      status = GpioInputExample(XPAR_PUSH_BUTTONS_4BITS_DEVICE_ID, &DataRead);
      
      if (status == 0) {
         xil_printf("GpioInputExample PASSED. Read data:0x%X\r\n", DataRead);
      }
      else {
         print("GpioInputExample FAILED.\r\n");
      }
   }
   
   /*
    * Peripheral SelfTest will not be run for RS232_Uart_1
    * because it has been selected as the STDOUT device
    */

   
/*
   {
      int status;
      
      print("\r\nRunning UartLiteSelfTestExample() for debug_module...\r\n");
      status = UartLiteSelfTestExample(XPAR_DEBUG_MODULE_DEVICE_ID);
      if (status == 0) {
         print("UartLiteSelfTestExample PASSED\r\n");
      }
      else {
         print("UartLiteSelfTestExample FAILED\r\n");
      }
   }*/

   print("---Exiting main---\n\r");


   return 0;
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

void drawCircle(int x0, int y0, int radius, u8 color)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	putPixel(x0, y0 + radius,color);
	putPixel(x0, y0 - radius,color);
	putPixel(x0 + radius, y0,color);
	putPixel(x0 - radius, y0,color);

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
		putPixel(x0 + x, y0 + y,color);
		putPixel(x0 - x, y0 + y,color);
		putPixel(x0 + x, y0 - y,color);
		putPixel(x0 - x, y0 - y,color);
		putPixel(x0 + y, y0 + x,color);
		putPixel(x0 - y, y0 + x,color);
		putPixel(x0 + y, y0 - x,color);
		putPixel(x0 - y, y0 - x,color);
	}
}

void fillCircle(int x0, int y0, int radius, u8 color)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	//putPixel(x0, y0 + radius,color);
	//putPixel(x0, y0 - radius,color);
	drawLine(x0, y0 + radius,x0, y0 - radius,color);

	//putPixel(x0 + radius, y0,color);
	//putPixel(x0 - radius, y0,color);
	drawLine(x0 + radius, y0 ,x0 - radius, y0,color);


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
		//putPixel(x0 + x, y0 + y,color);
		//putPixel(x0 - x, y0 + y,color);
		drawLine(x0 + x, y0 + y,x0 - x, y0 + y,color);

		//putPixel(x0 + x, y0 - y,color);
		//putPixel(x0 - x, y0 - y,color);
		drawLine(x0 + x, y0 - y,x0 - x, y0 - y,color);

		//putPixel(x0 + y, y0 + x,color);
		//putPixel(x0 - y, y0 + x,color);
		drawLine(x0 + y, y0 + x,x0 - y, y0 + x,color);

		//putPixel(x0 + y, y0 - x,color);
		//putPixel(x0 - y, y0 - x,color);
		drawLine(x0 + y, y0 - x,x0 - y, y0 - x,color);

	}
}

void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, u8 color)
{
	fanFromPointToLine(x1,y1,x2,y2,x3,y3,color);
	fanFromPointToLine(x3,y3,x1,y1,x2,y2,color);
	fanFromPointToLine(x2,y2,x3,y3,x1,y1,color);

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



uint m_w = 25;    /* must not be zero */
uint m_z = 683;    /* must not be zero */

uint randNum()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}


