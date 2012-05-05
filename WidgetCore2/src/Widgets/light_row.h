/*
 * light_row.h
 *
 *  Created on: Apr 22, 2012
 *      Author: ACM
 */

#ifndef LIGHT_ROW_H_
#define LIGHT_ROW_H_

#include<stdlib.h>
#include "../WidgetCore/widget.h"
#include "../GraphicsEngine/Graphics.h"
#include "light.h"

Packet LRow_runFunction(Widget* this, u8 funcN, Packet* pack);

typedef struct lrow_widget{
	Widget row[8];		//base portion
	LEDWidget drow[8];	//derived portion
}LRowWidget;

Widget new_LRowWidget(u32 xi, u32 yi){

	LRowWidget* w = (LRowWidget*) malloc(sizeof(LRowWidget));

	struct widget lrow = {
			.x = xi,
			.y = yi,
			.derive = (const void*)w,
			.destroy = default_destroy,
			.runFunction = LRow_runFunction
	};

	int i;
	for(i = 0; i < 8; ++i){
		w->row[i].x = 190 + i*20;

		w->drow[i].radius = 10;
		w->drow[i].color = RED;

		w->row[i].x = 190 + i*20;
		w->row[i].y = 35;
		w->row[i].derive = &(w->drow[i]);
		w->row[i].runFunction = LED_runFunction;
	}

	return lrow;
}

Packet LRow_runFunction(Widget* base, u8 funcN, Packet* pack){

	LRowWidget* derive = (LRowWidget*)(base->derive);

	Packet op;
	op.bytes[0] = 0;

	switch(funcN){

		case 2:{
			int i;
			Packet p;
			for(i = 0; i < 8; ++i){
				p.bytes[0] = pack->bytes[i];
				derive->row[i].runFunction(&(derive->row[i]), 2, &p);
			}
		}
		break;
	}

	return op;

}

#endif /* LIGHT_ROW_H_ */
