#ifndef ___WIDGET___
#define ___WIDGET___

#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"

#include "packet.h"

#define NFUNCS 16

struct widget;
void Widget_move(struct widget* this, u16 x_s, u16 y_s);

typedef struct widget{
	u16 x, y;
	const void* derive;

	Packet (*runFunction) (struct widget* this, u8 funcN, Packet* pack);

} Widget;

void Widget_move(struct widget* this, u16 x_s, u16 y_s){
	this->x = x_s;
	this->y = y_s;
}


#endif