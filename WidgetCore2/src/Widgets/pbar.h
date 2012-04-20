/*
 * pbar.h
 *
 *  Created on: Apr 18, 2012
 *      Author: ACM
 */

#ifndef PBAR_H_
#define PBAR_H_

#include<stdlib.h>
#include "../WidgetCore/widget.h"
#include "../GraphicsEngine/Graphics.h"

Packet PBAR_runFunction(Widget* this, u8 funcN, Packet* pack);

typedef struct pbar_widget{
	u32 percent;
	u16 width;
}PBarWidget;

struct widget new_PBarWidget(u32 progressBar_x, u32 progressBar_y){

	PBarWidget* w = (PBarWidget*) malloc(sizeof(PBarWidget));

	struct widget PBar = {
			.x = progressBar_x,
			.y = progressBar_y,
			.derive = (const void*)w,
			.runFunction = PBAR_runFunction
	};

	return PBar;
}

Packet PBAR_runFunction(Widget* base, u8 funcN, Packet* pack){

	PBarWidget* derive = (PBarWidget*)(base->derive);

	switch(funcN){

		case 1:{
			//stuff to draw a progress bar here
			drawCircle(base->x,base->y,15,BLACK,1);
			drawCircle(base->x+200,base->y,15,BLACK,1);
			drawRectangle(base->x,base->y-15,base->x+200,base->y+15,BLACK,1);
			drawCircle(base->x,base->y,13,GREEN,1);
			drawDigit(base->x-4,base->y+17,0,BLACK);
			drawNumber(base->x+188,base->y+17,100,BLACK);
		}
		case 2:{
			//stuff to draw a progress bar here
			u8 temperature = 0;
			u8 oldTemp = temperature;
			temperature = pack->bytes[0];

			if(oldTemp != temperature)
			{
				drawCircle(base->x+200,base->y,13,WHITE,1);
				drawRectangle(base->x,base->y-13,base->x+200,base->y+13,WHITE,1);
				drawRectangle(base->x,base->y-13,base->x+temperature,base->y+13,GREEN,1);
				if (temperature==200)
					drawCircle(base->x+200,base->y,13,GREEN,1);
			}
		}
	}

}


#endif /* PBAR_H_ */
