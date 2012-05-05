#ifndef ___WIDGET___
#define ___WIDGET___

#include "xbasic_types.h"
#include "xuartlite_l.h"
#include "xparameters.h"

#include "packet.h"

#define NFUNCS 16

typedef struct widget{
	u16 x, y;
	const void* derive;

	void (*destroy)(void);
	Packet (*runFunction) (struct widget* this, u8 funcN, Packet* pack);

} Widget;

void default_destroy(void){
;
}


#endif
