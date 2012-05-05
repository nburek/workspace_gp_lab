/*
 * text_box.h
 *
 *  Created on: Apr 22, 2012
 *      Author: ACM
 */

#ifndef TEXT_BOX_H_
#define TEXT_BOX_H_

#include<stdlib.h>
#include "../WidgetCore/widget.h"
#include "../GraphicsEngine/Graphics.h"
#include "stringWid.h"

Packet TB_runFunction(Widget* wthis, u8 funcN, Packet* pack);

typedef struct tb_widget {
	STRWidget lines[5];
	u8 line_pos;
	u8 pos;
} TBWidget;

struct widget new_TBWidget(u32 x_i, u32 y_i, char chars[], u8 length, u8 color_i){

	TBWidget* w = (TBWidget*) malloc(sizeof(TBWidget));
	w->size  = length;
	w->color = color_i;

	int i;
	for(i = 0; i < w->size; ++i){
		w->chars[i] = chars[i];
	}

	Widget textBoxW ={
			.x = x_i,
			.y = y_i,
			.derive = (const void*)w,
			.destroy = default_destroy,
			.runFunction = STR_runFunction
	};

	return stringW;
}


Packet TB_runFunction(Widget* base, u8 funcN, Packet* pack){

	TBWidget* derive = (TBWidget*)(base->derive);

	switch(funcN){

		case 1:{

		}
		break;
	}
}


#endif /* TEXT_BOX_H_ */
