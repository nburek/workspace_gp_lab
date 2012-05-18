/*
 * graph.h
 *
 *  Created on: May 5, 2012
 *      Author: ACM
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include<stdlib.h>
#include "../WidgetCore/widget.h"
#include "../WidgetCore/packet.h"
#include "../WidgetCore/util.h"
#include "../GraphicsEngine/Graphics.h"

Packet Graph_runFunction(Widget* wthis, u8 funcN, Packet* pack);
Widget new_GraphWidget(u32 x, u32 y, u16 widthi, u16 heighti);

void graphBackground(Widget*);

typedef struct graph_widget {
	u16 xg[20];
	u16 yg[20];
	u8 max_xi;//index of max
	u8 max_yi;//index of max
	u8 pts;
	u16 width;
	u16 height;
} GraphWidget;


Widget new_GraphWidget(u32 xi, u32 yi, u16 widthi, u16 heighti){

	GraphWidget* w = (GraphWidget*) malloc(sizeof(GraphWidget));

	Widget Graph ={
			.x = xi,
			.y = yi,
			.derive = (const void*)w,
			.destroy = default_destroy,
			.runFunction = Graph_runFunction
	};

	w->width = widthi;
	w->height = heighti;
	w->pts = 0;
	w->max_xi = 0;
	w->max_yi = 0;

	graphBackground(&Graph);

	return Graph;
}

//private helper function
void graphBackground(Widget* base){

	GraphWidget* derive = (GraphWidget*)(base->derive);

	drawRectangle(base->x, base->y - derive->height, base->x + derive->width, base->y, WHITE, 1);
	drawLine(base->x, base->y - derive->height, base->x, base->y, BLACK);
	drawLine(base->x, base->y, base->x + derive->width, base->y, BLACK);
	drawDigit(base->x - 10, base->y - 5, 0, BLACK);
}
void graph_drawLines(Widget* base){

	GraphWidget* derive = (GraphWidget*)(base->derive);

	u8 xs = derive->width/derive->xg[derive->max_xi];
	u8 ys = derive->height/derive->yg[derive->max_yi];

	int i;
	for(i=0; i<derive->pts-1; ++i){
		drawLine(xs*derive->xg[i]+base->x, -ys*derive->yg[i]+base->y, xs*derive->xg[i+1]+base->x, -ys*derive->yg[i+1]+base->y, RED);
	}

	drawNumber(base->x + derive->width + 5, base->y - 5, derive->xg[derive->max_xi], BLACK);
	drawNumber(base->x - 10, base->y - derive->height - 5, derive->yg[derive->max_yi], BLACK);
}

Packet Graph_runFunction(Widget* base, u8 funcN, Packet* pack){

	GraphWidget* derive = (GraphWidget*)(base->derive);

	Packet op;
	op.bytes[0] = 0;

	switch(funcN){

		case 0:{
			break;
		}
		case 1:{
			graphBackground(base);
			break;
		}
		case 2:{
			graph_drawLines(base);
			break;
		}
		case 3:{
			u16 x = weldU16(pack->bytes[0], pack->bytes[1]);
			u16 y = weldU16(pack->bytes[2], pack->bytes[3]);

			derive->xg[derive->pts] = x;
			derive->yg[derive->pts] = y;

			if(x > derive->xg[derive->max_xi])	derive->max_xi = derive->pts;
			if(y > derive->yg[derive->max_yi])	derive->max_yi = derive->pts;

			(derive->pts)++;
			break;
		}

	}

	return op;
}

#endif /* GRAPH_H_ */
