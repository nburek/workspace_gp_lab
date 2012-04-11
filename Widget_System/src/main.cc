/*
 * Empty C++ Application
 */


#include <stdio.h>
#include "Graphics.h"
//#include "RoundMeter.h"
#include "xbasic_types.h"
//#include "math.h"
//#include "mb_interface.h" //Contains the functions for registering the
						  //interrupt controller with the microblaze MP



int main()
{
	int x = 0;
	int y = 215;
	u8 color = 1;
	volatile int delayCounter = 0;

	for (x = 0; x<MAX_WIDTH; ++x)
		for (y = 0; y<MAX_HEIGHT; ++y)
			Xil_Out32(VGA_BASEADDR, ((y*384 + x)<<3)| (7));
	print("---Entering main---\n\r");
	//Widget *w = new RoundMeter(100,100);
	//w->draw();
	//RoundMeter rm(100,100,1.0);
	//rm.draw();
	x = 100;
	y = 100;
	double angle = 1.0;
	drawCircle(x,y,50,BLACK,1);
	drawCircle(x,y,48,WHITE,1);
	drawCircle(x,y,5,BLUE,1);
	int x2 = 45;//*cos(angle) + x;
	//int y2 = y + 45*( angle - (angle*angle*angle)/6.0 + (angle*angle*angle*angle*angle)/120.0 - (angle*angle*angle*angle*angle*angle*angle)/5040);
	int y2 = 45;//*sin(angle) + y;
	drawLine(x,y,x2,y2,BLACK);

	print("---Leaving main---\n\r");

	return 0;
}

