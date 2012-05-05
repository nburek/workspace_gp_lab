/*
 * light.h
 *
 *  Created on: Apr 18, 2012
 *      Author: ACM
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include<stdlib.h>
#include "../WidgetCore/widget.h"
#include "../GraphicsEngine/Graphics.h"

Packet LED_runFunction(Widget* wthis, u8 funcN, Packet* pack);

typedef struct led_widget {
	u16 radius;
	u8	color;
	u8  on;
} LEDWidget;

Widget new_LEDWidget(u32 x_i, u32 y_i, u16 radius_i, u8 color_i){

	LEDWidget* w = (LEDWidget*) malloc(sizeof(LEDWidget));
	w->radius = radius_i;
	w->color  = color_i;
	w->on	  = 0;

	Widget light ={
			.x = x_i,
			.y = y_i,
			.derive = (const void*)w,
			.destroy = default_destroy,
			.runFunction = LED_runFunction
	};

	drawCircle(light.x, light.y, w->radius, BLACK, 1);

	return light;
}

void ledW_update(Widget* base, LEDWidget* derive){
	u8 color = WHITE;
	if (derive->on > 0)
		color = derive->color;
	drawCircle(base->x, base->y, derive->radius - (derive->radius/5), color, 1);
}

Packet LED_runFunction(Widget* base, u8 funcN, Packet* pack){

	LEDWidget* derive = (LEDWidget*)(base->derive);

	Packet op;
	op.bytes[0] = 0;

	switch(funcN){

		case 1:{
			drawCircle(base->x, base->y, derive->radius, BLACK, 1);
			ledW_update(base, derive);
			break;
		}
		case 2:{
			derive->on = pack->bytes[0];
			ledW_update(base, derive);
			break;
		}

	}

	return op;
}

#endif /* LIGHT_H_ */
