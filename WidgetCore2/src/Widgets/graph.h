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

	graphBackground(&Graph);

	return Graph;
}

//private helper function
void graphBackground(Widget* base){

	//GraphWidget* derive = (GraphWidget*)(base->derive);

	drawRectangle(100, 30, 350, 160, WHITE, 1);
	drawLine(100, 30, 100, 160, BLACK);
	drawLine(100, 160, 350, 160, BLACK);
	drawDigit(90, 155, 0, BLACK);
}
void graph_drawLines(Widget* base){

	GraphWidget* derive = (GraphWidget*)(base->derive);

	u16 xg[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	u16 yg[] = {1, 3, 5, 2, 1, 6, 10, 12, 1, 3, 8, 7, 10,2, 9, 15};
	u8 pts = 16;

	u8 max_xi= 0;
	u8 max_yi= 0;

	int i;
	for(i=0; i < pts; ++i){
		if(xg[i] > xg[max_xi]){
			max_xi = i;
		}
		if(yg[i] > yg[max_yi]){
			max_yi = i;
		}
	}

	u8 xs = derive->width/xg[max_xi];
	u8 ys = derive->height/yg[max_yi];


	for(i=0; i<pts-1; ++i){
		drawLine(xs*xg[i]+base->x, -ys*yg[i]+base->y, xs*xg[i+1]+base->x, -ys*yg[i+1]+base->y, RED);
	}

	drawNumber(355, 155, xg[max_xi], BLACK);
	drawNumber(80, 22, yg[max_yi], BLACK);
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
			//u16 x = weldU16(byte_codes[], byte_codes[]);
			//u16 y = weldU16(byte_codes[], byte_codes[]);

		}
		case 3:{

		}
		break;
	}

	return op;
}

#endif /* GRAPH_H_ */
