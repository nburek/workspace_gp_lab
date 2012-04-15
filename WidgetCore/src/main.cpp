#include"common.h"
#include"mc_intr_codes.h"
#include"widget.h"
#include"widget_table.h"
#include"progress_bar.h"
#include "Graphics.h"

#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"

WidgetTable WT;

int main(){

	int x = 0;
	int y = 0;

	//positions for the different components
	int circleX = 80, circleY = 65;
	int progressBarX = 160, progressBarY = 85;
	int lightsX = 160, lightsY = 35;

	u32 counter = 0;

	volatile int delayCounter = 0;


	//white out the entire screen to start
	for (x = 0; x<MAX_WIDTH; ++x)
		for (y = 0; y<MAX_HEIGHT; ++y)
			Xil_Out32(VGA_BASEADDR, ((y*384 + x)<<3)| (7));


	//stuff to draw the shell of the round meter
	drawCircle(circleX,circleY,50,BLACK,1);
	drawCircle(circleX,circleY,48,WHITE,1);
	for(double i = 0; i <= 6.2831853; i += (3.14159269/12)){
		drawLine(circleX,circleY,(int)(circleX+48*cos(i)),(int)(circleY+48*sin(i)),BLACK);
	}
	drawDigit(circleX+52,circleY-4,0,BLACK);
	drawNumber(circleX-75,circleY-4,180,BLACK);
	drawNumber(circleX-8,circleY-59,90,BLACK);
	drawNumber(circleX-12,circleY+52,270,BLACK);

	//stuff to draw a progress bar here
	drawCircle(progressBarX,progressBarY,15,BLACK,1);
	drawCircle(progressBarX+200,progressBarY,15,BLACK,1);
	drawRectangle(progressBarX,progressBarY-15,progressBarX+200,progressBarY+15,BLACK,1);
	drawCircle(progressBarX,progressBarY,13,GREEN,1);
	drawDigit(progressBarX-4,progressBarY+17,0,BLACK);
	drawNumber(progressBarX+188,progressBarY+17,100,BLACK);

	//Lights
	for (int i = 0; i<8; ++i)
		drawCircle(lightsX+30*i,lightsY, 10, BLACK, 1);

	//draw test digits 0-9
	for (int i = 0; i<10; ++i)
		drawDigit(264+i*12,207,i,BLACK);

	while (1==1)
	{
		//this is getting sent as a temporary handshake of sorts to request a byte
		XUartLite_SendByte(XPAR_UARTLITE_1_BASEADDR, 128);


		//stuff to draw a round meter
		u8 degree;
		u8 oldDegree = degree;
		degree = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
		if(oldDegree != degree)
		{
			double angle = ((double)degree) * 3.14159/180.0;
			//print("Starting to draw RoundMeter.");
			int x2 = (int)(43*cos(angle) + circleX);
			//int y2 = y + 45*( angle - (angle*angle*angle)/6.0 + (angle*angle*angle*angle*angle)/120.0 - (angle*angle*angle*angle*angle*angle*angle)/5040);
			int y2 = (int)(-43*sin(angle) + circleY);

			int deltaX = (int)(6*cos(angle + (3.14/2)));
			int deltaY = (int)(-6*sin(angle + (3.14/2)));

			drawCircle(circleX,circleY,44,WHITE,1);
			drawCircle(circleX,circleY,5,BLUE,1);

			drawTriangle(x2, y2, (circleX+deltaX),(circleY+deltaY),(circleX-deltaX),(circleY-deltaY),BLUE, 1);
			drawLine(circleX,circleY,x2,y2,RED);
		}

		//stuff to draw a progress bar here
		u8 temperature;
		u8 oldTemp = temperature;
		temperature = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
		if(oldTemp != temperature)
		{
			drawCircle(progressBarX+200,progressBarY,13,WHITE,1);
			drawRectangle(progressBarX,progressBarY-13,progressBarX+200,progressBarY+13,WHITE,1);
			drawRectangle(progressBarX,progressBarY-13,progressBarX+temperature,progressBarY+13,GREEN,1);
			if (temperature==200)
				drawCircle(progressBarX+200,progressBarY,13,GREEN,1);
		}


		//stuff to draw some lights here
		u8 buttons;
		buttons = XUartLite_RecvByte(XPAR_UARTLITE_1_BASEADDR);
		for (int i = 0; i<8; ++i)
		{
			if ((buttons & (0x01<<i)) > 0)
				drawCircle(lightsX+30*i,lightsY,8,RED,1);
			else
				drawCircle(lightsX+30*i,lightsY,8,WHITE,1);
		}



		drawNumber(4, 207,counter, CYAN);
		++counter;

		delayCounter = 0;
		while (delayCounter<999999)
			delayCounter++;
	}


/*

	u8 bytes[] = {'B', '8', '7', '6'};
	Packet p(4, bytes);

	s16 loc = WT.insert(new PBar(80));//proper way to add a widget
	WT[loc]->render();
*/
	return 0;

}
