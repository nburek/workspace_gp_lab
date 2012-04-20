/*
 * stringWid.h
 *
 *  Created on: Apr 18, 2012
 *      Author: ACM
 */

#ifndef STRINGWID_H_
#define STRINGWID_H_

#include<stdlib.h>
#include "../WidgetCore/widget.h"
#include "../GraphicsEngine/Graphics.h"

Packet STR_runFunction(Widget* wthis, u8 funcN, Packet* pack);

typedef struct str_widget {
	char chars[32];
	u8 size;
	u8 color;
} STRWidget;

struct widget new_STRWidget(u32 x_i, u32 y_i, char chars[], u8 length, u8 color_i){

	STRWidget* w = (STRWidget*) malloc(sizeof(STRWidget));
	w->size  = length;
	w->color = color_i;

	int i;
	for(i = 0; i < w->size; ++i){
		w->chars[i] = chars[i];
	}

	Widget stringW ={
			.x = x_i,
			.y = y_i,
			.derive = (const void*)w,
			.runFunction = STR_runFunction
	};

	return stringW;
}


Packet STR_runFunction(Widget* base, u8 funcN, Packet* pack){

	STRWidget* derive = (STRWidget*)(base->derive);

	switch(funcN){

		case 1:{
			int i;
			for(i = 0; i < derive->size; ++i){
				if(derive->chars[i] >= 48 && derive->chars[i] <= 57){
					drawDigit(base->x+(i*8), base->y, derive->chars[i] - 48, derive->color);
				}else{
					drawLetter(base->x+i*8, base->y, derive->chars[i], derive->color);
				}
			}
		}
	}
}


#endif /* STRINGWID_H_ */