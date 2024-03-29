/*
 * RoundMeter.cpp
 *
 *  Created on: Apr 6, 2012
 *      Author: nb418308
 */

#include "RoundMeter.h"

RoundMeter::RoundMeter(int x, int y, double angle) : Widget(x,y)
{
	this->angle = angle;
	//print("In RoundMeter Constructor.");
}

void RoundMeter::draw()
{
	//print("Starting to draw RoundMeter.");
	drawCircle(this->x,this->y,50,BLACK,1);
	drawCircle(this->x,this->y,48,WHITE,1);
	drawCircle(this->x,this->y,5,BLUE,1);
	int x2 = (int)(45*cos(angle) + this->x);
	//int y2 = y + 45*( angle - (angle*angle*angle)/6.0 + (angle*angle*angle*angle*angle)/120.0 - (angle*angle*angle*angle*angle*angle*angle)/5040);
	int y2 = 1;//45*sin(angle) + this->y;
	drawLine(this->x,this->y,x2,y2,BLACK);
	//drawTriangle();
	//print("Done drawing RoundMeter.");
}
