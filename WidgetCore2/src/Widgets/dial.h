/*
 * dial.h
 *
 *  Created on: Apr 18, 2012
 *      Author: ACM
 */

#ifndef DIAL_H_
#define DIAL_H_

#include<stdlib.h>
#include "../WidgetCore/widget.h"
#include "../WidgetCore/packet.h"
#include "../GraphicsEngine/Graphics.h"

Packet DIAL_runFunction(Widget* wthis, u8 funcN, Packet* pack);
Widget new_DialWidget(u32 circle_x, u32 circle_y);

typedef struct dial_widget {
	u32 angle;
	u16 radius;
} DialWidget;


Widget new_DialWidget(u32 circle_x, u32 circle_y){

	DialWidget* w = (DialWidget*) malloc(sizeof(DialWidget));

	Widget Dial ={
			.x = circle_x,
			.y = circle_y,
			.derive = (const void*)w,
			.runFunction = DIAL_runFunction
	};

	return Dial;
}


Packet DIAL_runFunction(Widget* base, u8 funcN, Packet* pack){

	DialWidget* derive = (DialWidget*)(base->derive);

	switch(funcN){

		case 1:{

			//stuff to draw the shell of the round meter
			drawCircle(base->x,base->y,50,BLACK,1);
			drawCircle(base->x,base->y,48,WHITE,1);
			float fi = 0;
			for(fi = 0; fi <= 6.2831853; fi += (3.14159269/12)){
				drawLine(base->x,base->y,(int)(base->x+48*cos(fi)),(int)(base->y+48*sin(fi)),BLACK);
			}
			drawDigit(base->x+52,base->y-4,0,BLACK);
			drawNumber(base->x-75,base->y-4,180,BLACK);
			drawNumber(base->x-8,base->y-59,90,BLACK);
			drawNumber(base->x-12,base->y+52,270,BLACK);
		}
		break;
		case 2:{

			//stuff to draw a round meter
			u8 degree = 0;
			u8 oldDegree = degree;

			degree = pack->bytes[0];

			if(oldDegree != degree)
			{
				double angle = ((double)degree) * 3.14159/180.0;
				//print("Starting to draw RoundMeter.");
				int x2 = (int)(43*cos(angle) + base->x);
				//int y2 = y + 45*( angle - (angle*angle*angle)/6.0 + (angle*angle*angle*angle*angle)/120.0 - (angle*angle*angle*angle*angle*angle*angle)/5040);
				int y2 = (int)(-43*sin(angle) + base->y);

				int deltaX = (int)(6*cos(angle + (3.14/2)));
				int deltaY = (int)(-6*sin(angle + (3.14/2)));

				drawCircle(base->x,base->y,44,WHITE,1);
				drawCircle(base->x,base->y,5,BLUE,1);

				drawTriangle(x2, y2, (base->x+deltaX),(base->y+deltaY),(base->x-deltaX),(base->y-deltaY),BLUE, 1);
				drawLine(base->x,base->y,x2,y2,RED);
			}
		}
		break;
	}
}

#endif /* DIAL_H_ */
