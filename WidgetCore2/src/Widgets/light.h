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
} LEDWidget;

struct widget new_LEDWidget(u32 x_i, u32 y_i, u16 radius_i, u8 color_i){

	LEDWidget* w = (LEDWidget*) malloc(sizeof(LEDWidget));
	w->radius = radius_i;
	w->color  = color_i;

	Widget light ={
			.x = x_i,
			.y = y_i,
			.derive = (const void*)w,
			.runFunction = LED_runFunction
	};

	return light;
}


Packet LED_runFunction(Widget* base, u8 funcN, Packet* pack){

	LEDWidget* derive = (LEDWidget*)(base->derive);

	switch(funcN){

		case 1:{
			drawCircle(base->x, base->y, derive->radius, BLACK, 1);
		}
		case 2:{
			if (pack->bytes[0] > 0)
				drawCircle(base->x, base->y, derive->radius - (derive->radius/5), derive->color, 1);
			else
				drawCircle(base->x, base->y, derive->radius - (derive->radius/5), WHITE, 1);
		}
	}

}

#endif /* LIGHT_H_ */
